#pragma once

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <Windows.h>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <iostream>

class Serializer {
	std::filesystem::path directory;
	std::unordered_map <std::filesystem::path, unsigned int*> fileHashes;
	std::fstream file;
	std::vector <std::string> changed;

public:
	Serializer(std::filesystem::path directory) : directory(directory), fileHashes(deserialize()) {};
	~Serializer();
	void serialize();
	std::unordered_map <std::filesystem::path, unsigned int*> deserialize();
	void update(std::string filename, unsigned int* hn);
	std::vector <std::string> getChangedFilenames();
};

#endif // !SERIALIZER_H