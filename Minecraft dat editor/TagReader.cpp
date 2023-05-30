#pragma warning(disable:6385)
#pragma warning(disable:6386)

#include "TagReader.h"

std::byte readByte(std::ifstream* _File) {
  std::byte byte[1];
  _File->read((char*) byte, 1);
  return *byte;
}

short readShort(std::ifstream* _File) {
  std::byte bytes[sizeof(short)];
  _File->read((char*) bytes, sizeof(short));
  return littleEndianToShort(bytes);
}

std::string readString(std::ifstream* _File) {
  short nameLength = readShort(_File);

  char* name = (char*)malloc((nameLength + 1) * sizeof(char));

  if (name == NULL) {
    printf("Failed to allocate memory for the string.\n");
    return "";
  }

  if (nameLength != 0) {
    _File->read((char*)name, nameLength);
  }

  name[nameLength] = '\0';

  std::string nameStr(name);

  free(name);

  return nameStr;
}

int readInt(std::ifstream* _File) {
  std::byte bytes[sizeof(int)];
  _File->read((char*)bytes, sizeof(int));
  return littleEndianToInt(bytes);
}

long long readLong(std::ifstream* _File) {
  std::byte bytes[sizeof(long long)];
  _File->read((char*)bytes, sizeof(long long));
  return littleEndianToLong(bytes);
}

float readFloat(std::ifstream* _File) {
  std::byte bytes[sizeof(float)];
  _File->read((char*)bytes, sizeof(float));
  return littleEndianToFloat(bytes);
}

double readDouble(std::ifstream* _File) {
  std::byte bytes[sizeof(double)];
  _File->read((char*)bytes, sizeof(double));
  return littleEndianToDouble(bytes);
}

int readTag(TagType _Type, std::ifstream* _File) {
  switch (_Type) {
  case TagType::Byte: {
    // read Byte
    std::byte byte = readByte(_File);
    printf("%X", byte);
    return 1;
    break;
  }
  case TagType::Int: {
    // read Int
    int read = readInt(_File);
    printf("%i", read);
    return 1;
    break;
  }
  case TagType::Long: {
    // read Long
    int64_t read = readLong(_File);
    printf("%lld", read);
    return 1;
    break;
  }
  case TagType::Float: {
    // read Float
    float read = readFloat(_File);
    printf("%f", read);
    return 1;
    break;
  }
  case TagType::String: {
    // read String
    std::string str = readString(_File);

    printf("\"%s\"", str.c_str());
    return 1;
    break;
  }
  case TagType::List: {
    // read List
    TagType listTypeByte = (TagType) readByte(_File);
    const int listLength = readInt(_File);

    printf("\"");
    for (size_t i = 0; i < listLength; ++i) {
      readTag(listTypeByte, _File);
      if (i < listLength - 1) {
        printf(".");
      }
    }
    printf("\"");

    return listLength;
    break;
  }
  default:
    return 0;
    break;
  }
}
