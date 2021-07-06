#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "mem.h"
#include "path.h"


directory_path *get_path(void) {

	directory_path *retval;

	size_t szoftv = sizeof(directory_path *);
	retval = (directory_path*)rcmalloc(szoftv);
	retval->curr_path = (char*) rcmalloc(path_max);

    __attribute__((unused)) char temp[path_max];
	size_t szofcp = sizeof(temp);
	if (getcwd(retval->curr_path, szofcp) == NULL) {
		perror("getcwd() error");
		exit(-1);
	}


	return retval;
}
