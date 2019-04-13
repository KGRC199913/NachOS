#include "syscall.h"

int main() {
	char buffer[100];
	int r;
	while (1) {
		r = Read(buffer, 100, 0);	
		Write(buffer, r, 1);
		Write("\n", 1, 1);
	}
}
