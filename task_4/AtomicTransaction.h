#pragma once

#include <utility>

template<typename T>
class AtomicTransaction {
public:
	explicit AtomicTransaction(T& object)
		: original_(object), copy_(object) {}

	template<typename... Operations>
	bool operator()(Operations&&... ops) {
		if (applyAll(std::forward<Operations>(ops)...)) {
			original_ = copy_;
			return true;
		}
		return false;
	}

private:
	T& original_;
	T copy_;

	template<typename Operation>
	bool applyOne(Operation&& op) {
		try {
			return op(copy_);
		} catch (...) {
			return false;
		}
	}

	template<typename First, typename... Rest>
	bool applyAll(First&& first, Rest&&... rest) {
		if (!applyOne(std::forward<First>(first))) {
			return false;
		}
		if constexpr (sizeof...(Rest) > 0) {
			return applyAll(std::forward<Rest>(rest)...);
		}
		return true;
	}
};
