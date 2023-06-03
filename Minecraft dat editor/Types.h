#pragma once
#include <cstddef>
#include <string>
#include <vector>

enum class TagType : unsigned char {
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
  const TagType type;
  virtual std::vector<std::byte> valueToBytes();
  Tag(TagType _Type) : type(_Type) {};
protected:
  Tag(const Tag&) = delete;
  Tag& operator =(Tag&) = delete;
};

class NamedTag : public Tag {
public:
  const TagType type;
  std::string name;
  std::vector<std::byte> nameToBytes();
  std::vector<std::byte> toBytes();
  NamedTag(const std::string& _Name, TagType _Type) : name(_Name), type(_Type), Tag(_Type) { /*printf("----%02X----\n", _Type);*/ };
};

#pragma endregion

#pragma region SimpleTypes

class TagByte : public NamedTag {
public:
  const TagType type = TagType::Byte;
  std::byte value;
  TagByte(const std::string& _Name, const std::byte& _Value) : value(_Value), NamedTag(_Name, TagType::Byte) {};
  std::vector<std::byte> valueToBytes();
};

class TagShort : public NamedTag {
public:
  const TagType type = TagType::Short;
  int16_t value;
  TagShort(const std::string& _Name, const int16_t& _Value) : value(_Value), NamedTag(_Name, TagType::Short) {};
  std::vector<std::byte> valueToBytes();
};

class TagInt : public NamedTag {
public:
  const TagType type = TagType::Int;
  int32_t value;
  TagInt(const std::string& _Name, const int32_t& _Value) : value(_Value), NamedTag(_Name, TagType::Int) {};
  std::vector<std::byte> valueToBytes();
};

class TagLong : public NamedTag {
public:
  const TagType type = TagType::Long;
  int64_t value;
  TagLong(const std::string& _Name, const int64_t& _Value) : value(_Value), NamedTag(_Name, TagType::Long) {};
  std::vector<std::byte> valueToBytes();
};

class TagFloat : public NamedTag {
public:
  const TagType type = TagType::Float;
  float value;
  TagFloat(const std::string& _Name, const float& _Value) : value(_Value), NamedTag(_Name, TagType::Float) {};
  std::vector<std::byte> valueToBytes();
};

class TagDouble : public NamedTag {
public:
  const TagType type = TagType::Double;
  double value;
  TagDouble(const std::string& _Name, const double& _Value) : value(_Value), NamedTag(_Name, TagType::Double) {};
  std::vector<std::byte> valueToBytes();
};

class TagString : public NamedTag {
public:
  const TagType type = TagType::String;
  std::string value;
  TagString(const std::string& _Name, const std::string& _Value) : value(_Value), NamedTag(_Name, TagType::String) {};
  std::vector<std::byte> valueToBytes();
};

#pragma endregion

#pragma region ArrayTypes

class TagByteArray : public NamedTag {
public:
  const TagType type = TagType::ByteArray;
  std::vector<int8_t> values;
  TagByteArray(const std::string& _Name) : NamedTag(_Name, TagType::ByteArray) {};
  std::vector<std::byte> valueToBytes();
};

class TagIntArray : public NamedTag {
public:
  const TagType type = TagType::IntArray;
  std::vector<int32_t> values;
  TagIntArray(const std::string& _Name) : NamedTag(_Name, TagType::IntArray) {};
  std::vector<std::byte> valueToBytes();
};

class TagLongArray : public NamedTag {
public:
  const TagType type = TagType::LongArray;
  std::vector<int64_t> values;
  TagLongArray(const std::string& _Name) : NamedTag(_Name, TagType::LongArray) {};
  std::vector<std::byte> valueToBytes();
};

#pragma endregion

#pragma region ComplexTypes


class TagList : public NamedTag {
public:
  const TagType type = TagType::List;
  const TagType listType;
  std::vector<Tag*> entries;
  TagList(const std::string& _Name, TagType _EntryType) : NamedTag(_Name, TagType::List), listType(_EntryType) {};
  std::vector<std::byte> valueToBytes();
};

class TagCompound : public NamedTag {
public:
  const TagType type = TagType::CompoundStart;
  std::vector<NamedTag*> tags;
  TagCompound(const std::string& _Name) : NamedTag(_Name, TagType::CompoundStart) {};
  std::vector<std::byte> valueToBytes();
};

#pragma endregion

#pragma endregion

extern int16_t littleEndianToShort(const std::byte* _Bytes);
extern int32_t littleEndianToInt(const std::byte* _Bytes);
extern int64_t littleEndianToLong(const std::byte* _Bytes);
extern float littleEndianToFloat(const std::byte* _Bytes);
extern double littleEndianToDouble(const std::byte* _Bytes);
