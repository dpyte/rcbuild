#include "Path.hxx"
#include "PathSC.hxx"
#include "RcError.hxx"
#include <sstream>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <algorithm>


namespace fs = std::filesystem;

enum RC_MACRO_TABLE {
    RCBUILD_PATH,
    RCBUILD_PATH_LEVEL_UP_N,
    RCBUILD_PATH_LEVEL_DOWN_N,
    NIL,
};

static const std::unordered_map<const char *, RC_MACRO_TABLE> RC_MACRO_MAP = {
    {"RCBUILD_PATH", RCBUILD_PATH},
    {"RCBUILD_PATH_LEVEL_UP_", RCBUILD_PATH_LEVEL_UP_N},
    {"RCBUILD_PATH_LEVEL_DOWN_", RCBUILD_PATH_LEVEL_DOWN_N},
};


// implementing an entire state-machine will be a huge waste of processing
// power ...
// - true: is RC_PATH else not
static RC_MACRO_TABLE rc_path_validation(const std::string_view path, std::string &path_type) {
    RC_MACRO_TABLE return_macro = RC_MACRO_TABLE::NIL;
    if (path.size() <= 1) return RC_MACRO_TABLE::NIL;
    const auto f_char = path.at(0) == '{';
    const auto s_char = path.at(path.size() - 1) == '}';

    if (f_char && s_char) {
        const auto rc_macro = path.substr(1, path.size() - 2);
        const auto rc_macro_len = rc_macro.length();
        // is rcbuild_path_level... equivalent
        if (rc_macro_len >= 12) {
            if (rc_macro_len >= 23) {
                if (rc_macro.substr(0, 22) == "RCBUILD_PATH_LEVEL_UP_") {
                    const auto rc_up_level = rc_macro.substr(22, rc_macro.length());
                    path_type = "RCBUILD_PATH_LEVEL_UP_" + std::string(rc_up_level);
                    return_macro = RC_MACRO_TABLE::RCBUILD_PATH_LEVEL_UP_N;
                }
                if (rc_macro.substr(0, 24) == "RCBUILD_PATH_LEVEL_DOWN_") {
                    const auto rc_down_level = rc_macro.substr(24, rc_macro.length());
                    path_type = "RCBUILD_PATH_LEVEL_DOWN_" + std::string(rc_down_level);
                    return_macro = RC_MACRO_TABLE::RCBUILD_PATH_LEVEL_DOWN_N;
                }
            }
            if (rc_macro == "RCBUILD_PATH") {
                path_type = "RCBUILD_PATH";
                return_macro = RC_MACRO_TABLE::RCBUILD_PATH;
            }
        }
    }
    return return_macro;
}

static bool rc_is_valid_dot_path(const std::string &pt) {
    const auto len = pt.length();
    const auto dot_count = std::count(pt.begin(), pt.end(), '.');
    if (dot_count <= 2) return true;
    else RcError::rc_report_error(RcError::FATAL, "invalid use of relative path '%s'\n", pt.c_str());
    return false;
}

static std::string rc_infer_path_from_macro(RC_MACRO_TABLE macro, const std::string &prev_path,
                                            const std::string &macro_path) {
    switch (macro) {
        case RCBUILD_PATH: {
            if (prev_path.empty()) {
                const auto path = fs::current_path();
                return path.string();
            } else {
                // !FIXME: improve this message
                RcError::rc_report_error(RcError::FATAL,
                                         "invalid use of macro <RCBUILD_PATH>\n\tRCBUILD_PATH must be placed before any other path");
            }
        } break;
        case RCBUILD_PATH_LEVEL_UP_N:
            break;
        case RCBUILD_PATH_LEVEL_DOWN_N:
            break;
    }
}

static void rc_fix_path(std::string &rc_path, const std::string &new_path) {
    const fs::path rc_prev_path = rc_path;
    const fs::path rc_new_path = new_path;
}

#include <iostream>
static std::string rc_infer_sys_path(const char *path_type, const std::string &prev_path) {
    std::string sys_path;
    const fs::path fs_path = prev_path + "/" + std::string(path_type);
    const auto gen_path = fs::canonical(fs_path);
    std::cerr << "generated path >> " << gen_path << '\n';
    return sys_path;
}

std::string RcPath::rc_infer_path(const std::string &path) {
    std::vector<std::string> buffer;
    std::stringstream rc_ss_path;
    rc_ss_path << path;

    while (rc_ss_path.good()) {
        std::string sstr;
        getline(rc_ss_path, sstr, '/');
        buffer.emplace_back(sstr);
    }

    std::string rc_path;
    rc_path.reserve(512);
    for (auto &pt: buffer) {
        std::string rc_macro_path_type;
        const auto macro_type = rc_path_validation(pt, rc_macro_path_type);
        if (macro_type != RC_MACRO_TABLE::NIL) {
            const auto rc_infered_macro_path = rc_infer_path_from_macro(macro_type, rc_path, rc_macro_path_type);
            rc_path += rc_infered_macro_path;
        } else {
            const auto is_valid_dot_path = rc_is_valid_dot_path(pt);
            if (is_valid_dot_path) rc_fix_path(rc_path, rc_infer_sys_path(pt.c_str(), rc_path));
            else rc_path += pt;
        }
    }
    std::cerr << "constructed path: " << rc_path << '\n';
    return rc_path;
}
