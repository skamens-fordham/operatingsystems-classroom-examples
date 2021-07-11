// A C program to demonstrate Orphan Process.  
// Child becomes an orphan if the parent exits 
// while the child is still running. 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 

#include <iostream>

using namespace std;

int main() 
{ 
    cout << "Parent pid: " << getpid() << ". " << "Parent of parent: " << getppid() << endl;

    // Create a child process       
    int pid = fork(); 

    if (pid > 0) {
        sleep(5);
    } else if (pid == 0) 
    { 
        // We're in the child process

        cout << "Child pid: " << getpid() << ". Parent pid: " << getppid() << endl;
        sleep(6); 
        cout << "Child pid: " << getpid() << ". Parent pid: " << getppid() << endl;
    } 
  
    return 0; 
} 
