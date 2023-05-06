#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

int main() {
    // Input sets
    std::vector<std::string> setA{"one", "two", "three", "four"};
    std::vector<std::string> setB{"two", "four", "six"};

    // Sort the input sets
    std::sort(setA.begin(), setA.end());
    std::sort(setB.begin(), setB.end());

    // Declare a vector to store the result
    std::vector<std::string> resultSet;

    // Calculate the set difference and store it in the resultSet
    std::set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(), std::back_inserter(resultSet));

    // Print the result set
    std::cout << "Result set: ";
    for (const auto& elem : resultSet) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
