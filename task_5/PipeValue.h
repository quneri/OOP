#pragma once

template<typename T>
class PipeValue
{
public:
	explicit PipeValue(T value)
		: value_(value)
	{
	}

	T& get()
	{
		return value_;
	}

	const T& get() const
	{
		return value_;
	}

private:
	T value_;
};
