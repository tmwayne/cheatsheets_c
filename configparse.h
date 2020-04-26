/* configparse.h */

struct configs {
  char ext[128];
  char cs_dir[128];
  char template_path[128];
};

int config_parse(const char*, struct configs*);
