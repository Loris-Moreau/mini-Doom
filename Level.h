#pragma once

#include <vector>
#include <iostream>

class Level
{
public:
    void LoadLevel(const char* fileName);
    
    std::vector<std::string> layout; // Loaded from a text file
};
