// Peterson's Solution for 2 processes // Pi
int turn; 
boolean flag[2];


flag[0] = false;
flag[1] = false;

while (true) {

         turn = 1; // (2)
         flag[0] = true; // (3)

         while (flag[1] && turn == 1); (4)
         /* critical section */
         flag[0] = false;
         /*remainder section */
} 

// Drawbacks of Peterson's Solution

// 1. Dealt with only 2 processes
// 2. In the modern computer architectures
// that provide for multiple cores,
// parallel execution, and hence, 
// Instruction Reordering, it is possible
// that the logic dictated by 
// Peterson's Solution is violated by 
// the reordered instructions