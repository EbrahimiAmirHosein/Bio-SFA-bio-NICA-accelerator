#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>
#include <ap_int_base.h>
//#include <stdio.h>
typedef ap_axis<32,2,5,6> intSdCh;
//



typedef union floatToU32{
	float_t dval;
	uint32_t uval;
};
float_t u32_to_float(uint32_t val){
	floatToU32 v;
	v.uval=val;
	return v.dval;
}
uint32_t float_to_u32(float_t val){
	floatToU32 v;
	v.dval=val;
	return v.uval;
}

float_t X[14];
float_t zt[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float_t xt_old[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float_t temp[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float_t yztT[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float_t wxxT[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//initialization
float_t W[14] ={0.12573022, 0.13210486, 0.64042265, 0.10490012, 0.53566937, 0.36159505, 1.30400005, 0.94708096, 0.70373524, 1.26542147, 0.62327446, 0.04132598, 2.32503077, 0.21879166};
float_t M = 1;

float_t lr=100000;
float_t eta=2e-4;
float_t iteration = 1e5;


float_t ybar;
float_t wzt;
float_t Reg;
float_t eta_;
float_t wx ;
float_t y_;
float_t y_yT;
float_t yTy_ ;

int DLU(hls::stream<intSdCh> &inStream, hls::stream<intSdCh> &outStream){

#pragma HLS array_partition variable=zt block factor=14 dim=1
#pragma HLS array_partition variable=xt_old block factor=14 dim=1
#pragma HLS array_partition variable=X block factor=14 dim=1
#pragma HLS array_partition variable=temp block factor=14 dim=1
#pragma HLS array_partition variable=yztT block factor=14 dim=1
#pragma HLS array_partition variable=wxxT block factor=14 dim=1
//#pragma HLS array_partition variable=filter block factor=16 dim=1
//#pragma HLS array_partition variable=out block factor=16

#pragma HLS INTERFACE axis port=outStream
#pragma HLS INTERFACE axis port=inStream
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
/*
 * Instruction set:
 * 0: set block data -> 8bit w1, 8bit h1, 16 bit size1, size1*32 bit data
 * 1: Conv -> 8bit w2,8bit h2, 8bit stride, 8bit padding, size2*32 bit filter
 *
 */


	intSdCh valOut;
	valOut.keep = 0xf;
	valOut.strb = 0xf;
	valOut.user = 0x0;
	valOut.last = 0;
	valOut.id = 0x0;
	valOut.dest = 0x0;

	int i,j;
	int inst=inStream.read().data;
	int rows=inStream.read().data;
	int sr=inStream.read().data;
	if(inst==0){
		for(i=sr;i<sr+rows;i++){
			//ap_uint<32> t= ap_uint<32> (inStream.read().data);
			for(j=0;j<14;j++){
				X[j]=u32_to_float(inStream.read().data);
			}
		//stage1
			Reg = lr / (lr+i);
			eta_ = Reg * eta;
		//stage2
			int c;
			//zt= Xt + xt_old
			for(c=0; c<14; c++){
			#pragma HLS UNROLL
				zt[c]= X[c]+xt_old[c];
				xt_old[c]=X[c];
			}
		//stage3
			//wzt = W[14:1] @ zt[1:14] {MAC}
			for(c=0;c<14;c++){
			#pragma HLS UNROLL
				temp[c]=W[c] * zt[c];
			}
			wzt= temp[0]+temp[1]+temp[2]+temp[3]+
			temp[4]+temp[5]+temp[6]+temp[7]+temp[8]+temp[9]
			+temp[10]+temp[11]+temp[12]+temp[13];
			//ybar = M @ wzt
			ybar = wzt * M;
			//yztT = ybar @ ztT[1:14]{zt transpose)
			for(c=0;c<14;c++){
			#pragma HLS UNROLL
				yztT[c]= ybar * zt[c];
			}
			//wx = W[1:14] @ xt [14:1]  {MAC, in this section X=xt_old}
			for(c=0;c<14;c++){
			#pragma HLS UNROLL
				temp[c]=W[c] * xt_old[c];
			}
			wx= temp[0]+temp[1]+temp[2]+temp[3]+
			temp[4]+temp[5]+temp[6]+temp[7]+temp[8]+temp[9]
			+temp[10]+temp[11]+temp[12]+temp[13];
			//wxxT = wx @ xT
			for(c=0;c<14;c++){
			#pragma HLS UNROLL
				wxxT[c]= wx * X[c];
			}
			//W = W + eta_ * (yztT - wxxT)

			for(c=0;c<14;c++){
			#pragma HLS UNROLL
				W[c]= W[c] + eta_ * (yztT[c] - wxxT[c]);
			}
		//stage4
			// M = M/1-eta_
			M = M / (1-eta_);
			// y_ = M @ ybar
			y_ = M * ybar;
			//y_yT = y_ @ yT {yT is ybar transpose}
			y_yT = y_ * y_;
			//yTy_ = ybar @ y_
			yTy_ = ybar * y_;
			// M = M - ( eta_ / 1 + eta_ yTy_ ) * y_yT
			M = M - ((eta_ / (1 + (eta_ * yTy_))) * y_yT);
		}
		//Print M
		valOut.last = 0;
		valOut.data = float_to_u32(M);
		outStream.write(valOut);
		//Print W
		int c=0;
		for(c=0; c<13; c++){
			valOut.data = float_to_u32(W[c]);
			outStream.write(valOut);
		}
		valOut.last = 1;
		valOut.data = float_to_u32(W[13]);
		outStream.write(valOut);
	}


	return 0;
}


