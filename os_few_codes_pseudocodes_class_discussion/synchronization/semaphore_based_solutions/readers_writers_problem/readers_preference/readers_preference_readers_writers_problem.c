Semaphore mutex = {1, emptyQueue()};       // Protects read_count
Semaphore rw_mutex = {1, emptyQueue()};    // Controls access to the shared resource
int read_count = 0;                        // Number of active readers


reader() {
    while (true) {
        wait(&mutex);
        read_count++;
        if (read_count == 1) {
            wait(&rw_mutex);  // first reader locks writers
        }
        signal(&mutex);

        // --- Reading section ---
        read_data();
        // -----------------------

        wait(&mutex);
        read_count--;
        if (read_count == 0) {
            signal(&rw_mutex);  // last reader unlocks writers
        }
        signal(&mutex);
    }
}


writer() {
    while (true) {
        wait(&rw_mutex);     // writer locks out readers and other writers

        // --- Writing section ---
        write_data();
        // ------------------------

        signal(&rw_mutex);   // release resource
    }
}
