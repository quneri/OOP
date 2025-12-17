#pragma once
#include <cstddef>
#include <utility>

#include "NotEnoughSlotsError.h"
#include "EmptySlotError.h"

template<typename T, size_t N>
class MemReserver {
private:
	alignas(T) char storage_[sizeof(T) * N];
	bool occupied_[N] = { false };
	size_t current_count_ = 0;

	T* getPointer(size_t index) {
		return reinterpret_cast<T*>(storage_ + index * sizeof(T));
	}

public:
	MemReserver() = default;

	~MemReserver() {
		for (size_t i = 0; i < N; ++i) {
			if (occupied_[i]) {
				getPointer(i)->~T();
			}
		}
	}

	template<typename... Args>
	T& create(Args&&... args) {
		for (size_t i = 0; i < N; ++i) {
			if (!occupied_[i]) {
				T* object = new (getPointer(i)) T(std::forward<Args>(args)...);
				occupied_[i] = true;
				++current_count_;
				return *object;
			}
		}
		throw NotEnoughSlotsError(current_count_, N);
	}

	void deleteObject(size_t index) {
		if (index >= N || !occupied_[index]) {
			throw EmptySlotError(index);
		}
		getPointer(index)->~T();
		occupied_[index] = false;
		--current_count_;
	}

	T& get(size_t index) {
		if (index >= N || !occupied_[index]) {
			throw EmptySlotError(index);
		}
		return *getPointer(index);
	}

	size_t position(T& object) {
		for (size_t i = 0; i < N; ++i) {
			if (occupied_[i] && getPointer(i) == &object) {
				return i;
			}
		}
		throw EmptySlotError(static_cast<size_t>(-1));
	}

	size_t count() const {
		return current_count_;
	}
};
