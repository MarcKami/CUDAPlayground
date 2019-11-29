/*
 * Copyright 2019-2020 Marc Martos.  All rights reserved.
 */
//
//// System includes
//#include <iostream>
//#include <stdio.h>
//#include <assert.h>
//#include <math.h>
//
//// CUDA Runtime
//#include <cuda_runtime.h>
//
//// helper functions and utilities to work with CUDA
//#include <helper_functions.h>
//#include <helper_cuda.h>
//
//// Kernel function to add the elements of two arrays
//__global__
//void add(int n, float* x, float* y) {
//	int index = blockIdx.x * blockDim.x + threadIdx.x;
//	int stride = blockDim.x * gridDim.x;
//	for (int i = index; i < n; i += stride)
//		y[i] = x[i] + y[i];
//}
//
//__global__
//void calcError(int n, float* y, float* err) {
//	int index = blockIdx.x * blockDim.x + threadIdx.x;
//	int stride = blockDim.x * gridDim.x;
//	for (int i = index; i < n; i += stride)
//		*err = fmax(*err, fabs(y[i] - 3.0f));
//}
//
//int main(int argc, char** argv) {
//	const int N = 1 << 20;
//	float* x, * y;
//	float s_x[N], s_y[N];
//
//	// Allocate Unified Memory – accessible from CPU or GPU
//	cudaMallocManaged(&x, N * sizeof(float));
//	cudaMallocManaged(&y, N * sizeof(float));
//
//	// initialize x and y arrays on the host
//	for (int i = 0; i < N; i++) {
//		x[i] = 1.0f;
//		y[i] = 2.0f;
//	}
//	int blockSize = 256;
//	int numBlocks = (N + blockSize - 1) / blockSize;
//	// Run kernel on 1M elements on the GPU
//	//cudaMemcpy(x, s_x, N * sizeof(float), cudaMemcpyHostToDevice);
//	add <<< numBlocks , blockSize >>> (N, x, y);
//	//cudaMemcpy(s_x, x, N * sizeof(float), cudaMemcpyDeviceToHost);
//
//	// Wait for GPU to finish before accessing on host
//	cudaDeviceSynchronize();
//
//	// Check for errors (all values should be 3.0f)
//	float* maxError;
//
//	// Allocate Unified Memory – accessible from CPU or GPU
//	cudaMallocManaged(&maxError, sizeof(float));
//
//	// Run kernel on 1M elements on the GPU
//	calcError <<< 8, 1024 >> > (N, y, maxError);
//
//	// Wait for GPU to finish before accessing on host
//	cudaDeviceSynchronize();
//	
//	std::cout << "Max error: " << *maxError << std::endl;
//
//	// Free memory
//	cudaFree(x);
//	cudaFree(y);
//	cudaFree(maxError);
//
//	return EXIT_SUCCESS;
//}