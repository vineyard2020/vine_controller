/*
 * Copyright 2018 Foundation for Research and Technology - Hellas
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0 [1] [1]
 *
 * Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *  implied.
 * See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * Links:
 *  ------
 * [1] http://www.apache.org/licenses/LICENSE-2.0 [1]
*/
#ifndef VINE_LIB_OPENCL_UTILS_HEADER
#define VINE_LIB_OPENCL_UTILS_HEADER

#include "VineLibMgr.h"
#include "vine_pipe.h"
#include <CL/cl2.hpp>
#include <vector>
#ifdef LIBRARY_BUILD

// Here put the GetOpenCLKernel from a string



extern bool Host2OpenCL(vine_task_msg_s *vine_task, std::vector<void *> &ioHD);

/* Cuda Memcpy from Device to host*/
extern bool OpenCL2Host(vine_task_msg_s *vine_task, std::vector<void *> &ioDH);

/* Free Device memory */
extern bool OpenCLMemFree(std::vector<void *> &io);

/* Get the kernel object from a kernel function name.*/
extern cl::Kernel OpenCLGetKernel(std::string name);


cl::Platform getDefaultPlatform();
cl::Device getDefaultDevice();
cl::Context getDefaultContext();
cl::CommandQueue getDefaultCommandQueue();

/* Reset GPU */
// extern bool shouldResetGpu();

// #define cudaDeviceSynchronize my_cudaDeviceSynchronize

// extern cudaError_t my_cudaDeviceSynchronize() __attribute__((used));

#endif
#endif
