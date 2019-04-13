#include "syscall.h"

int main() {
	char buffer[100];
	int r = Read(buffer, 100, 0);
	CreateFile(buffer);
	Halt();
}
