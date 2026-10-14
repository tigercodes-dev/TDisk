// TDisk commands/basic-io.cpp
// Copyright (C) 2026 tigercodes-dev

#include "basic-io.hpp"
#include <iostream>
#include <fstream>
#include "../error.hpp"

namespace tdisk::commands
{
    int ReadSectors(const std::vector<std::string> &args)
    {
        const std::string *disk_fp = nullptr;
        const std::string *out_fp = nullptr;
        unsigned long lba;
        bool lba_set = false;
        unsigned long count;
        bool count_set = false;

        // Parse args
        for (int i = 2; i < static_cast<int>(args.size()); i++)
        {
            const std::string &arg = args[i];
            if (arg[0] == '-')
            {
                if (arg == "-o" || arg == "--out")
                {
                    if (out_fp == nullptr)
                    {
                        if (i + 1 >= static_cast<int>(args.size()))
                        {
                            error::MsgError("The -o (--out) flag was specified, but no file was specified.");
                            return 1;
                        }
                        out_fp = &(args[i + 1]);
                        i++;
                    }
                    else
                    {
                        error::MsgError("The -o (--out) flag was specified twice. It should only be included once.");
                        return 1;
                    }
                }
                else
                {
                    error::MsgError("Unrecognized option '" + arg + "'. Use '" + args[0] + " help readsectors' to see command usage.");
                    return 1;
                }
            }
            else if (disk_fp == nullptr)
            {
                disk_fp = &arg;
            }
            else if (!lba_set)
            {
                try
                {
                    lba = std::stoul(arg, nullptr, 0);
                }
                catch (const std::invalid_argument &e)
                {
                    error::MsgError("Invalid number '" + arg + "'. lba must be a valid number.");
                    return 1;
                }
                catch (const std::out_of_range &e)
                {
                    error::MsgError("Number too large. lba must be a valid 64-bit unsigned integer.");
                    return 1;
                }

                lba_set = true;
            }
            else if (!count_set)
            {
                try
                {
                    count = std::stoul(arg, nullptr, 0);
                }
                catch (const std::invalid_argument &e)
                {
                    error::MsgError("Invalid number '" + arg + "'. count must be a valid number.");
                    return 1;
                }
                catch (const std::out_of_range &e)
                {
                    error::MsgError("Number too large. count must be a valid 64-bit unsigned integer.");
                    return 1;
                }

                count_set = true;
            }
            else
            {
                error::MsgError("Extra arguments specified. Use '" + args[0] + " help readsectors' to see command usage.");
                return 1;
            }
        }

        if (disk_fp == nullptr)
        {
            error::MsgError("No disk specified. Use '" + args[0] + " help readsectors' to see command usage.");
            return 1;
        }
        if (!lba_set)
        {
            error::MsgError("No lba specified. Use '" + args[0] + " help readsectors' to see command usage.");
            return 1;
        }
        if (!count_set)
        {
            error::MsgError("No count specified. Use '" + args[0] + " help readsectors' to see command usage.");
            return 1;
        }

        // Open disk file
        std::ifstream disk(*disk_fp, std::ios::binary);
        if (!disk.is_open())
        {
            error::MsgError("Unable to open disk file '" + *disk_fp + "'.");
            return 2;
        }

        std::ofstream *out = nullptr;
        if (out_fp != nullptr)
        {
            out = new std::ofstream(*out_fp, std::ios::binary);
            if (!out->is_open())
            {
                error::MsgError("Unable to open output file '" + *out_fp + "' for writing.");
                delete out;
                return 2;
            }
        }

        // Seek to correct position
        disk.seekg(lba * 512);
        if (disk.fail())
        {
            error::MsgError("Failed to access the correct sector.");
            if (out != nullptr)
            {
                delete out;
            }
            return 2;
        }

        char buffer[512] = {};
        unsigned long i = 0;
        while (i < count)
        {
            disk.read(buffer, 512);
            if (disk.fail())
            {
                error::MsgError("Read from disk failed.");
                if (out != nullptr)
                {
                    delete out;
                }
                return 2;
            }

            if (out == nullptr)
            {
                std::cout.write(buffer, disk.gcount());
                if (std::cout.fail())
                {
                    error::MsgError("Write to standard output failed.");
                    return 2;
                }
            }
            else
            {
                out->write(buffer, disk.gcount());
                if (out->fail())
                {
                    error::MsgError("Write to output file failed.");
                    delete out;
                    return 2;
                }
            }

            i++;
        }

        if (out != nullptr)
        {
            delete out;
        }

        return 0;
    }

    void ReadSectorsHelp()
    {
        std::cout << "Reads sectors from a disk and outputs them.\n"
                  << "Usage: readsectors <disk> <lba> <count> [-o/--out <file>]\n"
                  << "disk: the filepath of the disk\n"
                  << "lba: the logical block address of the target sector\n"
                  << "count: the number of sectors to read\n"
                  << "-o/--out <file>: changes output to a file instead of stdout\n"
                  << std::endl;
    }

