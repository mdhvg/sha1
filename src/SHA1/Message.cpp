#include "SHA1/SHA1.h"

Message::Message(char* input) {

	// Measure input string size
	while (input[initSize]) {
		initSize++;
	}

	numBlocks = (initSize + 8 + MESSAGE_SIZE) / MESSAGE_SIZE;

	this->input = input;


	/*

	***REMOVE***





	// Make size of string array as needed while adding 1 byte for padding and 8 bytes for initial length
	stringsLen = (size + MESSAGE_SIZE + 8) / MESSAGE_SIZE;
	strings = new char* [stringsLen];

	// Copy string into chunks of 512 bit (64 byte) char arrays
	int chunkNum = 0, currentByte = 0;
	for (chunkNum = 0; chunkNum < stringsLen; chunkNum++) {
		strings[chunkNum] = new char[MESSAGE_SIZE];
		for (currentByte = chunkNum * MESSAGE_SIZE; currentByte < (MESSAGE_SIZE * (chunkNum + 1)); currentByte++) {
			if (currentByte >= size) {
				break;
			}
			strings[chunkNum][currentByte] = input[currentByte];
		}
	}

	// Add extra 0x80 byte
	strings[chunkNum][currentByte] = 0x80;







	*/
}
Message::Message(char* filename, bool isFile) {
	if (!isFile) {
		Message::Message(filename);
	}

	// Opening file
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error Opening file: " << filename << std::endl;
	}

	// Measuring size
	file.seekg(0, std::ios::end);
	initSize = file.tellg();
	file.seekg(0, std::ios::beg);

	this->isFile = isFile;
}

void Message::formatMessage() {
	if (currentBlock == numBlocks) {
		for (int currentChar = initSize % MESSAGE_SIZE; currentChar < MESSAGE_SIZE; currentChar++) {
			string[currentChar] = 0;
		}
		string[initSize % MESSAGE_SIZE] = 0x80;
		unsigned char* initSizeCharArray = (unsigned char*)initSize;
		for (int i = 0; i < sizeof(unsigned long long int); i++) {
			string[MESSAGE_SIZE - 1 - i] = initSizeCharArray[i];
		}
	}
	littleToBigEndian(string);
}

void Message::littleToBigEndian(unsigned char* block) {
	int j, temp;
	for (int i = 0; i < MESSAGE_SIZE; i += 4) {
		j = i + 3;
		while (i < j) {
			temp = block[i];
			block[i] = block[j];
			block[j] = temp;
			i++; j--;
		}
	}
}

unsigned char* Message::getBlock() {
	if (isFile) {
		file.read((char*)string, MESSAGE_SIZE);
		formatMessage();
	}
	else {
		int currentChar;
		for (currentChar = currentBlock * MESSAGE_SIZE; currentChar < MESSAGE_SIZE * (currentBlock + 1); currentChar++) {
			if (currentChar < initSize) {
				string[currentChar - (currentBlock * MESSAGE_SIZE)] = input[currentChar];
			}
			else {
				string[currentChar - (currentBlock * MESSAGE_SIZE)] = 0;
			}
		}
		formatMessage();
	}
	currentBlock++;
	return string;
}