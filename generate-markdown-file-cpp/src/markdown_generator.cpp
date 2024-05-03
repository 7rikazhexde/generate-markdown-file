#include "markdown_generator.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

MarkdownGenerator::MarkdownGenerator(const Config &config) : config_(config) {}

void MarkdownGenerator::processDirectory(const std::string &directory, const std::string &output_filename)
{
    config_.addExcludedFile(output_filename);

    std::cout << "Creating output file " << output_filename << "..." << std::endl;
    std::ofstream output(output_filename);
    if (!output)
    {
        std::cout << "Failed to create output file: " << output_filename << std::endl;
        return;
    }
    std::cout << "Output file created successfully" << std::endl;

    bool is_first_file = true;
    for (const auto &entry : fs::recursive_directory_iterator(directory))
    {
        const auto path = entry.path();
        if (fs::is_regular_file(path))
        {
            std::string filename = path.filename().string();
            std::string parent_dir = path.parent_path().string();
            bool is_target_extension = config_.isTargetExtension(filename);
            bool is_target_filename = config_.isTargetFilename(filename);
            bool is_excluded_file = config_.isExcludedFile(filename);
            bool is_excluded_directory = config_.isExcludedDirectory(parent_dir);

            std::cout << "File: " << path << std::endl;
            std::cout << "  Is target extension: " << is_target_extension << std::endl;
            std::cout << "  Is target filename: " << is_target_filename << std::endl;
            std::cout << "  Is excluded file: " << is_excluded_file << std::endl;
            std::cout << "  Is excluded directory: " << is_excluded_directory << std::endl;

            if ((!is_excluded_directory && (is_target_extension || is_target_filename)) && !is_excluded_file)
            {
                std::cout << "Processing file " << path << "..." << std::endl;
                file_processor_.processFile(path.string(), output, is_first_file, output_filename);
                is_first_file = false;
                std::cout << "File " << path << " processed successfully" << std::endl;
            }
        }
    }

    output.close();

    // Remove blank line at end of file
    std::string line;
    std::vector<std::string> lines;
    // Read output file line by line
    std::ifstream file(output_filename);
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    // Check if the last element (line) is empty
    if (!lines.empty() && lines.back().empty())
    {
        // Remove last element if empty
        lines.pop_back();
    }

    // Reopen the output file
    std::ofstream outputFile(output_filename);
    for (const auto &l : lines)
    {
        // Write each element (line) of the lines vector with '\n' (line feed) to the output file
        outputFile << l << '\n';
    }
    // Close output file
    outputFile.close();
}