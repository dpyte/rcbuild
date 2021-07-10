
#ifndef RCBUILD_RCGENSOURCES_HXX
#define RCBUILD_RCGENSOURCES_HXX

#include <vector>
#include <array>
#include <string>
#include <toml.hpp>
#include "RcValues.hxx"
#include "Details.hxx"

class RCGenSources {
private:
    using RcValueTable_Ptr = std::shared_ptr<RcValues>;

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
