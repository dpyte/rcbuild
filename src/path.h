#ifndef PATH_H
#define PATH_H

#if defined(__WINDOWS__) || defined(_WIN64)
#include <windows.h>
#elif defined(__gnu_linux__) || defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#endif 

#include <string.h>
#include <limits.h> 
#include <stddef.h>
#include "details.h"


#define RCBUILD_FILENAME "/RCBUILD"

static const size_t path_max = PATH_MAX;

typedef struct __directory_path directory_path;

struct __directory_path {
	char *curr_path;
	char *proposed_path;
};

RCEXTERN directory_path *get_path(void); 

#endif // PATH_H



