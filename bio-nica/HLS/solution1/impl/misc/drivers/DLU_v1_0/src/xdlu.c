// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xdlu.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XDlu_CfgInitialize(XDlu *InstancePtr, XDlu_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Crtl_bus_BaseAddress = ConfigPtr->Crtl_bus_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XDlu_Start(XDlu *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_AP_CTRL) & 0x80;
    XDlu_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_AP_CTRL, Data | 0x01);
}

u32 XDlu_IsDone(XDlu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XDlu_IsIdle(XDlu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XDlu_IsReady(XDlu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XDlu_EnableAutoRestart(XDlu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDlu_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_AP_CTRL, 0x80);
}

void XDlu_DisableAutoRestart(XDlu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDlu_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_AP_CTRL, 0);
}

u32 XDlu_Get_return(XDlu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_AP_RETURN);
    return Data;
}
void XDlu_InterruptGlobalEnable(XDlu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDlu_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_GIE, 1);
}

void XDlu_InterruptGlobalDisable(XDlu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDlu_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_GIE, 0);
}

void XDlu_InterruptEnable(XDlu *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_IER);
    XDlu_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_IER, Register | Mask);
}

void XDlu_InterruptDisable(XDlu *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_IER);
    XDlu_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_IER, Register & (~Mask));
}

void XDlu_InterruptClear(XDlu *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDlu_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_ISR, Mask);
}

u32 XDlu_InterruptGetEnabled(XDlu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_IER);
}

u32 XDlu_InterruptGetStatus(XDlu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XDlu_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XDLU_CRTL_BUS_ADDR_ISR);
}

