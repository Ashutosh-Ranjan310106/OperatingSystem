#define N 5

enum { THINKING, HUNGRY, EATING } state[N];    // Track each philosopher’s state

Semaphore mutex = {1, emptyQueue()};           // Mutual exclusion for state array
Semaphore S[N];                                 // Semaphore for each philosopher

// Initialization function (run once before starting threads)
initialize() {
    for (int i = 0; i < N; i++) {
        state[i] = THINKING;
        S[i] = (Semaphore){0, emptyQueue()};   // Initialize each S[i] with 0
    }
}

// Check if philosopher[i] can eat
test(int i) {
    if (state[i] == HUNGRY &&
        state[(i + N - 1) % N] != EATING &&       // Left neighbor not eating
        state[(i + 1) % N] != EATING) {           // Right neighbor not eating
        
        state[i] = EATING;
        signal(&S[i]);    // Let philosopher i eat
    }
}

// Philosopher i tries to pick up both chopsticks
pick_up_chopsticks(int i) {
    wait(&mutex);               // Enter critical section
    state[i] = HUNGRY;          // Philosopher i is hungry
    test(i);                    // Try to acquire chopsticks
    signal(&mutex);             // Exit critical section
    wait(&S[i]);                // Block if unable to eat
}

// Philosopher i puts down both chopsticks
put_down_chopsticks(int i) {
    wait(&mutex);                 // Enter critical section
    state[i] = THINKING;          // Done eating, back to thinking
    test((i + N - 1) % N);        // Check if left neighbor can eat
    test((i + 1) % N);            // Check if right neighbor can eat
    signal(&mutex);               // Exit critical section
}

// Simulates the philosopher’s lifecycle
simulate_philosopher(int i) {
    while (true) {
        think(i);                 // Simulate thinking
        pick_up_chopsticks(i);    // Try to acquire chopsticks
        eat(i);                   // Simulate eating
        put_down_chopsticks(i);   // Release chopsticks
    }
}


think(int i) {
    // Simulate philosopher i thinking
}

eat(int i) {
    // Simulate philosopher i eating
}
