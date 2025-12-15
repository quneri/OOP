#include "SimpleRNG.h"
#include <limits>

SimpleRNG::SimpleRNG(double modulus, double multiplier, double increment, double initial_state)
	: modulus_(modulus),
	  multiplier_(multiplier),
	  increment_(increment),
	  initial_state_(initial_state),
	  current_state_(initial_state) {
	validateParameters();
	if (!std::isfinite(initial_state_)) {
		throw std::invalid_argument("Initial_state must be finite");
	}
	initial_state_ = std::fmod(initial_state_, modulus_);
	if (initial_state_ < 0.0) initial_state_ += modulus_;
	current_state_ = initial_state_;
}

void SimpleRNG::validateParameters() const {
	if (!(modulus_ > 1.0)) {
		throw std::invalid_argument("Modulus must be > 1");
	}
	if (!(multiplier_ > 0.0 && multiplier_ < 1.0)) {
		throw std::invalid_argument("Multiplier must be > 0 and < 1");
	}
	if (!(increment_ >= 0.0 && increment_ < modulus_)) {
		throw std::invalid_argument("Increment must satisfy 0 <= increment < modulus");
	}
}

void SimpleRNG::reset() {
	current_state_ = initial_state_;
}

void SimpleRNG::reset(double new_initial) {
	if (!std::isfinite(new_initial)) {
		throw std::invalid_argument("New initial must be finite");
	}
	double normalized = std::fmod(new_initial, modulus_);
	if (normalized < 0.0) normalized += modulus_;
	initial_state_ = normalized;
	current_state_ = initial_state_;
}

SimpleRNG::Iterator SimpleRNG::begin() const {
	return Iterator(current_state_, multiplier_, increment_, modulus_, initial_state_, 0.05, false);
}

SimpleRNG::Iterator SimpleRNG::end(double eps) const {
	return Iterator(0.0, multiplier_, increment_, modulus_, initial_state_, eps, true);
}

double SimpleRNG::Iterator::NextValue(double x, double a, double c, double m) {
	double next = a * x + c;
	next = std::fmod(next, m);
	if (next < 0.0) next += m;
	if (next >= m) next = std::nextafter(m, 0.0);
	return next;
}

bool SimpleRNG::Iterator::approxEqual(double a, double b, double eps) {
	return std::fabs(a - b) <= eps + std::numeric_limits<double>::epsilon();
}

SimpleRNG::Iterator::Iterator(double current,
                              double multiplier,
                              double increment,
                              double modulus,
                              double generator_initial,
                              double eps,
                              bool is_end_marker)
	: current_(current),
	  multiplier_(multiplier),
	  increment_(increment),
	  modulus_(modulus),
	  generator_initial_(generator_initial),
	  eps_(eps),
	  is_end_marker_(is_end_marker),
	  is_start_(true),
	  reached_cycle_(false),
	  seen_values_(is_end_marker ? nullptr : std::make_shared<std::vector<double>>()),
	  iterations_(0) {
	if (!(eps_ >= 0.0)) {
		throw std::invalid_argument("Eps must be non-negative");
	}
	if (seen_values_) seen_values_->push_back(current_);
}

SimpleRNG::Iterator::reference SimpleRNG::Iterator::operator*() const {
	return current_;
}

SimpleRNG::Iterator& SimpleRNG::Iterator::operator++() {
	if (!is_end_marker_) {
		is_start_ = false;
		iterations_++;
		const std::size_t max_iter = 1000000;
		if (iterations_ > max_iter) {
			reached_cycle_ = true;
			return *this;
		}
		double next = NextValue(current_, multiplier_, increment_, modulus_);
		const double internal_eps = 1e-12;
		bool found = false;
		for (double v : *seen_values_) {
			if (approxEqual(next, v, internal_eps)) {
				found = true;
				break;
			}
		}
		current_ = next;
		if (found) {
			reached_cycle_ = true;
		} else {
			seen_values_->push_back(current_);
		}
	}
	return *this;
}

SimpleRNG::Iterator SimpleRNG::Iterator::operator++(int) {
	Iterator copy = *this;
	++(*this);
	return copy;
}

bool SimpleRNG::Iterator::operator==(const Iterator& other) const {
	if (this == &other) return true;
	if (is_end_marker_ && other.is_end_marker_) return true;
	if (other.is_end_marker_) {
		if (is_end_marker_) return true;
		return reached_cycle_;
	}
	if (is_end_marker_) {
		return other.reached_cycle_;
	}
	if (multiplier_ == other.multiplier_ &&
	    increment_ == other.increment_ &&
	    modulus_ == other.modulus_ &&
	    generator_initial_ == other.generator_initial_ &&
	    eps_ == other.eps_ &&
	    current_ == other.current_ &&
	    is_start_ == other.is_start_) {
		return true;
	}
	return false;
}

bool SimpleRNG::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}
