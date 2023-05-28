#ifndef HYPERPLANE_INCLUDE_GUARD_
#define HYPERPLANE_INCLUDE_GUARD_

#include "FP_Signed_Multiplier.hpp"
#include "signed_addition.hpp"

template<int ID,int N>
void hyperplane(
  const ap_uint<N>& ramData,
  const ap_uint<N>& svData,
  const ap_uint<16>& index,
  const ap_uint<N>& bias,
  ap_uint<24>& result,
  ap_uint<24>& TRUE_CONT,
  ap_uint<64>& sum
) {
#pragma HLS INLINE

  ap_uint<N> ramDataInt = ramData;
  ap_uint<N> svDataInt = svData;
  ap_uint<N> indexInt = index;
  ap_uint<N> biasInt = bias;
  
  ap_uint<N> o_result;
  ap_uint<1> o_ovr;
  FP_Signed_Multiplier<N,2>(ramDataInt,svDataInt,o_result,o_ovr);

  ap_uint<64> in1;
  ap_uint<64> in2;
  if(indexInt>5){
    in1=o_result;
    in2=sum;
  } else {
    in1=0;
    in2=0;
  }
  signed_addition<0,N>(in1,in2,sum);

  ap_uint<N> biass_added;
  signed_addition<1,N>(in1,biasInt,biass_added);
   
  ap_uint<1> comp_result;
  comparator<N>(biass_added,0,comp_result);
  if(indexInt>7&&indexInt<780){
    if(comp_result==1){
      TRUE_CONT+=1;
    }
  } else if (indexInt>781) {
    result=TRUE_CONT;
  }
}

#endif
