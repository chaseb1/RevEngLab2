// RevEngLab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>

char GlobalChars13[14] = "Here's  data!";
char GlobalChars15[16] = "More      data!";

int SomeAddress = 1234;

#pragma bss_seg(".myData")
int BssData[3] = { 1, 2, 3 };

void myFunc (int a)
{
	printf ("A is: %d\n", a);
}

int main()
{
	char uninitString[15];
	int  localData[3];
	char myChar14[15] = "abcdefghijklmn";

	// Copies 12 bytes from the BSS section of the program to the stack
	//   copy 3 integers at 4 bytes each
	//   from bss to local variables in the stack
	for (int i = 0; i < 3; i++)
		localData[i] = BssData[i];

	// Copies 13 bytes from the heap to the DATA section
	//   'new' operator declares string in the heap
	//   GlobalChars was declared as a global, so it's in DATA
	char *allocatedData = new char[13];
	sprintf_s (allocatedData, 13, "Yeah,  data!");
	strncpy_s (GlobalChars13, allocatedData, 13);
	delete[] allocatedData;

	// Copies 14 bytes from the stack to the heap
	char *newData = new char[15];
	for (int i = 0; i < 14; i++)
		newData[i] = myChar14[i];
	//strncpy_s (newData, &myChar14[0], 14);

	// Copies 15 bytes from the data section to the BSS
	char *allocated15Bytes = new char[15];
	for (int i = 0; i < 15; i++)
		allocated15Bytes[i] = GlobalChars15[i];


	// Copies 4 bytes from the text section to the DATA section
	//   A function pointer can point at the beginning of a function in the text section
	//   Copy this to a global variable in the DATA section
	void(*myFuncPtr)(int);
	myFuncPtr = &myFunc;
	SomeAddress = (int)myFuncPtr;
	return 0;
}

