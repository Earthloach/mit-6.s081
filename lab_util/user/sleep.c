#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(2, "Usage: sleep <number>\n");
        exit(1);
    }
    
    char *time = argv[1];

    int result = sleep(atoi(time));
    exit(result == 0 ? 0 : 1);
}