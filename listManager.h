#include "dataStructures.h"

#ifndef MANAGERDEFINED

    JobNode* addJob(JobNode* jobs, Job job);

    JobNode* removeJob(JobNode* jobs, int id);

    JobNode* getJob(JobNode* jobs, int id);

    OperationNode* addOperation(OperationNode* operations, Operation operation);

    OperationNode* removeOperation(OperationNode* operations, char* name);

    OperationNode* removeOperations(OperationNode* operations);

    OperationNode* changeOperation(OperationNode* operations, OperationMachineNode* machines, char* name);

    OperationNode* changeOperationMachine(OperationNode* operations, char* name, int id, int time);

    OperationMachineNode* removeOperationMachine(OperationMachineNode* operationMachines);

    int getMinTimeJob(Job job);

    int getMaxTimeJob(Job job);

    float getAverageTimeOperation(Operation operation);

    OperationMachineNode* addOperationMachine(OperationMachineNode* operationMachines, OperationMachine opMachine);

#define MANAGERDEFINED 1
#endif