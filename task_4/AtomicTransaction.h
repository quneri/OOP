#pragma once

#include <tuple>
#include "AtomicChange.h"

template<typename T>
class AtomicTransaction {
public:
	explicit AtomicTransaction(T& object)
		: original_(object), working_copy_(object) {}

	template<typename... Changes>
	bool operator()(Changes&&... changes) {
		bool success = applyAll(std::forward<Changes>(changes)...);
		if (success) {
			original_ = working_copy_;
		}
		return success;
	}

private:
	T& original_;
	T working_copy_;

	template<typename First, typename... Rest>
	bool applyAll(First&& first, Rest&&... rest) {
		if (!first.apply(working_copy_)) {
			return false;
		}
		if constexpr (sizeof...(Rest) > 0) {
			return applyAll(std::forward<Rest>(rest)...);
		}
		return true;
	}
};
