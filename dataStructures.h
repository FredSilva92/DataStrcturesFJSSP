
#ifndef DADOSGLOBAIS

    typedef struct OperationMachine{
        int machineId;
        int time;
    } OperationMachine;

    typedef struct OperationMachineNode {
        OperationMachine operationMachine;
        struct OperationMachineNode* next;
    } OperationMachineNode;

    typedef struct Operation
    {
        char* name;
        OperationMachineNode* opMachines;
    } Operation;

    typedef struct OperationNode {
        Operation operation;
        struct OperationNode* next;
    } OperationNode;

    typedef struct Machine {
        int id;
        int isBusy; // 1 está disponivel, 0 está ocupada;
    } Machine;

    typedef struct Job {
        int id;
        OperationNode* operations;
    } Job;

    typedef struct JobNode
    {
        Job job;
        struct JobNode* next;
    } JobNode;
    
#define DADOSGLOBAIS 1
#endif