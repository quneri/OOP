#pragma once

#include <string>
#include <stdexcept>

struct Record {
	bool setName(const std::string& str) {
		if (str.empty()) {
			return false;
		}
		name_ = str;
		return true;
	}

	void age(int value) {
		if (value < 0) {
			throw std::invalid_argument("Age < 0");
		}
		age_ = value;
	}

	std::string position;

private:
	int age_ = 0;
	std::string name_;
};
