#include "syscall.h"

int main() {
	char buffer[501];
	buffer[500] = 0;
	ReadString(buffer, 500);
	Halt();
	return 0;
}
