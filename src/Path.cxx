#include "Path.hxx"

void Path::set_path(std::string &rcbuild) {
    char path[path_max];
    if (getcwd(path, sizeof(path)) == nullptr) {
        std::fprintf(stderr, "error <internal> :: getcwd() error\n");
        exit (EXIT_FAILURE);
    }
    rcbuild = std::string(path);
}