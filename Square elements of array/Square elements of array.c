#include <stdio.h>

//short kernel program
//This is a way that cuda knows this code is a kernel as opposed to the CPU code
//using void function because the kernel doesn't return a value
//instead it writes the output into the pointer specified in its argument list.
//These pointers need to be allocated on the GPU. Without pointer program will crash.
__global__ void square(float *d_out, float *d_in)
{     
    //threadIdx variable built in CUDA, it tell each thread its index within a block
    //threadIdx is a c struct of 3 members x,y and z. It's called a dim3
    // In the first iteration, it return zero and so on till 63.
    int idx = threadIdx.x;
    float f = d_in[idx];
    d_out[idx] = f*f;
    
    
}//end of square kernel



int main(void)
{
    //size of array and determine how many bytes it uses
    const int ARRAY_SIZE = 64;
    const int ARRAY_BYTES = ARRAY_SIZE * sizeof (float);
	
	printf("size of float =%d\n ", sizeof (float) );
	printf("size of ARRAY_BYTES =%d ", ARRAY_BYTES );
	
	//----generate the input array on host----
	//build an array
	float h_in[ARRAY_SIZE];
	//convert each element in array to float
	for (int i = 0; i<ARRAY_SIZE ; i++)
	{
	    h_in[i] = float(i);
	}//end of for loop
	
	float h_out[ARRAY_SIZE];
	
	
	
	
	
	//----declare GPU memory pointers----
	//To declare variable on GPU, you deal with it as pointer
	float * d_in;
	float * d_out;
	
	//----allocate GPU memory----
	cudaMalloc((void **) &d_in, ARRAY_BYTES);
	cudaMalloc((void **) &d_out, ARRAY_BYTES);

	
	//----transfer the array to the GPU----
	//It transfer data from h_in to d_in. The fouth argument say the direction of transfer
	//There are 3 choices: from cude memory host to device, from cude memory device to host and 
	//cude memory device to device
	cudaMemcpy( d_in, h_in, ARRAY_BYTES, cudaMemcpyHostToDevice );

	
	//----Launch the kernel----
	//syntax of program on GPU, parameters between <<< >>>
	
	square<<<1, ARRAY_SIZE>>> (d_out, d_in);
	
	
	//copy back the result array to CPU
	//This code tells CPU to launch on the GPU copies of the kernel on 64 threads
	cudaMemcpy( h_out, d_out, ARRAY_BYTES, cudaMemcpyDeviceToHost );
	
	//print out the resulting array
	for (int  i =0;i<ARRAY_SIZE; i++)
	{
	    printf("%f", h_out[i]);
	    
	}//end of for loop
	
	//free GPU Memory allocation
	cudaFree(d_in);
	cudaFree(d_out);
	return 0;
}//end of main
