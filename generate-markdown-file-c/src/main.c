#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include "process_directory.h"
#include "utils.h"

void print_usage(char *program_name)
{
    printf("Usage: %s <directory> <output_file>\n", program_name);
}

int main(int argc, char *argv[])
{
    load_config("config.toml");

    if (argc != 3)
    {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        print_usage(argv[0]);
        return 0;
    }

    char *directory = argv[1];
    char *output_filename = argv[2];

    // Add output destination markdown file name to excluded_files
    add_excluded_file(output_filename);

    printf("Checking if %s is a directory...\n", directory);
    DIR *dir = opendir(directory);
    if (dir == NULL)
    {
        printf("Failed to open %s: Not a directory\n", directory);
        return 1;
    }
    closedir(dir);
    printf("%s is a directory\n", directory);

    printf("Creating output file %s...\n", output_filename);
    FILE *output = fopen(output_filename, "w");
    if (output == NULL)
    {
        printf("Failed to create output file: %s\n", output_filename);
        return 1;
    }
    printf("Output file created successfully\n");

    processDirectory(directory, output, output_filename);

    int fd = fileno(output);
    // Seek just before last newline
    fseek(output, -1, SEEK_END);
    // Adjust file size and remove extra lines
    ftruncate(fd, ftell(output));

    fclose(output);

    return 0;
}