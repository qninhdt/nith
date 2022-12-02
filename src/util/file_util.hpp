#pragma once

#include "common.hpp"

namespace nith::util {

    bool ReadTextFile(const char* path, std::string& dst);

    std::string GetFileNameFromPath(const std::string& path);
}