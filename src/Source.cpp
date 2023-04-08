#include "Tracker/Tracker.h"
#include "SHA1/SHA1.h"

#include <iostream>
#include <string>
#include <iomanip>

#define MESSAGE_BYTES 64

int main(int argc, char** argv) {
#ifdef DEBUG
	PRINT("Number of command line arguments: " << argc << std::endl);
	PRINT("Command line arugments are: ");
	for (int i = 1; i < argc; i++) {
		PRINT(argv[i] << " ");
	}
	PRINT(std::endl);
#endif // DEBUG

	switch (argc) {
	case 1:		// No input for tracking
	{
		Tracker track((char*)".");

#ifdef DEBUG || DEBUG_TRACKER
		PRINT("Changed files are: \n");
#endif // DEBUG

		for (auto& i : track.getSerializer()->getChangedFilenames()) {

#ifdef DEBUG || DEBUG_TRACKER
			PRINT(i << std::endl);
#endif // DEBUG

		}
		break;
	}
	case 2:		// Only directory/filename as input for tracking
	{
		Tracker track(argv[1]);

#ifdef DEBUG || DEBUG_TRACKER
		PRINT("Changed files are: \n");
#endif // DEBUG

		for (auto& i : track.getSerializer()->getChangedFilenames()) {

#ifdef DEBUG || DEBUG_TRACKER
			PRINT(i << std::endl);
#endif // DEBUG

		}
		break;
	}
	case 3:
		// Directory/filename/string as input for only hashing
		break;
	default:
		break;
	}

	return 0;
}