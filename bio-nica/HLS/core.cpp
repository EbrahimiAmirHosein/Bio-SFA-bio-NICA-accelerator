#include <hls_stream.h>

#include <ap_axi_sdata.h>

#include <hls_math.h>

#include <ap_int_base.h>

#include <stdio.h>

#include "solve_QP.h"

#define min(x, y)(((x) < (y)) ? (x) : (y))
typedef ap_axis < 32, 2, 5, 6 > intSdCh;

typedef union floatToU32 {
    float_t dval;
    uint32_t uval;
};
float_t u32_to_float(uint32_t val) {
    floatToU32 v;
    v.uval = val;
    return v.dval;
}
uint32_t float_to_u32(float_t val) {
    floatToU32 v;
    v.dval = val;
    return v.uval;
}


float_t X[3];
float_t y[3] = { 0, 0, 0};
float_t X_bar[3] = { 0, 0, 0};
float_t y_bar[3] = { 0, 0, 0};
float_t n_bar[3] = { 0, 0, 0};
float_t W_xt[3] = { 0, 0, 0};
float_t MT_y[3] = { 0, 0, 0};

float_t Outter_1[3] = { 0, 0, 0};
float_t Outter_2[3] = { 0, 0, 0};
float_t Outter_3[3] = { 0, 0, 0};

float_t temp[3][3] = {  { 0, 0, 0 },
						 { 0, 0, 0 },
						 { 0, 0, 0 } };

float_t G[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};

float_t Res_1_outter[3][3];
float_t Res_2_outter[3][3];

