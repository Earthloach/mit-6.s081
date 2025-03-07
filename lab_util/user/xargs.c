#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

#define MESGSIZE 16

int main(int argc, char *argv[]) {
    char buf[MESGSIZE];
    read(0, buf, MESGSIZE);

    char *xargv[MAXARG];
    int xargc = 0;
    for (int i = 1;i < argc; i++) {
        xargv[xargc++] = argv[i];
    } 

    char *p = buf;
    for (int i = 0; i < MESGSIZE; i++) {
        if (buf[i] == '\n') {
            int pid = fork();
            if (pid == 0) {
                buf[i] = 0;
                xargv[xargc++] = p;
                xargv[xargc++] = 0; 
                exec(xargv[0], xargv);
                exit(1);
            } else {
                p = &buf[i+1];
                wait(0);    
            }
        }
    }

    exit(0);
}