#include "syscall.h"

int main() {
	OpenFileId id;
	
	id = Open("v.txt", 0);
	PrintInt(id);
        return 0;
}
