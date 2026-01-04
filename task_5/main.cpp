#include <iostream>
#include <string>
#include "Pipeline.h"

int main()
{
	{
		std::cout << "Test 1" << std::endl;

		std::string str = "It is just a test string for Pipeline";

		Pipeline<std::size_t>(str.size())
			| [](std::size_t x)
			{
				return x * 2;
			}
			| [](std::size_t x)
			{
				std::cout << "Result: " << x << std::endl;
				return x;
			};

		std::cout << std::endl;
	}

	{
		std::cout << "Test 2" << std::endl;

		Pipeline<int>(5)
			| [](int x)
			{
				return x + 123;
			}
			| [](int x)
			{
				return x * 4;
			}
			| [](int x)
			{
				std::cout << "Result: " << x << std::endl;
				return x;
			};

		std::cout << std::endl;
	}

	{
		std::cout << "Test 3" << std::endl;

		std::string str = "C++ is interesting language";

		Pipeline<std::size_t>(str.length())
			| [](std::size_t x)
			{
				std::cout << "Result: " << x << std::endl;
				return x;
			};

		std::cout << std::endl;
	}

	{
		std::cout << "Test 4" << std::endl;

		auto pipeline = Pipeline<int>(12)
			| [](int x)
			{
				return x * x;
			}
			| [](int x)
			{
				std::cout << "Result: " << x << std::endl;
				return x;
			};

		pipeline();

		std::cout << std::endl;
	}

	return 0;
}
