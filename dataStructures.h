
#ifndef DADOSGLOBAIS

    /**
     * @brief	Estrutura de uma operação-máquina
     */
    typedef struct OperationMachine{
        int machineId;
        int time;
    } OperationMachine;

    /**
     * @brief	Nó de uma operação-máquina na linked list
     */
    typedef struct OperationMachineNode {
        OperationMachine operationMachine;
        struct OperationMachineNode* next;
    } OperationMachineNode;

    /**
     * @brief	Estrutura de uma operação
     */
    typedef struct Operation
    {
        char* name;
        OperationMachineNode* opMachines;
    } Operation;

    /**
     * @brief	Nó de uma operação na linked list
     */
    typedef struct OperationNode {
        Operation operation;
        struct OperationNode* next;
    } OperationNode;

    /**
     * @brief	Máquina
     */
    typedef struct Machine {
        int id;
        int currentTime;
        int isBusy; // 1 está disponivel, 0 está ocupada;
        OperationMachine* currentMachine;
    } Machine;

    /**
     * @brief	Máquina
     */
    typedef struct MachineNode {
        Machine machine;
        struct Machine* next;
    } MachineNode;

   /**
     * @brief	Estrutura de um job
     */
    typedef struct Job {
        int id;
        OperationNode* operations;
    } Job;

    /**
     * @brief	Nó de um job na linked list
     */
    typedef struct JobNode
    {
        Job job;
        struct JobNode* next;
    } JobNode;

    typedef struct Cell {
        int machineId;
        int currentTime;
    } Cell;
    
#define DADOSGLOBAIS 1
#endif