/* 
 * cheatsheets.c
 *
 * Print a cheatsheet to the terminal to remind of useful commands
 *
 * Tyler Wayne © 2020
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

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

    fprintf(pipe, "%s\n", cs_text->text);
    pclose(pipe);
  } else {
    fprintf(stdout, "%s\n", cs_text->text);
  }

}

int main(int argc, char** argv) {

  const char* cs_dir = getenv("CHEATSHEETS_DIR");
  const char* ext = ".txt";

  if (cs_dir == NULL) {
    fprintf(stderr, "Please set CHEATSHEETS_DIR\n");
    exit(EXIT_FAILURE);
  }

  if (argc != 2) {
    fprintf(stderr, "Usage: %s cheatsheet\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const char* cs = argv[1];                   // Name of the cheatsheet
  char* cs_path = join_path(cs_dir, cs, ext); // Full path
  cs_file* cs_text = read_cs(cs_path);        // Full text
  print_cs(cs_text);                          // Page with less if too long

  free(cs_path);
  free(cs_text->text);
  free(cs_text);

}

