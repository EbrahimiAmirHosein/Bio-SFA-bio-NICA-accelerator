// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// CRTL_BUS
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of ap_return
//        bit 31~0 - ap_return[31:0] (Read)
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XDLU_CRTL_BUS_ADDR_AP_CTRL   0x00
#define XDLU_CRTL_BUS_ADDR_GIE       0x04
#define XDLU_CRTL_BUS_ADDR_IER       0x08
#define XDLU_CRTL_BUS_ADDR_ISR       0x0c
#define XDLU_CRTL_BUS_ADDR_AP_RETURN 0x10
#define XDLU_CRTL_BUS_BITS_AP_RETURN 32