    int WriteSectors(const std::vector<std::string> &args)
    {
        const std::string *disk_fp = nullptr;
        const std::string *in_fp = nullptr;
        unsigned long lba;
        bool lba_set = false;
        unsigned long count;
        bool count_set = false;

        // Parse args
        for (int i = 2; i < static_cast<int>(args.size()); i++)
        {
            const std::string &arg = args[i];
            if (arg[0] == '-')
            {
                if (arg == "-i" || arg == "--in")
                {
                    if (in_fp == nullptr)
                    {
                        if (i + 1 >= static_cast<int>(args.size()))
                        {
                            error::MsgError("The -i (--in) flag was specified, but no file was specified.");
                            return 1;
                        }
                        in_fp = &(args[i + 1]);
                        i++;
                    }
                    else
                    {
                        error::MsgError("The -i (--in) flag was specified twice. It should only be included once.");
                        return 1;
                    }
                }
                else
                {
                    error::MsgError("Unrecognized option '" + arg + "'. Use '" + args[0] + " help writesectors' to see command usage.");
                    return 1;
                }
            }
            else if (disk_fp == nullptr)
            {
                disk_fp = &arg;
            }
            else if (!lba_set)
            {
                try
                {
                    lba = std::stoul(arg, nullptr, 0);
                }
                catch (const std::invalid_argument &e)
                {
                    error::MsgError("Invalid number '" + arg + "'. lba must be a valid number.");
                    return 1;
                }
                catch (const std::out_of_range &e)
                {
                    error::MsgError("Number too large. lba must be a valid 64-bit unsigned integer.");
                    return 1;
                }

                lba_set = true;
            }
            else if (!count_set)
            {
                try
                {
                    count = std::stoul(arg, nullptr, 0);
                }
                catch (const std::invalid_argument &e)
                {
                    error::MsgError("Invalid number '" + arg + "'. count must be a valid number.");
                    return 1;
                }
                catch (const std::out_of_range &e)
                {
                    error::MsgError("Number too large. count must be a valid 64-bit unsigned integer.");
                    return 1;
                }

                count_set = true;
            }
            else
            {
                error::MsgError("Extra arguments specified. Use '" + args[0] + " help writesectors' to see command usage.");
                return 1;
            }
        }

        if (disk_fp == nullptr)
        {
            error::MsgError("No disk specified. Use '" + args[0] + " help writesectors' to see command usage.");
            return 1;
        }
        if (!lba_set)
        {
            error::MsgError("No lba specified. Use '" + args[0] + " help writesectors' to see command usage.");
            return 1;
        }
        if (!count_set)
        {
            error::MsgError("No count specified. Use '" + args[0] + " help writesectors' to see command usage.");
            return 1;
        }

        // Open disk file
        std::fstream disk(*disk_fp, std::ios::in | std::ios::out | std::ios::binary);
        if (!disk.is_open())
        {
            error::MsgError("Unable to open disk file '" + *disk_fp + "'.");
            return 2;
        }

        std::ifstream *in = nullptr;
        if (in_fp != nullptr)
        {
            in = new std::ifstream(*in_fp, std::ios::binary);
            if (!in->is_open())
            {
                error::MsgError("Unable to open input file '" + *in_fp + "' for reading.");
                delete in;
                return 2;
            }
        }

        // Seek to correct position
        disk.seekp(lba * 512);
        if (disk.fail())
        {
            error::MsgError("Failed to access the correct sector.");
            if (in != nullptr)
            {
                delete in;
            }
            return 1;
        }

        char buffer[512] = {};
        unsigned long i = 0;
        while (i < count)
        {
            if (in == nullptr)
            {
                std::cin.read(buffer, 512);
                if (std::cin.fail())
                {
                    error::MsgError("Read from standard input failed.");
                    return 2;
                }
            }
            else
            {
                in->read(buffer, 512);
                if (in->fail())
                {
                    error::MsgError("Read from input file failed.");
                    delete in;
                    return 2;
                }
            }

            disk.write(buffer, 512);
            if (disk.fail())
            {
                error::MsgError("Write to disk failed.");
                if (in != nullptr)
                {
                    delete in;
                }
                return 2;
            }

            i++;
        }

        if (in != nullptr)
        {
            delete in;
        }

        return 0;
    }

    void WriteSectorsHelp()
    {
        std::cout << "Writes sectors to a disk from an input.\n"
                  << "Usage: writesectors <disk> <lba> <count> [-i/--in <file>]\n"
                  << "disk: the filepath of the disk\n"
                  << "lba: the logical block address of the target sector\n"
                  << "count: the number of sectors to write\n"
                  << "-i/--in <file>: takes data to write from a file instead of stdin\n"
                  << std::endl;
    }
}
