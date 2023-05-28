#include "common.h"

ap_uint<32> xorshift(ap_uint<32> state)
{
  ap_uint<32> tmp = state;
  tmp ^= tmp << 13;
  tmp ^= tmp >> 17;
  tmp ^= tmp << 5;
  return tmp;
}
