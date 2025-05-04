// Consumer - Not synchronized
while (true) {
    while (count == 0); /* do nothing */

    next_consumed = buffer[out];
	out = (out + 1) % BUFFER SIZE;

    count--; 
	/* consume the item in next_consumed */ 
} 
