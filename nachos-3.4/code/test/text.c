#include "syscall.h"

int main() {
	char buffer[501];
	buffer[500] = 0;
	ReadString(buffer, 500);
	PrintString(buffer);
	PrintChar('\n');
	Halt();
	return 0;
}
