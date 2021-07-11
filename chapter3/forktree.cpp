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

    cout << getpid() << ": Main program" << endl;

    for (i = 0; i < 4; ++i) {
        pid = fork();
        if (pid != 0) {
            cout << getpid() << setw(i * 4) << ": i= " << i << ". forked child " << pid << endl;
        }   
    }

    sleep(100);
    return 0;
}
