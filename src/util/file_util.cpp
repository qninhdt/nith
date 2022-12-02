#include "util/file_util.hpp"

namespace nith::util {

    /// @brief Read all text from text file (ex: .txt, .vert, .frag, ...)
    /// @param path - File path.
    /// @param dst  - String to store result.
    /// @return True if read text successfully, otherwise false.
    bool ReadTextFile(const char* path, std::string& dst)
    {
        std::ifstream file(path);

        if (!file.is_open()) {
            dst = "";
            NITH_CORE_ERROR("File not found: {0}", path);
            return false;
        }

        // avoid automatic reallocation
        file.seekg(0, std::ios::end);
        dst.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        // read text
        dst.assign(std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>());

        file.close();
        return true;
    }

    std::string GetFileNameFromPath(const std::string& path)
    {
        std::filesystem::path pathObj(path);
        return pathObj.stem().string();
    }
}