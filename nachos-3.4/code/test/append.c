#include "syscall.h"

int main() {
	char buffer[100];
	OpenFileId srcId, desId;
	int r, test, len;
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
	desId = Open(buffer, 0);
	if (desId < 0) {
		CreateFile(buffer);
		desId = Open(buffer, 0);
	}
	Seek(-1, desId);
	do {
		r = Read(buffer, 100, srcId);
		if (r <= 0) {
			break;
		}
		Write(buffer, 100, desId);
	} while (r > 0);

	CloseF(srcId);
	CloseF(desId);

	Halt();
}
