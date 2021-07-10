#include <iostream>
#include "Path.hxx"
#include <toml.hpp>
#include "RcGenSources.hxx"

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
        auto rc_gen =  RCGenSources(path_to_rcbuild);
        std::fprintf(stderr, "%s\n", rc_gen.status() ? "success" : "failure");
        const auto t = rc_gen.construct_table();
    }

    return 0;
}
