// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __DLU_fptrunc_64ns_hbi__HH__
#define __DLU_fptrunc_64ns_hbi__HH__
#include "ACMP_fptrunc.h"
#include <systemc>

template<
    int ID,
    int NUM_STAGE,
    int din0_WIDTH,
    int dout_WIDTH>
SC_MODULE(DLU_fptrunc_64ns_hbi) {
    sc_core::sc_in_clk clk;
    sc_core::sc_in<sc_dt::sc_logic> reset;
    sc_core::sc_in<sc_dt::sc_logic> ce;
    sc_core::sc_in< sc_dt::sc_lv<din0_WIDTH> >   din0;
    sc_core::sc_out< sc_dt::sc_lv<dout_WIDTH> >   dout;



    ACMP_fptrunc<ID, 2, din0_WIDTH, dout_WIDTH> ACMP_fptrunc_U;

    SC_CTOR(DLU_fptrunc_64ns_hbi):  ACMP_fptrunc_U ("ACMP_fptrunc_U") {
        ACMP_fptrunc_U.clk(clk);
        ACMP_fptrunc_U.reset(reset);
        ACMP_fptrunc_U.ce(ce);
        ACMP_fptrunc_U.din0(din0);
        ACMP_fptrunc_U.dout(dout);

    }

};

#endif //
