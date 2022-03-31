#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructures.h"
#include "persistance.h"
#include "manager.h"

#define JOBS_FILE "Resources/jobs.bin"
#define OPERATIONS_FILE "Resources/operations.bin"
#define OPERATION_MACHINES_FILE "Resources/operation_machines.bin"

int main() {

    Job job1 = {12, NULL};

    Operation operation1 = {"o1", NULL};
    Operation operation2 = {"o2", NULL};
    Operation operation3 = {"o3", NULL};
    Operation operation4 = {"o4", NULL};

    OperationMachine om1o1 = {1, 4};
    OperationMachine om2o1 = {3, 5};

    OperationMachine om1o2 = {2, 4};
    OperationMachine om2o2 = {4, 1};

    OperationMachine om1o3 = {1, 2};
    OperationMachine om2o3 = {3, 3};

    OperationMachine om1o4 = {4, 5};
    OperationMachine om2o4 = {5, 5};
    OperationMachine om3o4 = {6, 4};
    OperationMachine om4o4 = {7, 5};
    OperationMachine om5o4 = {8, 9};

    OperationMachine newOm1o3 = {3, 5};
    OperationMachine newOm2o3 = {5, 6};

    operation1.opMachines = addOperationMachine(operation1.opMachines, om1o1);
    operation1.opMachines = addOperationMachine(operation1.opMachines, om2o1);

    operation2.opMachines = addOperationMachine(operation2.opMachines, om1o2);
    operation2.opMachines = addOperationMachine(operation2.opMachines, om2o2);

    operation3.opMachines = addOperationMachine(operation3.opMachines, om1o3);
    operation3.opMachines = addOperationMachine(operation3.opMachines, om2o3);

    operation4.opMachines = addOperationMachine(operation4.opMachines, om1o4);
    operation4.opMachines = addOperationMachine(operation4.opMachines, om2o4);
    operation4.opMachines = addOperationMachine(operation4.opMachines, om3o4);
    operation4.opMachines = addOperationMachine(operation4.opMachines, om4o4);
    operation4.opMachines = addOperationMachine(operation4.opMachines, om5o4);

    job1.operations = addOperation(job1.operations, operation1);
    job1.operations = addOperation(job1.operations, operation2);
    job1.operations = addOperation(job1.operations, operation3);
    job1.operations = addOperation(job1.operations, operation4);

    job1.operations = removeOperation(job1.operations, "o4");
    job1.operations = addOperation(job1.operations, operation4);

    OperationMachineNode* newOpMachines = NULL;
    newOpMachines = addOperationMachine(newOpMachines, newOm1o3);
    newOpMachines = addOperationMachine(newOpMachines, newOm2o3);

    job1.operations = changeOperation(job1.operations, newOpMachines, "o3");

    job1.operations = changeOperationMachine(job1.operations, "o2", 4, 5);

    int minTime = getMinTimeJob(job1);
    int maxTime = getMaxTimeJob(job1);
    int averageTime = getAverageTimeOperation(job1.operations->operation);

    JobNode* jobs = (JobNode*) malloc(sizeof(JobNode));
    jobs->job = job1;

    saveJobsToFile(jobs, JOBS_FILE);
    saveOperationsToFile(job1, OPERATIONS_FILE);
    saveOperationMachinesToFile(job1, OPERATION_MACHINES_FILE);

    JobNode* newJobs = readJobsFromFile(JOBS_FILE);
    Job* newJob = &newJobs->job;
    newJob->operations = readOperationsFromFile(newJob->id, OPERATIONS_FILE);

    OperationNode* operationsFromFile = newJob->operations;

    while (operationsFromFile)
    {   
        OperationMachineNode* opMachinesFromFile = readOperationMachinesFromFile(newJob->id,
            operationsFromFile->operation.name, OPERATION_MACHINES_FILE);

        operationsFromFile->operation.opMachines = opMachinesFromFile;

        operationsFromFile = operationsFromFile->next;
    }
}