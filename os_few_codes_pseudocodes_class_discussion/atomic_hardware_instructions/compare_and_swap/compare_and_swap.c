// Compare and Exchange // Compare and Change
int compare_and_swap(int *value, int expected, int new_value) {
	int temp = *value; 
	if (*value == expected) {
		*value = new_value; 
	}
	return temp; 
} 

// HW Support for Synchronization
// => the function compare_and_swap(..) is 
// definitely executed ATOMICALLY
// (as an UNINTERRUPTIBLE UNIT).
// HW ensures this.




while (true) {
    while (compare_and_swap(&lock, 0, 1) != 0); /* do nothing */

	/* critical section */
    lock = 0;
    /* remainder section */
} 



Two Cooperating Processes are not taking into consideration the previous value
while incrementing it to the next value,

then its possible that both the processes
behave asynchronously and change the incremented value to the same value.

comparison => increment the value

// Incrementing the counter variable
// P_0
do {
	old = counter;
	new = old + 1;
} while (compare_and_swap(&counter, old, new));


// P_1
do {
	old = counter;
	new = old + 1;
} while (compare_and_swap(&counter, old, new));

"counter" will incremented by 2 if compare_and_swap(...) is not used







// P_0
do {
	old = counter;
	new = old + 1;
} while (test_and_set(new));


// P_1
do {
	old = counter;
	new = old + 1;
} while (test_and_set(new));

"counter" will incremented by 2 if test_and_set(...) is used