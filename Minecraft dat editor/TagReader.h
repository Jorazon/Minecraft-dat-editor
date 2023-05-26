#pragma once

#include "Types.h"

uint8_t readByte(FILE* _File);
short readShort(FILE* _File);
const char* readString(FILE* _File);
int readInt(FILE* _File);
long readLong(FILE* _File);
float readFloat(FILE* _File);

int readTag(TagType _Type, void* _Out, FILE* _File);
