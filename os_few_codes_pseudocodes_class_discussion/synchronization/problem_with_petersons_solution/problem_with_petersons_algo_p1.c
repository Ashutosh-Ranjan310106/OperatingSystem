// Peterson's Solution for 2 processes - P1
int turn;
boolean flag[2];


flag[0] = false;
flag[1] = false;

while (true) {

         turn = 0; // (1)
         flag[1] = true; // (5)

         while (flag[0] && turn == 0); (6)
         /* critical section */
         flag[1] = false;
         /*remainder section */
} 

// Dummy concurrent run

// flag[0] = false
// flag[1] = false
// turn = 0
// turn = 1
// flag[0] = true

// (flag[1] && turn == 1) = false
// (entered the CS of P_0)

// flag[1] = true
// (flag[0] && turn == 0) = false
// (entered the CS of P_1)