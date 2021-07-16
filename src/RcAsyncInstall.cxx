#include "RcAsyncInstall.hxx"

RcAsync::RcInstaller::RcInstaller(std::vector<RcValueTable_Ptr> &rc_install) noexcept
    : rc_generated_values(rc_install) {}

bool RcAsync::RcInstaller::rc_async_installer() {

    for (const auto &rc_iter: rc_generated_values) {
        const auto rc_project_value = rc_iter->rcv_project_name();
        std::cerr << "location: " << rc_project_value << '\n';
    }
    return false;
}
