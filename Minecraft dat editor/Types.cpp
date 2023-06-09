#include "Types.h"

#pragma region Punning

union pun16
{
  uint16_t value;
  std::byte bytes[sizeof(uint16_t)];
  pun16(uint16_t _Value) : value(_Value) {};
};

union pun32
{
  uint32_t value;
  std::byte bytes[sizeof(uint32_t)];
  pun32(uint32_t _Value) : value(_Value) {};
};

union pun64
{
  uint64_t value;
  std::byte bytes[sizeof(uint64_t)];
  pun64(uint64_t _Value) : value(_Value) {};
};

union punFloat
{
  float value;
  std::byte bytes[sizeof(float)];
  punFloat(float _Value) : value(_Value) {};
};

union punDouble
{
  double value;
  std::byte bytes[sizeof(double)];
  punDouble(double _Value) : value(_Value) {};
};

#pragma endregion

#pragma region FromLittle

int16_t littleEndianToShort(const std::byte* _Bytes) {
  int16_t value = 0;
  for (size_t i = 0; i < sizeof(int16_t); ++i) {
    value += (int16_t)_Bytes[i] << 8 * i;
  }
  return *(short*)&value;
}

int32_t littleEndianToInt(const std::byte* _Bytes) {
  int32_t value = 0;
  for (size_t i = 0; i < sizeof(int32_t); ++i) {
    value += (int32_t)_Bytes[i] << 8 * i;
  }
  return *(int*)&value;
}

int64_t littleEndianToLong(const std::byte* _Bytes) {
  int64_t value = 0;
  for (size_t i = 0; i < sizeof(int64_t); ++i) {
    value += (int64_t)_Bytes[i] << 8 * i;
  }
  return *(long long*)&value;
}

float littleEndianToFloat(const std::byte* _Bytes) {
  int32_t value = littleEndianToInt(_Bytes);
  return *(float*)&value;
}

double littleEndianToDouble(const std::byte* _Bytes) {
  int64_t value = littleEndianToLong(_Bytes);
  return *(double*)&value;
}

#pragma endregion

#pragma region ToBytes

std::vector<std::byte> Tag::valueToBytes() {
  std::vector<std::byte> bytes;
  bytes.push_back((std::byte)TagType::CompoundEnd);
  return bytes;
};

std::vector<std::byte> NamedTag::nameToBytes() {
  std::vector<std::byte> bytes;

  pun16 size((uint16_t)name.length());

  for (size_t i = 0; i < sizeof(uint16_t); ++i) {
    bytes.push_back(size.bytes[i]);
  }

  for (size_t i = 0; i < size.value; ++i) {
    bytes.push_back((std::byte)name.at(i));
  }

  return bytes;
}

std::vector<std::byte> TagByte::valueToBytes() {
  std::vector<std::byte> bytes;
  bytes.push_back(value);
  return bytes;
}

std::vector<std::byte> TagShort::valueToBytes() {
  std::vector<std::byte> bytes;

  pun16 val(value);

  for (size_t i = 0; i < sizeof(uint16_t); ++i) {
    bytes.push_back(val.bytes[i]);
  }

  return bytes;
}

std::vector<std::byte> TagInt::valueToBytes() {
  std::vector<std::byte> bytes;

  pun32 val(value);

  for (size_t i = 0; i < sizeof(uint32_t); ++i) {
    bytes.push_back(val.bytes[i]);
  }

  return bytes;
}

std::vector<std::byte> TagLong::valueToBytes() {
  std::vector<std::byte> bytes;

  pun64 val(value);

  for (size_t i = 0; i < sizeof(uint64_t); ++i) {
    bytes.push_back(val.bytes[i]);
  }

  return bytes;
}

std::vector<std::byte> TagFloat::valueToBytes() {
  std::vector<std::byte> bytes;

  punFloat val(value);

  for (size_t i = 0; i < sizeof(float); ++i) {
    bytes.push_back(val.bytes[i]);
  }

  return bytes;
}

std::vector<std::byte> TagDouble::valueToBytes() {
  std::vector<std::byte> bytes;

  punDouble val(value);

  for (size_t i = 0; i < sizeof(double); ++i) {
    bytes.push_back(val.bytes[i]);
  }

  return bytes;
}

std::vector<std::byte> TagString::valueToBytes() {
  std::vector<std::byte> bytes;

  pun16 size((uint16_t)value.length());

  for (size_t i = 0; i < sizeof(uint16_t); ++i) {
    bytes.push_back(size.bytes[i]);
  }

  for (size_t i = 0; i < value.length(); ++i) {
    bytes.push_back((std::byte) value.at(i));
  }

  return bytes;
}

std::vector<std::byte> TagByteArray::valueToBytes() {
  std::vector<std::byte> bytes;

  pun32 size((uint32_t)values.size());

  for (size_t i = 0; i < sizeof(uint32_t); ++i) {
    bytes.push_back(size.bytes[i]);
  }

  for (auto value : values) {
    bytes.push_back((std::byte)value);
  }

  return bytes;
}

std::vector<std::byte> TagIntArray::valueToBytes() {
  std::vector<std::byte> bytes;

  pun32 size((uint32_t)values.size());

  for (size_t i = 0; i < sizeof(uint32_t); ++i) {
    bytes.push_back(size.bytes[i]);
  }

  for (auto value : values) {
    pun32 val(value);

    for (size_t i = 0; i < sizeof(uint32_t); ++i) {
      bytes.push_back(val.bytes[i]);
    }
  }

  return bytes;
}

std::vector<std::byte> TagLongArray::valueToBytes() {
  std::vector<std::byte> bytes;

  pun32 size((uint32_t)values.size());

  for (size_t i = 0; i < sizeof(uint32_t); ++i) {
    bytes.push_back(size.bytes[i]);
  }

  for (auto value : values) {
    pun64 val(value);

    for (size_t i = 0; i < sizeof(uint64_t); ++i) {
      bytes.push_back(val.bytes[i]);
    }
  }

  return bytes;
}

std::vector<std::byte> TagList::valueToBytes() {
  std::vector<std::byte> bytes;

  bytes.push_back((std::byte) listType);

  pun32 size((uint32_t)entries.size());

  for (size_t i = 0; i < sizeof(uint32_t); ++i) {
    bytes.push_back(size.bytes[i]);
  }

  for (auto tag : entries) {
    std::vector<std::byte> tagBytes = tag->valueToBytes();
    bytes.insert(bytes.end(), tagBytes.begin(), tagBytes.end());
  }

  return bytes;
}

std::vector<std::byte> TagCompound::valueToBytes() {
  std::vector<std::byte> bytes;

  for (auto tag : tags) {
    std::vector<std::byte> tagBytes = tag->toBytes();
    bytes.insert(bytes.end(), tagBytes.begin(), tagBytes.end());
  }

  return bytes;
}

std::vector<std::byte> NamedTag::toBytes() {
  std::vector<std::byte> bytes;

  bytes.push_back((std::byte) type);

  std::vector<std::byte> nameBytes = nameToBytes();
  bytes.insert(bytes.end(), nameBytes.begin(), nameBytes.end());

  std::vector<std::byte> valueBytes = valueToBytes();
  bytes.insert(bytes.end(), valueBytes.begin(), valueBytes.end());

  // check if tag is a compound and add compound end byte
  if (TagCompound* tag = dynamic_cast<TagCompound*>(this)) {
    bytes.push_back((std::byte)TagType::CompoundEnd);
  }

  return bytes;
};

#pragma endregion
