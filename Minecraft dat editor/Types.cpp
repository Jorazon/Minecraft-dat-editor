#include "Types.h"

short littleEndianToShort(const uint8_t* _Bytes) {
  uint16_t value =
    ((uint16_t)_Bytes[1] << 8) | (uint16_t)_Bytes[0];
  return *(short*)&value;
}

int littleEndianToInt(const uint8_t* _Bytes) {
  uint32_t value =
    ((uint32_t)_Bytes[3] << 24) | ((uint32_t)_Bytes[2] << 16) |
    ((uint32_t)_Bytes[1] << 8) | (uint32_t)_Bytes[0];
  return *(int*)&value;
}

long littleEndianToLong(const uint8_t* _Bytes) {
  uint64_t value =
    ((uint64_t)_Bytes[7] << 56) | ((uint64_t)_Bytes[6] << 48) |
    ((uint64_t)_Bytes[5] << 40) | ((uint64_t)_Bytes[4] << 32) |
    ((uint64_t)_Bytes[3] << 24) | ((uint64_t)_Bytes[2] << 16) |
    ((uint64_t)_Bytes[1] << 8) | (uint64_t)_Bytes[0];
  return *(long*)&value;
}

float littleEndianToFloat(const uint8_t* _Bytes) {
  uint32_t value =
    ((uint32_t)_Bytes[3] << 24) | ((uint32_t)_Bytes[2] << 16) |
    ((uint32_t)_Bytes[1] << 8) | (uint32_t)_Bytes[0];
  return *(float*)&value;
}


