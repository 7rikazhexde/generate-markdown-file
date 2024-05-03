#ifndef UTILS_H
#define UTILS_H

#define MAX_EXTENSIONS 10
#define MAX_DIRECTORIES 10
#define MAX_FILES 10
#define MAX_LENGTH 100

void load_config(const char *config_file);
int is_target_extension(const char *filename);
int is_target_filename(const char *filename);
int is_excluded_file(const char *filename);
int is_excluded_directory(const char *directory_name);

extern char excluded_files[MAX_FILES][MAX_LENGTH];
extern int num_files;

void add_excluded_file(const char *filename);

#endif