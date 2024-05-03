#include "config.hpp"
#include <algorithm>

Config::Config(const std::string &filename)
{
    config_ = toml::parse(filename);
}

bool Config::isTargetExtension(const std::string &filename) const
{
    const auto extensions = toml::find<std::vector<std::string>>(config_, "target_extensions");
    const auto pos = filename.find_last_of('.');
    if (pos != std::string::npos)
    {
        const auto extension = filename.substr(pos);
        return std::find(extensions.begin(), extensions.end(), extension) != extensions.end();
    }
    return false;
}

bool Config::isTargetFilename(const std::string &filename) const
{
    const auto filenames = toml::find<std::vector<std::string>>(config_, "target_filenames");
    return std::find(filenames.begin(), filenames.end(), filename) != filenames.end();
}

bool Config::isExcludedFile(const std::string &filename) const
{
    const auto excluded = toml::find<std::vector<std::string>>(config_, "excluded_files");
    return std::find(excluded.begin(), excluded.end(), filename) != excluded.end();
}

bool Config::isExcludedDirectory(const std::string &dirname) const
{
    const auto excluded = toml::find<std::vector<std::string>>(config_, "excluded_directories");
    return std::any_of(excluded.begin(), excluded.end(), [&](const std::string &dir)
                       { return dirname.find(dir) != std::string::npos; });
}

void Config::addExcludedFile(const std::string &filename)
{
    auto excluded = toml::find<std::vector<std::string>>(config_, "excluded_files");
    excluded.push_back(filename);
    config_["excluded_files"] = excluded;
}