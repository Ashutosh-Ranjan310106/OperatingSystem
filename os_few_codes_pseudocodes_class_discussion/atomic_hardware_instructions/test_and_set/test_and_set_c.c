lock = false;

boolean test_and_set(boolean *target) {
	boolean rv = *target;
    *target = true; 
	return rv; 
} 



// HW Support for Synchronization
// => the function test_and_set(..) is 
// definitely executed ATOMICALLY
// (as an UNINTERRUPTIBLE UNIT).
// HW ensures this.


// P_0 attempts to get the lock
// P_0 finds the lock to be false
// P_0 acquires the lock => lock = true



lock = false;

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

