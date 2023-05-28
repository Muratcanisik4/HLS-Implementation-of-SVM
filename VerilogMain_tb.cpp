#include <iostream>
#include "VerilogMain.h"

int main()
{
  ap_uint<16> sw0;
  ap_uint<4> an;
  ap_uint<7> seg;
  ap_uint<4> led;
  ap_uint<1> done;
  ap_uint<14> imginx;

  sw0=0;
  VerilogMain(sw0,&an,&seg,&led,&done,&imginx);

  std::cout << "sw0: " << sw0.to_string(16).c_str() << ", "
    << "an: " << an.to_string(16).c_str() << ", "
    << "seg: " << seg.to_string(16).c_str() << ", "
    << "led: " << led.to_string(16).c_str() << ", "
    << "imginx: " << imginx.to_string(16).c_str() << '\n';

  sw0=783;
  VerilogMain(sw0,&an,&seg,&led,&done,&imginx);

  std::cout << "sw0: " << sw0.to_string(16).c_str() << ", "
    << "an: " << an.to_string(16).c_str() << ", "
    << "seg: " << seg.to_string(16).c_str() << ", "
    << "led: " << led.to_string(16).c_str() << ", "
    << "imginx: " << imginx.to_string(16).c_str() << '\n';

  for(int count=1; count<20; ++count){
		sw0+=784;
		VerilogMain(sw0,&an,&seg,&led,&done,&imginx);

		std::cout << "sw0: " << sw0.to_string(16).c_str() << ", "
			<< "an: " << an.to_string(16).c_str() << ", "
			<< "seg: " << seg.to_string(16).c_str() << ", "
			<< "led: " << led.to_string(16).c_str() << ", "
			<< "imginx: " << imginx.to_string(16).c_str() << '\n';
  }
}
