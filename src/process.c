#include "process.h"
#include "mem.h"
#include <assert.h>
#include <stdlib.h>

#define PROJECT_LIMIT 256

struct rcconfig_table {
	const char *project_name[PROJECT_LIMIT];
	uint16_t project_list;
};

struct rcb_config {
	toml_table_t *projects;
	struct rcconfig_table *rc_table;
};

static void extract_project_list(struct rcb_config *rcconfig) {

}

void process_config_file(toml_table_t *rc_config) {

	assert(rc_config != NULL);
	struct rcb_config *rcconfig = (struct rcb_config*)
		rcmalloc(sizeof(struct rcb_config*));
	rcconfig->projects = toml_table_in(rc_config, "projects");
	if (!rcconfig->projects) {
		fprintf(stderr, "err :: missing 'projects', type => Required\n");
		exit (-1);
	}
	extract_project_list(rcconfig);
}
