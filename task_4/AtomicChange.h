#pragma once

#include <functional>
#include <tuple>
#include <utility>
#include <exception>

template<typename T>
class Change {
public:
	explicit Change(std::function<bool(T&)> action)
		: action_(std::move(action)) {}

	bool apply(T& obj) const {
		try {
			return action_(obj);
		} catch (...) {
			return false;
		}
	}

private:
	std::function<bool(T&)> action_;
};
