/****************************************************************************************
 * @brief Create a parent process to share the memory with child process using Shared Memory
 * SetupRead data from import files (around 5 files)
 * Import files with below structure, this is an email content need to be collected. 
 * From: sender 1 
 * To: receiver 1 
 * Content of email, write some thing here 
 * Send Monitor message (“is_alive”) to process 2 via socket (time out 1 second), this is a message check if process 2 still alive. Then wait for process 2 response alive message (“alive”). 
 * If process 2 still alive, save email data to shared memory. 
 * If process 2 is not alive, fork new process 2 
 * After process all files, send socket to Process 2 (“shutdown”), check alive of process 2, if not alive, shutdown process 1 also. 
*****************************************************************************************/

#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}