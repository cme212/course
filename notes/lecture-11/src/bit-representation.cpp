#include<iostream>

void printBits(float f) {
        printf("Input: %12.9f = ", f);
        char *p = reinterpret_cast<char*>(&f);
        for (int i = sizeof(float)-1; i >= 0; --i) {
                for (int j = 7; j >= 0; --j)
                        // Look at i'th byte of float, pull out bits one at a time.
                        std::cout << (p[i] & (1 << j) ? 1 : 0);
                std::cout << ' ';
        }
        std::cout << std::endl;
}

int main() {
        printBits(0);
        printBits(1);
        printBits(2);
        printBits(-2);
        printBits(2.5);
        printBits(-2.5);
        printBits(0.15625);
        std::cout << "Evaluating 1e-8F + 1.0F\n";
        printBits(1e-8F + 1.0F);
        std::cout << "Evaluating 1.0F - 0.99999F\n";
        printBits(1.0F - 0.99999F);
        std::cout << "Evaluating 1e-8F\n";
        printBits(1e-8F);
        std::cout << "Evaluating 1e-8F + (1.0F - 0.99999F)\n";
        printBits(1e-8F + (1.0F - 0.99999F));
}
