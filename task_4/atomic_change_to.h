#pragma once

#include "AtomicTransaction.h"

template<typename T>
AtomicTransaction<T> atomic_change_to(T& object) {
	return AtomicTransaction<T>(object);
}
