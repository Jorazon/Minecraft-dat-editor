#define _CRT_SECURE_NO_WARNINGS



#include "TagReader.h"

void printIndent(int level) {
  for (size_t i = 0; i < level; ++i) {
    printf("\t");
  }
}

int main(void) {

  // open file
  const char* filename = "level.dat";

  FILE* file = fopen(filename, "rb");
  
  if (file == NULL) {
    printf("Failed to open file: %s\n", filename);
    return 1;
  }

  // read file header
  int version = readInt(file);
  
  int length = readInt(file) + 8;

  printf("Version: %i\nLength: %i\n\n", version, length);
  
  int indent = 0;

  // read file
  while (ftell(file) < length) {
    // read tag type
    uint8_t typeByte = readByte(file);

    if (typeByte == 0x00) {
      indent--;
      printIndent(indent);
      printf("}\n");
      continue;
    }
    
    // read tag name
    const char* name = readString(file);
    if (name == NULL) {
      fclose(file);
      return 1;
    }

    printIndent(indent);

    if (name[0] != '\0') {
      printf("\"%s\":", name);
    }

    if (typeByte == 0x0A) {
      printf("{");
      indent++;
    }

    void* value = nullptr;
    // read type
    readTag(typeByte, value, file);

    if (typeByte != 0x0A) {
      printf(",");
    }
    printf("\n");
  }

  fclose(file);
  return 0;
}
