#include "RcGenSources.hxx"
#include <iostream>
#include <thread>
#include <chrono>
#include "RcError.hxx"

using RcValueTable_Ptr = std::shared_ptr<RcValues>;

enum TABLE_VALUES {
    FETCH_SRC,
    FETCH_TYPE,
    GIT_DEPTH,
    LOCATION,
    PROJECT_NAME,
};

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

static auto check_for_project_names(const toml::value &tml) {
    auto retval = 0;
    for (auto iter : project_name_list) {
        // Do not return a value if the project name is not in ascending order.
        // Consider the case:
        //      - project_1, project_3, ...
        if (tml.contains(iter)) retval++;
    }
    return retval;
}

static std::vector<std::pair<TABLE_VALUES, bool>>
rc_table_detect_values(const toml::value &tml) {
    std::vector<std::pair<TABLE_VALUES, bool>> retval;

    retval.emplace_back(std::make_pair(PROJECT_NAME, tml.contains("project_name")));
    retval.emplace_back(std::make_pair(FETCH_SRC, tml.contains("fetch_src")));
    retval.emplace_back(std::make_pair(FETCH_TYPE, tml.contains("fetch_type")));
    retval.emplace_back(std::make_pair(LOCATION, tml.contains("location")));
    retval.emplace_back(std::make_pair(GIT_DEPTH, tml.contains("git_depth")));

    return retval;
}

static void print_packages(const std::vector<std::pair<TABLE_VALUES, bool>> &tb) {
    for (const auto &iter: tb) {
        std::this_thread::sleep_for(std::chrono::milliseconds(128));
        switch (iter.first) {
            case LOCATION: RcError::rc_report_error(RcError::STATUS,
                    "found location");
                break;
            case FETCH_SRC: RcError::rc_report_error(RcError::STATUS,
                    "found fetch_src");
                break;
            case FETCH_TYPE: RcError::rc_report_error(RcError::STATUS,
                    "found fetch_type");
                break;
            case GIT_DEPTH: RcError::rc_report_error(RcError::STATUS,
                    "found git_depth");
                break;
            case PROJECT_NAME: RcError::rc_report_error(RcError::STATUS,
                    "found project_name");
                break;
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
        "amount of detected projects: %ld", number_of_projects);

    // for (auto iter : project_name_list) {
    for (auto iter = 0; iter < number_of_projects; iter++) {
        const auto detected_values = rc_table_detect_values(projects);
        print_packages(detected_values);
    }
    return value_table;
}
