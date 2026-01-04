#pragma once
#include "PipelineOperation.h"
#include <functional>

template<typename T>
class LambdaOperation final : public PipelineOperation<T>
{
public:
	explicit LambdaOperation(std::function<T(const T&)> function)
		: function_(std::move(function))
	{
	}

	T execute(const T& value) const override
	{
		return function_(value);
	}

private:
	std::function<T(const T&)> function_;
};
