#pragma once
#ifndef SHA1_H
#define SHA1_H

#define MASK 0XF
#define MESSAGE_SIZE 512>>3

#include <iostream>
#include <string>
#include <fstream>

class SHA1 {
public:

	int t, s, quarter;
	unsigned int* Kt, * Hn, * Wn, temp, A, B, C, D, E;

	SHA1();

	unsigned int* update(unsigned char* Message);
	unsigned int circularLeftShift(unsigned int num, int shift);
	unsigned int bitWiseFunction(unsigned int B, unsigned int C, unsigned int D);
	void oneRound();
};

class Message {
public:
	/*
	Variables:
		unsigned char* string			: Pointer to 512 bit long unsigned character array
		unsigned long long int initSize	: Size of initial message in 64 bit unsigned integer
		unsigned int numBlocks			: Number of 512 bit long character arrays that will be used
		unsigned int currentBlock		: Counter for current block
		bool isFile						: Flag to check if input is file
		char* input						: Input variable pointer in case of string input
		std::ifstream file				: File stream pointer in case of file input
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
	void littleToBigEndian(unsigned char* block);
	unsigned char* getBlock();
};

#endif // !SHA1_H