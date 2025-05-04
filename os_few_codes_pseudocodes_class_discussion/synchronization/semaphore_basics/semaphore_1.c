struct Semaphore {
    int value;
    Queue Q;
};

Semaphore S;

wait(S) {
    S.value--;
    if (S.value < 0) {
        // block this process
        add this process to S.Q;
        suspend();
    }
}

signal(S) {
    S.value++;
    if (S.value <= 0) {
        // unblock one process
        remove a process from S.Q;
        wakeup(P_i);
    }
}


