#pragma once
#include "GameError.h"
#include <string>

class FileFormatError : public GameError
{
public:
    FileFormatError(const std::string& filename, int line = 0): GameError("Error de formato en " + filename + " linea " + std::to_string(line) + ": ") {}
};

