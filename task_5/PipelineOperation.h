#pragma once

template<typename T>
class PipelineOperation
{
public:
	virtual ~PipelineOperation() = default;
	virtual T execute(const T& value) const = 0;
};
