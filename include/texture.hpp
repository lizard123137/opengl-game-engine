#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include "glad.h"

class Texture {
public:
    unsigned int ID;
    std::string type;
    std::string path;

    Texture(const char *path, const char *type);
};

#endif