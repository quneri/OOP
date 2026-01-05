#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "PipeOperator.h"

int main()
{
	std::cout << "Test 1: " << std::endl;

	std::string str = "Hello World!";

	make_pipe(str)
		| [](const std::string& s)
		{
			return s.size();
		}
		| [](std::size_t x)
		{
			return x * 2;
		}
		| [](std::size_t x)
		{
			std::cout << "Result: " << x << std::endl;
		};

	std::cout << std::endl;

	std::cout << "Test 2: " << std::endl;

	make_pipe(11)
		| [](int x)
		{
			return x * 1.5;
		}
		| [](double x)
		{
			return std::to_string(x);
		}
		| [](const std::string& s)
		{
			std::cout << "Result: " << s << std::endl;
		};

	std::cout << std::endl;

	std::cout << "Test 3: " << std::endl;

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};

	make_pipe(vec)
		| [](const std::vector<int>& v)
		{
			return v.size();
		}
		| [](std::size_t size)
		{
			std::cout << "Result: " << size << std::endl;
		};

	std::cout << std::endl;

	std::cout << "Test 4: " << std::endl;

	std::array<int, 4> arr = {11, 22, 33, 44};

	make_pipe(arr)
		| [](const std::array<int, 4>& a)
		{
			return a.size();
		}
		| [](std::size_t x)
		{
			return x * 7;
		}
		| [](std::size_t x)
		{
			std::cout << "Result: " << x << std::endl;
		};

	std::cout << std::endl;

	std::cout << "Test 5: " << std::endl;

	make_pipe(12345)
		| [](int x)
		{
			std::cout << "Result: " << x << std::endl;
		};

	std::cout << std::endl;

	std::cout << "Test 6: " << std::endl;

	make_pipe(3)
		| [](int x) { return x + 10; }
		| [](int x)
		{
			std::cout << "Result: " << x << std::endl;
		};

	make_pipe(3)
		| [](int x) { return x * 10; }
		| [](int x)
		{
			std::cout << "Result: " << x << std::endl;
		};

	std::cout << std::endl;

	std::cout << "Test 7: " << std::endl;

	make_pipe(std::string("C++ is interesting language"))
		| [](const auto& value)
		{
			return value.size();
		}
		| [](auto size)
		{
			std::cout << "Result: " << size << std::endl;
		};

	std::cout << std::endl;

	return 0;
}
