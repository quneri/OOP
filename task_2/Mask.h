#ifndef MASK_H
#define MASK_H

#include <array>
#include <cstddef>
#include <stdexcept>

template <std::size_t MaskSize>
class Mask {
public:
    template <typename... Values>
    explicit Mask(Values... values) : mask_{static_cast<bool>(values)...} {
        static_assert(sizeof...(Values) == MaskSize, "Wrong number of elements in mask");
        bool valid[] = { ((values == 0 || values == 1) ? true : throw std::invalid_argument("Mask can contain only 0 or 1"))... };
        (void)valid;
    }

    [[nodiscard]] std::size_t size() const noexcept { return MaskSize; }

    bool at(std::size_t index) const {
        if (index >= MaskSize) throw std::out_of_range("Mask index out of range");
        return mask_[index];
    }

    template <typename Container>
    void slice(Container& container) const {
        if (container.size() == 0) return;
        for (std::size_t i = container.size(); i-- > 0;) {
            if (!is_mask_enabled(i)) container.erase(container.begin() + static_cast<long>(i));
        }
    }

    template <typename Container, typename UnaryFunction>
    Container transform(const Container& container, UnaryFunction transform_function) const {
        Container result = container;
        for (std::size_t i = 0; i < result.size(); ++i) {
            if (is_mask_enabled(i)) result.at(i) = transform_function(result.at(i));
        }
        return result;
    }

    template <typename Container, typename UnaryFunction>
    Container slice_and_transform(const Container& container, UnaryFunction transform_function) const {
        Container result;
        for (std::size_t i = 0; i < container.size(); ++i) {
            if (is_mask_enabled(i)) result.push_back(transform_function(container.at(i)));
        }
        return result;
    }

private:
    std::array<bool, MaskSize> mask_;

    [[nodiscard]] bool is_mask_enabled(std::size_t index) const noexcept { return mask_[index % MaskSize]; }
};

#endif
