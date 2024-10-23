#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Level
{
public:
    bool LoadLevel(const std::string& levelFilePath);
    
    std::vector<std::string> layout; // Loaded from a text file
};
