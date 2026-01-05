#include <iostream>
#include "atomic_change_to.h"
#include "FieldProxy.h"
#include "Record.h"

int main() {
	Record person;

	FieldProxy<Record, std::string> name(
		[](Record& r, const std::string& v) {
			return r.setName(v);
		}
	);

	FieldProxy<Record, int> age(
		[](Record& r, int v) {
			r.age(v);
			return true;
		}
	);

	FieldProxy<Record, std::string> position(
		[](Record& r, const std::string& v) {
			r.position = v;
			return true;
		}
	);

	std::cout << std::boolalpha;

	bool success1 = atomic_change_to(person)(
		name = "Vasya",
		age = 22,
		position = "Best Developer"
	);

	std::cout << "Test 1: " << success1 << std::endl;

	bool success2 = atomic_change_to(person)(
		name = "",
		age = 19,
		position = "Junior Developer"
	);

	std::cout << "Test 2: " << success2 << std::endl;

	bool success3 = atomic_change_to(person)(
		name = "Roma",
		age = -19,
		position = "Student"
	);

	std::cout << "Test 3: " << success3 << std::endl;

	bool success4 = atomic_change_to(person)(
		position = "Manager",
		age = -10
	);

	std::cout << "Test 4: " << success4 << std::endl;

	bool success5 = atomic_change_to(person)(
		name = "Dima",
		age = 55,
		position = "Driver"
	);

	std::cout << "Test 5: " << success5 << std::endl;

	return 0;
}
