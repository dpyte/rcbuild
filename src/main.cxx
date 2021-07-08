#include <iostream>
#include <toml.hpp>
#include "Path.hxx"

int main(int argc, const char **argv) {

    bool stage_one = false;
    std::string path_to_rcbuild;
    if (argc == 1) {
        fprintf(stderr, "Scanning for RCBUILD file in current directory\n");
        Path::set_path(path_to_rcbuild);
        path_to_rcbuild.append(Path::rcbuild_filename);
        stage_one = true;
    }

    if (stage_one) {
        std::fprintf(stderr, "Attempting to read from the file '%s' ... ",
            path_to_rcbuild.c_str());
        auto data = toml::parse(path_to_rcbuild);
        std::fprintf(stderr, "success!\n");
    }

    return 0;
}
