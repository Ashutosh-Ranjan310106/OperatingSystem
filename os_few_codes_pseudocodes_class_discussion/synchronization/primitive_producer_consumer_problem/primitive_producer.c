// Producer - Not synchronized
while (true) {
    /* produce an item in next_produced */ 
	
    while (count == BUFFER SIZE) ; /* do nothing */ 

    buffer[in] = next_produced;
	in = (in + 1) % BUFFER SIZE;
	count++; 

}