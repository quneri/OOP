#include <iostream>

#include "atomic_change_to.h"
#include "Record.h"

int main() {
	Record person;

	std::cout << std::boolalpha;

	bool success1 = atomic_change_to(person)(
		[](Record& r) { return r.setName("Vasya"); },
		[](Record& r) { r.age(22); return true; },
		[](Record& r) { r.position = "Best Developer"; return true; }
	);

	std::cout << "Test 1: " << success1 << '\n';

	bool success2 = atomic_change_to(person)(
		[](Record& r) { return r.setName(""); },
		[](Record& r) { r.age(30); return true; }
	);

	std::cout << "Test 2: " << success2 << '\n';

	bool success3 = atomic_change_to(person)(
		[](Record& r) { r.age(-1); return true; }
	);

	std::cout << "Test 3: " << success3 << '\n';

	bool success4 = atomic_change_to(person)(
		[](Record& r) { r.position = "manager"; return true; },
		[](Record& r) { r.age(-1); return true; }
	);

	std::cout << "Test 4: " << success4 << '\n';

	bool success5 = atomic_change_to(person)(
		[](Record& r) { return r.setName("Roma"); },
		[](Record& r) { r.age(19); return true; },
		[](Record& r) { r.position = "Student"; return true; }
	);

	std::cout << "Test 5: " << success5 << '\n';

	return 0;
}
