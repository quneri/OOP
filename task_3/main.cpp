#include <iostream>
#include "MemReserver.h"

#define COLOR_RED       "\033[1;31m"
#define COLOR_YELLOW    "\033[33m"
#define COLOR_CYAN      "\033[36m"
#define COLOR_MAGENTA   "\033[35m"
#define COLOR_RESET     "\033[0m"

class SomeClass {
private:
	int x_, y_, z_;

public:
	SomeClass(int x = 0, int y = 0, int z = 0)
		: x_(x), y_(y), z_(z) {}

	void print() const {
		std::cout << "SomeClass(" << x_ << ", " << y_ << ", " << z_ << ")";
	}
};

template<typename T, size_t N>
void printContainerState(MemReserver<T, N>& reserver) {
	std::cout << COLOR_MAGENTA << "Container state: ";

	for (size_t i = 0; i < N; ++i) {
		try {
			T& object = reserver.get(i);
			std::cout << "[";
			object.print();
			std::cout << "]";
		}
		catch (const EmptySlotError&) {
			std::cout << "[ ]";
		}
	}

	std::cout << COLOR_RESET << "\n";
}

void runCapacityTest() {
	std::cout << COLOR_YELLOW
	          << "\n[TEST 1] Capacity overflow test\n"
	          << COLOR_RESET;

	MemReserver<SomeClass, 2> reserver;
	printContainerState(reserver);

	try {
		std::cout << COLOR_CYAN << "Creating first object\n" << COLOR_RESET;
		reserver.create();
		printContainerState(reserver);

		std::cout << COLOR_CYAN << "Creating second object\n" << COLOR_RESET;
		reserver.create(1, 2, 3);
		printContainerState(reserver);

		std::cout << COLOR_CYAN
		          << "Attempting to create third object\n"
		          << COLOR_RESET;
		reserver.create();
	}
	catch (const NotEnoughSlotsError& e) {
		std::cout << COLOR_RED << "Exception caught: "
		          << e.what() << COLOR_RESET << "\n";
		printContainerState(reserver);
	}
}

void runDeleteAndAccessTest() {
	std::cout << COLOR_YELLOW
	          << "\n[TEST 2] Delete and access test\n"
	          << COLOR_RESET;

	MemReserver<SomeClass, 2> reserver;
	printContainerState(reserver);

	std::cout << COLOR_CYAN << "Creating object\n" << COLOR_RESET;
	auto& object = reserver.create(10, 20, 30);
	printContainerState(reserver);

	size_t index = reserver.position(object);
	std::cout << COLOR_CYAN
	          << "Object position: " << index << "\n"
	          << COLOR_RESET;

	std::cout << COLOR_CYAN
	          << "Deleting object at index " << index << "\n"
	          << COLOR_RESET;
	reserver.deleteObject(index);
	printContainerState(reserver);

	try {
		std::cout << COLOR_CYAN
		          << "Attempting to access deleted object\n"
		          << COLOR_RESET;
		reserver.get(index);
	}
	catch (const EmptySlotError& e) {
		std::cout << COLOR_RED << "Exception caught: "
		          << e.what() << COLOR_RESET << "\n";
		printContainerState(reserver);
	}
}

int main() {
	std::cout << COLOR_MAGENTA
	          << "MemReserver demonstration started\n"
	          << COLOR_RESET;

	runCapacityTest();
	runDeleteAndAccessTest();

	std::cout << COLOR_MAGENTA
	          << "\nAll tests finished\n"
	          << COLOR_RESET;

	return 0;
}
