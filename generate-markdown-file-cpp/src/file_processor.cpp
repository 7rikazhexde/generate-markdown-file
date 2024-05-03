#include "file_processor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void FileProcessor::processFile(const std::string &filename, std::ofstream &output, bool is_first_file, const std::string &output_filename) const
{
    std::ifstream input(filename);
    if (!input)
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string extension = filename.substr(filename.find_last_of('.') + 1);
    if (extension.empty())
    {
        extension = "txt";
    }

    if (is_first_file)
    {
        output << "# " << output_filename << "\n\n";
    }

    output << "## " << filename << "\n\n";

    if (extension == "md")
    {
        std::string line;
        while (std::getline(input, line))
        {
            output << line << "\n";
        }
        output << "\n";
    }
    else
    {
        if (filename.find("Makefile") != std::string::npos)
        {
            output << "```txt\n";
        }
        else
        {
            output << "```" << extension << "\n";
        }
        std::string line;
        while (std::getline(input, line))
        {
            output << line << "\n";
        }
        output << "```\n\n";
    }

    input.close();
}