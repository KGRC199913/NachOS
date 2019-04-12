// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

#define MAX_INT32_LENGTH	5
#define MAX_BUFFER_SIZE		1024

void ExceptionHandler_NonSyscall(ExceptionType which, int type) {
    /*
    Handle non-syscall exceptions
    @param which: Exception type, type: syscall codes in r2
    @return void
    */
	switch (which){	case PageFaultException: {
			printf("No valid translation found/%d %d\n", which, type);
			ASSERT(FALSE);
		}
		case ReadOnlyException: {
			printf("Write attempted on page marked 'read-only'/%d %d\n", which, type);
			ASSERT(FALSE); 
		}
		case BusErrorException: {
			printf("Translation result in an invalid physical address/%d %d\n", which, type);
			ASSERT(FALSE);
		}
		case AddressErrorException: {
			printf("Unaligned reference or one that was beyond the endof the address space/%d %d\n", which, type);
			ASSERT(FALSE); 
		}
		case OverflowException: {
			printf("Interger overflow in add or sub/%d %d\n", which, type);
			ASSERT(FALSE);
		}
		case IllegalInstrException: {
			printf("Unimplemented or reserved instruction/%d %d\n", which, type);
			ASSERT(FALSE);
		}
		case NumExceptionTypes: {}
		default: {
			printf("Unexpected user mode exception %d %d\n", which, type);
			ASSERT(FALSE);
		}
	}

    if ((which == SyscallException) && (type == SC_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    } else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
}

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
    if (which == NoException)
        return;
    else if (which == SyscallException) {
        switch (type) {
                case SC_Halt:
                {
	                DEBUG('a', "Shutdown, initiated by user program.\n");
   	                interrupt->Halt();
                    break;
                }
                case SC_Exit:{
   	                Exit(0);
                    break;
                }
		case SC_ReadInt: {
			int numberRead = 0;
			int numberOfDigits = 0;
			int negativeModifier = 1;
			bool isInt = true;
			char* OneByteBuffer = new char[2]; //preserved for terminated char
			OneByteBuffer[1] = 0;			
			int consoleStatusNum = 0;
			do {
				consoleStatusNum = gSynchConsole->Read(OneByteBuffer, 1);
				if (consoleStatusNum != 1) {  // ^D, CR, etc
					break;  
				}
				if ((OneByteBuffer[0] < 48) || (OneByteBuffer[0] > 57)) {
					if (numberOfDigits == 0) {
						if (OneByteBuffer[0] == '-') {
							negativeModifier = -1;
						} else {
							if (OneByteBuffer[0] == ' ') {
								continue;							
							}
							isInt = false;
							break;
						}
					} else {
						if (OneByteBuffer[0] != ' ')
							isInt = false;
						else
							break;
					}
				} else {
					numberRead *= 10;
					numberRead += (OneByteBuffer[0] - 48);
					++numberOfDigits;
				}
			} while (numberOfDigits < MAX_INT32_LENGTH);
			numberRead *= isInt;
			numberRead *= negativeModifier;
			machine->WriteRegister(2, numberRead);
			delete[]OneByteBuffer;
		}			
			break;
		case SC_PrintInt: {
			int numberToPrint = machine->ReadRegister(4);
			if (numberToPrint == 0) {
				char zero = '0';
				gSynchConsole->Write(&zero, 1);
				break;
			}

			char* buffer = new char[MAX_INT32_LENGTH + 2]; // preserved for negative and terminated \0
			if (!buffer) {
				DEBUG('a', "Failed to init a read buffer at PrintInt");
				break;
			}

			int bufferCurrentPositionPtr = 0;	
			int numberLength = 0;		

			if (numberToPrint < 0) {
				buffer[bufferCurrentPositionPtr++] = '-';
				numberToPrint = -numberToPrint;		
				++numberLength;	
			}

			int maskNum = 1;
			for (int numberToPrintCopy = numberToPrint; numberToPrintCopy != 0; numberToPrintCopy /= 10) {
				maskNum *= 10;
				++numberLength;
			}  // loop to ensure flexibility
			maskNum /= 10;

			do {
				buffer[bufferCurrentPositionPtr++] = (numberToPrint / maskNum) + 48;
				numberToPrint %= maskNum;
				maskNum /= 10;
			} while (maskNum != 0);
			buffer[bufferCurrentPositionPtr] = 0;

			gSynchConsole->Write(buffer, numberLength);
			delete[]buffer;
		}
			break;
		case SC_ReadChar: {
			char readBuffer[2]; // preserved for \0
			gSynchConsole->Read(readBuffer, 1);
			
			machine->WriteRegister(2, readBuffer[0]);
		}
			break;
		case SC_PrintChar: {
			char chToPrint = static_cast<char>(machine->ReadRegister(4));
			gSynchConsole->Write(&chToPrint, 1);
		}
			break;
		case SC_ReadString: {
			char* readBuffer = new char[MAX_BUFFER_SIZE];
			if (!readBuffer) {
				DEBUG('a', "Failed to init a read buffer at ReadString");
				break;
			}
			
			int strUserAddress = machine->ReadRegister(4);
			int length = machine->ReadRegister(5);
			int actualReadCharacterNumber = gSynchConsole->Read(readBuffer, length);
			readBuffer[actualReadCharacterNumber] = 0;
			machine->System2User(strUserAddress, actualReadCharacterNumber + 1, readBuffer);
			delete[]readBuffer;
		}
			break;
		case SC_PrintString: {
			int toPrintStrAddr = machine->ReadRegister(4);
			char* buffer = new char[MAX_BUFFER_SIZE];
			if (!buffer) {
				DEBUG('a', "Failed to init a read buffer at PrintString");
				break;
			}
			buffer = machine->User2System(toPrintStrAddr, MAX_BUFFER_SIZE);
			int curStrPtr = 0;
			while (buffer[curStrPtr] != 0) {
				gSynchConsole-> Write(buffer + curStrPtr, 1);
				++curStrPtr;
			} // Because we dont know the lenght of the print str, we'll print it char by char
			delete[]buffer;
		}
			break;
                case SC_CreateFile: {
                        int toCreateFileAddr = machine->ReadRegister(4);
                        char* buffer = new char [MAX_BUFFER_SIZE];
                        buffer = machine->User2System(toCreateFileAddr, MAX_BUFFER_SIZE);
                        if (fileSystem->Create(buffer, 0) == false)
				{	
					//TODO: Duplicate name
					DEBUG('f',"Unsucessful");
					machine->WriteRegister(2, -1);
				} else
				{
					DEBUG('f',"Successful");
					machine->WriteRegister(2, 0);
				};
			delete [] buffer;
			break;
                }
                case SC_Open: {
			int bufferAddress = machine->ReadRegister(4); // read string pointer from user
			int type = machine->ReadRegister(5);
			char *buffer = new char[MAX_BUFFER_SIZE];
			buffer = machine->User2System(bufferAddress, MAX_BUFFER_SIZE);
                        bool check = false;
			int i;
                        for (i=2;i<10;i++)
			{
				OpenFile* f = fileSystem->Open(buffer);
				if (f) {
					if ((fileSystem->FileList[i] == NULL) && (!check) && (fileSystem->countfile < 11))
					{
				    		fileSystem->FileList[i] = f;
                                    		fileSystem->type[i] = type;
                                    		check = true;
                                    		++fileSystem->countfile;
				    		break;
					}
				}
			}

                        if (check==false)
                        {
				DEBUG('f',"unsucessful");
                                machine->WriteRegister(2, -1);
                                delete []buffer;
                                break;
			}
			else
                        {
				DEBUG('f',"Successful");
				machine->WriteRegister(2, i);
			};
			delete [] buffer;
			break;
		}
                case SC_Close: {
			int id = machine->ReadRegister(4);
                        bool check=false;
			if ((fileSystem->FileList[id]) && (id > 2) && (id < 10)) {
				delete fileSystem->FileList[id];
				fileSystem->FileList[id] = NULL;
				fileSystem->type[id] = 0;	
				--fileSystem->countfile;
				check = true;			
			}                        

                        if (check)
 			{
				DEBUG('f'," File Closed Successfully");
				machine->WriteRegister(2,0);
			} 
			else
			{
				DEBUG('f',"File Closed Unsuccessfully");
				machine->WriteRegister(2,-1);
			}
                        break;
		}
		case SC_Read: {
			int userBufferAddress = machine->ReadRegister(4);
			int length = machine->ReadRegister(5);
			int id = machine->ReadRegister(6);
			char * buffer = new char[4096];
			int actualRead = 0;
			if (id == 1 || id < 0 || id > 10) { // read from output console or invalid fileID
				machine->WriteRegister(4, -1);
				delete[]buffer;
				break;			
			}
			if (id == 0) { //console
				actualRead = gSynchConsole->Read(buffer, length); 
			} else { //file
				if (!fileSystem->FileList[id]) { // no opnened file with id
					machine->WriteRegister(4, -1);
					delete[]buffer;
					break;
				}
				actualRead = fileSystem->FileList[id]->Read(buffer, length);
			}
			actualRead = (actualRead == 0 || actualRead == -1) ? -2 : actualRead;
			machine->WriteRegister(4, actualRead);
			machine->System2User(userBufferAddress, actualRead, buffer);
			delete[]buffer;
			break;
		}
		case SC_Write: {
			int toWriteAddress = machine->ReadRegister(4);
			int length = machine->ReadRegister(5);
			int id = machine->ReadRegister(6);
			char * buffer = new char[4096];
			int actualWrite = 0;
			if (fileSystem->type[id] == 1) { // Read only files
				machine->WriteRegister(4, -1);
				delete[]buffer;
				break;	
			}
			if (id <= 0 || id > 10) { // write to input console or invalid id
				machine->WriteRegister(4, -1);
				delete[]buffer;
				break;	
			}
			buffer = machine->User2System(toWriteAddress, 4096);
			if (id == 1) { //console
				while (buffer[actualWrite] != 0) {
					gSynchConsole-> Write(buffer + actualWrite, 1);
					++actualWrite;
				}
				--actualWrite;
			} else {
				if (!fileSystem->FileList[id]) { // no opnened file with id
					machine->WriteRegister(4, -1);
					delete[]buffer;
					break;
				}
				while (buffer[actualWrite] != 0) {
					fileSystem->FileList[id]->Write(buffer + actualWrite, 1);
					++actualWrite;
				}
				--actualWrite;
			}
			machine->WriteRegister(4, actualWrite);
			delete[]buffer;
			break;
		}
		case SC_Seek: {
			int pos = machine->ReadRegister(4);
			int id = machine->ReadRegister(5);
			if (id < 2 || id > 10 || !fileSystem->FileList[id]) {
				machine->WriteRegister(4, -1);
				break;
			}
			int len = fileSystem->FileList[id]->Length();
			if (pos == -1 || pos > len) {
				pos = len;
			}
			fileSystem->FileList[id]->Seek(pos);
			machine->WriteRegister(4, pos);
			break;
		}		
                default:{}
        }
	// Advance program counters.
    	machine->registers[PrevPCReg] = machine->registers[PCReg];
    	machine->registers[PCReg] = machine->registers[NextPCReg];
    	machine->registers[NextPCReg] += 4;
    } else {
	ExceptionHandler_NonSyscall(which, type);
    }	
}



