// Peterson's Solution for 2 processes P_j // P_1
// Shared Variable
int turn;

// Shared Array
boolean flag[2];

flag[0] = false;
flag[1] = false;
// Neither of the processes wish to enter the
// CS

// Mutual Exclusion
// Progress
// Bounded Waiting

while (true) {
         flag[j] = true; 
         // P_j expresses its intent to 
         // enter the CS

         turn = i;
         // P_j is giving a chance to 
         // P_i to enter the CS by 
         // modifying "turn" to "i"

        // Keep on waiting till the other process has raised its flag and its the other process's turn
         while (flag[i] == true && turn == i); 
         // Busy Waiting Loop
         /* critical section */
         flag[j] = false;
         /*remainder section */
} 

