#include "SHA1/SHA1.h"

Message::Message(char* input) {

	// Measure input string size
	while (input[initSize]) {
		initSize++;
	}

	// Measuring number of 512 bit message blocks needed
	numBlocks = (initSize + 8 + MESSAGE_SIZE) / MESSAGE_SIZE;

	// Pass input as member variable
	this->input = input;
}
Message::Message(char* filename, bool isFile) {
	if (!isFile) {
		Message::Message(filename);
	}

	// Opening file
	file.open(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error Opening file: " << filename << std::endl;
		throw NO_FILE_ERROR;
	}
	else {
		// Measuring size
		file.seekg(0, std::ios::end);
		initSize = file.tellg();
		file.seekg(0);

		// Measuring number of 512 bit message blocks needed 
		numBlocks = (initSize + 8 + MESSAGE_SIZE) / MESSAGE_SIZE;
		this->isFile = isFile;
	}
}

void Message::formatMessage() {

	// Set nth bit as 1
	if (currentBlock == initSize / MESSAGE_SIZE) {
		string[initSize % MESSAGE_SIZE] = 0x80;
	}

	// After initial message ends, fill the rest of string with zeroes
	if (currentBlock == numBlocks - 1) {

		// Set last 64 bits as initial message size
		unsigned long long int initSizeBytes = initSize * 8;
		unsigned char* initSizeCharArray = (unsigned char*)&initSizeBytes;
		for (int i = 0; i < sizeof(unsigned long long int); i++) {
			string[MESSAGE_SIZE - 1 - i] = initSizeCharArray[i];
		}
	}

	// Reverse the message in sets of 4 bytes to fix reversed cast in little endian systems
	littleToBigEndian(string, MESSAGE_SIZE);
}

unsigned char* Message::getBlock() {
	for (int currentChar = currentBlock * MESSAGE_SIZE; currentChar < MESSAGE_SIZE * (currentBlock + 1); currentChar++) {
		if (currentChar < initSize) {
			if (this->isFile) {
				file.read((char*)&string[currentChar - (currentBlock * MESSAGE_SIZE)], 1);
			}
			else {
				string[currentChar - (currentBlock * MESSAGE_SIZE)] = input[currentChar];
			}
		}
		else {
			string[currentChar - (currentBlock * MESSAGE_SIZE)] = 0;
		}
	}
	formatMessage();
	return string;
}

bool Message::hasNextBlock() {
	return (currentBlock != numBlocks);
}