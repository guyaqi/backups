#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void sleep();

int main() {
    char str[] = "Hello,world!";
    for (int i = 0; i < sizeof(str) - 1; i++) {
        fprintf(stderr, "%c", str[i]);
        sleep();
    }
    return 0;
}

void sleep() {
#ifdef _WIN32
    Sleep(600);
#else
    usleep(600000);
#endif
}