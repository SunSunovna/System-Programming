#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>
#include <iostream>
#include <dirent.h>

using namespace std;

int main(int argc, char **file_1) 
{
    //file_1[1] - из какой директории копируем, "/home/746-saa1/dir_lab4/"
    //file_1[2] - в какую директорию копируем, "/home/746-saa1/"

    DIR *dir = opendir(file_1[1]);
    struct dirent *entry;
    if (!dir)
    {
        perror("diropen");
        exit(1);
    }
    while ((entry = readdir(dir))!=NULL)
    {
        string file = entry->d_name; // d_name - название файла
        if (file[0] != '.')
        {
            file = file_1[1] + file; // полный путь к файлу
            //cout << file << endl;

            pid_t num; // идентификатор процесса 
            num = fork(); // запуск процесса
            cout << num << endl;

            switch(num) {
            case -1:
                perror("fork"); // произошла ошибка
                return -1;
            case 0: 
                //дочерний процесс
                execl("/home/746-saa1/lab4", "lab4", file.c_str(), file_1[2], (char *)0);
                return 13;
            default: {
                //процесс-родитель 
                int status;
                waitpid(num, &status, 0);
                //wait(&status);
                printf("exit normally? %s\n", (WIFEXITED(status) ? "true" : "false"));
                printf("child exitcode = %i\n", WEXITSTATUS(status));
                break;
                }
            } 
        }
    }   
    closedir(dir);
    exit(EXIT_SUCCESS);

    //system("find /home/746-saa1/dir_lab4/ -maxdepth 1 -type f");

    return 0;
}