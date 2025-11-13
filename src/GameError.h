#pragma once
#include <stdexcept>
using namespace std;

class GameError : public logic_error
{
public:
    using logic_error::logic_error;
    using logic_error::what;
};

