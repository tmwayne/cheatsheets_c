/* 
 * cheatsheets.c
 *
 * Print useful commands and options for given topic
 *
 * Tyler Wayne © 2020
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "argparse.h"

int file_exists(const char* path) {
  struct stat buffer;
  int exist = stat(path, &buffer);
  if (exist == 0)
    return 1;
  else // -1
    return 0;
}

char* join_path(const char* path, const char* basename, const char* ext) {
  
  size_t buf_size = 128;
  char* buf = malloc(buf_size * sizeof(char));
  const char* sep = "/";
  const char * path_parts[4] = { path, sep, basename, ext };

  const size_t len = strlen(path) + strlen(sep) + strlen("/") + 1;
  size_t len_used = 0;

  while (buf_size < len) {
    buf_size *= 2;
    if ((buf = realloc(buf, buf_size)) == NULL) {
      perror("Unable to reallocate memory for the buffer.");
      free(buf);
      exit(1);
    }
  }

  for (int i=0; i < 4; i++) {
    strncpy(buf + len_used, path_parts[i], buf_size - len_used);
    len_used += strlen(path_parts[i]);
  }

  return buf;

}

typedef struct cs_file {
  char* text;
  size_t nlines;
} cs_file;

cs_file* read_cs(const char* cs_path) {
  
  size_t buf_size = 128;
  char line[buf_size];

  cs_file* out = malloc(sizeof(cs_file));
  out->text = malloc(sizeof(line));
  out->nlines = 0;
  

  FILE* fp = fopen(cs_path, "r");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  out->text[0] = '\0';

  while(fgets(line, sizeof(line), fp) != NULL) {
    
    // Resize the buffer if necessary
    size_t len_used = strlen(out->text);
    size_t line_used = strlen(line);

    if (buf_size - len_used < line_used) {
      buf_size *= 2;
      if ((out->text = realloc(out->text, buf_size)) == NULL) {
        perror("Unable to reallocate memory for the line buffer.");
        free(out->text);
        free(out);
        exit(1);
      }
    }

    strncpy(out->text + len_used, line, buf_size - len_used);
    out->nlines++;
  }

  fclose(fp);

  return out;

}

void print_cs(cs_file* cs_text) {

  // Get number of lines in terminal
  FILE* pipe = popen("tput lines", "r");
  if (pipe == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }

  char input[10];
  int lines;
  while (fgets(input, sizeof(input), pipe) != NULL)
    lines = atoi(input);

  pclose(pipe);

  // Pipe to less if number of rows in text
  // is greater than number of lines in terminal
  if (cs_text->nlines >= lines) {
    FILE* pipe = popen("less", "w");
    if (pipe == NULL) {
      perror("popen");
      exit(EXIT_FAILURE);
    }

    fprintf(pipe, "%s", cs_text->text);
    pclose(pipe);
  } else {
    fprintf(stdout, "%s", cs_text->text);
  }

}

void edit_cs(const char* cs_path) {
  
  char prog[] = "vim ";
  int len_prog = strlen(prog);
  char system_call[len_prog + strlen(cs_path) + 1];

  system_call[0] = '\0';

  strncpy(system_call, prog, len_prog + 1 );
  strncpy(system_call + len_prog, cs_path, strlen(cs_path) + 1);

  // fprintf(stdout, "%s\n", system_call);

  if (file_exists(cs_path))
    system(system_call);
  
}

int main(int argc, char** argv) {

  /* ARGUMENTS */
  // const char* cs_dir = getenv("CHEATSHEETS_DIR");
  const char* ext = ".txt";

  // if (cs_dir == NULL) {
    // fprintf(stderr, "Please set CHEATSHEETS_DIR\n");
    // exit(EXIT_FAILURE);
  // }

  // Defaults
  struct arguments arguments;
  arguments.edit = 0;
  arguments.cs_dir = getenv("CHEATSHEETS_DIR");

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

