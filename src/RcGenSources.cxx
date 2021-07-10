#include "RcGenSources.hxx"
#include <iostream>
#include <type_traits>

using RcValueTable_Ptr = std::shared_ptr<RcValues>;


template <typename Value, typename AssertType = bool>
static AssertType assert_extracted_value(Value val, const AssertType type) {
    return val == type;
}

RCGenSources::RCGenSources(const std::string &fname) noexcept {
    rc_path_to_config = fname;
    parse_file = toml::parse(fname);
}

// !NOTE: Kinda redundant
bool RCGenSources::status() const noexcept {

    std::ifstream ifs(rc_path_to_config, std::ios_base::binary);
    return ifs.good();
}

std::vector<RcValueTable_Ptr> RCGenSources::construct_table() {

    const auto title = toml::find<std::string>(parse_file, "title");
    const auto check_type = assert_extracted_value<bool>(title.empty(), true);
    if (!check_type) {
      std::fprintf(stderr,
                   "err :: missing required label from the configuration file."
                   // This statement makes no sense but oh well ...
                   "\n'title' is required in order to parse the file\n");
      exit(EXIT_FAILURE);
    }

    const auto projects = toml::find(parse_file, "projects");
    for (auto iter = 0; iter != RCBUILD_MAX; iter++) {
        const auto project_number = "project_" + std::to_string(iter);
        const auto &project = toml::find(projects, project_number);
        const auto rc_project_name = toml::find<std::string>(project, "project_name");
        std::cerr << " project name >> " << rc_project_name << '\n';
    }

    return value_table;
}


