#pragma once
#include <exception>
#include <string>

class NotEnoughSlotsError : public std::exception {
private:
	std::string message_;

public:
	NotEnoughSlotsError(size_t created, size_t capacity) {
		message_ =
			"Not enough memory slots. Created objects: " +
			std::to_string(created) +
			" out of " +
			std::to_string(capacity) + ".";
	}

	const char* what() const noexcept override {
		return message_.c_str();
	}
};
