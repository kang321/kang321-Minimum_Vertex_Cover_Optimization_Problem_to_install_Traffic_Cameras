//references: https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
#include<vector>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<cstdlib>
#include<string.h>
#include<sstream>

using namespace std;

int main (int argc, char *argv[]){
vector<int> pid_Vect;

//initializing status for killing purpose
        int status;
        int def_s = 10;      //streets default
        int def_n = 5;       
        int def_l = 5;       
        int def_c = 20;     

        for(int i = 0; i< argc; i++){
            // street 
            if (strncmp("-s",argv[i],2)==0){
                def_s = atoi(argv[i+1]);
            }

            //  line segment
            if (strncmp("-n",argv[i],2)==0){
                def_n = atoi(argv[i+1]);
            }

            // wait time
            if (strncmp("-l",argv[i],2)==0){
                def_l = atoi(argv[i+1]);
            }
            // point range
            if (strncmp("-c",argv[i],2)==0){
                def_c = atoi(argv[i+1]);
        }
        }

    if(def_s<2){
        cerr<<"Error: input Streets > 5"<<endl;
        return 1;
    }

    if(def_c<1){
        cerr<<"Error: enter Coordinates more then 1"<<endl;
        return 1;
    }

    if(def_n<1){
        cerr<<"Error: enter Line segemnt  more than 1"<<endl;
        return 1;
    }

    if(def_l<5){
        cerr<<"Error: enter wait time > 5"<<endl;
        return 1;
    }

      

      


    //adding arrays with arguments
    char* a1_arg[3];
    a1_arg[0] = (char*)"/usr/bin/python3";
    a1_arg[1] = (char*)"ece650-a1.py";
    a1_arg[2] = nullptr;
    
    char* arg_rgen[10];
    arg_rgen[0] = (char*)"./rgen";
    arg_rgen[1] = (char*)"-s";
    //int_to_string_to_char
    arg_rgen[2] = (char*)to_string(def_s).c_str();
    arg_rgen[3] = (char*)"-n";
    arg_rgen[4] = (char*)to_string(def_n).c_str();
    arg_rgen[5] = (char*)"-l";
    arg_rgen[6] = (char*)to_string(def_l).c_str();
    arg_rgen[7] = (char*)"-c";
    arg_rgen[8] = (char*)to_string(def_c).c_str();
    arg_rgen[9] = nullptr;

    

    //process is 3, 
    //2 file  discreptors are present for 2 pipes.
    int fd1[2];
    int fd2[2];

    pid_t pid1, pid2, pid3;

    pipe(fd1);
    pipe(fd2);

    //regen -> A1
    pid1 = fork();
    if (pid1 == 0)
    {
		//child process 1 .... regen
        close(fd1[0]);
        dup2(fd1[1], 1);
        
        
        execv("./rgen", arg_rgen);
    }
    else if (pid1 < 0)
    {
        cerr << "Error: fork issue at pid1";
    }

    pid_Vect.push_back(pid1);

    //going from Ass1 to Ass2*/
    pid2 = fork();

    if (pid2 == 0)
    {
        //child process 2, .......A1
        close(fd1[1]);
        dup2(fd1[0], 0);
        
        
        close(fd2[0]);
        dup2(fd2[1], 1);
        

        execv("/usr/bin/python3", a1_arg);
    }
    else if (pid2 < 0)
    {
        cerr << "Error: fork issue at pid2";
    }

    pid_Vect.push_back(pid2);

    //EXECUTING  A2 */
    pid3 = fork();

    if (pid3 == 0)
    {
        //child process 3,.......... A2
        close(fd2[1]);
        dup2(fd2[0], 0);
        
        execlp("./ece650-a2", "./ece650-a2", nullptr);
    }
    else if (pid3 < 0)
    {
        cerr << "Error: fork issue at pid3";

    }

    pid_Vect.push_back(pid3);
    
    //A3 tooooooo A2
    dup2(fd2[1], 1);

    while(true){
    string inp;
    getline(cin, inp);
    if (cin.eof()){
        break;
    }
    if (inp.size() > 0)
       cout << inp << endl;
    }


    //Closing  write end of  the pipe
    close(fd1[1]);
    close(fd2[1]);

    //kill all child processes using for loop
    for (pid_t pid : pid_Vect)
    {       //using kill and sigterm to kill
            kill (pid, SIGTERM);
            waitpid(pid, &status, 0);
    }


return 0;
}


