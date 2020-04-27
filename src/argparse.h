/* argparse.h */

#include <argp.h>

const char* argp_program_version = "cheatsheets 1.0\n"
  "Copyright © 2020 Tyler Wayne";

const char* argp_program_bug_address = "<tylerwayne3@gmail.com>";

// This structure is used by main to communicate with parse_opt.
struct arguments {
  char *args[1];      // cheatsheet
  char *config;       // config file
  char* cs_dir;       // directory for cheatsheets
  int edit;           // the -e flag
  // char* string;       // some argument
};

/*
 * OPTIONS : Field 1 in Argp
 * Order of fields: { name, key, arg, flags, doc }
 */
static struct argp_option options[] = {
  {"config", 'c', "file", 0, "Config file"},
  {"cs-dir", 'd', "dir", 0, "Cheatsheet directory."
    " Defaults to $CHEATSHEETS_DIR"},
  {"edit", 'e', 0, 0, "Edit the cheatsheet"},
  // {"alpha", 'a', "STRING", 0, "Placeholder for a"},
  {0}
};

/*
 * PARSER : Field 2 in Argp
 * Order of parameters: key, arg, state
 */
static error_t parse_opt(int key, char* arg, struct argp_state* state) {
  struct arguments* arguments = state->input;

  switch (key) {
    case 'c':
      arguments->config = arg;
      break;
    case 'd':
      arguments->cs_dir = arg;
      break;
    case 'e':
      arguments->edit = 1;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        argp_usage(state);
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
        argp_usage(state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

/*
 * ARGS_DOC : Field 3 in Argp
 * A description of the non-option command-line arguments that we accepted
 */
static char args_doc[] = "cheatsheet";

/*
 * DOC : Field 4 in Argp
 * Program documentation
 */
static char doc[] = "cheatsheet -- print useful commands and options "
  "for given topic";

/*
 * Argp structure
 */
static struct argp argp = { options, parse_opt, args_doc, doc };

