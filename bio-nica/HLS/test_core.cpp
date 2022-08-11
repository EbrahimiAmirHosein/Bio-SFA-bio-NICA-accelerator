#include <stdio.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

#include "data_(10000).h"


float_t u32_to_float(uint32_t val);
uint32_t float_to_u32(float_t val);


typedef ap_axis<32,2,5,6> intSdCh;

int DLU(hls::stream < intSdCh > & inStream, hls::stream < intSdCh > & outStream) ;

int main(){

	hls::stream<intSdCh> inputStream;
	hls::stream<intSdCh> outputStream;

	int inst=0;
	int rows=10;
	int sr=0;

	intSdCh valIn1;
	valIn1.data = 0;
	valIn1.keep = 1;
	valIn1.strb = 1;
	valIn1.user = 1;
	valIn1.id   = 0;
	valIn1.dest = 0;
	valIn1.last =0;

	valIn1.data = inst;
	inputStream << valIn1;
	valIn1.data = rows;
	inputStream << valIn1;
	valIn1.data = sr;
	inputStream << valIn1;

	for(int i=0;i<rows-1;i++){
		valIn1.data = float_to_u32( array[i][0]);
		inputStream << valIn1;

		valIn1.data =float_to_u32( array[i][1]);
		inputStream << valIn1;

		valIn1.data =float_to_u32( array[i][2]);
		inputStream << valIn1;
	}

	valIn1.data = float_to_u32( array[rows-1][0]);
	inputStream << valIn1;

	valIn1.data =float_to_u32( array[rows-1][1]);
	inputStream << valIn1;

	valIn1.last=1;
	valIn1.data =float_to_u32( array[rows-1][2]);
	inputStream << valIn1;


	int r=DLU(inputStream, outputStream);

	for(int idxOut =0; idxOut<9; idxOut++){
		intSdCh valOut;
		valOut=outputStream.read();
		printf("M[%d]=%f \r\n", idxOut,u32_to_float(valOut.data));
	}
	for(int idxOut =0; idxOut<9; idxOut++){
		intSdCh valOut;
		valOut=outputStream.read();
		printf("W[%d]=%f \r\n", idxOut,u32_to_float(valOut.data));
	}
	return 0;
}
