#include "syscall.h"

int main() {
	PrintChar('A');
	PrintChar('\n');
	PrintChar('@');
	PrintChar(57);
	Halt();
	return 0;
}
