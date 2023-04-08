#include "Tracker/Tracker.h"
#include "SHA1/SHA1.h"

#include <iostream>
#include <strsafe.h>

Tracker::Tracker(char* path) {
	switch (GetFileAttributesA(path)) {
	case FILE_ATTRIBUTE_DIRECTORY: // For Directory Input
        directoryHandler(path);
		break;
	
    case FILE_ATTRIBUTE_ARCHIVE: // For Single file Input
        SaveFileHash(path);
		break;
	
    default:
		std::cout << "Invalid Path provided" << std::endl;
	};
}

void Tracker::directoryHandler(char* path) {
    SetCurrentDirectoryA(path);

#ifdef DEBUG_TRACKER
    char* a = new char[MAX_PATH_SIZE];
    GetCurrentDirectoryA(MAX_PATH_SIZE, a);
    PRINT("Current Directory is: " << a << std::endl);
#endif // DEBUG_TRACKER

    this->folder = path;
    this->ser = new Serializer(std::filesystem::path(std::string(this->folder)));
    getFileNames();
}

void Tracker::getFileNames() {
    std::vector<std::filesystem::path> files;
    for (const auto& file : std::filesystem::directory_iterator(this->folder)) {

#ifdef DEBUG_TRACKER
		std::cout << file.path() << std::endl;
#endif // DEBUG_TRACKER

        files.push_back(file.path());
	}
}

void Tracker::SaveFileHash(char* filename) {
    this->ser = new Serializer(std::filesystem::path(std::string(this->folder)));
    Message contents(&filename.string()[0], true);
    SHA1 context(&contents);
    context.createDigest();

#ifdef DEBUG_TRACKER
    std::cout << digestString(context.getDigest()) << std::endl;
#endif // DEBUG_TRACKER

    ser->update(filename.string(), context.getDigest());
    ser->serialize();        
}

Serializer* Tracker::getSerializer() {
    return ser;
}



// Debug code copied from Microsoft Docs

#include <strsafe.h>

void ErrorExit(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}