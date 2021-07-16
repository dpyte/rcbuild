#ifndef RCBUILD_PATH_HXX
#define RCBUILD_PATH_HXX

#include <filesystem>
#include <string>
#include "Details.hxx"

namespace Path {
    static constexpr auto rcbuild_filename = "/RCBUILD";
    RCEXTERN void set_path(std::string& rcbuild);
}
#endif //RCBUILD_PATH_HXX
