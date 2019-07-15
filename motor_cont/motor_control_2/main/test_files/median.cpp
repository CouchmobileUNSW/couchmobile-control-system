#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> values;
    values.push_back(4);
    values.push_back(0);
    values.push_back(100);
    values.push_back(0);
    values.push_back(0);
    values.push_back(4);
    values.push_back(2);


    std::sort(values.begin(), values.end());

    std::cout << "Sorted list: ";
    for(std::vector<int>::iterator it = values.begin(); 
        it != values.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Median: ";
    int median;

    // Odd number
    if(values.size() % 2 == 0) {
        median = ( values[values.size()/2] + values[values.size()/2 - 1] )/2;
    }
    // Even number 
    else {
        median = values[values.size()/2];
    }
    std::cout << median << std::endl;

    return 0;
}