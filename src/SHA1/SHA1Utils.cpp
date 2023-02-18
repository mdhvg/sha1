#include "SHA1/SHA1.h"

void littleToBigEndian(unsigned char* block, int size) {
	int j, temp;
	for (int i = 0; i < size; i += 2) {
		j = i + 3;
		while (i < j) {
			temp = block[i];
			block[i] = block[j];
			block[j] = temp;
			i++; j--;
		}
	}
}

unsigned char* digestString(unsigned int* Hn) {
	unsigned char* hnCharArray = new unsigned char[20] {0};
	for (int i = 0; i < 20; i++) {
		hnCharArray[i] = ((unsigned char*)Hn)[i];
	}
	littleToBigEndian(hnCharArray, 20);
	unsigned char* digest = new unsigned char[41] {0};
	int charIndex = 39;
	unsigned int n;
	for (int i = 19; i >= 0; i--) {
		n = hnCharArray[i];
		for (int j = 0; j < 2; j++) {
			digest[charIndex] = getHexChar(n % 16);
			charIndex--, n /= 16;
		}
	}
	return digest;
}

unsigned char getHexChar(unsigned int charInt) {
	if (charInt < 10) {
		return (unsigned char)(charInt + ASCII_ZERO);
	}
	else if (charInt < 16) {
		return (unsigned char)((charInt % 10) + ASCII_SMALL_A);
	}
}