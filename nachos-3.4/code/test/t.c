#include "syscall.h"

int main() {
	OpenFileId id;
	char buffer[10];
	id = Open("a.b", 0);
	Write("NEKONEKO", 9, id);
	Seek(4, id);
	Read(buffer, 4, id);
	PrintString(buffer);
	CloseF(id);
        return 0;
}
