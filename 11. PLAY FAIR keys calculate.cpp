#include <stdio.h>
#include <math.h>

// Function to calculate factorial of a number
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Function to calculate the total possible keys (25!)
unsigned long long totalPossibleKeys() {
    return factorial(25);
}

// Function to calculate the approximate number of effectively unique keys (around 10^6)
unsigned long long effectivelyUniqueKeys() {
    return 1000000; // Approximate number of effectively unique keys (10^6)
}

int main() {
    // Calculate total possible keys for Playfair cipher (25!)
    unsigned long long totalKeys = totalPossibleKeys();
    
    // Calculate effectively unique keys (approximately 10^6)
    unsigned long long uniqueKeys = effectivelyUniqueKeys();
    
    // Output results
    printf("Total possible keys (25!): %llu\n", totalKeys);
    printf("Effectively unique keys (approx): %llu\n", uniqueKeys);
    
    // Calculate and display the total possible keys as a power of 2 approximation
    double log2TotalKeys = log2(totalKeys);
    printf("Total possible keys (approx. as power of 2): 2^%.2f\n", log2TotalKeys);
    
    return 0;
}

