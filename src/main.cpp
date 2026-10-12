// TDisk main.cpp
// Copyright (C) 2026 tigercodes-dev

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include "error.hpp"
#include "commands/basic-io.hpp"

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
    for (char &c : command)
    {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    if (command == "version")
    {
        std::cout << "TDisk Version 0.1.0\n"
                  << std::endl;
        return 0;
    }
    else if (command == "help")
    {
        if (args.size() > 2)
        {
            std::string help_command = args[2];
            for (char &c : help_command)
            {
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }

            if (help_command == "readsectors")
            {
                commands::ReadSectorsHelp();
            }
            else if (help_command == "writesectors")
            {
                commands::WriteSectorsHelp();
            }
            else
            {
                error::MsgError("Unknown command '" + args[2] + "'.");
                return 1;
            }

            return 0;
        }
        else
        {
            std::cout << "Usage: " << args[0] << " <command> [args...]\n"
                      << "Commands:\n"
                      << "version - Displays version information.\n"
                      << "help [command] - Displays a help message for a command. A list of commands will be shown if the user does not specify one.\n"
                      << "readsectors <disk> <lba> <count> [-o/--out <file>] - Reads sectors from a disk.\n"
                      << "writesectors <disk> <lba> <count> [-i/--in <file>] - Writes sectors to a disk.\n"
                      << std::endl;
        }
        return 0;
    }
    else if (command == "readsectors")
    {
        return commands::ReadSectors(args);
    }
    else if (command == "writesectors")
    {
        return commands::WriteSectors(args);
    }
    else
    {
        error::MsgError("Invalid command '" + command + "'. Use '" + args[0] + " help' to see valid commands.");
        return 1;
    }
}
