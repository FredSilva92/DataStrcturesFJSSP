/**
 * @brief	Ficheiro com as funções de persistência: Guardar e ler dados
 * @file	persistence.c
 * @author	Pedro Silva
 * @email	a20721@alunos.ipca.pt
 * @date	31/03/2022
*/

#include "persistance.h"
#include "listManager.h"
#include "hashManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

FILE* openFile(FILE *myFile, char* fileName, char* accessType);
void closeFile(FILE *myFile);

/**
* @brief	Criar uma nova operação
* @param	name	Nome da operação
* @return	Operação
*/
Operation getOperation(char* name) {
    Operation operation = {name};
    //strcpy(operation.name, name);

    return operation;
};

/**
* @brief	Criar uma nova operação-máquina
* @param	id	Id da máquina
* @param	time	tempo que a operação demora na máquina especifico 
* @return	Operação-máquina
*/
OperationMachine getOperationMachine(int id, int time) {
    OperationMachine operationMachine = {id, time};

    return operationMachine;
}

/**
* @brief	Guardar os jobs de uma linked list
* @param	jobs	Referência da head da linked list
* @param	fileName	Nome do ficheiro onde vão ser persistidos os jobs
*/
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

/**
* @brief	Ler os jobs de um ficheiro 
* @param	fileName	Nome do ficheiro de onde vão ser lidos os jobs
* @return	Operação-máquina
*/
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

/**
* @brief	Guardar as operações num ficheiro 
* @param	job	    Job que contem as operações a serem guardadas
* @param	fileName	Nome do ficheiro de onde vão ser guardadas as operações
*/
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

/**
* @brief	Ler as operações de um ficheiro 
* @param	id	Id do job à qual pertence as operações
* @param	fileName	Nome do ficheiro de onde vão ser lidos as operações
* @return	Referência da head da linked list das operações
*/
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

/**
* @brief	Guardar as operações-máquina num ficheiro 
* @param	job	Job onde estão presente as operações e as respetivas operações-máquina
* @param	fileName	Nome do ficheiro de onde vão ser guardadas as operações-máquina
*/
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

/**
* @brief	Ler as operações-máquina de um ficheiro 
* @param	jobId	Id do job onde estão as operações com as respectivas máquinas
* @param	name	Nome da operação à qual pertencem as operações-máquina
* @param	fileName	Nome do ficheiro de onde vão ser lidos as operações-máquina
* @return	Referência da head da linked list das operações-máquina
*/
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

/**
* @brief	Ler os jobs de um ficheiro de texto
* @param	fileName	Id do job onde estão as operações com as respectivas máquinas
* @param	size	Tamanho da hash table
* @return	Referência para a Hash Table com jobs carregados do ficheiro de texto
*/
JobNode** getJobsFromTextFile(char* fileName, int size) {
    JobNode* hashTable[size];
    FILE *myFile;

    createHashTable(hashTable, size);

    myFile = openFile(myFile, fileName, "rb");

    char* text = (char*) malloc(sizeof(char));

     while(fscanf(myFile, "%s\n", text) != EOF) {
         printf("%s", text);

         char *jobText = strtok(text, ";");
         int id = atoi(jobText);

        Job job = {id, NULL};

        jobText = strtok(NULL, ";");
        char* operationsText = (char*) malloc(sizeof(char)); 
        strcpy(operationsText, jobText);
        operationsText = strtok(operationsText, ",");

        do {
            char* opToLoad = (char*) malloc(sizeof(char));
            strcpy(opToLoad, operationsText);
            opToLoad = strtok(opToLoad, ":");

            Operation* operation = (Operation*) malloc(sizeof(Operation));
            operation->name = (char*) malloc(sizeof(char));
            strcpy(operation->name, opToLoad);

            opToLoad = strtok(NULL, ":");

            char* opMachineToLoad = (char*) malloc(sizeof(char));
            strcpy(opMachineToLoad, opToLoad);
            opMachineToLoad = strtok(opMachineToLoad, "_");

            do {
                //do {
                    char* opMachineValues = (char*) malloc(sizeof(char));
                    strcpy(opMachineValues, opMachineToLoad);
                    opMachineValues = strtok(opMachineValues, "-");

                    OperationMachine* opMachine 
                        = (OperationMachine*) malloc(sizeof(OperationMachine));

                    opMachine->machineId = atoi(opMachineValues);
                    opMachineValues = strtok(NULL, "-");
                    opMachine->time = atoi(opMachineValues);

                    operation->opMachines 
                        = addOperationMachine(operation->opMachines, *opMachine);

                    //free(opMachineValues);
                    /*opMachineToLoad = strtok(opToLoad, "_");
                } while((opMachineToLoad = strtok(NULL, "_")) != NULL);*/

                //free(opMachineToLoad);
            } while((opMachineToLoad = strtok(NULL, "_")) != NULL);

            job.operations = addOperation(job.operations, *operation);
            printf("asdasdas");
            //free(opToLoad);

            operationsText = strtok(jobText, ",");   
        }
        while ((operationsText = strtok(NULL, ",")) != NULL);
      
        
        *hashTable = addHashJob(job, hashTable);

        free(operationsText);
    }

    closeFile(myFile);

    return *hashTable;
}

