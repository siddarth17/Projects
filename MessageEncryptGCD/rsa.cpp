#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <limits>


long long gcd(long long a, long long b) {
    // Loops till b is 0 and uses euclidean algorithm formula.
    while (b != 0) {
        long long temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}


long long extendedeuclideanalgo(long long e, long long L) {
    // Initializing coefficients.
    long long s = 0;
    long long old_s = 1;
    long long t = 1;
    long long old_t = 0;

    long long r = e;
    long long old_r = L;
    long long temp;

    // Continously updates coefficients and remainders till current remainder is not 0. 
    // Using Euclidean algorithm formula as well.
    while (r != 0) {
        long long quotient = old_r / r;
        temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    return old_t;
}

long long modularexponentiation(long long base, long long exponent, long long modulus) {
    long long output = 1;
    base = base % modulus;

    // Converting the exponent to binary.
    int maxsize = 64; // for long long type.
    bool N[maxsize];
    int len = 0;
    while (exponent > 0) {
        N[len] = exponent % 2;
        exponent = exponent / 2;
        len++;
    }

    // Using modular exponentiation algorithm.
    for (int i = 0; i < len; i++) {
        if (N[i] == true) {
            output = (output * base) % modulus;
        }
        base = (base * base) % modulus;
    }
    
    return output;
}



long long decryptionkeycalculator(long long p, long long q) {
    long long e = 65537;
    long long denom = gcd(p - 1, q - 1);
    long long L = (p - 1) * (q - 1) / denom;

    // Checking if L is less than or equal to e.
    if (L <= e) {
        std::cerr << "Invalid choice of p and q" << std::endl;
        exit(1);
    }

    long long d = extendedeuclideanalgo(e, L);
    
    // Addressing case where d is less than 0.
    while (d < 0){
        d = d + L;
    } 
     // Validating  
    if ((e * d) % L != 1) {
        std::cerr << "Invalid choice of p and q" << std::endl;
        exit(1);
    }

    return d;
}

long long numberconverter(const std::string& str) {
    long long number = 0;
    for (char c : str) {
        if (c == ' ') {
            number = number * 100;   // For space.
        } else {
            number = number * 100 + (c - 'a' + 1); // Since a is first value.
        }
    }
    return number;
}

void encrypt(const std::string& message, long long e, long long n, std::ofstream& outputFile) {

    // Calculating x and rounding it down.
    size_t x = 1 + std::floor(std::log(n/27.0) / std::log(100));
    
    // Checking invalid case where n is less than 27.
    if (n < 27) {
        std::cerr << "Wrong. n should be at least 27." << std::endl;
        exit(1);
    } 

    for (size_t i = 0; i < message.size(); i += x) {
        std::string convertstring = message.substr(i, x);
        while(convertstring.size() < x) {
            convertstring += ' ';  // Adding spaces when less than x characters remain.
        } 

        // Calling the appropriate functions to encrypt the appropriate strings.
        long long M = numberconverter(convertstring);
        long long C = modularexponentiation(M, e, n);
        outputFile << C << " ";
    }
}

std::string stringconverter(long long num, int length) {
    std::string str;
    // Iterating through for the length.
    while (length--) {
        int val = num % 100; 
        if (val == 0) {
            str = ' ' + str; // For spaces.
        } else {
            str = char(val - 1 + 'a') + str; 
        }
        num = num/100; // Removing last 2 digits of num for next iteration.
    }
    return str;
}


void decrypt(std::ifstream &inFile, long long n, long long d, std::ofstream &outFile) {
    size_t x = 1 + std::floor(std::log(n/27.0) / std::log(100));
    
    long long C;
    // Extracting the ints from file and applying decryption algorithm.
    while (inFile >> C) {
        long long M = modularexponentiation(C, d, n);
        std::string decryptedtext = stringconverter(M, x);
        outFile << decryptedtext;
    }
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cerr << "Wrong input. Please provide values for p and q." << std::endl;
        return 1;
    }

    long long p = std::stoll(argv[1]); // Learnt about stoll in cplusplus.com
    long long q = std::stoll(argv[2]);
    long long n = p * q;
    long long d = decryptionkeycalculator(p, q);

    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::cin >> command;
        
        // Identifying command and getting appropriate cin statements and performing appropriate operations.
        if (command == "EXIT") {
            break;
        } 
        else if (command == "DECRYPT") {
            std::string inputPath, outputPath;
            std::cin >> inputPath >> outputPath;

            std::ifstream inFile(inputPath);
            std::ofstream outFile(outputPath);

            // Checking the files.
            if (!inFile.is_open()) {
                std::cerr << "Error: Could not open input file." << std::endl;
                exit(1);
            }
            if (!outFile.is_open()) {
                std::cerr << "Error: Could not open output file." << std::endl;
                exit(1);
            }

            decrypt(inFile, n, d, outFile);

            inFile.close();
            outFile.close();
        } 
        else if (command == "ENCRYPT") {
            std::string filename, message;
            long long encryption_n;
            std::cin >> filename >> encryption_n;
            char dummychar;
            std::cin.get(dummychar);
            std::getline(std::cin, message);
            std::ofstream outFile(filename);

            // Checking the file.
            if (!outFile.is_open()) {
                std::cerr << "Error: Could not open output file." << std::endl;
                continue;
            }

            encrypt(message, 65537, encryption_n, outFile);
            outFile.close();
        }

    }

    return 0;
}




