#ifndef TEST_DATA_INCLUDE_GUARD_
#define TEST_DATA_INCLUDE_GUARD_

#include "ap_int.h"

template<int A,int N>
void test_data(
  const ap_uint<A>& address,
  ap_uint<N>& data_out
) {
  static const ap_uint<N> lutArr[] = {
#include "test_data.txt"
  };

  static ap_uint<N> lutOut = 0;
  lutOut = lutArr[address];
  data_out = lutOut;
}

#endif
