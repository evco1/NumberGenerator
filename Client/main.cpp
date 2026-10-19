#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "ProcessMessage.h"

// Client connects to a named pipe created by the number generator process and
// reads a single-line message. Pipe name is configurable here.
int main(int /*argc*/, char** /*argv*/)
{
	const char* pipeName = "\\\\.\\pipe\\NumberGeneratorPipe";

	// Try to open the pipe. Wait for up to 5 seconds for the server to create it.
	DWORD waitMs = 5000;
	BOOL connected = FALSE;
	HANDLE hPipe = INVALID_HANDLE_VALUE;

	DWORD start = GetTickCount();
	while (GetTickCount() - start < waitMs) {
		hPipe = CreateFileA(
			pipeName,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if (hPipe != INVALID_HANDLE_VALUE) {
			connected = TRUE;
			break;
		}

		// If the pipe is busy, wait a little and retry
		if (GetLastError() == ERROR_PIPE_BUSY) {
			if (!WaitNamedPipeA(pipeName, 1000)) {
				Sleep(100);
			}
		} else {
			Sleep(100);
		}
	}

	if (!connected) {
		std::cerr << "Failed to connect to pipe: " << pipeName << std::endl;
		return 1;
	}

	std::vector<char> buffer(4096);
	std::string received;
	DWORD bytesRead = 0;
	BOOL success = FALSE;

	// Read until the server closes the pipe or no data remains
	for (;;) {
		success = ReadFile(hPipe, buffer.data(), static_cast<DWORD>(buffer.size()), &bytesRead, NULL);
		if (!success || bytesRead == 0) break;
		received.append(buffer.data(), buffer.data() + bytesRead);
		// If less than buffer, likely end of message
		if (bytesRead < buffer.size()) break;
	}

	CloseHandle(hPipe);

	// Trim trailing newlines

	while (!received.empty() && (received.back() == '\n' || received.back() == '\r')) received.pop_back();

	ProcessMessage msg(received);
	std::cout << "Received: " << msg.toString() << std::endl;
	return 0;
}
