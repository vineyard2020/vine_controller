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
#ifndef WEIGHTED_ROUND_ROBIN_SCHEDULER
#define VINE_ROUND_ROBIN_SCHEDULER
#include "Scheduler.h"
#include <map>
#include <vector>
#include "utils/queue.h"
#include <mutex>
#include <bitset>

class WeightedRoundRobinScheduler : public Scheduler {
    public:
        /*Class with the description of each job*/
        class JobDescription
        {
            public:
                JobDescription();
                /*vector per vine_proc with reduction units for all accel_groups*/
                vector <int> RUnitsVector;

        };
        /*Class that describes a Client*/
        class ClientState
        {
            public:
                ClientState();
                ClientState(vector<int> weights);
                ~ClientState();
                vector <int> vectorCredit;
                vector <int> vectorWeight;
        };
        /*Class that describes the Low\High control queue*/
        class State
        {
            public:
                State();
                ~State();
                /*In Low/High queue we store VAQs*/
                utils_queue_s low, high;
        };

        /*Struct with all the information for a specific VAQ*/
        struct VAQInfo
        {
            VAQInfo(int numOfGroups);
            utils_queue_s    *utilsQueue;
            int              clientId;

            /*return inGroup bitset*/
            bool getInGroup(int groupId)
            {
                bool tmp;
                inGroupMutex.lock();
                //cerr<<__LINE__<<"  : "<<this<<"  :  (VAQInfo::GetinGroup) InGroup bitset : "<<inGroup<<endl;
                tmp = inGroup[groupId];
                inGroupMutex.unlock();
                return tmp;
            }
            /*set inGroup bitset for a particular groupId*/
            void setInGroup (bool value, int groupId)
            {
                inGroupMutex.lock();
                //	cerr<<__LINE__<<"  : "<<this<<": (VAQInfo::setInGroup)  InGroup bitset : "<<inGroup<<endl;
                inGroup[groupId] = value;
                //	cerr<<__LINE__<<"  : "<<this<<": (VAQInfo::setInGroup)  InGroup bitset : "<<inGroup<<endl;
                inGroupMutex.unlock();
            }
            /*checks if none of the bits is set*/
            bool getInAnyGroup()
            {
                bool tmp;
                inGroupMutex.lock();
                //cerr<<__LINE__<<"  : "<<this<<": (VAQInfo::getInAnyGroup)  InGroup bitset : "<<inGroup<<endl;
                tmp = inGroup.none();
                //cerr<<__LINE__<<"  : "<<this<<": (VAQInfo::getInAnyGroup)  InGroup bitset : "<<inGroup<<endl;
                inGroupMutex.unlock();
                return !tmp;
            }
            private :
            bitset<64>	 inGroup;/*In which Low/High queue a VAQ is added*/
            mutex            inGroupMutex;

        };

        /*Create WeightedRoundRobin Scheduler instance*/
        WeightedRoundRobinScheduler(std::string args,State * state = new State());

        virtual ~WeightedRoundRobinScheduler();

        /*Select a Virtual Accelerator Queue from all the VAQs that exists in the system*/
        virtual utils_queue_s *selectVirtualAcceleratorQueue(accelThread *threadPerAccel);

        /*Select a Virtual Accelerator Queue from all the VAQs that exists in the system*/
        virtual vine_vaccel_s *selectVirtualAcceleratorQueue(accelThread *threadPerAccel, size_t id);

        /*Select a task from all the VAQs that exist in the system  */
        virtual vine_task_msg_s *selectTask(accelThread *threadPerAccel);

        /*Load configuration file with weights*/
        virtual void loadConfigurationFile();

        /*load the file with the reduction units per job type*/
        virtual void loadreductionUnitFile();

        /*convert execution time to reduction units for each task type*/
        virtual void time2ReductionUnits();

        /*chekcs if the jobId provided by job Generator is correct*/
        virtual void checkJobIdRange(size_t jobId);

        /*Functions for SLA*/
        /*returns the customer id for a specific VAQ*/
        virtual int getId(vine_vaccel_s *vaq);
        /*returns client's credits*/
        virtual int & getClientCredits(int clientId, int groupId);
        /*set client's credits*/
        virtual void setClientCredits(int clientId, int groupId, int value);

        /*get client's weights*/
        virtual int & getClientWeight(int clientId, int groupId);
        /*set client's weights*/
        virtual void setClientWeight(int clientId, int groupId, int value);

    private:
        /*Low-High queue*/
        State * state;

        /**
         * Used to load the configuration file with the weights per customer
         * each line of the file is a row of that vector
         **/
        vector<ClientState> vectorClientState;
        /*Lock to guarantee that only one accelThread will push/pull in a controll queue*/
        mutex myMutex;
        /*Map between job types and execution time (used as reduction units)*/
        //map<vine_proc*, JobDescription> reductionUnitsForAllVineProcs;
        map<string, JobDescription> reductionUnitsForAllVineProcs;
};
#endif
