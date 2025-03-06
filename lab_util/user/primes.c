#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int p[2]);

int main (int argc, char *argv[]) {
    int pipefd[2];
    pipe(pipefd);
    
    int pid = fork();
    if (pid < 0) {
        fprintf(2, "fork failed\n");
        exit(1);
    }
    if (pid != 0) {
        close(pipefd[0]);
        for (int i = 2; i <= 35; i++) {
            write(pipefd[1], &i, sizeof(i));
        }
        close(pipefd[1]);
        wait(0);
    } else {
        sieve(pipefd);
    }
    exit(0);
}

void sieve(int p[2]) {
    int prime;
    close(p[1]);
    
    if (read(p[0], &prime, sizeof(prime)) == 0) {
        close(p[0]);
        exit(0);
    }
    printf("prime %d\n", prime);
    
    int new_pipefd[2];
    pipe(new_pipefd);
    int new_pid = fork();
    
    if (new_pid == 0) {
        close(p[0]);
        sieve(new_pipefd);
    } else {
        int new_num;
        close(new_pipefd[0]);
        while (read(p[0], &new_num, sizeof(new_num)) > 0) {
            if (new_num % prime != 0) {
                write(new_pipefd[1], &new_num, sizeof(new_num));
            }
        }
        close(p[0]);
        close(new_pipefd[1]);
        wait(0); 
    }
    exit(0);
}