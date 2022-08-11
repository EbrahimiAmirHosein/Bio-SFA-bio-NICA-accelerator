// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2019.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _triangular_invert_HH_
#define _triangular_invert_HH_

#include "systemc.h"
#include "AESL_pkg.h"

#include "axpy_1.h"
#include "scal.h"
#include "DLU_fmul_32ns_32ncud.h"
#include "DLU_fdiv_32ns_32ndEe.h"
#include "DLU_mux_94_32_1_1.h"

namespace ap_rtl {

struct triangular_invert : public sc_module {
    // Port declarations 33
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_in< sc_lv<32> > G_0_i;
    sc_out< sc_lv<32> > G_0_o;
    sc_out< sc_logic > G_0_o_ap_vld;
    sc_in< sc_lv<32> > G_1_i;
    sc_out< sc_lv<32> > G_1_o;
    sc_out< sc_logic > G_1_o_ap_vld;
    sc_in< sc_lv<32> > G_2_i;
    sc_out< sc_lv<32> > G_2_o;
    sc_out< sc_logic > G_2_o_ap_vld;
    sc_in< sc_lv<32> > G_3_i;
    sc_out< sc_lv<32> > G_3_o;
    sc_out< sc_logic > G_3_o_ap_vld;
    sc_in< sc_lv<32> > G_4_i;
    sc_out< sc_lv<32> > G_4_o;
    sc_out< sc_logic > G_4_o_ap_vld;
    sc_in< sc_lv<32> > G_5_i;
    sc_out< sc_lv<32> > G_5_o;
    sc_out< sc_logic > G_5_o_ap_vld;
    sc_in< sc_lv<32> > G_6_i;
    sc_out< sc_lv<32> > G_6_o;
    sc_out< sc_logic > G_6_o_ap_vld;
    sc_in< sc_lv<32> > G_7_i;
    sc_out< sc_lv<32> > G_7_o;
    sc_out< sc_logic > G_7_o_ap_vld;
    sc_in< sc_lv<32> > G_8_i;
    sc_out< sc_lv<32> > G_8_o;
    sc_out< sc_logic > G_8_o_ap_vld;
    sc_signal< sc_logic > ap_var_for_const0;
    sc_signal< sc_lv<32> > ap_var_for_const1;


    // Module declarations
    triangular_invert(sc_module_name name);
    SC_HAS_PROCESS(triangular_invert);

    ~triangular_invert();

    sc_trace_file* mVcdFile;

