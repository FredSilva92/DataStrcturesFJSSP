#include "dataStructures.h"

#ifndef MANAGERDEFINED

    JobNode* addJob(JobNode* jobs, Job job);

    OperationNode* addOperation(OperationNode* operations, Operation operation);

    OperationNode* removeOperation(OperationNode* operations, char* name);

    OperationNode* changeOperation(OperationNode* operations, OperationMachineNode* machines, char* name);

    OperationNode* changeOperationMachine(OperationNode* operations, char* name, int id, int time);

    int getMinTimeJob(Job job);

    int getMaxTimeJob(Job job);

    float getAverageTimeOperation(Operation operation);

    OperationMachineNode* addOperationMachine(OperationMachineNode* operationMachines, OperationMachine opMachine);

#define MANAGERDEFINED 1
#endif