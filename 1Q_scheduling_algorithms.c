#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time
    int priority;      // Priority
    int remainingTime; // Remaining time for RR
};

// Function to perform FCFS scheduling
void fcfs(struct Process processes[], int n) {
    int waitingTime[n], turnaroundTime[n];
    
    // Calculate waiting time for the first process
    waitingTime[0] = 0;
    
    // Calculate waiting time for the rest of the processes
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }
    
    // Calculate turnaround time for all processes
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
    
    // Print results
    printf("\nFCFS Scheduling:\n");
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].pid, waitingTime[i], turnaroundTime[i]);
    }
}

// Function to perform SJF scheduling
void sjf(struct Process processes[], int n) {
    // Sort processes by burst time (shortest first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burstTime > processes[j + 1].burstTime) {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    // Calculate waiting time and turnaround time (same as FCFS)
    fcfs(processes, n);
}

// Function to perform Priority Scheduling
void priorityScheduling(struct Process processes[], int n) {
    int waitingTime[n], turnaroundTime[n];
    
    // Sort processes by priority (highest first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority < processes[j + 1].priority) {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    // Calculate waiting time for the first process
    waitingTime[0] = 0;
    
    // Calculate waiting time for the rest of the processes
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }
    
    // Calculate turnaround time for all processes
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
    
    // Print results
    printf("\nPriority Scheduling:\n");
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].pid, waitingTime[i], turnaroundTime[i]);
    }
}

// Function to perform Round Robin Scheduling
void roundRobin(struct Process processes[], int n, int quantum) {
    int waitingTime[n], turnaroundTime[n];
    int remainingBurstTime[n];
    
    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }
    
    int time = 0; // Current time
    int done = 0; // Number of processes completed
    
    // Continue until all processes are done
    while (done < n) {
        int flag = 0; // Flag to check if any process executed in the current time slice
        
        // Traverse all processes
        for (int i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0) {
                if (remainingBurstTime[i] <= quantum) {
                    // Execute the process for the remaining burst time
                    time += remainingBurstTime[i];
                    waitingTime[i] = time - processes[i].burstTime;
                    remainingBurstTime[i] = 0;
                    done++;
                } else {
                    // Execute the process for the time quantum
                    time += quantum;
                    remainingBurstTime[i] -= quantum;
                }
                flag = 1; // A process was executed
            }
        }
        
        // If no process was executed in this time slice, increment time
        if (flag == 0) {
            time++;
        }
    }
    
    // Calculate turnaround time for all processes
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
    
    // Print results
    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].pid, waitingTime[i], turnaroundTime[i]);
    }
}

int main() {
    // Define the processes
    struct Process processes[] = {
        {1, 0, 24, 3},
        {2, 4, 3, 1},
        {3, 5, 3, 4},
        {4, 6, 12, 2}
    };
    
    int n = sizeof(processes) / sizeof(processes[0]);
    
    // Perform scheduling using different algorithms
    fcfs(processes, n);
    sjf(processes, n);
    priorityScheduling(processes, n);
    roundRobin(processes, n, 4);
    
    return 0;
}