    axpy_1* grp_axpy_1_fu_109;
    scal* grp_scal_fu_136;
    DLU_fmul_32ns_32ncud<1,4,32,32,32>* DLU_fmul_32ns_32ncud_U85;
    DLU_fdiv_32ns_32ndEe<1,16,32,32,32>* DLU_fdiv_32ns_32ndEe_U86;
    DLU_mux_94_32_1_1<1,1,32,32,32,32,32,32,32,32,32,4,32>* DLU_mux_94_32_1_1_U87;
    DLU_mux_94_32_1_1<1,1,32,32,32,32,32,32,32,32,32,4,32>* DLU_mux_94_32_1_1_U88;
    sc_signal< sc_lv<26> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_lv<32> > zext_ln63_fu_215_p1;
    sc_signal< sc_lv<32> > zext_ln63_reg_433;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_lv<5> > zext_ln63_1_fu_219_p1;
    sc_signal< sc_lv<5> > zext_ln63_1_reg_438;
    sc_signal< sc_lv<4> > zext_ln63_2_fu_223_p1;
    sc_signal< sc_lv<4> > zext_ln63_2_reg_443;
    sc_signal< sc_lv<2> > k_fu_233_p2;
    sc_signal< sc_lv<2> > k_reg_451;
    sc_signal< sc_lv<5> > zext_ln65_fu_247_p1;
    sc_signal< sc_lv<5> > zext_ln65_reg_456;
    sc_signal< sc_lv<1> > icmp_ln63_fu_227_p2;
    sc_signal< sc_lv<32> > grp_fu_167_p2;
    sc_signal< sc_lv<32> > G_8_assign_reg_461;
    sc_signal< sc_logic > ap_CS_fsm_state17;
    sc_signal< sc_lv<5> > sub_ln66_fu_269_p2;
    sc_signal< sc_lv<5> > sub_ln66_reg_466;
    sc_signal< sc_lv<32> > bitcast_ln66_1_fu_282_p1;
    sc_signal< sc_lv<32> > bitcast_ln66_1_reg_471;
    sc_signal< sc_logic > ap_CS_fsm_state18;
    sc_signal< sc_lv<64> > zext_ln66_fu_290_p1;
    sc_signal< sc_lv<64> > zext_ln66_reg_476;
    sc_signal< sc_lv<32> > j_fu_295_p2;
    sc_signal< sc_lv<32> > j_reg_482;
    sc_signal< sc_logic > ap_CS_fsm_state20;
    sc_signal< sc_lv<1> > icmp_ln68_fu_301_p2;
    sc_signal< sc_lv<32> > sub_ln70_fu_312_p2;
    sc_signal< sc_lv<32> > sub_ln70_reg_537;
    sc_signal< sc_logic > ap_CS_fsm_state21;
    sc_signal< sc_lv<4> > add_ln70_fu_322_p2;
    sc_signal< sc_lv<4> > add_ln70_reg_542;
    sc_signal< sc_lv<32> > tmp_fu_327_p11;
    sc_signal< sc_lv<32> > tmp_reg_547;
    sc_signal< sc_lv<32> > tmp_2_fu_355_p11;
    sc_signal< sc_logic > ap_CS_fsm_state23;
    sc_signal< sc_logic > grp_axpy_1_fu_109_ap_start;
    sc_signal< sc_logic > grp_axpy_1_fu_109_ap_done;
    sc_signal< sc_logic > grp_axpy_1_fu_109_ap_idle;
    sc_signal< sc_logic > grp_axpy_1_fu_109_ap_ready;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_0_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_0_o_ap_vld;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_1_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_1_o_ap_vld;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_2_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_2_o_ap_vld;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_3_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_3_o_ap_vld;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_4_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_4_o_ap_vld;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_5_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_5_o_ap_vld;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_6_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_6_o_ap_vld;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_7_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_7_o_ap_vld;
    sc_signal< sc_lv<32> > grp_axpy_1_fu_109_G_8_o;
    sc_signal< sc_logic > grp_axpy_1_fu_109_G_8_o_ap_vld;
    sc_signal< sc_logic > grp_scal_fu_136_ap_start;
    sc_signal< sc_logic > grp_scal_fu_136_ap_done;
    sc_signal< sc_logic > grp_scal_fu_136_ap_idle;
    sc_signal< sc_logic > grp_scal_fu_136_ap_ready;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_0_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_0_o_ap_vld;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_1_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_1_o_ap_vld;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_2_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_2_o_ap_vld;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_3_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_3_o_ap_vld;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_4_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_4_o_ap_vld;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_5_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_5_o_ap_vld;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_6_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_6_o_ap_vld;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_7_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_7_o_ap_vld;
    sc_signal< sc_lv<32> > grp_scal_fu_136_G_8_o;
    sc_signal< sc_logic > grp_scal_fu_136_G_8_o_ap_vld;
    sc_signal< sc_lv<2> > ap_phi_mux_k_0_phi_fu_68_p4;
    sc_signal< sc_lv<2> > k_0_reg_64;
    sc_signal< sc_lv<32> > ap_phi_mux_phi_ln65_phi_fu_79_p6;
    sc_signal< sc_lv<32> > j_0_in_reg_88;
    sc_signal< sc_logic > ap_CS_fsm_state19;
    sc_signal< sc_logic > ap_CS_fsm_state26;
    sc_signal< sc_lv<32> > ap_phi_mux_phi_ln71_phi_fu_100_p6;
    sc_signal< sc_logic > grp_axpy_1_fu_109_ap_start_reg;
    sc_signal< sc_logic > ap_CS_fsm_state22;
    sc_signal< sc_logic > grp_scal_fu_136_ap_start_reg;
    sc_signal< sc_lv<32> > grp_fu_162_p2;
    sc_signal< sc_lv<4> > shl_ln_fu_239_p3;
    sc_signal< sc_lv<32> > bitcast_ln66_fu_273_p1;
    sc_signal< sc_lv<32> > xor_ln66_fu_276_p2;
    sc_signal< sc_lv<32> > sext_ln66_fu_287_p1;
    sc_signal< sc_lv<32> > shl_ln70_fu_307_p2;
    sc_signal< sc_lv<4> > trunc_ln70_fu_318_p1;
    sc_signal< sc_lv<4> > tmp_fu_327_p10;
    sc_signal< sc_lv<26> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<26> ap_ST_fsm_state1;
    static const sc_lv<26> ap_ST_fsm_state2;
    static const sc_lv<26> ap_ST_fsm_state3;
    static const sc_lv<26> ap_ST_fsm_state4;
    static const sc_lv<26> ap_ST_fsm_state5;
    static const sc_lv<26> ap_ST_fsm_state6;
    static const sc_lv<26> ap_ST_fsm_state7;
    static const sc_lv<26> ap_ST_fsm_state8;
    static const sc_lv<26> ap_ST_fsm_state9;
    static const sc_lv<26> ap_ST_fsm_state10;
    static const sc_lv<26> ap_ST_fsm_state11;
    static const sc_lv<26> ap_ST_fsm_state12;
    static const sc_lv<26> ap_ST_fsm_state13;
    static const sc_lv<26> ap_ST_fsm_state14;
    static const sc_lv<26> ap_ST_fsm_state15;
    static const sc_lv<26> ap_ST_fsm_state16;
    static const sc_lv<26> ap_ST_fsm_state17;
    static const sc_lv<26> ap_ST_fsm_state18;
    static const sc_lv<26> ap_ST_fsm_state19;
    static const sc_lv<26> ap_ST_fsm_state20;
    static const sc_lv<26> ap_ST_fsm_state21;
    static const sc_lv<26> ap_ST_fsm_state22;
    static const sc_lv<26> ap_ST_fsm_state23;
    static const sc_lv<26> ap_ST_fsm_state24;
    static const sc_lv<26> ap_ST_fsm_state25;
    static const sc_lv<26> ap_ST_fsm_state26;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<32> ap_const_lv32_10;
    static const sc_lv<32> ap_const_lv32_11;
    static const sc_lv<32> ap_const_lv32_13;
    static const sc_lv<32> ap_const_lv32_14;
    static const sc_lv<32> ap_const_lv32_16;
    static const sc_lv<2> ap_const_lv2_0;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<2> ap_const_lv2_1;
    static const sc_lv<32> ap_const_lv32_12;
    static const sc_lv<32> ap_const_lv32_19;
    static const sc_lv<32> ap_const_lv32_15;
    static const sc_lv<4> ap_const_lv4_7;
    static const sc_lv<4> ap_const_lv4_6;
    static const sc_lv<4> ap_const_lv4_5;
    static const sc_lv<4> ap_const_lv4_4;
    static const sc_lv<4> ap_const_lv4_3;
    static const sc_lv<4> ap_const_lv4_2;
    static const sc_lv<4> ap_const_lv4_1;
    static const sc_lv<4> ap_const_lv4_0;
    static const sc_lv<32> ap_const_lv32_3F800000;
    static const sc_lv<2> ap_const_lv2_3;
    static const sc_lv<32> ap_const_lv32_80000000;
    static const sc_lv<32> ap_const_lv32_2;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_var_for_const0();
    void thread_ap_var_for_const1();
    void thread_ap_clk_no_reset_();
    void thread_G_0_o();
    void thread_G_0_o_ap_vld();
    void thread_G_1_o();
    void thread_G_1_o_ap_vld();
    void thread_G_2_o();
    void thread_G_2_o_ap_vld();
    void thread_G_3_o();
    void thread_G_3_o_ap_vld();
    void thread_G_4_o();
    void thread_G_4_o_ap_vld();
    void thread_G_5_o();
    void thread_G_5_o_ap_vld();
    void thread_G_6_o();
    void thread_G_6_o_ap_vld();
    void thread_G_7_o();
    void thread_G_7_o_ap_vld();
    void thread_G_8_o();
    void thread_G_8_o_ap_vld();
    void thread_add_ln70_fu_322_p2();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state17();
    void thread_ap_CS_fsm_state18();
    void thread_ap_CS_fsm_state19();
    void thread_ap_CS_fsm_state2();
    void thread_ap_CS_fsm_state20();
    void thread_ap_CS_fsm_state21();
    void thread_ap_CS_fsm_state22();
    void thread_ap_CS_fsm_state23();
    void thread_ap_CS_fsm_state26();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_phi_mux_k_0_phi_fu_68_p4();
    void thread_ap_phi_mux_phi_ln65_phi_fu_79_p6();
    void thread_ap_phi_mux_phi_ln71_phi_fu_100_p6();
    void thread_ap_ready();
    void thread_bitcast_ln66_1_fu_282_p1();
    void thread_bitcast_ln66_fu_273_p1();
    void thread_grp_axpy_1_fu_109_ap_start();
    void thread_grp_scal_fu_136_ap_start();
    void thread_icmp_ln63_fu_227_p2();
    void thread_icmp_ln68_fu_301_p2();
    void thread_j_fu_295_p2();
    void thread_k_fu_233_p2();
    void thread_sext_ln66_fu_287_p1();
    void thread_shl_ln70_fu_307_p2();
    void thread_shl_ln_fu_239_p3();
    void thread_sub_ln66_fu_269_p2();
    void thread_sub_ln70_fu_312_p2();
    void thread_tmp_fu_327_p10();
    void thread_trunc_ln70_fu_318_p1();
    void thread_xor_ln66_fu_276_p2();
    void thread_zext_ln63_1_fu_219_p1();
    void thread_zext_ln63_2_fu_223_p1();
    void thread_zext_ln63_fu_215_p1();
    void thread_zext_ln65_fu_247_p1();
    void thread_zext_ln66_fu_290_p1();
    void thread_ap_NS_fsm();
};

}

using namespace ap_rtl;

#endif