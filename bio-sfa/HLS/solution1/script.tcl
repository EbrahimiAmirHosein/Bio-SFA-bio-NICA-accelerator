############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project HLS_SampleGn
set_top DLU
add_files HLS_SampleGn/core.cpp
add_files -tb HLS_SampleGn/data_10k.h
add_files -tb HLS_SampleGn/test_core.cpp -cflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7z020-clg400-1} -tool vivado
create_clock -period 10 -name default
config_export -format ip_catalog -rtl vhdl
source "./HLS_SampleGn/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design -O -rtl vhdl -tool xsim
export_design -rtl vhdl -format ip_catalog
