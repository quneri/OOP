#pragma once

#include "AtomicChange.h"

template<typename T, typename Field>
class FieldProxy {
public:
	using Setter = std::function<bool(T&, Field)>;

	FieldProxy(Setter setter)
		: setter_(std::move(setter)) {}

	Change<T> operator=(Field value) const {
		return Change<T>(
			[=](T& obj) {
				return setter_(obj, value);
			}
		);
	}

private:
	Setter setter_;
};
