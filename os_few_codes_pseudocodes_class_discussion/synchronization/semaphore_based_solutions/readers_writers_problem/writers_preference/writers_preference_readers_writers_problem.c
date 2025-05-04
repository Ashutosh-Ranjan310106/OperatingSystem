Semaphore mutex = {1, emptyQueue()};    // Protects read_count and write_count
Semaphore rw_mutex = {1, emptyQueue()}; // Controls access to shared resource
Semaphore read_try = {1, emptyQueue()}; // Prevents new readers if writer is waiting

int read_count = 0;
int write_count = 0;

reader()
{
    while (true)
    {
        wait(&read_try); // Check if a writer is waiting
        wait(&mutex);
        read_count++;
        if (read_count == 1)
        {
            wait(&rw_mutex); // First reader blocks writers
        }
        signal(&mutex);
        signal(&read_try); // Allow others (unless blocked again by writer)

        // --- Reading section ---
        read_data();
        // -----------------------

        wait(&mutex);
        read_count--;
        if (read_count == 0)
        {
            signal(&rw_mutex); // Last reader unblocks writers
        }
        signal(&mutex);
    }
}

writer()
{
    while (true)
    {
        wait(&mutex);
        write_count++;
        if (write_count == 1)
        {
            wait(&read_try); // First writer blocks new readers
        }
        signal(&mutex);

        wait(&rw_mutex); // Get exclusive access

        // --- Writing section ---
        write_data();
        // ------------------------

        signal(&rw_mutex);

        wait(&mutex);
        write_count--;
        if (write_count == 0)
        {
            signal(&read_try); // Last writer unblocks readers
        }
        signal(&mutex);
    }
}
