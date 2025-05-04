bool request_resource(
    int i,                        // Process ID making the request
    int Request[m],               // Request[i]: amount of each resource type being requested
    int n,                        // Number of processes
    int m,                        // Number of resource types
    int Available[m],            // Available[j]: how many instances of resource j are currently free
    int Max[n][m],               // Max[i][j]: maximum demand of process i for resource j
    int Allocation[n][m]         // Allocation[i][j]: currently allocated to process i
) {
    // To check whether the system will be in a Safe State, 
    // you have to simulate resource requests

    int Need[n][m];              // Remaining resource need per process

    // 1. Calculate Need matrix = Max - Allocation
    for (int j = 0; j < m; j++) {
        Need[i][j] = Max[i][j] - Allocation[i][j];

        // 2. Check if the request exceeds the declared maximum need
        if (Request[j] > Need[i][j]) {
            printf("Error: Process %d is requesting more than its declared maximum.\n", i);
            return false; // Invalid request
        }

        // 3. Check if the requested resources are available
        if (Request[j] > Available[j]) {
            printf("Process %d must wait: resources not available now.\n", i);
            return false; // Cannot grant now, but may later
        }
    }

    // 4. Pretend to allocate resources to process i (temporary state)
    for (int j = 0; j < m; j++) {
        Available[j] -= Request[j];       // Reduce available resources
        Allocation[i][j] += Request[j];   // Temporarily grant request
    }

    // 5. Call safety algorithm to test system safety after temporary allocation
    if (is_safe(n, m, Available, Max, Allocation)) {
        printf("Request can be safely granted to process %d.\n", i);
        return true;  // It is safe to grant the request
    }
    else {
        // 6. Rollback the temporary allocation (restore original state)
        for (int j = 0; j < m; j++) {
            Available[j] += Request[j];
            Allocation[i][j] -= Request[j];
        }
        printf("Request cannot be granted to process %d: would lead to unsafe state.\n", i);
        return false;
    }
}
