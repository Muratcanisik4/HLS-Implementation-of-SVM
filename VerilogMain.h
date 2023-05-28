#ifndef VERILOGMAIN_INCLUDE_GUARD_
#define VERILOGMAIN_INCLUDE_GUARD_

#include "ap_int.h"

void VerilogMain(
  ap_uint<16> sw,
  ap_uint<4>* an,
  ap_uint<7>* seg,
  ap_uint<4>* led,
  volatile ap_uint<1>* done,
  ap_uint<14>* imginx
);

#endif
