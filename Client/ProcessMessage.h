#pragma once

#include <string>

class ProcessMessage {
public:
	explicit ProcessMessage(std::string payload = std::string()) : payload_(std::move(payload)) {}

	// Serialize message to a single-line string suitable for piping.
	std::string toString() const { return payload_; }

private:
	std::string payload_;
};
