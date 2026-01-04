#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <utility>
#include "LambdaOperation.h"

template<typename T>
class Pipeline
{
public:
	explicit Pipeline(T initialValue)
		: value_(std::move(initialValue)), executed_(false)
	{
	}

	~Pipeline()
	{
		if (!executed_)
		{
			execute();
		}
	}

	Pipeline(const Pipeline&) = delete;
	Pipeline& operator=(const Pipeline&) = delete;

	Pipeline(Pipeline&&) noexcept = default;
	Pipeline& operator=(Pipeline&&) noexcept = default;

	Pipeline& operator()()
	{
		execute();
		return *this;
	}

	template<typename Function>
	Pipeline& operator|(Function function) &
	{
		addOperation(std::move(function));
		return *this;
	}

	template<typename Function>
	Pipeline&& operator|(Function function) &&
	{
		addOperation(std::move(function));
		return std::move(*this);
	}

private:
	template<typename Function>
	void addOperation(Function function)
	{
		operations_.push_back(
			std::make_unique<LambdaOperation<T>>(
				std::function<T(const T&)>(std::move(function))
			)
		);
	}

	void execute()
	{
		for (const auto& operation : operations_)
		{
			value_ = operation->execute(value_);
		}
		executed_ = true;
	}

	T value_;
	bool executed_;
	std::vector<std::unique_ptr<PipelineOperation<T>>> operations_;
};
