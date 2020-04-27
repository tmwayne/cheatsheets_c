/* configparse.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configparse.h"

int config_parse(const char* config_file, struct configs* configs) {

  FILE* fp = fopen(config_file, "r");

  if (fp == NULL) {
    // perror("fopen");
    // exit(EXIT_FAILURE);
    return 1;
  }

  int buf_size = 128;
  char line[buf_size];
  line[0] = '\0';

  const char delim[2] = ": ";
  const char delim2[1] = "\n";
  
  while (fgets(line, buf_size, fp) != NULL) {
    char* saveptr;
    char *key = strtok_r(line, delim, &saveptr);
    char *val = strtok_r(NULL, delim, &saveptr);
    val = strtok(val, delim2);

    if (strcmp(key, "cs-dir") == 0)
      strncpy(configs->cs_dir, val, 127);

    else if (strcmp(key, "cs-template-path") == 0)
      strncpy(configs->template_path, val, 127);

    else if (strcmp(key, "ext") == 0)
      strncpy(configs->ext, val, 127);
      
  }

  return 0;

}
