
#ifndef RCBUILD_RCGENSOURCES_HXX
#define RCBUILD_RCGENSOURCES_HXX

#include "Details.hxx"
#include "RcValues.hxx"
#include <array>
#include <string>
#include <toml.hpp>
#include <vector>

using RcValueTable_Ptr = std::shared_ptr<RcValues>;

enum TABLE_VALUES {
    FETCH_SRC,
    FETCH_TYPE,
    GIT_DEPTH,
    LOCATION,
    PROJECT_NAME,
};

class RCGenSources {
private:
    std::string rc_path_to_config;
    toml::value parse_file;
    std::vector<RcValueTable_Ptr> value_table;

public:
    RCGenSources() = delete;
    explicit RCGenSources(const std::string &fname) noexcept;

    [[nodiscard]] bool status() const noexcept;

    [[nodiscard]] std::vector<RcValueTable_Ptr> construct_table();

};


#endif //RCBUILD_RCGENSOURCES_HXX
