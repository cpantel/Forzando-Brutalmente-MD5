#include <cuda.h>
#include <cuda_runtime_api.h>
#include <stdio.h>
#include <driver_types.h>



struct device_stats {
	unsigned char word[64];			// found word passed from GPU
	int hash_found;			// boolean if word is found
};

struct cuda_device {
	int device_id;
	struct cudaDeviceProp prop;

	int max_threads;
	int max_blocks;
	int shared_memory;

	void *device_global_memory;
	int device_global_memory_len;

	void *host_memory;

	void *device_stats_memory;
	struct device_stats stats;

	unsigned int target_hash[4];

	// to be used for debugging
	void *device_debug_memory;
};



#define FUNCTION_PARAM_ALLOC 256
#define REQUIRED_SHARED_MEMORY 64


int get_cuda_device(struct cuda_device *device) {
        int device_count;

        if (cudaGetDeviceCount(&device_count) != CUDA_SUCCESS) {
                // cuda not supported
                return -1;
        }


        printf("Device count             : %d\n", device_count);
       
        while(device_count >= 0) {
                if (cudaGetDeviceProperties(&device->prop, device_count) == CUDA_SUCCESS) {
                        // we have found our device
                        device->device_id = device_count;
                        return device_count;
                }

                device_count--;
        }

        return -1;
}



int calculate_cuda_params(struct cuda_device *device) {
        int max_threads;
        int max_blocks;
        int shared_memory;

        max_threads = device->prop.maxThreadsPerBlock;
        shared_memory = device->prop.sharedMemPerBlock - FUNCTION_PARAM_ALLOC;
        
        // calculate the most threads that we can support optimally
        
        while ((shared_memory / max_threads) < REQUIRED_SHARED_MEMORY) { max_threads--; } 

        // now we spread our threads across blocks 
        
        max_blocks = 40;                // ?? we need to calculate this !

        device->max_threads = max_threads;              // most threads we support
        device->max_blocks = max_blocks;                // most blocks we support
        device->shared_memory = shared_memory;          // shared memory required

        // now we need to have (device.max_threads * device.max_blocks) number of words in memory for the graphics card
        
        device->device_global_memory_len = (device->max_threads * device->max_blocks) * 64;

        return 1;
}



int main(int argc, char* argv[]) {

        struct cuda_device device;
        int devCount = get_cuda_device(&device);
        if (devCount == -1) {
                printf("No Cuda Device Installed\n");
                return -1;
        }

        // we now need to calculate the optimal amount of threads to use for this card

        printf("name                     : %s\n", device.prop.name);

        printf("clockRate                : %d\n", device.prop.clockRate);

        printf("compute capability       : %d.%d\n", device.prop.major, device.prop.minor);
        
        printf("compute mode             : %d\n", device.prop.computeMode);
        printf("discrete?                : %d\n\n", device.prop.integrated);

        printf("max global mem           : %ld\n", device.prop.totalGlobalMem);
        printf("max const  mem           : %ld\n", device.prop.totalConstMem);

        printf("multiProcessorCount      : %d\n", device.prop.multiProcessorCount);

        printf("regsPerBlock             : %d\n", device.prop.regsPerBlock);
        printf("regsPerMultiprocessor    : %d\n", device.prop.regsPerMultiprocessor);
        printf("kernelExecTimeoutEnabled : %d\n", device.prop.kernelExecTimeoutEnabled);
        printf("isMultiGpuBoard          : %d\n", device.prop.isMultiGpuBoard);
        printf("concurrentKernels        : %d\n", device.prop.concurrentKernels);
        printf("maxThreadsPerBlock       : %d\n", device.prop.maxThreadsPerBlock);

     
        printf("threads in a warp        : %d\n", device.prop.warpSize);

        printf("max thread dimensions:   : %d, %d, %d\n", device.prop.maxThreadsDim[0], device.prop.maxThreadsDim[1], device.prop.maxThreadsDim[2]);
        printf("max grid size            : %d, %d, %d\n", device.prop.maxGridSize[0], device.prop.maxGridSize[1], device.prop.maxGridSize[2]);


//        printf(": %d\n", device.prop.);
        
        calculate_cuda_params(&device);

    return 0;

}

