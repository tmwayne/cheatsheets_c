/* 
 * main.c
 *
 * Print useful commands and options for given topic
 *
 * Tyler Wayne © 2020
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "configparse.h"
#include "argparse.h"
#include "cheatsheets.h"

int main(int argc, char** argv) {

  /* ARGUMENTS */
  char* ext = ".txt";
  // Configurations
  struct configs configs;
  config_parse("config.txt", &configs);

  // Defaults
  struct arguments arguments;
  arguments.edit = 0;
  // arguments.cs_dir = getenv("CHEATSHEETS_DIR");
  // Don't know how long arguments.cs_dir is
  arguments.cs_dir = configs.cs_dir;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  /* PROGRAM LOGIC */
  const char* cs_name = arguments.args[0];
  char* cs_path = join_path(arguments.cs_dir, cs_name, ext);

  if (arguments.edit)
    edit_cs(cs_path);
  else {
    cs_file* cs_text = read_cs(cs_path);
    print_cs(cs_text);
    free(cs_text->text);
    free(cs_text);
  }

  free(cs_path);

}

