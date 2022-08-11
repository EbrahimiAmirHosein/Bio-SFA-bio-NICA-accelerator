################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../core.cpp 

OBJS += \
./source/core.o 

CPP_DEPS += \
./source/core.d 


# Each subdirectory must supply rules for building sources it contributes
source/core.o: C:/Users/Mohsen/Desktop/zturn_sg_DMA/Mahsa/HLS_SampleGn/core.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -ID:/Xilinx2019/Vivado/2019.1/include -ID:/Xilinx2019/Vivado/2019.1/include/ap_sysc -ID:/Xilinx2019/Vivado/2019.1/win64/tools/auto_cc/include -ID:/Xilinx2019/Vivado/2019.1/win64/tools/systemc/include -IC:/Users/Mohsen/Desktop/zturn_sg_DMA/Mahsa -ID:/Xilinx2019/Vivado/2019.1/include/etc -IC:/Users/Mohsen/Desktop/zturn_sg_DMA -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


