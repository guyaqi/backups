#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Tlhelp32.h>

#define MAX_COUNT 256
#define MAX_LEN 128
// BlackList can only contain 256 items.
// Every name in the list contains 128 chars at most.
char blacklist[MAX_COUNT][MAX_LEN];
unsigned blacklist_len;

bool read_blaacklist() {
    FILE *file = fopen("blacklist", "r");
    if(!file) {
        fprintf(stderr, "faied to open blacklist.");
        return false;
    }
    int i = 0;
    while(fgets(blacklist[i], MAX_LEN, file)) i++;
    blacklist_len = (unsigned)i;
    return true;
}

bool in_blacklist(char *process_name) {
    for(int i=0;i<blacklist_len;i++) {
        if(strcmp(blacklist[i], process_name) == 0) return true;
    }
    return false;
}

bool killProcess(DWORD pid) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,TRUE, pid);
    if(!hProcess) {
        fprintf(stderr, "faied to get handle of target process.");
        return false;
    }
    TerminateProcess(hProcess,0);
    CloseHandle(hProcess);
}

int main(int argc, char *argv[])
{
    if(!read_blaacklist()) return -1;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);

    HANDLE hSnapshot_proc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot_proc != INVALID_HANDLE_VALUE)
    {
        BOOL check = Process32First(hSnapshot_proc, &pe32);
        while (check)
        {
//            printf("进程PID = %d 进程名 = %s\n", pe32.th32ProcessID, pe32.szExeFile);
            check = Process32Next(hSnapshot_proc, &pe32);
            if(in_blacklist(pe32.szExeFile)) {
                if(killProcess(pe32.th32ProcessID)) {
                    printf("%s(PID = %d) is killed\n", pe32.szExeFile, pe32.th32ProcessID);
                }

            }
        }
    }
    CloseHandle(hSnapshot_proc);
    return 0;
}