#include "syscall.h"

int main() {
	char buffer[100];
	OpenFileId fstId, secId, desId;
	int r, w;
	r = Read(buffer, 100, 0);
	buffer[r] = 0;
	fstId = Open(buffer, 0);
	if (fstId < 2) {
		Write("Error orcurred when open first file\n", 37, 1);
		Halt();
	}
	
	r = Read(buffer, 100, 0);
	buffer[r] = 0;
	secId = Open(buffer, 0);	
	if (secId < 2) {
		CloseF(fstId);
		Write("Error orcurred when open second file\n", 38, 1);
		Halt();
	}

	r = Read(buffer, 100, 0);
	buffer[r] = 0;
	desId = Open(buffer, 0);
	if (desId > 0) {
		CloseF(fstId);
		CloseF(secId);
		Write("Destination file is already existed\n", 37, 1);
		Halt();
	}
	CreateFile(buffer);
	desId = Open(buffer, 0);
	if (desId < 2) {
		CloseF(fstId);
		CloseF(secId);
		Write("Error orcurred when open third file\n", 38, 1);
		Halt();
	}
	
	do {
		r = Read(buffer, 100, fstId);
		if (r <= 0)
			break;
		Write(buffer, r, desId);
	} while (1);
	CloseF(fstId);	

	do {
		r = Read(buffer, 100, secId);
		if (r <= 0)
			break;
		Write(buffer, r, desId);
	} while (1);
	CloseF(secId);

	CloseF(desId);
	Halt();
}
