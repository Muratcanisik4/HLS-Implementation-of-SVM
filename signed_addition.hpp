#ifndef SIGNED_ADDITION_INCLUDE_GUARD_
#define SIGNED_ADDITION_INCLUDE_GUARD_

template<int ID,int N>
void signed_addition(
  const ap_uint<N>& a,
  const ap_uint<N>& b,
  ap_uint<N>& sum
) {
#pragma HLS INLINE
  ap_uint<N-1> mag_a, mag_b, max, min;
  ap_uint<1> sign_a, sign_b, sign;

  mag_a(N-2,0) = a(N-2,0);
  mag_b(N-2,0) = b(N-2,0);
  sign_a = a(N-1,N-1);
  sign_b = b(N-1,N-1);

  if(mag_a>mag_b) {
    max=mag_a; 
    min=mag_b;
    sign=sign_a;
  } else {
    max=mag_b;
    min=mag_a; 
    sign=sign_b;
  }
  
  ap_uint<N> sumTmp;
  if(sign_a==sign_b){
    sumTmp(N-2,0)=max+min;
  } else {
    sumTmp(N-2,0)=max-min;
  }
  sumTmp(N-1,N-1)=sign;
  sum=sumTmp;
}

template<int N>
void comparator(
  const ap_uint<N>& A,
  const ap_uint<N>& B,
  ap_uint<1>& A_greater_or_equals_zero
) {
#pragma HLS INLINE
  ap_uint<1> tmp;
  if(A(N-1,N-1)==0){
    tmp=1;
  } else {
    tmp=0;
  }
  A_greater_or_equals_zero=tmp;
}

#endif
