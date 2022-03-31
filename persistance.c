#include "persistance.h"
#include "manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

FILE* openFile(FILE *myFile, char* fileName, char* accessType);
void closeFile(FILE *myFile);

Operation getOperation(char* name) {
    Operation operation = {name};
    //strcpy(operation.name, name);

    return operation;
};

OperationMachine getOperationMachine(int id, int time) {
    OperationMachine operationMachine = {id, time};

    return operationMachine;
}

void saveJobsToFile(JobNode* jobs, char* fileName) {
    FILE *myFile;

    myFile = openFile(myFile, fileName, "wb");

    JobNode* ref = jobs;

    while (ref != NULL)
    {
        int id = ref->job.id;

        fwrite(&id, sizeof(int), 1, myFile);

        ref = ref->next;
    }

    closeFile(myFile);
    
    free(ref);
};

JobNode* readJobsFromFile(char* fileName) {
    JobNode* head = NULL;
    JobFile* refFromFile = (JobFile*) malloc(sizeof(JobFile));

    FILE *myFile;

    myFile = openFile(myFile, fileName, "rb");

    while (fread(refFromFile, sizeof(JobFile), 1, myFile)) {
        Job newJob = {refFromFile->id, NULL};
        head = addJob(head, newJob);
    }

    return head;
}

void saveOperationsToFile(Job job, char* fileName) {

    OperationNode* ref = job.operations;
    FILE *myFile;

    myFile = openFile(myFile, fileName, "wb");

    while (ref)
    {
        OperationFile operationFile = {ref->operation.name, job.id};
        /* code */
        fwrite(&operationFile, sizeof(OperationFile), 1, myFile);

        ref = ref->next;
    }
    
    closeFile(myFile);
};

OperationNode* readOperationsFromFile(int id, char* fileName) {
    OperationNode* head = NULL;
    OperationFile* refFromFile = (OperationFile*) malloc(sizeof(OperationFile));

    FILE *myFile;

    myFile = openFile(myFile, fileName, "rb");

    char* name = malloc(sizeof(char));

    while (fread(refFromFile, sizeof(OperationFile), 1, myFile))
    {  
        Operation opToAdd = getOperation(refFromFile->name);
        head = addOperation(head, opToAdd);
    }
    

    closeFile(myFile);

    return head;
};

void saveOperationMachinesToFile(Job job, char* fileName) {
    OperationNode* operation = job.operations;
    
    FILE *myFile;

    myFile = openFile(myFile, fileName, "wb");

    while (operation)
    {
        OperationMachineNode* machine = operation->operation.opMachines;

        while (machine)
        {
            OperationMachineFile machineToFile = {
                job.id,
                operation->operation.name,
                machine->operationMachine.machineId,
                machine->operationMachine.time
            };

            fwrite(&machineToFile, sizeof(OperationMachineFile), 1, myFile);

            machine = machine->next;
        }
        
        operation = operation->next;
    }
    

    closeFile(myFile);
}

OperationMachineNode* readOperationMachinesFromFile(int jobId, char* name, char* fileName) {
    OperationMachineNode* machines = NULL;
    FILE *myFile;

    myFile = openFile(myFile, fileName, "rb");

    OperationMachineFile* refFromFile = (OperationMachineFile*) malloc(sizeof(OperationMachineFile));

    while (fread(refFromFile, sizeof(OperationMachineFile), 1, myFile))
    {
        if (refFromFile->jobId == jobId && strcmp(refFromFile->name, name) == 0) {
            OperationMachine opMachineToAdd = getOperationMachine(refFromFile->id, refFromFile->time);
            machines = addOperationMachine(machines, opMachineToAdd);
        }
    }
    
    closeFile(myFile);

    return machines;
}

FILE* openFile(FILE *myFile, char* fileName, char* accessType) {
    mkdir("./Resources", 0777);

    myFile = fopen(fileName, accessType);

    if(myFile == NULL) {
        perror("Not possible to open file");
        exit(1);
    }

    return myFile;
};

void closeFile(FILE *myFile) {
    if (myFile != NULL) {
        fclose(myFile);
    }
};