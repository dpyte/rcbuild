/*
 *	path_sc: process shortcuts:
 *		- {RCBUILD_PATH}: Path to RCBUILD file
 *		- {RCBUILD_PATH_LEVEL_UP_N}: level up by one directory by N, N >= 1
 *		- {RCBUILD_PATH_LEVEL_DOWN_N}: level down by one directory by N, N >= 1
 */

#ifndef PATH_SC_H
#define PATH_SC_H

#include "Details.hxx"
#include <string>

namespace RcPath {
    std::string rc_infer_path(const std::string &path);
}
#endif //PATH_SC_H
