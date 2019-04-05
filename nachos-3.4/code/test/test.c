#include "syscall.h"

int main() {
        OpenFileId create;
        int testclose;
 	create=OpenFile("test.txt",0);
        if (create==-1)
          PrintString("Unsucessful\n"); else PrintString("Successful\n");
	testclose=CloseFile(create);
        if (testclose==-1)
           PrintString("Unsucessful close\n"); else PrintString("Successful closel\n");
        return 0;
}
