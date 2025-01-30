#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

// Define the system call number (this will depend on where it's located in the syscall table)
#define __NR_test_call 335 // Replace 335 with your actual syscall number, you can find it in the syscall table.

int main() {
    long result = syscall(__NR_test_call); // Call the system call
    if (result < 0) {
        printf("System call failed with error code %ld.\n", result);
        
    } else {
        printf("congratulations System call executed successfully. now execute demsg to get system level call\n");
    }
    return 0;
}
