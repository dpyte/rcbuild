#include "mem.h"
#include "path.h"
#include "process.h"

#include <errno.h>
#include <error.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <toml.h>


static bool check_file(const char *filename) {

	struct stat buffer;
	return stat(filename, &buffer) == 0;
}

static toml_table_t *read_buffer(const char *path) {

	if (check_file(path))
		fprintf(stderr, "reading from :: '%s'\n", path);	
	else 
		fprintf(stderr, "err :: file does not exist at '%s'\n", path);

	char errbuf[1024u << 2u];
	FILE *fp = fopen(path, "r");
	if (!fp) error("failed to open RCBUILD - ", strerror(errno));

	toml_table_t *retval = toml_parse_file(fp, errbuf, sizeof(errbuf));
	
	fclose(fp);
	if (!retval)
		error(" :: failed to parse - ", errbuf);

	return retval;
}

int main(int argc, const char **argv) {
	
	char path_to_rcbuild[path_max];
	bool pass = false;
	if (argc == 1) {
		fprintf(stderr, "scanning for RCBUILD file in current directory\n");
		directory_path *dp = get_path();
		memcpy(path_to_rcbuild, dp->curr_path, strlen(dp->curr_path));
		strcat(path_to_rcbuild, RCBUILD_FILENAME);
		pass = true;
	}

	if (pass) {
		toml_table_t *config_file = read_buffer(path_to_rcbuild);
		process_config_file(config_file);
	}

	return 0;
}
