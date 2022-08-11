// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __DLU_W_H__
#define __DLU_W_H__


#include <systemc>
using namespace sc_core;
using namespace sc_dt;




#include <iostream>
#include <fstream>

struct DLU_W_ram : public sc_core::sc_module {

  static const unsigned DataWidth = 32;
  static const unsigned AddressRange = 14;
  static const unsigned AddressWidth = 4;

//latency = 1
//input_reg = 1
//output_reg = 0
sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in <sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> we0;
sc_core::sc_in<sc_lv<DataWidth> > d0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


sc_lv<DataWidth> ram[AddressRange];


   SC_CTOR(DLU_W_ram) {
        ram[0] = "0b00111110000000001011111101101100";
        ram[1] = "0b00111110000001110100011001111111";
        ram[2] = "0b00111111001000111111001010111101";
        ram[3] = "0b00111101110101101101010111100000";
        ram[4] = "0b00111111000010010010000110100001";
        ram[5] = "0b00111110101110010010001011111101";
        ram[6] = "0b00111111101001101110100101111001";
        ram[7] = "0b00111111011100100111001111100110";
        ram[8] = "0b00111111001101000010011111111110";
        ram[9] = "0b00111111101000011111100101010101";
        ram[10] = "0b00111111000111111000111011101010";
        ram[11] = "0b00111101001010010100010101101110";
        ram[12] = "0b01000000000101001100110101001110";
        ram[13] = "0b00111110011000000000101011101100";


SC_METHOD(prc_write_0);
  sensitive<<clk.pos();
   }


void prc_write_0()
{
    if (ce0.read() == sc_dt::Log_1) 
    {
        if (we0.read() == sc_dt::Log_1) 
        {
           if(address0.read().is_01() && address0.read().to_uint()<AddressRange)
           {
              ram[address0.read().to_uint()] = d0.read(); 
              q0 = d0.read();
           }
           else
              q0 = sc_lv<DataWidth>();
        }
        else {
            if(address0.read().is_01() && address0.read().to_uint()<AddressRange)
              q0 = ram[address0.read().to_uint()];
            else
              q0 = sc_lv<DataWidth>();
        }
    }
}


}; //endmodule


SC_MODULE(DLU_W) {


static const unsigned DataWidth = 32;
static const unsigned AddressRange = 14;
static const unsigned AddressWidth = 4;

sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in<sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> we0;
sc_core::sc_in<sc_lv<DataWidth> > d0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


DLU_W_ram* meminst;


SC_CTOR(DLU_W) {
meminst = new DLU_W_ram("DLU_W_ram");
meminst->address0(address0);
meminst->ce0(ce0);
meminst->q0(q0);
meminst->we0(we0);
meminst->d0(d0);


meminst->reset(reset);
meminst->clk(clk);
}
~DLU_W() {
    delete meminst;
}


};//endmodule
#endif
