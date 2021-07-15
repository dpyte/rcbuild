#include "RcAsyncInstall.hxx"

RcAsync::RcInstaller::RcInstaller(std::vector<RcValueTable_Ptr> &rc_install) noexcept
    : rc_generated_values(rc_install) {}

bool RcAsync::RcInstaller::rc_async_installer() {

    for (const auto &rc_iter: rc_generated_values) {

    }
    return false;
}
