#include "RcError.hxx"
#include <cstring>
#include <cstdio>
#include <stdexcept>
#include <iostream>

enum COLOR {
    ERC_BLUE = 34,
    ERC_DEFAULT = 39,
    ERC_GREEN = 32,
    ERC_RED = 31,
    EBG_RED = 41,
    EBG_BLUE = 44,
    EBG_DEFAULT = 49
};

class RCErrPrint {
private:
    static constexpr const auto color_code = "\033[";
    COLOR code;
public:
    explicit RCErrPrint(COLOR cl);
    friend std::ostream &operator << (std::ostream & os, const RCErrPrint &rcerr);
};

RCErrPrint::RCErrPrint(COLOR cl) : code(cl) {}

std::ostream &operator<<(std::ostream& os, const RCErrPrint& rcerr) {
    return os << RCErrPrint::color_code << rcerr.code << 'm';
}

static const char *err_style(const RcError::rc_error_type &et) {
    switch (et) {
        case RcError::FATAL: return " [ERROR] ";
        case RcError::REQUIRED: return " <REQUIRED> ";
        case RcError::WARNING: return " !WARNING! ";
        case RcError::STATUS: return " ~> ";
        case RcError::MESSAGE: return " >> ";
    }
    return "";
}

static void concatenate_message(const RcError::rc_error_type &et, const std::string &str) {
    switch (et) {
        case RcError::FATAL:
            std::cout << RCErrPrint(ERC_RED) << str << RCErrPrint(ERC_DEFAULT) << '\n';
            throw std::exception();
        case RcError::REQUIRED:
            std::cout << RCErrPrint(ERC_GREEN) << str << RCErrPrint(ERC_DEFAULT) << '\n';
            throw std::exception();
        case RcError::WARNING:
            std::cout << RCErrPrint(ERC_BLUE) << str << RCErrPrint(ERC_DEFAULT) << '\n';
            break;
        case RcError::STATUS:
            std::cout << RCErrPrint(ERC_GREEN) << str << RCErrPrint(ERC_DEFAULT) << '\n';
            break;
        case RcError::MESSAGE:
            std::cout << str << '\n';
            break;
    }
}

void RcError::rc_report_error(rc_error_type e_type, const char* fmt, ...) {

    va_list args;
    va_start(args, fmt);

    const auto sz = std::strlen(fmt) * sizeof(fmt) * 64;
    const auto str = new (std::nothrow) char[sz];
    if (!str) {
        std::fprintf(stderr, " system warning: <rc_report_error> -> allocation failure\n");
        throw std::exception();
    }
    std::vsnprintf(str, sz, fmt, args);
    va_end(args);

    std::string report_string(str);
    delete [] str;
    concatenate_message(e_type, err_style(e_type)+ report_string);
}