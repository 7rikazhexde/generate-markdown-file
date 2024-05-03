#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include "utils.h"
#include "process_file.h"

void processDirectory(const char *directory, FILE *output, char *output_filename)
{
    DIR *dir = opendir(directory);
    if (dir == NULL)
    {
        printf("Failed to open directory: %s\n", directory);
        return;
    }

    struct dirent *entry;
    long path_max = pathconf(directory, _PC_PATH_MAX);
    if (path_max == -1)
    {
        path_max = PATH_MAX;
    }
    char *path = malloc(path_max);

    // 最初のファイルかどうかを追跡する変数
    int is_first_file = 1;

    while ((entry = readdir(dir)) != NULL)
    {
        snprintf(path, path_max, "%s/%s", directory, entry->d_name);

        struct stat file_stat;
        if (stat(path, &file_stat) == 0)
        {
            if (S_ISREG(file_stat.st_mode))
            {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && (is_target_extension(entry->d_name) || is_target_filename(entry->d_name)) && !is_excluded_file(entry->d_name))
                {
                    printf("Processing file %s...\n", path);
                    processFile(path, output, is_first_file, output_filename);
                    is_first_file = 0; // 最初のファイル処理後はフラグを落とす
                    printf("File %s processed successfully\n", path);
                }
            }
            else if (S_ISDIR(file_stat.st_mode))
            {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && !is_excluded_directory(entry->d_name))
                {
                    processDirectory(path, output, output_filename);
                }
            }
        }
        else
        {
            printf("Failed to get file status: %s\n", path);
        }
    }

    free(path);
    closedir(dir);
}