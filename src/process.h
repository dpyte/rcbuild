#ifndef PROCESS_H
#define PROCESS_H

#include <toml.h>
#include "details.h"

RCEXTERN 
void process_config_file(toml_table_t *rc_config);

#endif // PROCESS_H
