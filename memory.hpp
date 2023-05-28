#ifndef MEMORY_INCLUDE_GUARD_
#define MEMORY_INCLUDE_GUARD_

#include "ap_int.h"

template<int DATA_WIDTH,int ADDR_WIDTH>
void memory(
  const ap_uint<ADDR_WIDTH>& address0,
  const ap_uint<ADDR_WIDTH>& address1,
  const ap_uint<ADDR_WIDTH>& address2,
  const ap_uint<ADDR_WIDTH>& address3,
  const ap_uint<ADDR_WIDTH>& address4,
  const ap_uint<ADDR_WIDTH>& address5,
  const ap_uint<ADDR_WIDTH>& address6,
  const ap_uint<ADDR_WIDTH>& address7,
  const ap_uint<ADDR_WIDTH>& address8,
  const ap_uint<ADDR_WIDTH>& address9,

  ap_uint<DATA_WIDTH>& data_output0,
  ap_uint<DATA_WIDTH>& data_output1,
  ap_uint<DATA_WIDTH>& data_output2,
  ap_uint<DATA_WIDTH>& data_output3,
  ap_uint<DATA_WIDTH>& data_output4,
  ap_uint<DATA_WIDTH>& data_output5,
  ap_uint<DATA_WIDTH>& data_output6,
  ap_uint<DATA_WIDTH>& data_output7,
  ap_uint<DATA_WIDTH>& data_output8,
  ap_uint<DATA_WIDTH>& data_output9
) {
  static const ap_uint<DATA_WIDTH> ramArr[] = {
#include "memory.txt"
  };

  data_output0 = ramArr[address0];
  data_output1 = ramArr[address1];
  data_output2 = ramArr[address2];
  data_output3 = ramArr[address3];
  data_output4 = ramArr[address4];
  data_output5 = ramArr[address5];
  data_output6 = ramArr[address6];
  data_output7 = ramArr[address7];
  data_output8 = ramArr[address8];
  data_output9 = ramArr[address9];
}

#endif
