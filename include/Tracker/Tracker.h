#pragma once
#ifndef TRACKER_H
#define TRACKER_H

#include "Serializer/Serializer.h"

#include <Windows.h>
#include <fileapi.h>
#include <libloaderapi.h>
#include <filesystem>
#include <vector>

#define SINGLE 0
#define MULTI 1
#define MAX_PATH_SIZE 512

#ifdef DEBUG_TRACKER
#define PRINT(x) std::cout << x
#else
#define PRINT(x)
#endif // DEBUG_TRACKER

class Tracker
{
	int mode = MULTI;
	folder = new char[MAX_PATH_SIZE];
	Serializer *ser;
public:
	Tracker(char* folder);
	void directoryHandler(char* path);
	void getFileNames();
	void SaveFileHash(char* filename);
	Serializer* getSerializer();
};
	void ErrorExit(LPTSTR lpszFunction);

#endif // !TRACKER_H