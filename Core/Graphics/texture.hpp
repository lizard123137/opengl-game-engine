#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <Libs/glad.h>

class Texture {
public:
    unsigned int ID;

    unsigned int Width, Height;

    unsigned int Internal_Format;
    unsigned int Image_Format;

    unsigned int Wrap_S;
    unsigned int Wrap_T;
    unsigned int Filter_Min;
    unsigned int Filter_Max;

    Texture();

    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;
};

#endif