#include <iostream>
#include <cmath>

int main() {
    int x;
    std::cout << "Enter x: ";
    std::cin >> x;
    for (int K = 0; K <= x; K++) {
        if (pow(3, K) > x)
            continue;
        for (int L = 0; L <= x; L++) {
            if (pow(5, L) > x)
                continue;
            for (int M = 0; M <= x; M++) {
                if (pow(7, M) > x)
                    continue;
                double number = pow(3, K) * pow(5, L) * pow(7, M);
                if (number <= x)
                    std::cout << K << "\t" << L << "\t" << M << "\t" << number << std::endl;
            }
        }
    }
    return 0;
}
