#include <iostream>
#include <string>
#include <memory>
#include <windows.h>
#include "RandomGenerator.h"
#include "Number.h"
#include "OddNumber.h"
#include "NumberStartsWithOne.h"
#include "ThreeDigitNumber.h"

int main()
{
	const std::size_t X = 10;

	RandomGenerator gen;
	auto v = gen.generate(X, 1, 999);

	// Build payload: each number's toString() on its own line
	std::string payload;
	for (auto val : v) {
		std::unique_ptr<Number> num;

		// Order: odd -> starts with '1' -> three-digit -> base Number
		if (val % 2 != 0) {
			num = std::make_unique<OddNumber>(val);
		} else {
			std::string s = std::to_string(val);
			if (!s.empty() && s[0] == '1') {
				num = std::make_unique<NumberStartsWithOne>(val);
			} else if (val >= 100 && val <= 999) {
				num = std::make_unique<ThreeDigitNumber>(val);
			} else {
				num = std::make_unique<Number>(val);
			}
		}

		payload += num->toString();
		payload += '\n';
	}

	// Create named pipe server and send payload
	const char* pipeName = "\\\\.\\pipe\\NumberGeneratorPipe";
	const DWORD outBufferSize = 4096;
	HANDLE hPipe = CreateNamedPipeA(
		pipeName,
		PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_BYTE | PIPE_WAIT,
		1,
		outBufferSize,
		outBufferSize,
		0,
		NULL);

	if (hPipe == INVALID_HANDLE_VALUE) {
		std::cerr << "CreateNamedPipe failed: " << GetLastError() << std::endl;
		return 1;
	}

	std::cout << "Waiting for client to connect to pipe " << pipeName << "..." << std::endl;
	BOOL connected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
	if (!connected) {
		std::cerr << "ConnectNamedPipe failed: " << GetLastError() << std::endl;
		CloseHandle(hPipe);
		return 1;
	}

	DWORD bytesWritten = 0;
	BOOL success = WriteFile(hPipe, payload.c_str(), static_cast<DWORD>(payload.size()), &bytesWritten, NULL);
	if (!success) {
		std::cerr << "WriteFile to pipe failed: " << GetLastError() << std::endl;
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);
		return 1;
	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	std::cout << "Sent payload to client (" << bytesWritten << " bytes)." << std::endl;
	return 0;
}
