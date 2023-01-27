#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
        return 1;
    }
    int i=1;
    while(i<argc){
        printf("%s",argv[i]);
        if(i < argc-1)
            printf(" ");
        i++;
    }
    return 0;
}