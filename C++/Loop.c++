#include <iostream>


int main() {
    int a = 5;
    int b = 5;
    int max;

    if (a > b) {
        max = a;
    } else if (a == b) {
        std::cout << "Kedua nilai sama." << std::endl;
        return 0;
    } else {
        max = b;
    }

    std::cout << "Nilai Maximal adalah " << max;
}