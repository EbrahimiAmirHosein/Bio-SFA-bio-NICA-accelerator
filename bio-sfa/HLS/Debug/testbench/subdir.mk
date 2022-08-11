################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test_core.cpp 

OBJS += \
./testbench/test_core.o 

CPP_DEPS += \
./testbench/test_core.d 


# Each subdirectory must supply rules for building sources it contributes
testbench/test_core.o: C:/Users/Mohsen/Desktop/zturn_sg_DMA/Mahsa/HLS_SampleGn/test_core.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -ID:/Xilinx2019/Vivado/2019.1/include -ID:/Xilinx2019/Vivado/2019.1/include/ap_sysc -ID:/Xilinx2019/Vivado/2019.1/win64/tools/auto_cc/include -ID:/Xilinx2019/Vivado/2019.1/win64/tools/systemc/include -IC:/Users/Mohsen/Desktop/zturn_sg_DMA/Mahsa -ID:/Xilinx2019/Vivado/2019.1/include/etc -O0 -g3 -Wall -Wno-unknown-pragmas -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"testbench/test_core.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


