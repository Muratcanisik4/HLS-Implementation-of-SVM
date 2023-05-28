#include "hyperplane.hpp"
#include "test_data.hpp"
#include "memory.hpp"

static ap_uint<4> get_index(const ap_uint<24>* result)
{
#pragma HLS INLINE
  ap_uint<24> max=0;
  ap_uint<4> index=0;

  max_loop: for(int J=0; J<10; ++J){
#pragma HLS PIPELINE
    if(result[J]>max){
      max=result[J];
      index=J;
    }
  }
  return index;
}

static ap_uint<7> sseg_display(const ap_uint<4>& hex)
{
#pragma HLS INLINE
  switch(hex){
		case 0: return 0b1000000;
		case 1: return 0b1111001;
		case 2: return 0b0100100;
		case 3: return 0b0110000;
		case 4: return 0b0011001;
		case 5: return 0b0010010;
		case 6: return 0b0000010;
		case 7: return 0b1111000;
		case 8: return 0b0000000;
		case 9: return 0b0010000;
		case 10: return 0b0001000;
		case 11: return 0b0000011;
		case 12: return 0b1000110;
		case 13: return 0b0100001;
		case 14: return 0b0000110;
		default : return 0b0001110; // 15
  }
}

#if 1
void VerilogMain(
  ap_uint<16> sw,
  ap_uint<4>* an,
  ap_uint<7>* seg,
  ap_uint<4>* led,
  volatile ap_uint<1>* done,
  ap_uint<14>* imginx
) {
  ap_uint<14> test_image_index = sw;
  ap_uint<14> test_image_index_end = test_image_index+783;
  ap_uint<14> test_image_index_begin = test_image_index;
  ap_uint<16> td_adress = test_image_index_begin;

  ap_uint<64> svDataHP[10] = {0,0,0,0,0,0,0,0,0,0};
  ap_uint<64> testDataHP = 0;


  static const ap_uint<64> bias[] = {
	  0b0000000000000000000001101101000111100100110010111011110011111111,
	  0b0000000000000000000001111000011001001001101011011001101010010101,
	  0b0000000000000000000001101110110111010000110100000101100010010011,
	  0b0000000000000000000001101100111111000000001001010010100010010000,
	  0b0000000000000000000001101010000010000001010101111011010100101110,
	  0b0000000000000000000001011100111000001101011001110011001100001011,
	  0b0000000000000000000001100110110011110111001100001110111010011001,
	  0b0000000000000000000001101111111011111110010111100001101100010110,
	  0b0000000000000000000001100110111100011101000011110110100100111010,
	  0b0000000000000000000001101011110001101011111110101101010111110010
  };

  ap_uint<14> mem_rd_add[10] = {0,783,1567,2351,3135,3919,4703,5487,6271,7055};
  ap_uint<64> data_output[10];

  *done=0;

  ap_uint<17> count[10];
#pragma HLS ARRAY_PARTITION variable=count complete

  ap_uint<24> result[10];
#pragma HLS ARRAY_PARTITION variable=result complete

	ap_uint<24> true_cont[10];
#pragma HLS ARRAY_PARTITION variable=true_cont complete

  ap_uint<64> sum[10];
#pragma HLS ARRAY_PARTITION variable=sum complete

	init_true_cont_loop: for(int J=0; J<10; ++J){
#pragma HLS PIPELINE
		true_cont[J]=0;
    sum[J]=0;
    count[J]=0;
	}

  main_loop: for(ap_uint<14> address=test_image_index_begin; address<test_image_index_end; ++address){
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=783 max=783
    ap_uint<64> td_data_temp;
    test_data<16,64>(td_adress,td_data_temp);
    ap_uint<64> test_data = td_data_temp;

    hyperplane<0,64>(test_data,svDataHP[0],count[0],bias[0],result[0],true_cont[0],sum[0]);
    hyperplane<1,64>(testDataHP,svDataHP[1],count[1],bias[1],result[1],true_cont[1],sum[1]);
    hyperplane<2,64>(testDataHP,svDataHP[2],count[2],bias[2],result[2],true_cont[2],sum[2]);
    hyperplane<3,64>(testDataHP,svDataHP[3],count[3],bias[3],result[3],true_cont[3],sum[3]);
    hyperplane<4,64>(testDataHP,svDataHP[4],count[4],bias[4],result[4],true_cont[4],sum[4]);
    hyperplane<5,64>(testDataHP,svDataHP[5],count[5],bias[5],result[5],true_cont[5],sum[5]);
    hyperplane<6,64>(testDataHP,svDataHP[6],count[6],bias[6],result[6],true_cont[6],sum[6]);
    hyperplane<7,64>(testDataHP,svDataHP[7],count[7],bias[7],result[7],true_cont[7],sum[7]);
    hyperplane<8,64>(testDataHP,svDataHP[8],count[8],bias[8],result[8],true_cont[8],sum[8]);
    hyperplane<9,64>(testDataHP,svDataHP[9],count[9],bias[9],result[9],true_cont[9],sum[9]);

    memory<64,14>(mem_rd_add[0],mem_rd_add[1],mem_rd_add[2],mem_rd_add[3],mem_rd_add[4],
      mem_rd_add[5],mem_rd_add[6],mem_rd_add[7],mem_rd_add[8],mem_rd_add[9],
      data_output[0],data_output[1],data_output[2],data_output[3],data_output[4],
      data_output[5],data_output[6],data_output[7],data_output[8],data_output[9]);
 
    testDataHP=td_data_temp;

    mem_next_loop: for(int J=0; J<10; ++J){
			svDataHP[J]=data_output[J];
			++mem_rd_add[J];
			++count[J];
    }

    ++td_adress;
  }

	*an=0;
  *imginx=test_image_index;
   
  ap_uint<4> index = get_index(result);
  *led=index;

  ap_uint<7> seg_ = sseg_display(index);
  *seg=seg_;

  *done = 1;
}
#endif
