#include <iostream>
#include <string>
#include "markdown_generator.hpp"
#include "config.hpp"

void print_usage(const char *program_name)
{
    std::cout << "Usage: " << program_name << " <directory> <output_file>" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        print_usage(argv[0]);
        return 1;
    }

    // -hや--helpのチェックを追加
    std::string arg1(argv[1]);
    if (arg1 == "-h" || arg1 == "--help")
    {
        print_usage(argv[0]);
        return 0;
    }

    std::string directory = argv[1];
    std::string output_filename = argv[2];

    Config config("config.toml");
    MarkdownGenerator generator(config);
    generator.processDirectory(directory, output_filename);

    return 0;
}