// TDisk main.cpp
// Copyright (C) 2026 tigercodes-dev

#include <iostream>
#include <vector>
#include <string>
#include "error.hpp"

using namespace tdisk;

int main(int argc, char *argv[])
{
    std::cerr << "TDisk - Tiger Disk Utility\n(C) 2026 tigercodes-dev\n"
              << std::endl;

    std::vector<std::string> args;
    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }

    if (args.size() == 1)
    {
        error::MsgError("No arguments were provided. Use '" + args[0] + " help' to see usage.");
        return 1;
    }

    std::string command = args[1];
    if (command == "version")
    {
        std::cout << "TDisk Version 0.1.0\n"
                  << std::endl;
        return 0;
    }
    else if (command == "help")
    {
        std::cout << "Usage: " << args[0] << " <command> [args...]\n"
                  << "Commands:\n"
                  << "version - Displays version information.\n"
                  << "help - Displays this help message.\n"
                  << std::endl;
        return 0;
    }
    else
    {
        error::MsgError("Invalid command '" + command + "'. Use '" + args[0] + " help' to see valid commands.");
        return 1;
    }
}
