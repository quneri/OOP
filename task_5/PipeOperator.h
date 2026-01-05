#pragma once

#include <type_traits>
#include <utility>
#include "PipeValue.h"

template<typename T>
PipeValue<T> make_pipe(T value)
{
	return PipeValue<T>(std::move(value));
}

template<typename T, typename Function>
auto operator|(PipeValue<T>&& pipe, Function&& function)
{
	using ResultType = decltype(function(pipe.get()));

	if constexpr (std::is_void_v<ResultType>)
	{
		function(pipe.get());
		return;
	}
	else
	{
		return PipeValue<ResultType>(function(pipe.get()));
	}
}
