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

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
<<<<<<< HEAD
    if (which == NoException)
        return;
    else if (which == SyscallExeption) {
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
                case SC_Exec:{
                
                }
                case SC_Join:{}
                case SC_Create:{}
                case SC_Open:{}
                case SC_Read:{}
                case SC_Close:{}
                case SC_Fork:{}
                case SC_Yield:{}
                default:{}
        }
    }
	else {
		ExceptionHandler_NonSyscall(which, type);
	}
}

void ExceptionHandler_NonSyscall(ExceptionType which, int type) {
    /*
    Handle non-syscall exceptions
    @param which: Exception type, type: syscall codes in r2
    @return void
    */
	switch (which){
		case PageFaultException: {
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
=======

    if ((which == SyscallException) && (type == SC_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    } else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
>>>>>>> efed15cba95bba139952880b797f7f9b0103e287
}
