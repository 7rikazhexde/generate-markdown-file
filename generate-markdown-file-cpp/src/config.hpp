#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <toml.hpp>

class Config
{
public:
    Config(const std::string &filename);
    bool isTargetExtension(const std::string &filename) const;
    bool isTargetFilename(const std::string &filename) const;
    bool isExcludedFile(const std::string &filename) const;
    bool isExcludedDirectory(const std::string &dirname) const;
    void addExcludedFile(const std::string &filename);

private:
    toml::value config_;
};

#endif