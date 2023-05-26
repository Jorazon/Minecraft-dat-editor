#pragma once
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

enum class TagType : int8_t {
  Invalid = -1,
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

short littleEndianToShort(const uint8_t* _Bytes);
int littleEndianToInt(const uint8_t* _Bytes);
long littleEndianToLong(const uint8_t* _Bytes);
float littleEndianToFloat(const uint8_t* _Bytes);
