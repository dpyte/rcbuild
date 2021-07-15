#include "PathSC.hxx"
#include "RcError.hxx"
#include "RcFetchSrc.hxx"
#include "RcGenSources.hxx"
#include <chrono>
#include <iostream>
#include <thread>

#define EMPTY_SPACE std::cout << '\n';

using RcValueTable_Ptr = std::shared_ptr<RcValues>;

static constexpr const auto project_name_list = {
    "project_1", "project_2", "project_3", "project_4",
    "project_5", "project_6", "project_7", "project_8",
    "project_9", "project_10", "project_11", "project_12",
    "project_13", "project_14", "project_15", "project_16",
    "project_17", "project_18", "project_19", "project_20",
    "project_21", "project_22", "project_23", "project_24",
    "project_25", "project_26", "project_27", "project_28",
    "project_29", "project_30", "project_31", "project_32",
};

static inline void rc_sleep_for(float secs) {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(secs)));
}

template <typename Value, typename AssertType = bool>
static AssertType assert_extracted_value(Value val, const AssertType type) {
    return val == type;
}

RCGenSources::RCGenSources(const std::string &fname) noexcept {
    rc_path_to_config = fname;
    parse_file = toml::parse<toml::discard_comments>(fname);
}

// !NOTE: Kinda redundant
bool RCGenSources::status() const noexcept {
    std::ifstream ifs(rc_path_to_config, std::ios_base::binary);
    return ifs.good();
}

/*
 * !TODO: make sense out this statement (fixme)
 * use the vector-values to generate table since the project_n can be in any order
 */
static std::pair<int, std::vector<const char *>> check_for_project_names(const toml::value &tml) {
    std::pair<int, std::vector<const char*>> retval;
    for (auto iter : project_name_list) {
        // Do not return a value if the project name is not in ascending order.
        // Consider the case:
        //      - project_1, project_3, ...
        if (tml.contains(iter)) {
            retval.first++;
            retval.second.push_back(iter);
        }
    }
    return retval;
}

static std::vector<std::pair<TABLE_VALUES, bool>>
rc_table_detect_values(const toml::value &tml) {
    std::vector<std::pair<TABLE_VALUES, bool>> retval;
    retval.emplace_back(std::make_pair(PROJECT_NAME, tml.contains("project_name")));
    retval.emplace_back(std::make_pair(FETCH_SRC, tml.contains("fetch_src")));
    retval.emplace_back(std::make_pair(FETCH_TYPE, tml.contains("fetch_type")));
    retval.emplace_back(std::make_pair(GIT_DEPTH, tml.contains("git_depth")));
    retval.emplace_back(std::make_pair(LOCATION, tml.contains("location")));
    return retval;
}

static void print_packages(const std::vector<std::pair<TABLE_VALUES, bool>> &tb,
    std::string const &current_project_name) {
    RcError::rc_report_error(RcError::MESSAGE,
        "detected configuration for %s\n",
        current_project_name.c_str());
    for (const auto &iter: tb) {
        rc_sleep_for(128);
        switch (iter.first) {
            case PROJECT_NAME: RcError::rc_report_error(RcError::STATUS, "found project_name"); break;
            case FETCH_SRC: RcError::rc_report_error(RcError::STATUS, "found fetch_src"); break;
            case FETCH_TYPE: RcError::rc_report_error(RcError::STATUS, "found fetch_type"); break;
            case GIT_DEPTH: RcError::rc_report_error(RcError::STATUS, "found git_depth"); break;
            case LOCATION: RcError::rc_report_error(RcError::STATUS, "found location"); break;
        }
    }
}

static void rc_option_details(const std::string &pname,
    std::string const &option,
    std::string const &val) {
    rc_sleep_for(50);
    RcError::rc_report_error(RcError::MESSAGE,
                             "<%s> %s: %s \r", pname.c_str(), option.c_str(), val.c_str());
}

static void populate_values(std::string const &str,
    toml::value const &tml,
    std::vector<std::pair<TABLE_VALUES, bool>> const &detected_values) {
    RcValueTable_Ptr val = std::make_shared<RcValues>();
    for (const auto& dv : detected_values) {
        const auto dv_first = dv.first;
        const auto dv_second = dv.second;

        if (dv_second) {
            std::string current_option;
            std::string option_value;
            switch (dv_first) {
                case FETCH_SRC: {
                    const auto fetch_value = toml::find<std::string>(tml, "fetch_src");
                    val->push_fetch_src(fetch_value);
                    rc_option_details(str, "fetch_src", fetch_value);
                } break;
                case FETCH_TYPE: {
                    const auto fetch_type = toml::find<std::string>(tml, "fetch_type");
                    val->push_fetch_type(fetch_type);
                    rc_option_details(str, "fetch_type", fetch_type);
                } break;
                case GIT_DEPTH: {
                    const auto depth = toml::find<int>(tml, "git_depth");
                    val->push_git_depth(depth);
                    rc_option_details(str, "git_depth", std::to_string(depth));
                } break;
                case LOCATION: {
                    const auto location = toml::find<std::string>(tml, "location");
                    rc_option_details(str, "location", location);
                    const auto infered_location = RcPath::rc_infer_path(location);
                    val->push_location(infered_location);
                    EMPTY_SPACE
                } break;
                case PROJECT_NAME: {
                    const auto project_name = toml::find<std::string>(tml, "project_name");
                    val->push_project_name(project_name);
                    rc_option_details(str, "project_name", project_name);
                } break;
            }
        }
    }
}

std::vector<RcValueTable_Ptr> RCGenSources::construct_table() {
    const auto title = toml::find<std::string>(parse_file, "title");
    const auto check_type = assert_extracted_value<bool>(title.empty(), false);
    if (!check_type) {
        RcError::rc_report_error(RcError::FATAL,
            "err :: detected empty string in title label\n"
                "%s ensure to set the title string to the name of the project\n",
            RcError::rc_error_space);
    }

    const auto projects = toml::find(parse_file, "projects");
    const auto number_of_projects = check_for_project_names(projects);
    RcError::rc_report_error(RcError::MESSAGE,
        "amount of detected projects: %ld", number_of_projects.first);

    // for (auto iter : project_name_list) {
    for (auto iter = 0; iter < number_of_projects.first; iter++) {
        const auto project_name = number_of_projects.second.at(iter);
        const auto &project_number = toml::find(projects, project_name);
        const auto detected_values = rc_table_detect_values(project_number);
        print_packages(detected_values, number_of_projects.second.at(iter));
        populate_values(project_name, project_number, detected_values);
    }
    return value_table;
}

