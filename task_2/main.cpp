#include <iostream>
#include <vector>
#include "Mask.h"

const std::string RED    = "\033[1;31m";
const std::string GREEN  = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE   = "\033[34m";
const std::string RESET  = "\033[0m";

template <typename T>
void print_container(const std::vector<T>& container, const std::string& color = RESET) {
    for (const auto& value : container) std::cout << color << value << " " << RESET;
    std::cout << std::endl;
}

std::vector<int> input_vector() {
    std::size_t size;
    std::cout << "Enter number of elements: ";
    std::cin >> size;
    std::vector<int> vec(size);
    std::cout << "Enter " << size << " integers separated by space: ";
    for (std::size_t i = 0; i < size; ++i) std::cin >> vec[i];
    return vec;
}

int main() {
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7};
    Mask<3> mask(1, 0, 0);

    std::cout << BLUE << "Test 1" << RESET << std::endl;
    std::cout << YELLOW << "Original container: " << RESET;
    print_container(numbers, GREEN);

    std::cout << YELLOW << "Mask: " << RESET;
    for (std::size_t i = 0; i < mask.size(); ++i) std::cout << mask.at(i) << " ";
    std::cout << std::endl;

    std::vector<int> numbers_for_slice = numbers;
    mask.slice(numbers_for_slice);
    std::cout << YELLOW << "After slice: " << RESET;
    print_container(numbers_for_slice, RED);

    std::vector<int> transformed = mask.transform(numbers, [](int v){ return v * 10; });
    std::cout << YELLOW << "After transform (*10): " << RESET;
    print_container(transformed, RED);

    std::vector<int> sliced_transformed = mask.slice_and_transform(numbers, [](int v){ return v * v; });
    std::cout << YELLOW << "After slice_and_transform (^2): " << RESET;
    print_container(sliced_transformed, RED);

    std::vector<int> numbers2{10, 20, 30, 40, 50};
    Mask<2> mask2(0, 1);

    std::cout << BLUE << "\nTest 2" << RESET << std::endl;
    std::cout << YELLOW << "Original container: " << RESET;
    print_container(numbers2, GREEN);
    std::cout << YELLOW << "Mask: " << RESET;
    for (std::size_t i = 0; i < mask2.size(); ++i) std::cout << mask2.at(i) << " ";
    std::cout << std::endl;

    std::vector<int> numbers2_for_slice = numbers2;
    mask2.slice(numbers2_for_slice);
    std::cout << YELLOW << "After slice: " << RESET;
    print_container(numbers2_for_slice, RED);

    std::vector<int> transformed2 = mask2.transform(numbers2, [](int v){ return v + 5; });
    std::cout << YELLOW << "After transform (+5): " << RESET;
    print_container(transformed2, RED);

    std::vector<int> sliced_transformed2 = mask2.slice_and_transform(numbers2, [](int v){ return v / 10; });
    std::cout << YELLOW << "After slice_and_transform (/10): " << RESET;
    print_container(sliced_transformed2, RED);

    std::cout << BLUE << "\nTest 3 (Interactive, Mask<3>)" << RESET << std::endl;
    std::vector<int> user_numbers = input_vector();

    Mask<3> user_mask(1, 0, 1);

    std::cout << YELLOW << "Original container: " << RESET;
    print_container(user_numbers, GREEN);

    std::cout << YELLOW << "Mask: " << RESET;
    for (std::size_t i = 0; i<user_mask.size(); ++i) std::cout << user_mask.at(i) << " ";
    std::cout << std::endl;

    std::vector<int> user_numbers_for_slice = user_numbers;
    user_mask.slice(user_numbers_for_slice);
    std::cout << YELLOW << "After slice: " << RESET;
    print_container(user_numbers_for_slice, RED);

    std::vector<int> user_transformed = user_mask.transform(user_numbers, [](int v){ return v * 2; });
    std::cout << YELLOW << "After transform (*2): " << RESET;
    print_container(user_transformed, RED);

    std::vector<int> user_sliced_transformed = user_mask.slice_and_transform(user_numbers, [](int v){ return v + 100; });
    std::cout << YELLOW << "After slice_and_transform (+100): " << RESET;
    print_container(user_sliced_transformed, RED);

    return 0;
}
