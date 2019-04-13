#include "syscall.h"

int main() {
	OpenFileId id;
	char buffer[100];
	int r;
	Read(buffer, 100, 0);
	id = Open(buffer, 0);
	if (id < 0) {
		Write("File Open Error\n", 16, 1);
		Halt();
	}	
	do {
		r = Read(buffer, 100, id);
		Write(buffer, r, 1);
	} while (r > 0);
	Write("\n", 1, 1);
	CloseF(id);
	Halt();
}
