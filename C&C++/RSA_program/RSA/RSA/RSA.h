
//
// Created by mikumifa on 2023/5/5.
//

#ifndef RSA_CMAKE_RSA_H
#define RSA_CMAKE_RSA_H
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace boost::multiprecision;

cpp_int gcd(cpp_int a, cpp_int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

cpp_int lcm(cpp_int a, cpp_int b) {
    return (a * b) / gcd(a, b);
}

cpp_int modpow(cpp_int base, cpp_int exponent, cpp_int modulus) {
    cpp_int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

bool is_prime(cpp_int n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (cpp_int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

cpp_int generate_prime(int bits) {
    boost::random::mt19937 rng;
    rng.seed(time(nullptr));
    boost::random::uniform_int_distribution<cpp_int> dist(1, 1);
    cpp_int n = dist(rng);
    while (!is_prime(n))
        n = dist(rng);
    return n;
}

cpp_int generateKey(int bits) {
    cpp_int p = generate_prime(bits / 2);
    cpp_int q = generate_prime(bits / 2);
    cpp_int phi = lcm(p - 1, q - 1);
    cpp_int e = 65537;
    while (gcd(e, phi) != 1)
        e++;
    cpp_int d = modpow(e, -1, phi);
    return d;
}

cpp_int encrypt(cpp_int plaintext, cpp_int e, cpp_int n) {
    return modpow(plaintext, e, n);
}

cpp_int decrypt(cpp_int ciphertext, cpp_int d, cpp_int n) {
    return modpow(ciphertext, d, n);
}


#endif//RSA_CMAKE_RSA_H
