#pragma once
#include <cstddef>
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

#pragma region TagTypeClasses

#pragma region BaseTypes

class Tag {
public:
  const TagType type = TagType::Invalid;
protected:
  Tag() {};
  Tag(const Tag&) = delete;
  Tag& operator =(Tag&) = delete;
};

class NamedTag : public Tag {
public:
  std::string name;
protected:
  NamedTag(const std::string& _Name) : name(_Name) {};
};

#pragma endregion

#pragma region SimpleTypes

class TagByte : public NamedTag {
public:
  const TagType type = TagType::Byte;
  uint8_t value;
  TagByte(const std::string& _Name, const uint8_t& _Value) : value(_Value), NamedTag(_Name) {};
};

class TagShort : public NamedTag {
public:
  const TagType type = TagType::Short;
  int16_t value;
  TagShort(const std::string& _Name, const int16_t& _Value) : value(_Value), NamedTag(_Name) {};
};

class TagInt : public NamedTag {
public:
  const TagType type = TagType::Int;
  int32_t value;
  TagInt(const std::string& _Name, const int32_t& _Value) : value(_Value), NamedTag(_Name) {};
};

class TagLong : public NamedTag {
public:
  const TagType type = TagType::Long;
  int64_t value;
  TagLong(const std::string& _Name, const int64_t& _Value) : value(_Value), NamedTag(_Name) {};
};

class TagFloat : public NamedTag {
public:
  const TagType type = TagType::Float;
  float value;
  TagFloat(const std::string& _Name, const float& _Value) : value(_Value), NamedTag(_Name) {};
};

class TagDouble : public NamedTag {
public:
  const TagType type = TagType::Double;
  double value;
  TagDouble(const std::string& _Name, const double& _Value) : value(_Value), NamedTag(_Name) {};
};

class TagString : public NamedTag {
public:
  const TagType type = TagType::String;
  std::string value;
  TagString(const std::string& _Name, const std::string& _Value) : value(_Value), NamedTag(_Name) {};
};

#pragma endregion

#pragma region ArrayTypes

class TagByteArray : public NamedTag {
public:
  const TagType type = TagType::ByteArray;
  std::vector<int8_t> values;
  TagByteArray(const std::string& _Name) : NamedTag(_Name) {};
};

class TagIntArray : public NamedTag {
public:
  const TagType type = TagType::IntArray;
  std::vector<int32_t> values;
  TagIntArray(const std::string& _Name) : NamedTag(_Name) {};
};

class TagLongArray : public NamedTag {
public:
  const TagType type = TagType::LongArray;
  std::vector<int64_t> values;
  TagLongArray(const std::string& _Name) : NamedTag(_Name) {};
};

#pragma endregion

#pragma region ComplexTypes

class TagList : public NamedTag {
public:
  const TagType type = TagType::List;
  const TagType listType;
  std::vector<NamedTag> entries;
};

class TagCompoundStart : public NamedTag {
public:
  const TagType type = TagType::CompoundStart;
  std::vector<NamedTag> tags;
};

#pragma endregion

#pragma endregion

extern short littleEndianToShort(const std::byte* _Bytes);
extern int littleEndianToInt(const std::byte* _Bytes);
extern long long littleEndianToLong(const std::byte* _Bytes);
extern float littleEndianToFloat(const std::byte* _Bytes);
extern double littleEndianToDouble(const std::byte* _Bytes);
