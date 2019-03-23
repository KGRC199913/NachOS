#include "syscall.h"

int main() {
	char c = ReadChar();
	Halt();
	return 0;
}
