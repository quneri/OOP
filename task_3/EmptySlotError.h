#pragma once
#include <exception>
#include <string>

class EmptySlotError : public std::exception {
private:
	std::string message_;

public:
	explicit EmptySlotError(size_t index) {
		message_ =
			"Slot with index " +
			std::to_string(index) +
			" is empty or does not exist.";
	}

	const char* what() const noexcept override {
		return message_.c_str();
	}
};
