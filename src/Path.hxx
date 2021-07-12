#ifndef RCBUILD_PATH_HXX
#define RCBUILD_PATH_HXX

#if defined(__WINDOWS__) || defined(_WIN64)
#include <windows.h>
#elif defined(__gnu_linux__) || defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#endif

#include <climits>
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include "Details.hxx"

namespace Path {
    static constexpr auto rcbuild_filename = "/RCBUILD";
    static constexpr auto path_max = PATH_MAX;

    struct directory_path {
        std::string curr_path;
        std::string proposed_path;
    };

    RCEXTERN void set_path(std::string& rcbuild);
}
#endif //RCBUILD_PATH_HXX
