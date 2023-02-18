#include "Tracker/Tracker.h"
#include "SHA1/SHA1.h"

#include <libloaderapi.h>
#include <iostream>
#include <string>
#include <iomanip>

#define MESSAGE_BYTES 64

void reverse(unsigned char *message, int i, int j) {
	char temp;
	while (i < j) {
		temp = message[i];
		message[i] = message[j];
		message[j] = temp;
		i++; j--;
	}
}

int main() {

	char a[] = ".";
	char* input = (char*)&a;
	Tracker v(input);
	for (int j = 0; j < 4; j++) {
		input[j] = a[j];
	}

	try {
		Message* msg = new Message(input);
		SHA1* context = new SHA1();

		std::cout << digestString(context->update(msg->getBlock())) << std::endl;
	}
	catch (int e) {
		if (e == NO_FILE_ERROR) {
			return 1;
		}
	}

	/*TCHAR pbuf[256];
	int bytes = GetCurrentDirectory((DWORD)256, pbuf);
	std::wcout << pbuf << std::endl;*/


	//std::string text = "abc";
	//unsigned char* message = new unsigned char[MESSAGE_BYTES] {0};
	//int length = text.size();
	//long long int length64 = length * 8;
	//unsigned char* lengthChar = (unsigned char*)&length64;
	//int i = 0, j;

	//for (i = 0; i < length; i++) {
	//	message[i] = text[i];
	//}
	//message[i] = 0X80;
	//
	//std::cout << "Length in char: " << length64 << std::endl;

	//if (MESSAGE_BYTES - (length + 1) >= 8) {
	//	for (i = 0; i < 8; i++) {
	//		message[MESSAGE_BYTES - 1 - i] = lengthChar[i];
	//	}
	//}

	//for (i = 0; i < MESSAGE_BYTES; i += 4) {
	//	j = i + 3;
	//	reverse(message, i, j);
	//}

	//for (int i = 0; i < MESSAGE_BYTES/4; i++) {
	//	std::wcout << std::hex << std::setw(9) << ((int *)message)[i] << " ";
	//	if ((i+1) % 8 == 0) {
	//		std::cout << std::endl;
	//	}
	//}
	//std::cout << std::endl;
	//SHA1 hash;
	//unsigned int* out = hash.update(message);
	//for (int i = 0; i < 5; i++) {
	//	std::wcout << std::hex << out[i];
	//}
	//std::cout << std::endl;
	return 0;
}