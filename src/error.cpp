// TDisk error.cpp
// Copyright (C) 2026 tigercodes-dev

#include "error.hpp"
#include <iostream>

namespace tdisk::error
{
    void MsgError(const std::string &msg)
    {
        std::cerr << "\e[1;31mError:\e[0m " << msg << std::endl;
    }

    void MsgWarning(const std::string &msg)
    {
        std::cerr << "\e[1;33mWarning:\e[0m " << msg << std::endl;
    }
}
