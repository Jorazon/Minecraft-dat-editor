#include "Types.h"

int16_t littleEndianToShort(const std::byte* _Bytes) {
  uint16_t value =
    ((uint16_t)_Bytes[1] << 8) | (uint16_t)_Bytes[0];
  return *(short*)&value;
}

int32_t littleEndianToInt(const std::byte* _Bytes) {
  uint32_t value =
    ((uint32_t)_Bytes[3] << 24) | ((uint32_t)_Bytes[2] << 16) |
    ((uint32_t)_Bytes[1] << 8) | (uint32_t)_Bytes[0];
  return *(int*)&value;
}

int64_t littleEndianToLong(const std::byte* _Bytes) {
  uint64_t value =
    ((uint64_t)_Bytes[7] << 56) | ((uint64_t)_Bytes[6] << 48) |
    ((uint64_t)_Bytes[5] << 40) | ((uint64_t)_Bytes[4] << 32) |
    ((uint64_t)_Bytes[3] << 24) | ((uint64_t)_Bytes[2] << 16) |
    ((uint64_t)_Bytes[1] << 8) | (uint64_t)_Bytes[0];
  return *(long long*)&value;
}

float littleEndianToFloat(const std::byte* _Bytes) {
  uint32_t value = littleEndianToInt(_Bytes);
  return *(float*)&value;
}

double littleEndianToDouble(const std::byte* _Bytes) {
  uint64_t value = littleEndianToLong(_Bytes);
  return *(double*)&value;
}

std::vector<std::byte> NamedTag::nameToBytes() {
  std::vector<std::byte> bytes;

  bytes.push_back((std::byte)type);

  int16_t size = (int16_t)name.length();
  int16_t length = littleEndianToShort((std::byte*) &size);
  for (size_t i = 0; i < sizeof(int16_t); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  const char* cstr = name.c_str();
  for (size_t i = 0; i < length; ++i) {
    bytes.push_back((std::byte)(cstr[i] & 0xFF));
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

  int16_t length = littleEndianToShort((std::byte*)&value);
  for (size_t i = 0; i < sizeof(int16_t); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  return bytes;
}

std::vector<std::byte> TagInt::valueToBytes() {
  std::vector<std::byte> bytes;

  int32_t length = littleEndianToInt((std::byte*)&value);
  for (size_t i = 0; i < sizeof(int32_t); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  return bytes;
}

std::vector<std::byte> TagLong::valueToBytes() {
  std::vector<std::byte> bytes;

  int64_t length = littleEndianToLong((std::byte*)&value);
  for (size_t i = 0; i < sizeof(int64_t); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  return bytes;
}

std::vector<std::byte> TagFloat::valueToBytes() {
  std::vector<std::byte> bytes;

  int32_t length = littleEndianToInt((std::byte*)&value);
  for (size_t i = 0; i < sizeof(float); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  return bytes;
}

std::vector<std::byte> TagDouble::valueToBytes() {
  std::vector<std::byte> bytes;

  int64_t length = littleEndianToLong((std::byte*)&value);
  for (size_t i = 0; i < sizeof(double); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  return bytes;
}

std::vector<std::byte> TagString::valueToBytes() {
  std::vector<std::byte> bytes;

  const char* cstr = name.c_str();
  for (size_t i = 0; i < value.length(); ++i) {
    bytes.push_back((std::byte)(cstr[i] & 0xFF));
  }

  return bytes;
}

std::vector<std::byte> TagByteArray::valueToBytes() {
  std::vector<std::byte> bytes;

  int32_t size = (int32_t)values.size();
  int32_t length = littleEndianToInt((std::byte*)&size);
  for (size_t i = 0; i < sizeof(int32_t); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  for (auto value : values) {
    bytes.push_back((std::byte)value);
  }

  return bytes;
}

std::vector<std::byte> TagIntArray::valueToBytes() {
  std::vector<std::byte> bytes;

  int32_t size = (int32_t)values.size();
  int32_t length = littleEndianToInt((std::byte*)&size);
  for (size_t i = 0; i < sizeof(int32_t); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  for (auto value : values) {
    int32_t length = littleEndianToInt((std::byte*)&size);
    for (size_t i = 0; i < sizeof(int32_t); ++i) {
      bytes.push_back((std::byte)((&length)[i] & 0xFF));
    }
  }

  return bytes;
}

std::vector<std::byte> TagLongArray::valueToBytes() {
  std::vector<std::byte> bytes;

  int32_t size = (int32_t)values.size();
  int32_t length = littleEndianToInt((std::byte*)&size);
  for (size_t i = 0; i < sizeof(int32_t); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  for (auto value : values) {
    int64_t length = littleEndianToInt((std::byte*)&size);
    for (size_t i = 0; i < sizeof(int64_t); ++i) {
      bytes.push_back((std::byte)((&length)[i] & 0xFF));
    }
  }

  return bytes;
}

std::vector<std::byte> TagList::valueToBytes() {
  std::vector<std::byte> bytes;

  bytes.push_back((std::byte) listType);

  int32_t size = (int32_t)entries.size();
  int32_t length = littleEndianToInt((std::byte*)&size);
  for (size_t i = 0; i < sizeof(int32_t); ++i) {
    bytes.push_back((std::byte)((&length)[i] & 0xFF));
  }

  for (auto tag : entries) {
    std::vector<std::byte> tagBytes = tag->valueToBytes();
    bytes.insert(bytes.end(), tagBytes.begin(), tagBytes.end());
  }

  return bytes;
}

std::vector<std::byte> TagCompound::valueToBytes() {
  std::vector<std::byte> bytes;

  bytes.push_back((std::byte) TagType::CompoundStart);

  for (auto tag : tags) {
    std::vector<std::byte> tagBytes = tag->toBytes();
    bytes.insert(bytes.end(), tagBytes.begin(), tagBytes.end());
  }

  bytes.push_back((std::byte) TagType::CompoundEnd);

  return bytes;
}

std::vector<std::byte> NamedTag::toBytes() {
  std::vector<std::byte> bytes;
  bytes.push_back((std::byte)type);
  std::vector<std::byte> nameBytes = nameToBytes();
  bytes.insert(bytes.end(), nameBytes.begin(), nameBytes.end());
  std::vector<std::byte> valueBytes = valueToBytes();
  bytes.insert(bytes.end(), valueBytes.begin(), valueBytes.end());
  return bytes;
};

std::vector<std::byte> TagCompound::toBytes() {
  std::vector<std::byte> bytes;

  bytes.push_back((std::byte) TagType::CompoundStart);

  std::vector<std::byte> nameBytes = nameToBytes();
  bytes.insert(bytes.end(), nameBytes.begin(), nameBytes.end());
  std::vector<std::byte> valueBytes = valueToBytes();
  bytes.insert(bytes.end(), valueBytes.begin(), valueBytes.end());

  bytes.push_back((std::byte) TagType::CompoundEnd);

  return bytes;
}
