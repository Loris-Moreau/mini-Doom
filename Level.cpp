#include "Level.h"

void Level::LoadLevel(const char* fileName)
{
    FILE* file;
    if (fopen_s(&file, fileName, "r") != 0)
    {
        std::cerr << "Could not load : " << fileName << '\n';
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        layout.emplace_back(line);
    }

    fclose(file);
}
