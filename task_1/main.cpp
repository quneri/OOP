#include "SimpleRNG.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>

int main() {
	SimpleRNG generator(5.0, 0.2, 1.0, 0.4);
	generator.reset(0.4);

	std::vector<double> vec;
	std::copy(generator.begin(), generator.end(0.05), std::back_inserter(vec));

	std::cout << "\033[36mGenerated sequence:\033[0m\n";
	for (double v : vec) {
		std::cout << v << " ";
	}
	std::cout << "\n";

	if (!vec.empty()) {
		double min_val = *std::min_element(vec.begin(), vec.end());
		double max_val = *std::max_element(vec.begin(), vec.end());
		double avg_val = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
		std::cout << "\033[1;31mStatistics: min = " << min_val
				  << ", max = " << max_val
				  << ", average = " << avg_val << "\033[0m\n";
	}

	std::cout << "\n\033[36mRange-based iteration starting from 0 with default eps:\033[0m\n";
	generator.reset(0.0);
	int cnt = 0;
	for (auto x : generator) {
		if (cnt++ > 20) break;
		std::cout << x << " ";
	}
	std::cout << "\n\n";

	std::cout << "\033[35mAdditional test: different parameters (modulus = 10, a = 0.3, c = 2, X0 = 1.0)\033[0m\n";
	SimpleRNG gen2(10.0, 0.3, 2.0, 1.0);
	std::vector<double> vec2;
	std::copy(gen2.begin(), gen2.end(0.0001), std::back_inserter(vec2));

	std::cout << "\033[36mGenerated sequence:\033[0m\n";
	for (double v : vec2) {
		std::cout << v << " ";
	}
	std::cout << "\n";

	if (!vec2.empty()) {
		double min_val = *std::min_element(vec2.begin(), vec2.end());
		double max_val = *std::max_element(vec2.begin(), vec2.end());
		double avg_val = std::accumulate(vec2.begin(), vec2.end(), 0.0) / vec2.size();
		std::cout << "\033[1;31mStatistics: min = " << min_val
				  << ", max = " << max_val
				  << ", average = " << avg_val << "\033[0m\n";
	}

	return 0;
}
