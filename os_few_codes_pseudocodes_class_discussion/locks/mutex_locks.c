// Software-based solution => MUTEX locks
// => Guaranteeing Mutual Exclusion
// no guarantee of Progress / Bounded Waiting

while (true) {
	acquire(lock);
	// critical section 
	release(lock);
	// remainder section 
} 

acquire() {
    // while (!available); /* P_0 is busy waiting */
	while (!available); /* P_0 waits inside a Waiting Queue */
    available = false;
} 

release() {
	available = true; 
} 

// Context-switching takes some time
// P_0 is "busy waiting" => No Context Switch

// P_0 waits in a Queue => PCB of P_0 is swapped to the queue
// PCB of P_0 is swapped to the CPU / Ready Queue.

// (Two * Context Switching Time)

// What if the resource / lock would have been available in lesser than (2 * Context Switching Time)?


// This decision of Busy Wait (Spin Lock) versus Waiting in a Queue should be dynamically taken on the basis of the comparison between the 
// Context Switching Time (twice) and time required for the resource to be available




// P_0 is attempting to acquire a resource
// "available" is the status of the resource

// P_1 already has the resource. 
// P_1 releases() the resource => availability = true;

// P_0 acquires the lock sets "available" to false
