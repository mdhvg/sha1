#pragma once
#ifndef SHA1_H
#define SHA1_H

#define MASK 0XF
#define MESSAGE_SIZE 64
#define NO_FILE_ERROR 0X01
#define ASCII_ZERO 48
#define ASCII_SMALL_A 97

#include <iostream>
#include <string>
#include <fstream>

/*
	Implementation details can be found in https://nvlpubs.nist.gov/nistpubs/Legacy/FIPS/fipspub180-1.pdf
*/

// Creates SHA1 context
class SHA1 {
public:

	/*
	Variables:
		int t,																			: Round counter
			s,																			: 512 bit word list index
			quarter;																	: Round counter to select bitwise function for every iteration
		unsigned int *Kt,																: SHA-1 constants
					 *Hn,																: Initial message digest
					 *Wn,																: 32-bit word array for each block
					 temp,																: Intermediate temporary variable used in iterations
					 A, B, C, D, E;														: Intermediate digest state variables

	Functions:
		SHA1();																			: Constructor to set initial values for SHA-1 constants
		unsigned int* update(unsigned char* Message);									: Performs 1 iteration and updates digest
		unsigned int circularLeftShift(unsigned int num, int shift);					: Performs circular shift
		unsigned int bitWiseFunction(unsigned int B, unsigned int C, unsigned int D);	: Performs bitwise function according to current iteration quarter on B,C,D
		unsigned char* digestString();
		unsigned char getHexChar(unsigned int charInt);
		void oneRound();																: Performs one round of 80 on input block
	*/

	int t, s, quarter;
	unsigned int* Kt, * Hn, * Wn, temp, A, B, C, D, E;

	SHA1();

	unsigned int* update(unsigned char* Message);
	unsigned int circularLeftShift(unsigned int num, int shift);
	unsigned int bitWiseFunction(unsigned int B, unsigned int C, unsigned int D);
	void oneRound();
};

// Forms message chunks required for SHA1
class Message {
public:
	/*
	Variables:
		unsigned char* string							: Pointer to 512 bit long unsigned character array
		unsigned long long int initSize					: Size of initial message in 64 bit unsigned integer
		unsigned int numBlocks							: Number of 512 bit long character arrays that will be used
		unsigned int currentBlock						: Counter for current block
		bool isFile										: Flag to check if input is file
		char* input										: Input variable pointer in case of string input
		std::ifstream file								: File stream pointer in case of file input

	Functions:
		Message(char* input)							: Constructor overload when input is string
		Message(char* filename, bool isFile)			: Constructor overload when input is file
		void formatMessage()							: Performs all necessary modifications to message string
		unsigned char* getBlock()						: Returns the next block of message as output
	*/

	unsigned char* string = new unsigned char[MESSAGE_SIZE] {0};
	unsigned long long int initSize = 0;
	unsigned int numBlocks = 0;
	unsigned int currentBlock = 0;
	bool isFile = false;
	char* input = nullptr;
	std::ifstream file;

	Message(char* input);
	Message(char* filename, bool isFile);

	void formatMessage();
	unsigned char* getBlock();
};

// Reverses a word stored in little endian format to big endian for parsing correctly
void littleToBigEndian(unsigned char* block, int size);

// Returns hex string for a given message digest
unsigned char* digestString(unsigned int* Hn);

// Returns corresponding ASCII value for given integer
unsigned char getHexChar(unsigned int charInt);

#endif // !SHA1_H