#ifndef FP_SIGNED_MULTIPLIER_INCLUDE_GUARD_
#define FP_SIGNED_MULTIPLIER_INCLUDE_GUARD_

#include "ap_int.h"

template<int N, int Q>
void FP_Signed_Multiplier(
  const ap_uint<N>& i_multiplicand,
  const ap_uint<N>& i_multiplier,
  ap_uint<N>& o_result,
  ap_uint<1>& ovr
) {
#pragma HLS INLINE
  ap_uint<2*N> result = i_multiplicand(N-2,0) * i_multiplier(N-2,0);

  ap_uint<N> retVal;
  retVal(N-2,0) = result(N-2+Q,Q);
  retVal(N-1,N-1) = i_multiplicand(N-1,N-1) ^ i_multiplier(N-1,N-1);
  o_result=retVal;

  ap_uint<1> ovrTmp;
  if(result(2*N-2,N-1+Q)>0){
    ovrTmp=1;
  } else {
    ovrTmp=0;
  }
  ovr=ovrTmp;
}

#endif
