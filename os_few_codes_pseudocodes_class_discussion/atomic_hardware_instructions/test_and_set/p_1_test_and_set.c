
// Process P_0

do {	

	// If the value of the lock is true
	// => The lock is acquired by some other 
	// process which is currently executing in 
	// the CS.

	while (test_and_set(&lock)); /* do nothing */
	 /* critical section */

	 // The lock is set to false on exiting the CS.
	 lock = false;
	/* remainder section */
} while (true); 
