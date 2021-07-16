#include <iostream>
#include "Path.hxx"
#include "RcAsyncInstall.hxx"

using RcValuesVec_Ptr = std::vector<RcValues*>;

int main(int argc, const char **argv) {

    bool stage_one = false;
    std::string path_to_rcbuild;
    if (argc == 1) {
        RcError::rc_report_error(RcError::MESSAGE, "Scanning for RCBUILD file in current directory\n");
        Path::set_path(path_to_rcbuild);
        path_to_rcbuild.append(Path::rcbuild_filename);
        stage_one = true;
    }

    if (stage_one) {
        RcError::rc_report_error(RcError::MESSAGE, "Attempting to read from the file '%s' ... ",
            path_to_rcbuild.c_str());
        auto rc_gen =  RCGenSources(path_to_rcbuild);
        RcError::rc_report_error(rc_gen.status() ? RcError::MESSAGE : RcError::FATAL,
            "%s\n", rc_gen.status() ? "success!" : "failure");
        auto rc_gen_table = rc_gen.construct_table();
        // Apparently we will have to declare this variable as such (and without using the auto keyword)
        // as it will cause failure in code compilation
        RcAsync::RcInstaller rc_install = RcAsync::RcInstaller(rc_gen_table);
        const auto rc_installer_exit_code = rc_install.rc_async_installer();
    }

    return 0;
}
