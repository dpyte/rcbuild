#include "RcAsyncInstall.hxx"
#include "RcError.hxx"
#include "RcFetchSrc.hxx"

RcAsync::RcInstaller::RcInstaller(std::vector<RcValueTable_Ptr> &rc_install) noexcept
    : rc_generated_values(rc_install) {}

//!NOTE: true -> is empty else is filled
static bool rc_confirm_git_values(std::string const &loc, std::string const &url) {
    const auto check_location = loc.empty();
    const auto check_url      = url.empty();
    return check_location && check_url;
}

bool RcAsync::RcInstaller::rc_async_installer() {

    for (const auto &rc_iter: rc_generated_values) {
        const auto rc_project_name = rc_iter->rcv_project_name();
        const auto rc_title = rc_iter->rcv_title();
        const auto rc_fetch_src = rc_iter->rcv_fetch_src();
        const auto rc_gdpeth = rc_iter->rcv_git_depth();
        const auto rc_location = rc_iter->rcv_location();
        const auto rc_fetch_type = rc_iter->rcv_fetch_type();

        //!TODO: spit out some more verbose output
        if (rc_fetch_type == "GIT") {
            const auto rc_check_fetch_type = rc_confirm_git_values(rc_location, rc_fetch_src);
            if (rc_check_fetch_type)
                RcError::rc_report_error(RcError::FATAL, "required values are missing to fetch source from git\n");
            rc_fetch_source_git(rc_location.c_str(), rc_fetch_src.c_str(), RcFetchSrc::RcFetchType::GIT);
        }
    }
    return false;
}
