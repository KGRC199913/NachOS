#include "syscall.h"

int main() {
	char buffer[100];
	OpenFileId srcId, desId;
	int r, test;
	Write("Src: \n", 6, 1);
	Read(buffer, 100, 0);
	srcId = Open(buffer, 0);
	if (srcId < 1) {
		CloseF(srcId);
		Write("Error: Source file not found\n", 30, 1);
		Halt(); 
	} 
	
	Write("Des: \n", 6, 1);
	r = Read(buffer, 100, 0);
	buffer[r] = '\0';
	test = Open(buffer, 0);
	if (test > 1) {
		CloseF(test);
		Write("Error: Desnitation file is already exist\n", 42, 1);
		Halt();
	}
	CreateFile(buffer);
	desId = Open(buffer, 0);
	do {	
		r = Read(buffer, 100, srcId);
		if (r <= 0)
			break;
		buffer[r] = '\0';
		Write(buffer, r, desId);
	} while (r > 0);
	CloseF(srcId);
	CloseF(desId);

	Halt();
}
