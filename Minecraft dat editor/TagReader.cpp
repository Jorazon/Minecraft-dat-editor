#pragma warning(disable:6385)
#pragma warning(disable:6386)

#include "TagReader.h"


uint8_t readByte(FILE* _File) {
  uint8_t byte;
  fread(&byte, sizeof(uint8_t), 1, _File);
  return byte;
}

short readShort(FILE* _File) {
  uint8_t bytes[2];
  fread(bytes, sizeof(uint8_t), 2, _File);
  return littleEndianToShort(bytes);
}

const char* readString(FILE* _File) {
  short nameLength = readShort(_File);

  char* name = (char*)malloc((nameLength + 1) * sizeof(char));

  if (name == NULL) {
    printf("Failed to allocate memory for the string.\n");
    return NULL;
  }

  if (nameLength != 0) {
    fread(name, sizeof(char), nameLength, _File);
  }
  name[nameLength] = '\0';

  return name;
}

int readInt(FILE* _File) {
  uint8_t lengthBytes[4];
  fread(lengthBytes, sizeof(uint8_t), 4, _File);
  return littleEndianToInt(lengthBytes);
}

long readLong(FILE* _File) {
  uint8_t lengthBytes[8];
  fread(lengthBytes, sizeof(uint8_t), 8, _File);
  return littleEndianToLong(lengthBytes);
}

float readFloat(FILE* _File) {
  uint8_t lengthBytes[4];
  fread(lengthBytes, sizeof(uint8_t), 4, _File);
  return littleEndianToFloat(lengthBytes);
}

int readTag(TagType _Type, void* _Out, FILE* _File) {
  switch (_Type) {
  case TagType::Byte: {
    // read Byte
    uint8_t byte = readByte(_File);
    printf("%X", byte);
    _Out = &byte;
    return 1;
    break;
  }
  case TagType::Int: {
    // read Int
    int read = readInt(_File);
    printf("%i", read);
    _Out = &read;
    return 1;
    break;
  }
  case TagType::Long: {
    // read Long
    long read = readLong(_File);
    printf("%i", read);
    _Out = &read;
    return 1;
    break;
  }
  case TagType::Float: {
    // read Float
    float read = readFloat(_File);
    printf("%f", read);
    _Out = &read;
    return 1;
    break;
  }
  case TagType::String: {
    // read String
    const char* str = readString(_File);

    if (str == NULL) {
      _Out = (void*) "Failed to allocate memory for the string.\n";
      printf("%s", (const char*) _Out);
      return 0;
    }

    printf("\"%s\"", str);
    _Out = (char*) str;
    return 1;
    break;
  }
  case TagType::List: {
    // read List
    uint8_t listTypeByte = readByte(_File);
    const int listLength = readInt(_File);
    void** arr = (void**)malloc((listLength) * sizeof(void*));

    if (arr == NULL) {
      _Out = (void*) "Failed to allocate memory for the list.\n";
      printf("%s", (const char*) _Out);
      return 0;
    }

    printf("\"");
    for (size_t i = 0; i < listLength; ++i) {
      readTag(listTypeByte, arr[i], _File);
      if (i < listLength - 1) {
        printf(".");
      }
    }
    printf("\"");

    _Out = arr;
    return listLength;
    break;
  }
  default:
    break;
  }
}
