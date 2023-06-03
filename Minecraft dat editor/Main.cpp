#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <stack>

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

  TagCompound* root = nullptr;

  std::stack<TagCompound*> compounds;

  // read file
  while (((int) file.tellg()) < length) {
    // read tag type
    TagType typeByte = (TagType) readByte(&file);

    if (typeByte == TagType::CompoundEnd) {
      root = compounds.top();
      compounds.pop();
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
    NamedTag* tag = readTag(typeByte, name, &file);

    if (typeByte == TagType::CompoundStart) {
      if (!compounds.empty()) {
        compounds.top()->tags.push_back(tag);
      }
      compounds.push((TagCompound*) tag);
    } else {
      compounds.top()->tags.push_back(tag);
    }
    printf("\n");
  }

  file.close();

  std::ofstream outFile("readworld.dat", std::ios::binary);

  TagInt fileVersion("version", 10);

  std::vector<std::byte> bytes = root->toBytes();
  TagInt fileLength("length", bytes.size());

  std::vector<std::byte> outFileBytes;

  std::vector<std::byte> versionBytes = fileVersion.valueToBytes();
  outFileBytes.insert(outFileBytes.end(), versionBytes.begin(), versionBytes.end());
  std::vector<std::byte> lengthBytes = fileLength.valueToBytes();
  outFileBytes.insert(outFileBytes.end(), lengthBytes.begin(), lengthBytes.end());

  outFileBytes.insert(outFileBytes.end(), bytes.begin(), bytes.end());

  for (auto byte : outFileBytes) {
    outFile.put((unsigned char) byte);
  }

  outFile.close();

  return 0;
}
