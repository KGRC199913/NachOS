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
	test = Open(buffer, 0);
	if (test > 1) {
		CloseF(test);
		Write("Error: Desnitation file is already exist\n", 42, 1);
		Halt();
	}
	CreateFile(buffer);
	desId = Open(buffer, 0);
	len = Seek(-1, srcId);
	--len;
	while (len >= 0) {
		--len;
		Seek(len, srcId);
		Read(buffer, 1, srcId);
		Write(buffer, 1, desId);
	}

	CloseF(srcId);
	CloseF(desId);
	Halt();
}