/**
* @brief	Armazenar os jobs num ficheiro de texto
* @param	table	Referência para a hash table
* @param	fileName	Id do job onde estão as operações com as respectivas máquinas
* @param	size	Tamanho da hash table
* @return	Referência para a Hash Table com jobs carregados do ficheiro de texto
*/
void saveJobsOnTextFile(JobNode *table[], int size, char* fileName) {
    JobNode* hashTable[size];
    FILE *myFile;
    myFile = openFile(myFile, fileName, "wb");

    for (int i = 0; i < size; i++) {
        JobNode* ref = table[i];

        

        while (ref != NULL)
        {
            char* dataToSave = (char*) malloc(sizeof(char) * 100);
            char* idText = (char*) malloc(sizeof(char));
            sprintf(idText, "%d", ref->job.id);

            strcat(dataToSave, idText);

            OperationNode* opRef = ref->job.operations;

            strcat(dataToSave, ";");

            while (opRef != NULL)
            {
                strcat(dataToSave, opRef->operation.name);

                strcat(dataToSave, ":");

                OperationMachineNode* opMachRef = opRef->operation.opMachines;

                while (opMachRef != NULL)
                {
                    char* valText = (char*) malloc(sizeof(char));
                    sprintf(valText, "%d", opMachRef->operationMachine.machineId);

                    strcat(dataToSave, valText);
                    strcat(dataToSave, "-");

                    sprintf(valText, "%d", opMachRef->operationMachine.time);
                    strcat(dataToSave, valText);

                    opMachRef = opMachRef->next;

                    if (opMachRef != NULL) {
                        strcat(dataToSave, "_");
                    }
                }

                opRef = opRef->next;

                if (opRef != NULL) {
                    strcat(dataToSave, ",");
                }
            }
            
            free(idText);
            ref = ref->next;

            fprintf(myFile, "%s\n", dataToSave);
        }
        

    }

    closeFile(myFile);
}

/**
* @brief	abrir ficheiros
* @param	myFile	Referência do ficheiro a abrir
* @param	fileName	Nome da operação à qual pertencem as operações-máquina
* @param	accessType	Tipo de acesso a estes ficheiros: leitura ou armazenamento
* @return	Referência do ficheiro aberto
*/
FILE* openFile(FILE *myFile, char* fileName, char* accessType) {
    mkdir("./Resources", 0777);

    myFile = fopen(fileName, accessType);

    if(myFile == NULL) {
        perror("Not possible to open file");
        exit(1);
    }

    return myFile;
};

/**
* @brief	Fechar ficheiros
* @param	myFile	Referência do ficheiro a abrir
*/
void closeFile(FILE *myFile) {
    if (myFile != NULL) {
        fclose(myFile);
    }
};