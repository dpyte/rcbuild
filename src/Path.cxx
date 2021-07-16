#include "Path.hxx"
#include "RcError.hxx"
#include <exception>

void Path::set_path(std::string &rcbuild) {
    rcbuild = std::filesystem::current_path().string();
}
