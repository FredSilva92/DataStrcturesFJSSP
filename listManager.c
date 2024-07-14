/**
 * @brief	Ficheiro com so funções à gestão de linked list: Jobs, Operations, OperationMachine
 * @file	manager.c
 * @author	Pedro Silva
 * @email	a20721@alunos.ipca.pt
 * @date	31/03/2022
*/

#include "dataStructures.h"
#include "listManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


void createProcessPlan(Cell processPlan[][MAX_MACHINES], int time, int machines) {
    Cell nullCell = *(Cell*) NULL;
    
    for (int i = 0; i < time; i++) {
        for (int j = 0; j < machines; j++) {
            processPlan[i][j] = nullCell;
        }
    }
}

/**
* @brief	Adicionar um novo job a uma linked list Job
* @param	jobs	Referência da head da linked list
* @param	job		Job a adicionar
* @return	Referência da head da linked list
*/
JobNode* addJob(JobNode* jobs, Job job) {
    JobNode* newNode = (JobNode*) malloc(sizeof(JobNode));
    //assert
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

JobNode* removeJob(JobNode* jobs, int id) {
    if (jobs == NULL) {
        return NULL;
    }
    JobNode* ref = jobs;
    if (ref->job.id == id) {
        jobs = jobs->next;
        free(ref);
        return jobs;
    }

    JobNode* previousOperation;

    while (ref != NULL)
    {
        previousOperation = ref;
        ref = ref->next;

         if (ref->job.id == id) {
             break;
         }
    }
    
    if (ref != NULL) {
        previousOperation->next = ref->next;
        ref->job.operations = removeOperations(ref->job.operations);
        free(ref);
    }

    return jobs;
};

/**
* @brief	Adicionar um novo job a uma linked list Job
* @param	jobs	Referência da head da linked list
* @param	job		Job a adicionar
* @return	Referência da head da linked list
*/
MachineNode* addMachine(MachineNode* machines, Machine machine) {
    MachineNode* newNode = (MachineNode*) malloc(sizeof(MachineNode));
    //assert
    newNode->machine = machine;

    if (machines == NULL) {
        machines = newNode;
        return machines;
    } 

    MachineNode* ref = machines;

    while (ref->next != NULL)
    {
        ref = ref->next;
    }

    ref->next = newNode;

    return machines;
};

MachineNode* removeMachine(MachineNode* machines, int id) {
    if (machines == NULL) {
        return NULL;
    }
    MachineNode* ref = machines;
    if (ref->machine.id == id) {
        machines = machines->next;
        free(ref);
        return machines;
    }

    MachineNode* previousOperation;

    while (ref != NULL)
    {
        previousOperation = ref;
        ref = ref->next;

         if (ref->machine.id == id) {
             break;
         }
    }
    
    if (ref != NULL) {
        previousOperation->next = ref->next;
        free(ref);
    }

    return machines;
};



JobNode* getJob(JobNode* jobs, int id) {
    JobNode* job = NULL;
    JobNode* ref = jobs;
    
    while (ref != NULL)
    {
        if (ref->job.id == id) {
            job = ref;
            break;
        } else {
            ref = jobs->next;
        }
    }
    
    return job;
}

/**
* @brief	Adicionar uma nova operação a uma linked list Operation
* @param	operations	Referência da head da linked list
* @param	operation	Operação a adicionar
* @return	Referência da head da linked list
*/
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

/**
* @brief	Remover uma nova operação a uma linked list Operation
* @param	operations	Referência da head da linked list
* @param	operation	Operação a remover
* @return	Referência da head da linked list
*/
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

/**
* @brief	Remover as operações todas de uma linked list Operation
* @param	operations	Referência da head da linked list
* @return	Referência da head da linked list
*/
OperationNode* removeOperations(OperationNode* operations) {
    
    if (operations == NULL) {
        return NULL;
    }

    OperationNode* ref = operations;

    while (ref != NULL)
    {
        OperationNode* opToDelete = ref;
        ref = ref->next;
        
        free(opToDelete);
    }
    
    return NULL;
};

/**
* @brief	Alterar uma linked list operação-máquina de uma operação
* @param	operations	Referência da head da linked list
* @param	machines	Referência da head da linked list OperationMachine que vai ser inserida na operação
* @param	name	Nome da operação a alterar
* @return	Referência da head da linked list das operações
*/
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

/**
* @brief	Alterar o tempo de uma máquina especifico em uma operação
* @param	operations	Referência da head da linked list
* @param	name	Nome na qual se encontra a operação-maquina a alterar
* @param	id	Id da máquina a alterar
* @param	time	Novo tempo
* @return	Referência da head da linked list das operações
*/
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

/**
* @brief	Adicionar uma operação máquina
* @param	operationMachines	Referência da head da linked list das operações-máquina
* @param	opMachine	operação-máquina que se pretende adicionar
* @return	Referência da head da linked list das operações-máquina
*/
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

/**
* @brief	Remover uma operação-máquina de uma linked list OperationMachine
* @param	operations	Referência da head da linked list
* @return	Referência da head da linked list
*/
OperationMachineNode* removeOperationMachine(OperationMachineNode* operationMachines) {
    if (operationMachines == NULL) {
        return NULL;
    }

    OperationMachineNode* ref = operationMachines;

    while (ref != NULL)
    {
        OperationMachineNode* opToDelete = ref;
        ref = ref->next;
        free(opToDelete);
    }
    
    return NULL;
}

/**
* @brief	Calcular o tempo minimo de execução de um job
* @param	job	Job
* @return	Tempo minimo de execução de uma máquina
*/
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

/**
* @brief	Calcular o tempo máximo de execução de uma job
* @param	job	Job
* @return	Tempo máximo de execução de uma máquina
*/
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


/**
* @brief	Calcular o tempo das média das máquinas de uma operação
* @param	job	Job
* @return	tempo médio de execução de uma máquina
*/
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