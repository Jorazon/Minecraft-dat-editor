#define _CRT_SECURE_NO_WARNINGS

#include <fstream>

#include "TagReader.h"

void printIndent(int level) {
  for (size_t i = 0; i < level; ++i) {
    printf("\t");
  }
}

int main(void) {
  // open file
  std::string filename("level.dat");

  std::ifstream file(filename, std::ios::binary);
  
  if (!file) {
    printf("Failed to open file: %s\n", filename.c_str());
    return 1;
  }

  // read file header
  int version = readInt(&file);
  
  int length = readInt(&file) + 8;

  printf("Version: %i\nLength: %i\n\n", version, length);
  
  int indent = 0;

  // read file
  while (((int) file.tellg()) < length) {
    // read tag type
    TagType typeByte = (TagType) readByte(&file);

    if (typeByte == TagType::CompoundEnd) {
      indent--;
      printIndent(indent);
      printf("}\n");
      continue;
    }
    
    // read tag name
    std::string name = readString(&file);

    printIndent(indent);

    if (name[0] != '\0') {
      printf("\"%s\":", name.c_str());
    }

    if (typeByte == TagType::CompoundStart) {
      printf("{");
      indent++;
    }

    // read type
    readTag(typeByte, &file);

    if (typeByte != TagType::CompoundStart) {
      printf(",");
    }
    printf("\n");
  }

  file.close();
  return 0;
}
