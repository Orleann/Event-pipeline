//
// Created by Sebastian Sobczyński on 25/11/2026.
//

#pragma once
#include <filesystem>

#include "storage_strategy.h"

class BinaryFileStorage : public IStorageStrategy {
    const std::filesystem::path& filePath;
public:
    BinaryFileStorage();

};
