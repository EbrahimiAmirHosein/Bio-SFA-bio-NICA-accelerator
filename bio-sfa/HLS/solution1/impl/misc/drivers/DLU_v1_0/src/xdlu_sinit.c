// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xdlu.h"

extern XDlu_Config XDlu_ConfigTable[];

XDlu_Config *XDlu_LookupConfig(u16 DeviceId) {
	XDlu_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XDLU_NUM_INSTANCES; Index++) {
		if (XDlu_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XDlu_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XDlu_Initialize(XDlu *InstancePtr, u16 DeviceId) {
	XDlu_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XDlu_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XDlu_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

