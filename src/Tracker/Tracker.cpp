#include "Tracker/Tracker.h"
#include <iostream>

Tracker::Tracker(char* filepath) {
	std::wcout << (GetFileAttributesA(filepath) == FILE_ATTRIBUTE_DIRECTORY ? "True" : "False") << std::endl;
}