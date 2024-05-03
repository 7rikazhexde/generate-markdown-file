#include <stdio.h>
#include <string.h>

void processFile(const char *filename, FILE *output, int is_first_file, char *output_filename)
{
    FILE *input = fopen(filename, "r");
    if (input == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char *extension = strrchr(filename, '.');
    if (extension == NULL)
    {
        // Set .txt if no extension
        extension = "txt";
    }
    else
    {
        // Move the pointer to the first character of the extension
        extension++;
    }

    // Add output file name and comments at the beginning of the file for the first file only
    if (is_first_file)
    {
        fprintf(output, "# %s\n\n", output_filename);
    }

    fprintf(output, "## %s\n\n", filename);

    // For md files, export as is for Markdown file format
    if (strcmp(extension, "md") == 0)
    {
        char line[256];
        while (fgets(line, sizeof(line), input))
        {
            if (ferror(input))
            {
                printf("Error reading file: %s\n", filename);
                fclose(input);
                fprintf(output, "\n");
                return;
            }
            fprintf(output, "%s", line);
        }

        if (ferror(input))
        {
            printf("Error reading file: %s\n", filename);
            fclose(input);
            fprintf(output, "\n");
            return;
        }
        fprintf(output, "\n");
    }
    else
    {
        if (strstr(filename, "Makefile") != NULL)
        {
            fprintf(output, "```txt\n");
        }
        else
        {
            fprintf(output, "```%s\n", extension);
        }

        char line[256];
        while (fgets(line, sizeof(line), input))
        {
            if (ferror(input))
            {
                printf("Error reading file: %s\n", filename);
                fclose(input);
                fprintf(output, "```\n\n");
                return;
            }
            fprintf(output, "%s", line);
        }

        if (ferror(input))
        {
            printf("Error reading file: %s\n", filename);
            fclose(input);
            fprintf(output, "```\n\n");
            return;
        }

        fprintf(output, "\n```\n\n");
    }

    fclose(input);
}