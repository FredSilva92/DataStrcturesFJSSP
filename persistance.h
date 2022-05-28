#include "dataStructures.h"

/**
 * @brief	Estrutura de um job em ficheiro
 */
typedef struct JobFile {
    int id;
} JobFile;

/**
 * @brief	Estrutura de uma operação em ficheiro
 */
typedef struct OperationFile {
    char* name;
    int id;
} OperationFile;

/**
 * @brief	Estrutura de uma operação-máquina em ficheiro
 */
typedef struct OperationMachineFile {
    int jobId;
    char* name;
    int id;
    int time;
} OperationMachineFile;

void saveJobsToFile(JobNode* jobs, char* fileName);
JobNode* readJobsFromFile(char* fileName);

void saveOperationsToFile(Job job, char* fileName);
OperationNode* readOperationsFromFile(int id, char* fileName);

void saveOperationMachinesToFile(Job job, char* fileName);
OperationMachineNode* readOperationMachinesFromFile(int jobId, char* name, char* fileName);