//float_t M_T[3][3];
float_t M_MT[3][3];
float_t M_MT_flatt[9];
float_t W_holder[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
float_t M_holder[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};

//initialization
float_t W[3][3] = { { 0.23288604,  0.6519036,  0.7216549},
					 { 0.92344145,  0.08448474, -0.37432369},
					 { 0.30499179, -0.7535808,   0.58231949}};

float_t M[3][3] = { {1.0, 0.0, 0.0},
					 {0.0, 1.0, 0.0},
					 {0.0, 0.0, 1.0}};

float_t eta = 1e-2;
float_t decay = 1e-3;
float_t step = 0;

int DLU(hls::stream < intSdCh > & inStream, hls::stream < intSdCh > & outStream) {
#pragma HLS ARRAY_PARTITION variable=Outter_3 complete dim=1
#pragma HLS ARRAY_PARTITION variable=M_MT complete dim=1
#pragma HLS ARRAY_PARTITION variable=Res_2_outter complete dim=1
#pragma HLS ARRAY_PARTITION variable=Outter_1 complete dim=1
#pragma HLS ARRAY_PARTITION variable=M_holder complete dim=1
#pragma HLS ARRAY_PARTITION variable=W_holder complete dim=1
#pragma HLS ARRAY_PARTITION variable=M_MT complete dim=1
#pragma HLS ARRAY_PARTITION variable=Res_1_outter complete dim=1
#pragma HLS ARRAY_PARTITION variable=Outter_2 complete dim=1
#pragma HLS ARRAY_PARTITION variable=MT_y complete dim=1
#pragma HLS ARRAY_PARTITION variable=W_xt complete dim=1
#pragma HLS ARRAY_PARTITION variable=n_bar complete dim=1
#pragma HLS ARRAY_PARTITION variable=y_bar complete dim=1
#pragma HLS ARRAY_PARTITION variable=X_bar complete dim=1
#pragma HLS ARRAY_PARTITION variable=temp complete dim=1
#pragma HLS ARRAY_PARTITION variable=M complete dim=1
#pragma HLS ARRAY_PARTITION variable=W complete dim=1
#pragma HLS ARRAY_PARTITION variable=X complete dim=1
#pragma HLS ARRAY_PARTITION variable=G complete dim=1

	#pragma HLS INTERFACE axis port=outStream
	#pragma HLS INTERFACE axis port=inStream
	#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS

    intSdCh valOut;
    valOut.keep = 0xf;
    valOut.strb = 0xf;
    valOut.user = 0x0;
    valOut.last = 0;
    valOut.id = 0x0;
    valOut.dest = 0x0;

    int i, j;
    int inst = inStream.read().data;
    int rows = inStream.read().data;
    int sr = inStream.read().data;
    //if (inst == 0) {
        for (i = sr; i < sr + rows; i++) {
            //ap_uint<32> t= ap_uint<32> (inStream.read().data);
            for (j = 0; j < 3; j++) {
                X[j] = u32_to_float(inStream.read().data);
                //printf("read date:...X[%d][%d]\r\n",i,j);
            }

            //stage1
            //printf("stage1\n");
            int c, c2, c3;
            //wxt= w @ xt
            for(c2=0; c2<3;c2++){
			#pragma HLS UNROLL
				for(c3=0; c3<3;c3++){
				#pragma HLS UNROLL
					temp[c2][c3]= W[c2][c3] * X[c3];
				}
            }
            W_xt[0] = temp[0][0] + temp[0][1] + temp[0][2];
            W_xt[1] = temp[1][0] + temp[1][1] + temp[1][2];
            W_xt[2] = temp[2][0] + temp[2][1] + temp[2][2];

            //stage2
            //printf("stage2\n");
            // calculate M transpose
            // calculate M_MT = M @ M_T
            for(c2=0; c2<3;c2++){
			#pragma HLS UNROLL
				for(c3=0; c3<3;c3++){
				#pragma HLS UNROLL
					temp[c2][c3]= M[0][c3] * M[c2][c3];
				}
            }
            M_MT[0][0]=temp[0][0]+temp[0][1]+temp[0][2];
            M_MT[0][1]=temp[1][0]+temp[1][1]+temp[1][2];
            M_MT[0][2]=temp[2][0]+temp[2][1]+temp[2][2];

            for(c2=0; c2<3;c2++){
			#pragma HLS UNROLL
				for(c3=0; c3<3;c3++){
				#pragma HLS UNROLL
					temp[c2][c3]= M[1][c3] * M[c2][c3];
				}
            }
            M_MT[1][0]=temp[0][0]+temp[0][1]+temp[0][2];
            M_MT[1][1]=temp[1][0]+temp[1][1]+temp[1][2];
            M_MT[1][2]=temp[2][0]+temp[2][1]+temp[2][2];

            for(c2=0; c2<3;c2++){
			#pragma HLS UNROLL
				for(c3=0; c3<3;c3++){
				#pragma HLS UNROLL
					temp[c2][c3]= M[2][c3] * M[c2][c3];
				}
            }
            M_MT[2][0]=temp[0][0]+temp[0][1]+temp[0][2];
            M_MT[2][1]=temp[1][0]+temp[1][1]+temp[1][2];
            M_MT[2][2]=temp[2][0]+temp[2][1]+temp[2][2];
            
            G[0] = M_MT[0][0];
            G[1] = M_MT[0][1];
            G[2] = M_MT[0][2];
            G[3] = M_MT[1][0];
            G[4] = M_MT[1][1];
            G[5] = M_MT[1][2];
            G[6] = M_MT[2][0];
            G[7] = M_MT[2][1];
            G[8] = M_MT[2][2];

            int stat = solve_qp(G, W_xt, y);

            //stage3
            //printf("stage3\n");
            // calculate y from qp_solver and MT_y = M_T @ y
            for(c2=0; c2<3;c2++){
			#pragma HLS UNROLL
				for(c3=0; c3<3;c3++){
				#pragma HLS UNROLL
					temp[c2][c3]= M[c3][c2] * y[c3];
				}
            }

            MT_y[0] = temp[0][0] + temp[0][1] + temp[0][2];
            MT_y[1] = temp[1][0] + temp[1][1] + temp[1][2];
            MT_y[2] = temp[2][0] + temp[2][1] + temp[2][2];
//---------------->
            //stage4
            //printf("stage4\n");

            int I = i+1;
            int minimum = min(i + 1, 100);

            X_bar[0] += (X[0] - X_bar[0]) / I;
            X_bar[1] += (X[1] - X_bar[1]) / I;
            X_bar[2] += (X[2] - X_bar[2]) / I;

            y_bar[0] += (y[0] - y_bar[0]) / minimum;
            y_bar[1] += (y[1] - y_bar[1]) / minimum;
            y_bar[2] += (y[2] - y_bar[2]) / minimum;

            n_bar[0] += (MT_y[0] - n_bar[0]) / minimum;
            n_bar[1] += (MT_y[1] - n_bar[1]) / minimum;
            n_bar[2] += (MT_y[2] - n_bar[2]) / minimum;

            //stage5
            //printf("stage5\n");
            //call step = eta / (1 + decay * i)
            step = (eta) / (1 + decay * i);

            //stage6
            //printf("stage6\n");
            // for calculating outer products
            for (c = 0; c < 3; c++) {
                Outter_1[c] = y[c] - y_bar[c];
                Outter_2[c] = X[c] - X_bar[c];
                Outter_3[c] = MT_y[c] - n_bar[c];
            }
            //res1_outer --> 3x3 matrix     np.outer(outer1 , outer2)
            //res2_outer --> 3x3 matrix     np.outer(outer1 , outer3)
            Res_1_outter[0][0]= Outter_1[0] * Outter_2[0];
            Res_1_outter[0][1]= Outter_1[0] * Outter_2[1];
            Res_1_outter[0][2]= Outter_1[0] * Outter_2[2];

            Res_1_outter[1][0]= Outter_1[1] * Outter_2[0];
            Res_1_outter[1][1]= Outter_1[1] * Outter_2[1];
            Res_1_outter[1][2]= Outter_1[1] * Outter_2[2];

            Res_1_outter[2][0]= Outter_1[2] * Outter_2[0];
            Res_1_outter[2][1]= Outter_1[2] * Outter_2[1];
            Res_1_outter[2][2]= Outter_1[2] * Outter_2[2];
            //////////////////////
            Res_2_outter[0][0]= Outter_1[0] * Outter_3[0];
            Res_2_outter[0][1]= Outter_1[0] * Outter_3[1];
            Res_2_outter[0][2]= Outter_1[0] * Outter_3[2];

            Res_2_outter[1][0]= Outter_1[1] * Outter_3[0];
            Res_2_outter[1][1]= Outter_1[1] * Outter_3[1];
            Res_2_outter[1][2]= Outter_1[1] * Outter_3[2];

            Res_2_outter[2][0]= Outter_1[2] * Outter_3[0];
            Res_2_outter[2][1]= Outter_1[2] * Outter_3[1];
            Res_2_outter[2][2]= Outter_1[2] * Outter_3[2];

            // Updating W and M

            W[0][0] += step * (Res_1_outter[0][0] - W[0][0]);
            W[0][1] += step * (Res_1_outter[0][1] - W[0][1]);
            W[0][2] += step * (Res_1_outter[0][2] - W[0][2]);

            W[1][0] += step * (Res_1_outter[1][0] - W[1][0]);
            W[1][1] += step * (Res_1_outter[1][1] - W[1][1]);
            W[1][2] += step * (Res_1_outter[1][2] - W[1][2]);

            W[2][0] += step * (Res_1_outter[2][0] - W[2][0]);
            W[2][1] += step * (Res_1_outter[2][1] - W[2][1]);
            W[2][2] += step * (Res_1_outter[2][2] - W[2][2]);
            ////////////////
            M[0][0] += step * (Res_2_outter[0][0] - M[0][0]);
            M[0][1] += step * (Res_2_outter[0][1] - M[0][1]);
            M[0][2] += step * (Res_2_outter[0][2] - M[0][2]);

            M[1][0] += step * (Res_2_outter[1][0] - M[1][0]);
            M[1][1] += step * (Res_2_outter[1][1] - M[1][1]);
            M[1][2] += step * (Res_2_outter[1][2] - M[1][2]);

            M[2][0] += step * (Res_2_outter[2][0] - M[2][0]);
            M[2][1] += step * (Res_2_outter[2][1] - M[2][1]);
            M[2][2] += step * (Res_2_outter[2][2] - M[2][2]);

        }
        W_holder[0] = W[0][0];
        W_holder[1] = W[0][1];
        W_holder[2] = W[0][2];
        W_holder[3] = W[1][0];
        W_holder[4] = W[1][1];
        W_holder[5] = W[1][2];
        W_holder[6] = W[2][0];
        W_holder[7] = W[2][1];
        W_holder[8] = W[2][2];

        M_holder[0] = M[0][0];
        M_holder[1] = M[0][1];
        M_holder[2] = M[0][2];
        M_holder[3] = M[1][0];
        M_holder[4] = M[1][1];
        M_holder[5] = M[1][2];
        M_holder[6] = M[2][0];
        M_holder[7] = M[2][1];
        M_holder[8] = M[2][2];

        //Print M
        //printf("Print M\n");
        int c;
        for (c = 0; c < 9; c++) {

            valOut.data = float_to_u32((float_t)M_holder[c]);
            outStream.write(valOut);

        }

        //Print W
        ////printf("Print W\n");
        for (c = 0; c < 8; c++) {

            valOut.data = float_to_u32((float_t)W_holder[c]);
            outStream.write(valOut);

        }
        valOut.last = 1;
        valOut.data = float_to_u32((float_t)W_holder[8]);
        outStream.write(valOut);
        return 0;
    //}

    //return 0;
}
