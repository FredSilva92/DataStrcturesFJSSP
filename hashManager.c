
#include "hashManager.h"
#include "dataStructures.h"
#include "listManager.h"
#include <stdio.h>
#include <stdlib.h>

int genHash(int id) {
    return id % HASH_TABLE_SIZE;
}

void createHashTable(JobNode *table[], int size) {
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
};

JobNode** addHashJob(Job job, JobNode* table[]) {

    int index = genHash(job.id);

    table[index] = addJob(table[index], job);
   
    return *table;
};

JobNode** removeHashJob(int id, JobNode* table[]) {
    
    int index = genHash(id);

    if (index < 0) {
        return *table;
    }

    table[index] = removeJob(table[index], id);

    return *table;
};

JobNode** addOpOnJob(JobNode* table[], Operation operation, int jobId) {

    int index = genHash(jobId);

    if (index < 0) {
        return *table;
    }

    JobNode* jobNode = getJob(table[index], jobId);

    if (jobNode != NULL) {
        jobNode->job.operations = addOperation(jobNode->job.operations, operation);
    } 
    

    return *table;
};

JobNode** removeOpOnJob(JobNode* table[], char* opName, int jobId) {
    int index = genHash(jobId);

    if (index < 0) {
        return *table;
    }

    JobNode* jobNode = getJob(table[index], jobId);

    if (jobNode != NULL) {
        jobNode->job.operations = removeOperation(jobNode->job.operations, opName);
    } 
    

    return *table;
};

JobNode** editOpOnJob(JobNode* table[], int jobId, char* opName, int machineId, int time) {
    int index = genHash(jobId);

    if (index < 0) {
        return *table;
    }

    JobNode* jobNode = getJob(table[index], jobId);

    if (jobNode != NULL) {
        jobNode->job.operations = changeOperationMachine(jobNode->job.operations, opName, machineId, time);
    } 
    
    return *table;
};

int getMinTimeProcessPlan(JobNode *table[], int size) {
    int result = 0;

    for(int i = 0; i < size; i++) {
        JobNode* ref = table[i];

        if (ref == NULL) {
            continue;
        }
        
        while (ref != NULL)
        {
            result += getMinTimeJob(ref->job);
            ref = ref->next;
        }
        
    }

    return result;
};