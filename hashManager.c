
#include "hashManager.h"
#include "dataStructures.h"
#include "listManager.h"
#include <stdio.h>
#include <stdlib.h>

/**
* @brief	Gerar um indice do array da hash table
* @param	id	Indice
* @return	Indice da linked list da hash table
*/
int genHash(int id) {
    return id % HASH_TABLE_SIZE;
}

/**
* @brief	Iniciar a has table, onde inicialmente todos as posições estão a apontar para um Null
* @param	table	Referencia da hash table
* @param	size	Tamanno da hash table
*/
void createHashTable(JobNode *table[], int size) {
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
};

void createHashTableMachines(MachineNode *table[], int size) {
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
};

/**
* @brief	Adicionar um job à hash table
* @param	job	 Job que se pretende adicionar
* @param	table	Hast table
* @return	Referência da hash table
*/
JobNode** addHashJob(Job job, JobNode* table[]) {

    int index = genHash(job.id);

    table[index] = addJob(table[index], job);
   
    return *table;
};

/**
* @brief	Remover um job da hash table
* @param	id	 id do job que se pretende remover
* @param	job	 Job que se pretende adicionar
* @return	Referência da hash table
*/
JobNode** removeHashJob(int id, JobNode* table[]) {
    
    int index = genHash(id);

    if (index < 0) {
        return *table;
    }

    table[index] = removeJob(table[index], id);

    return *table;
};

/**
* @brief	Adicionar um job à hash table
* @param	job	 Job que se pretende adicionar
* @param	table	Hast table
* @return	Referência da hash table
*/
MachineNode** addHashMachine(Machine machine, MachineNode* table[]) {

    int index = genHash(machine.id);

    table[index] = addMachine(table[index], machine);
   
    return *table;
};

/**
* @brief	Remover um job da hash table
* @param	id	 id do job que se pretende remover
* @param	job	 Job que se pretende adicionar
* @return	Referência da hash table
*/
MachineNode** removeHashMachine(int id, MachineNode* table[]) {
    
    int index = genHash(id);

    if (index < 0) {
        return *table;
    }

    table[index] = removeMachine(table[index], id);

    return *table;
};

/**
* @brief	Adicionar uma operação a um job existente da hash table
* @param	table	 referência da hash table
* @param	operation	 id do job que se pretende adicionar
* @param	jobId	 Job que se pretende adicionar
* @return	Referência da hash table
*/
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

/**
* @brief	Remover uma operação a um job existente da hash table
* @param	table	 referência da hash table
* @param	opName	 nome da operação que se pretende remover
* @param	jobId	 Job na qual se pretende Remover a operação
* @return	Referência da hash table
*/
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

/**
* @brief	Editar uma operação máquina num job existente da hash table
* @param	table	 referência da hash table
* @param	jobId	 Id do job onde se pretende editar a operação máquina
* @param	opName	 nome da operação que contem a operação máquina que se pretende editar
* @param	machineId	 Operação máquina que se pretende editar
* @param	time	 Novo tempo da operação máquina
* @return	Referência da hash table
*/
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

/**
* @brief	Calcular o tempo minimo de um processPlan
* @param	table	 referência da hash table
* @param	size	 tamanho da hash table
* @return	Tempo minimo do process plan
*/
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

void executeProcessPlan(Cell processPlan[][MAX_MACHINES], JobNode* jobHashTable[], MachineNode* machines, int time) {

    for(int i = 0; i < time; i++) {
        MachineNode* machineRef = machines;

        while (machineRef != NULL)
        {
            
        }
        
    }
}