
#include "dataStructures.h"

#define HASH_TABLE_SIZE 7

int genHash(int id);

void createHashTable(JobNode *table[], int n);

void createHashTableMachines(MachineNode *table[], int size);

JobNode** addHashJob(Job job, JobNode* table[]);

JobNode** removeHashJob(int id, JobNode* table[]);

JobNode** addOpOnJob(JobNode* table[], Operation operation, int jobId);

JobNode** removeOpOnJob(JobNode* table[], char* opName, int jobId);

JobNode** changeOpOnJob(JobNode* table[]);

JobNode** editOpOnJob(JobNode* table[], int jobId, char* opName, int machineId, int time);

MachineNode** addHashMachine(Machine machine, MachineNode* table[]);

MachineNode** removeHashMachine(int id, MachineNode* table[]);

int getMinTimeProcessPlan(JobNode *table[], int size);