############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project HLS_BIO_NICA
set_top DLU
add_files HLS_BIO_NICA/solve_QP.h
add_files HLS_BIO_NICA/core.cpp
add_files -tb HLS_BIO_NICA/test_core.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb HLS_BIO_NICA/data_(10000).h -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7z020clg400-1}
create_clock -period 10 -name default
config_export -format ip_catalog -rtl vhdl -vivado_optimization_level 2 -vivado_phys_opt place -vivado_report_level 0
config_sdx -optimization_level none -target none
#source "./HLS_BIO_NICA/solution1/directives.tcl"
csim_design -O
csynth_design
cosim_design -O -rtl vhdl -tool xsim
export_design -rtl vhdl -format ip_catalog
