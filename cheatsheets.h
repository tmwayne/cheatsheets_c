/* cheatsheets.h */

int path_exists(const char*);
char* join_path(const char*, const char*, const char*);

typedef struct cs_file {
  char* text;
  size_t nlines;
} cs_file;

cs_file* read_cs(const char*);
void print_cs(cs_file*);
void edit_cs(const char*);
