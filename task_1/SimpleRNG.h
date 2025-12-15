#ifndef SIMPLERNG_H
#define SIMPLERNG_H

#include <cmath>
#include <iterator>
#include <stdexcept>
#include <memory>
#include <vector>

class SimpleRNG {
public:
	class Iterator {
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = double;
		using difference_type = std::ptrdiff_t;
		using pointer = const double*;
		using reference = const double&;

		Iterator() = default;

		Iterator(double current,
		         double multiplier,
		         double increment,
		         double modulus,
		         double generator_initial,
		         double eps,
		         bool is_end_marker = false);

		reference operator*() const;
		Iterator& operator++();
		Iterator operator++(int);
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

	private:
		double current_{0.0};
		double multiplier_{0.0};
		double increment_{0.0};
		double modulus_{1.0};
		double generator_initial_{0.0};
		double eps_{0.05};
		bool is_end_marker_{false};
		bool is_start_{true};
		bool reached_cycle_{false};
		std::shared_ptr<std::vector<double>> seen_values_;
		std::size_t iterations_{0};
		static double NextValue(double x, double a, double c, double m);
		static bool approxEqual(double a, double b, double eps);
	};

	SimpleRNG(double modulus, double multiplier, double increment, double initial_state = 0.0);

	void reset();
	void reset(double new_initial);

	Iterator begin() const;
	Iterator end(double eps = 0.05) const;

	double getCurrentState() const { return current_state_; }
	double getInitialState() const { return initial_state_; }
	double getMultiplier() const { return multiplier_; }
	double getIncrement() const { return increment_; }
	double getModulus() const { return modulus_; }

private:
	void validateParameters() const;

	double modulus_;
	double multiplier_;
	double increment_;
	double initial_state_;
	double current_state_;
};

#endif
