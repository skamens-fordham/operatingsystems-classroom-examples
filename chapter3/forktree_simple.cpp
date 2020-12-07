#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <string>
 
using namespace std;

int main(int argc, char ** argv)
{
    pid_t pid;
    
    int i;

    for (i = 0; i < 3; ++i) {
        
        pid = fork();

        if (pid == 0) {
            wait(NULL);
        } else {
            cout << "Child Process. i = " << i << endl;
        }   
    }
    return 0;
}