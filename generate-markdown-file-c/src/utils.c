#include <stdio.h>
#include <string.h>
#include "../tomlc99/toml.h"
#include "utils.h"

#define MAX_EXTENSIONS 10
#define MAX_FILES 10
#define MAX_DIRECTORIES 10
#define MAX_LENGTH 100

char target_extensions[MAX_EXTENSIONS][MAX_LENGTH];
int num_extensions = 0;

char target_filenames[MAX_FILES][MAX_LENGTH];
int num_filenames = 0;

char excluded_files[MAX_FILES][MAX_LENGTH];
int num_files = 0;

char excluded_directories[MAX_DIRECTORIES][MAX_LENGTH];
int num_directories = 0;

void load_config(const char *config_file)
{
    FILE *file = fopen(config_file, "r");
    if (file == NULL)
    {
        printf("Failed to open config file: %s\n", config_file);
        return;
    }

    char errbuf[200];
    toml_table_t *conf = toml_parse_file(file, errbuf, sizeof(errbuf));
    fclose(file);

    if (conf == NULL)
    {
        printf("Failed to parse TOML file: %s\nError: %s\n", config_file, errbuf);
        return;
    }

    toml_array_t *extensions = toml_array_in(conf, "target_extensions");
    if (extensions != NULL)
    {
        num_extensions = 0;
        for (int i = 0; i < toml_array_nelem(extensions) && num_extensions < MAX_EXTENSIONS; i++)
        {
            toml_datum_t ext = toml_string_at(extensions, i);
            if (ext.ok)
            {
                strcpy(target_extensions[num_extensions], ext.u.s);
                num_extensions++;
            }
        }
    }

    toml_array_t *filenames = toml_array_in(conf, "target_filenames");
    if (filenames != NULL)
    {
        num_filenames = 0;
        for (int i = 0; i < toml_array_nelem(filenames) && num_filenames < MAX_FILES; i++)
        {
            toml_datum_t file = toml_string_at(filenames, i);
            if (file.ok)
            {
                strcpy(target_filenames[num_filenames], file.u.s);
                num_filenames++;
            }
        }
    }

    toml_array_t *files = toml_array_in(conf, "excluded_files");
    if (files != NULL)
    {
        num_files = 0;
        for (int i = 0; i < toml_array_nelem(files) && num_files < MAX_FILES; i++)
        {
            toml_datum_t file = toml_string_at(files, i);
            if (file.ok)
            {
                strcpy(excluded_files[num_files], file.u.s);
                num_files++;
            }
        }
    }

    toml_array_t *directories = toml_array_in(conf, "excluded_directories");
    if (directories != NULL)
    {
        num_directories = 0;
        for (int i = 0; i < toml_array_nelem(directories) && num_directories < MAX_DIRECTORIES; i++)
        {
            toml_datum_t dir = toml_string_at(directories, i);
            if (dir.ok)
            {
                strcpy(excluded_directories[num_directories], dir.u.s);
                num_directories++;
            }
        }
    }
    toml_free(conf);
}

int is_target_extension(const char *filename)
{
    char *ext = strrchr(filename, '.');
    if (ext == NULL)
    {
        return 0;
    }
    for (int i = 0; i < num_extensions; i++)
    {
        if (strcmp(ext, target_extensions[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int is_target_filename(const char *filename)
{
    for (int i = 0; i < num_filenames; i++)
    {
        if (strcmp(filename, target_filenames[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int is_excluded_file(const char *filename)
{
    for (int i = 0; i < num_files; i++)
    {
        if (strcmp(filename, excluded_files[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int is_excluded_directory(const char *directory_name)
{
    for (int i = 0; i < num_directories; i++)
    {
        if (strcmp(directory_name, excluded_directories[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void add_excluded_file(const char *filename)
{
    if (num_files < MAX_FILES)
    {
        strcpy(excluded_files[num_files], filename);
        num_files++;
    }
}