#include "Path.hxx"
#include "RcError.hxx"
#include <exception>

void Path::set_path(std::string &rcbuild) {
    char path[path_max];
    if (getcwd(path, sizeof(path)) == nullptr) {
        RcError::rc_report_error(RcError::FATAL,
            "error <internal> :: getcwd() error \n");
        std::terminate();
    }
    rcbuild = std::string(path);
}