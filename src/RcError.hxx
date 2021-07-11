#ifndef RCBUILD_RCERROR_HXX
#define RCBUILD_RCERROR_HXX

#include "Details.hxx"
#include <cstdarg>

namespace RcError {

enum rc_error_type {
    FATAL,
    MESSAGE,
    REQUIRED,
    STATUS,
    WARNING,
};

static constexpr const auto rc_error_space = '\t';

RCEXTERN void rc_report_error(rc_error_type e_type, const char* fmt, ...);

} // namespace RcError
#endif // RCBUILD_RCERROR_HXX
