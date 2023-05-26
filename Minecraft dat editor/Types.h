#pragma once
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

enum class TagType : uint8_t {
  Invalid = 0xFF,
  CompoundEnd = 0x00,
  Byte = 0x01,
  Short = 0x02,
  Int = 0x03,
  Long = 0x04,
  Float = 0x05,
  Double = 0x06,
  ByteArray = 0x07,
  String = 0x08,
  List = 0x09,
  CompoundStart = 0x0A,
  IntArray = 0x0B,
  LongArray = 0x0C
};

#pragma region BaseTypes

class Tag {
public:
  const TagType type;
protected:
  Tag() : type(TagType::Invalid) {};
  Tag(const Tag&) = delete;
  Tag& operator =(Tag&) = delete;
};

class NamedTag : public Tag {
public:
  uint16_t nameLength;
  char* name;
protected:
  NamedTag(uint16_t _NameLength, char* _Name) : nameLength(_NameLength), name(_Name) {};
};

#pragma endregion

#pragma region SimpleTypes

class TagByte : public NamedTag {
public:
  const TagType type = TagType::Byte;
  int8_t value;
};

class TagShort : public NamedTag {
public:
  const TagType type = TagType::Short;
  int16_t value;
};

class TagInt : public NamedTag {
public:
  const TagType type = TagType::Int;
  int32_t value;
};

class TagLong : public NamedTag {
public:
  const TagType type = TagType::Long;
  int64_t value;
};

class TagFloat : public NamedTag {
public:
  const TagType type = TagType::Float;
  float value;
};

class TagDouble : public NamedTag {
public:
  const TagType type = TagType::Double;
  double value;
};

class TagString : public NamedTag {
public:
  const TagType type = TagType::String;
  uint16_t stringLength;
  char* value;
};

#pragma endregion

#pragma region ArrayTypes

class TagByteArray : public NamedTag {
public:
  const TagType type = TagType::ByteArray;
  uint16_t arrayLength;
  int8_t* value;
};

class TagIntArray : public NamedTag {
public:
  const TagType type = TagType::IntArray;
  uint16_t arrayLength;
  int32_t* value;
};

class TagLongArray : public NamedTag {
public:
  const TagType type = TagType::LongArray;
  uint16_t arrayLength;
  int64_t* value;
};

#pragma endregion

#pragma region ComplexTypes

template <typename T>
class TagList : public NamedTag {
public:
  const TagType type = TagType::List;
  const TagType listType;
  std::vector<T> entries;
};

class TagCompoundStart : public NamedTag {
public:
  const TagType type = TagType::CompoundStart;
  std::vector<NamedTag> tags;
};

#pragma endregion

extern short littleEndianToShort(const uint8_t* _Bytes);
extern int littleEndianToInt(const uint8_t* _Bytes);
extern long littleEndianToLong(const uint8_t* _Bytes);
extern float littleEndianToFloat(const uint8_t* _Bytes);
