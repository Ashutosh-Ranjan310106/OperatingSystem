// Peterson's Solution for 2 processes // P_i // P_0
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
         flag[i] = true; 
         // P_i expresses its intent to 
         // enter the CS

         turn = j;
         // P_i is giving a chance to 
         // P_j to enter the CS by 
         // modifying "turn" to "j"

        // Keep on waiting till the other process has raised its flag and its the other process's turn
         while (flag[j] == true && turn == j); 
         // Busy Waiting Loop
         /* critical section */
         flag[i] = false;
         /*remainder section */
} 

