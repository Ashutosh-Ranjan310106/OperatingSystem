bool is_safe(
    int n,                       // Number of Processes  
    int m,                       // Number of Resource Types
    int Available[m],            // Available[i]: number of available instances of resource i
    int Max[n][m],               // Max[i][j]: maximum demand of process i for resource j
    int Allocation[n][m]) {      // Allocation[i][j]: current allocation to process i for resource j

    int Need[n][m];                      // Need[i][j] = Max[i][j] - Allocation[i][j]
    bool Finish[n];                      // Finish[i] = true if process i can finish
    int Work[m];                         // Work = copy of Available, simulates resource availability

    // 1. Initialize Need matrix and Finish flags
    for (int i = 0; i < n; i++) {
        Finish[i] = false;               // Initially, no process has finished
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];  // Calculate remaining need
        }
    }

    // 2. Initialize Work to Available resources
    for (int i = 0; i < m; i++) {
        Work[i] = Available[i];          // Simulated available resources
    }

    // 3. Try to find a process that can finish
    while (true) {
        bool found = false;             // Flag to check if any process can proceed in this round

        for (int i = 0; i < n; i++) {
            // Only consider unfinished processes
            if (!Finish[i]) {
                int j;

                // Check if all of the process's needs can be met with current Work
                for (j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        break; // Cannot satisfy this process
                    }
                }

                if (j == m) {  // If all needs were satisfied
                    // Simulate process i finishing
                    for (int k = 0; k < m; k++) {
                        Work[k] += Allocation[i][k];  // Release resources held by process i
                    }
                    Finish[i] = true;      // Mark process as completed
                    found = true;          // A process finished in this round
                }
            }
        }

        // If no process could finish in this round, exit loop
        if (!found) {
            break;
        }
    }

    // 4. After checking all processes, see if all are finished
    for (int i = 0; i < n; i++) {
        if (!Finish[i]) {
            return false;  // System is NOT in a safe state
        }
    }

    return true;  // All processes could finish ⇒ system is safe
}
