#include <iostream>

int main() {
    std::vector<int> vec;
    int x;

    while (1) {
        std::cin >> x;
        if (x < 0) break;
        vec.insert(vec.end(), x);
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std::cout << *it << " ";
        std::cout << "\n";
        std::cout << "first element is " << vec[1] << std::endl;
        /* vector::operator[] does not range check
         * vector::at does range check, throws exception
         */
    }
    std::sort(vec.begin(), vec.end());
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
        std::cout << *it << " ";
    
    
    return 0;
}
        

    
