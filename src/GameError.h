#pragma once
#include <stdexcept>

class GameError : public std:: logic_error
{
public:
    GameError(const std::string& message) : std::logic_error(message) {}
};

