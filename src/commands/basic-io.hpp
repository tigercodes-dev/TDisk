// TDisk commands/basic-io.hpp
// Copyright (C) 2026 tigercodes-dev

#include <vector>
#include <string>

namespace tdisk::commands
{
    int ReadSectors(const std::vector<std::string> &args);
    void ReadSectorsHelp();

    int WriteSectors(const std::vector<std::string> &args);
    void WriteSectorsHelp();
}
