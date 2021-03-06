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
#ifndef GPU_ACCELTHREAD
#define GPU_ACCELTHREAD
#include <pthread.h>
#include <mutex>
#include <atomic>
#include <vector>
#include "timers.h"
class GPUaccelThread;

#include "accelThread.h"
class GPUaccelThread : public accelThread {
	public:
		GPUaccelThread(vine_pipe_s * v_pipe, AccelConfig &conf);
		~GPUaccelThread();
		virtual bool acceleratorInit(); /* Function that initializes a GPU accelerator */
		virtual void acceleratorRelease(); /* Function that resets a GPU accelerator */
		virtual void printOccupancy();
		std::mutex mutexGPUAccess;
		void reset(accelThread * );
		int gpuDeviceID();
		static int getCurrentThreadGpuID();
		bool getGpuResetState(int dev);
		int getObjGpuId();
	
	private:
		int pciId;
		int gpuId;
};
bool shouldResetGpu ();

#endif
