#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Wall.h"

class Level
{
public:
    bool LoadLevel(const std::string& levelFilePath);
    
    std::vector<std::string> layout; // Loaded from a text file
    std::vector<Wall> walls; 
};
