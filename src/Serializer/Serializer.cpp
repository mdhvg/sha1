#include "Serializer/Serializer.h"

#define HASH_FILE ".hashDb"

#ifdef DEBUG_TRACKER
#define PRINT(x) std::cout << x
#endif // DEBUG_TRACKER

Serializer::~Serializer() {
	file.close();
}

std::unordered_map <std::filesystem::path, unsigned int*> Serializer::deserialize() {
	std::unordered_map <std::filesystem::path, unsigned int*> hashes;
	std::filesystem::path hashFile = this->directory / HASH_FILE;
#ifdef DEBUG_TRACKER
	PRINT("Hash file is: " << hashFile << std::endl);
#endif // DEBUG_TRACKER
	if (!std::filesystem::exists(hashFile)) {

#ifdef DEBUG_TRACKER
		PRINT("Hash file does not exist\n");
#endif // DEBUG_TRACKER
		std::fstream file(hashFile.c_str(), std::ios::out);
		file.close();
		return hashes;
	}

	file = std::fstream(hashFile.c_str(), std::ios::binary | std::ios::in | std::ios::out);
	if (!file.is_open()) {

#ifdef DEBUG_TRACKER
		PRINT("Could not open hash file\n");
#endif // DEBUG_TRACKER

		return hashes;
	}

	while (!file.eof()) {
		int nameSize;
		file.read((char*)&nameSize, sizeof(int));
		std::string filename(nameSize, ' ');
		file.read(&filename[0], nameSize);
		unsigned int* hash = new unsigned int[5];
		file.read((char*)hash, sizeof(int) * 5);
		hashes[std::filesystem::path(filename)] = hash;
	}
}

void Serializer::serialize() {
	for (const auto& entry : fileHashes) {
		int nameSize = entry.first.string().size();
		file.write((char*)&nameSize, sizeof(int));
		file.write(entry.first.string().c_str(), nameSize);
		for (int i = 0; i < 5; i++) {
			file.write((char*)&entry.second[i], sizeof(int));
		}
	}
}

void Serializer::update(std::string filename, unsigned int* hn) {
#ifdef DEBUG_TRACKER
	PRINT("Changed files are: \n");
#endif // DEBUG_TRACKER
	auto it = fileHashes.find(filename);
	if (it == fileHashes.end()) {
		fileHashes[filename] = new unsigned int[5];
	}
	for (int i = 0; i < 5; i++) {
		if (fileHashes[filename][i] != hn[i]) {
#ifdef DEBUG_TRACKER
		PRINT(filename << std::endl);
#endif // DEBUG_TRACKER
			fileHashes[filename][i] = hn[i];
			changed.push_back(filename);
		}
	}
}

std::vector <std::string> Serializer::getChangedFilenames() {
	return changed;
}