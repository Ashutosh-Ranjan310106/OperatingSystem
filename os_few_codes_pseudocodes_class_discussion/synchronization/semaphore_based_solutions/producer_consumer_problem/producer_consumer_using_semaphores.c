#define N 10
int buffer[N];
int in = 0, out = 0;

Semaphore mutex = {1, emptyQueue()};
Semaphore empty = {N, emptyQueue()};
Semaphore full = {0, emptyQueue()};

producer() {
    int item;
    while (true) {
        item = produce_item();        // produce an item
        wait(&empty);                 // wait for an empty slot
        wait(&mutex);                 // enter critical section

        buffer[in] = item;
        in = (in + 1) % N;

        signal(&mutex);              // exit critical section
        signal(&full);               // signal that a full slot is available
    }
}

consumer() {
    int item;
    while (true) {
        wait(&full);                 // wait for a full slot
        wait(&mutex);                // enter critical section

        item = buffer[out];
        out = (out + 1) % N;

        signal(&mutex);              // exit critical section
        signal(&empty);              // signal that an empty slot is available
        consume_item(item);          // consume the item
    }
}
