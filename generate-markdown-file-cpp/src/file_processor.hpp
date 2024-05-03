#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <string>
#include <fstream>

class FileProcessor
{
public:
    void processFile(const std::string &filename, std::ofstream &output, bool is_first_file, const std::string &output_filename) const;
};

#endif