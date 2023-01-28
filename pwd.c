#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char buffer[1024];
    char *path = getcwd(buffer, sizeof(buffer));
    printf("%s\n", path);
    return 0;
}