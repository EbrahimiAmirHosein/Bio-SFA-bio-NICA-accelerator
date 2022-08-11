// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XDLU_H
#define XDLU_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xdlu_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Crtl_bus_BaseAddress;
} XDlu_Config;
#endif

typedef struct {
    u32 Crtl_bus_BaseAddress;
    u32 IsReady;
} XDlu;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XDlu_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XDlu_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XDlu_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XDlu_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XDlu_Initialize(XDlu *InstancePtr, u16 DeviceId);
XDlu_Config* XDlu_LookupConfig(u16 DeviceId);
int XDlu_CfgInitialize(XDlu *InstancePtr, XDlu_Config *ConfigPtr);
#else
int XDlu_Initialize(XDlu *InstancePtr, const char* InstanceName);
int XDlu_Release(XDlu *InstancePtr);
#endif

void XDlu_Start(XDlu *InstancePtr);
u32 XDlu_IsDone(XDlu *InstancePtr);
u32 XDlu_IsIdle(XDlu *InstancePtr);
u32 XDlu_IsReady(XDlu *InstancePtr);
void XDlu_EnableAutoRestart(XDlu *InstancePtr);
void XDlu_DisableAutoRestart(XDlu *InstancePtr);
u32 XDlu_Get_return(XDlu *InstancePtr);


void XDlu_InterruptGlobalEnable(XDlu *InstancePtr);
void XDlu_InterruptGlobalDisable(XDlu *InstancePtr);
void XDlu_InterruptEnable(XDlu *InstancePtr, u32 Mask);
void XDlu_InterruptDisable(XDlu *InstancePtr, u32 Mask);
void XDlu_InterruptClear(XDlu *InstancePtr, u32 Mask);
u32 XDlu_InterruptGetEnabled(XDlu *InstancePtr);
u32 XDlu_InterruptGetStatus(XDlu *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
