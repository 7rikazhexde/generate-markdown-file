#ifndef MARKDOWN_GENERATOR_HPP
#define MARKDOWN_GENERATOR_HPP

#include <string>
#include <fstream>
#include "config.hpp"
#include "file_processor.hpp"

class MarkdownGenerator
{
public:
    MarkdownGenerator(const Config &config);
    void processDirectory(const std::string &directory, const std::string &output_filename);

private:
    Config config_;
    FileProcessor file_processor_;
};

#endif