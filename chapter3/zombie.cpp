// A C program to demonstrate Zombie Process.  
// Child becomes Zombie as parent is sleeping 
// when child process exits. 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h>

int main() 
{ 
    // Fork returns process id 
    // in parent process 
    pid_t child_pid = fork(); 
  
    // Parent process  
    if (child_pid > 0) {
        sleep(20);
        wait(NULL);
    }
    // Child process 
    else {
        // Child will exit right away, becoming a zombie
        // until the parent waits() for it

    	sleep(10);	    
        exit(0); 
    }

    return 0; 
} 
