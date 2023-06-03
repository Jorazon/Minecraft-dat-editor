#pragma once

#include <fstream>

#include "Types.h"

std::byte readByte(std::ifstream* _File);
short readShort(std::ifstream* _File);
std::string readString(std::ifstream* _File);
int readInt(std::ifstream* _File);
long long readLong(std::ifstream* _File);
float readFloat(std::ifstream* _File);
double readDouble(std::ifstream* _File);

NamedTag* readTag(TagType _Type, std::string _Name, std::ifstream* _File);
