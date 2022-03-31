#include "dataStructures.h"
#include "manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

JobNode* addJob(JobNode* jobs, Job job) {
    JobNode* newNode = (JobNode*) malloc(sizeof(JobNode));
    newNode->job = job;

    if (jobs == NULL) {
        jobs = newNode;
        return jobs;
    } 

    JobNode* ref = jobs;

    while (ref->next != NULL)
    {
        ref = ref->next;
    }

    ref->next = newNode;

    return jobs;
};

OperationNode* addOperation(OperationNode* operations, Operation operation) {
    OperationNode* newNode = (OperationNode*) malloc(sizeof(OperationNode));
    newNode->operation = operation;

    if (operations == NULL) {
        operations = newNode;
        return operations;
    } 

    OperationNode* ref = operations;

    while (ref->next != NULL)
    {
        ref = ref->next;
    }

    ref->next = newNode;

    return operations;
}

OperationNode* removeOperation(OperationNode* operations, char* name) {
    
    if (operations == NULL) {
        return NULL;
    }

    OperationNode* ref = operations;

    if (strcmp(name, ref->operation.name) == 0) {
        
        operations = operations->next;

        free(ref);

        return operations;
    }

    OperationNode* previousOperation;

    while (ref != NULL && strcmp(name, ref->operation.name) != 0)
    {
        previousOperation = ref;
        ref = ref->next;
    }
    
    if (ref != NULL) {
        previousOperation->next = ref->next;
        free(ref);
    }

    return operations;
};

OperationNode* changeOperation(OperationNode* operations, OperationMachineNode* machines, char* name) {
    OperationNode* ref = operations;

    if (ref == NULL) {
        return NULL;
    }

    while (ref)
    {
        if (strcmp(name, ref->operation.name) == 0) {
            break;
        }

        ref = ref->next;
    }
    
    ref->operation.opMachines = machines;

    return operations;
};

OperationNode* changeOperationMachine(OperationNode* operations, char* name, int id, int time) {
    OperationNode* ref = operations;

    if (ref == NULL) {
        return NULL;
    }

    while (ref)
    {
        if (strcmp(name, ref->operation.name) == 0) {
            break;
        }

        ref = ref->next;
    }

    if (ref == NULL) {
        return operations;
    }

    OperationMachineNode* refMachine = ref->operation.opMachines;

    while (refMachine)
    {
        if(refMachine->operationMachine.machineId == id) {
            refMachine->operationMachine.time = time;
            break;
        }

        refMachine = refMachine->next;
    }
    
    return operations;
};

OperationMachineNode* addOperationMachine(OperationMachineNode* operationMachines, OperationMachine opMachine) {
    OperationMachineNode* newNode = (OperationMachineNode*) malloc(sizeof(OperationMachineNode));
    newNode->operationMachine = opMachine;

    if (operationMachines == NULL) {
        operationMachines = newNode;
        return operationMachines;
    } 

    OperationMachineNode* ref = operationMachines;

    while (ref->next != NULL)
    {
        ref = ref->next;
    }

    ref->next = newNode;

    return operationMachines;
}

int getMinTimeJob(Job job) {
    int result = 0;

    OperationNode* ref = job.operations;

    if (ref == NULL) {
        return result;
    }

    while (ref != NULL)
    {
        OperationMachineNode* refMachine = ref->operation.opMachines;

        int minTime = refMachine->operationMachine.time;

        refMachine = refMachine->next;

        while (refMachine)
        {
            int machineTime = refMachine->operationMachine.time;
            if (minTime > machineTime) {
                minTime = machineTime;
            }

            refMachine = refMachine->next;
        }

        result += minTime;

        ref = ref->next;
    }
    
    return result;
};

int getMaxTimeJob(Job job) {
    int result = 0;

    OperationNode* ref = job.operations;

    if (ref == NULL) {
        return result;
    }

    while (ref != NULL)
    {
        OperationMachineNode* refMachine = ref->operation.opMachines;

        int maxTime = refMachine->operationMachine.time;

        refMachine = refMachine->next;

        while (refMachine)
        {
            int machineTime = refMachine->operationMachine.time;
            if (maxTime < machineTime) {
                maxTime = machineTime;
            }

            refMachine = refMachine->next;
        }

        result += maxTime;

        ref = ref->next;
    }
    
    return result;
};



float getAverageTimeOperation(Operation operation) {
    int sum = 0;
    int count = 0;

    OperationMachineNode* machines = operation.opMachines;

    while (machines)
    {
        count++;
        sum += machines->operationMachine.time;

        machines = machines->next;
    }
    

    return sum/(float)count;
};