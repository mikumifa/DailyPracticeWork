#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace boost::multiprecision;
cpp_int mod_exp(cpp_int base, cpp_int exp, cpp_int modulus) {
  cpp_int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % modulus;
    }
    base = (base * base) % modulus;
    exp /= 2;
  }
  return result;
}

cpp_int multiMod(cpp_int m, cpp_int e, cpp_int n) {
  return mod_exp(m, e, n);
}
void extended_gcd(cpp_int a, cpp_int b, cpp_int* gcd, cpp_int* x, cpp_int*y) {
  if (b == 0) {
    *gcd = a;
    *x = 1;
    *y = 0;
  }
  else {
    extended_gcd(b, a % b, gcd, y, x);
    *y -= (a / b) * (*x);
  }
}

cpp_int get_d(cpp_int p, cpp_int q, cpp_int e) {
  cpp_int l = (p - 1) * (q - 1);
  cpp_int x = 1;
  while ((x * l + 1) % e) {
    x++;
  }
  return (x * l + 1) / e;
}


cpp_int encrypt(cpp_int plaintext, cpp_int e, cpp_int n) {
  return multiMod(plaintext, e, n);
}
cpp_int decrypt(cpp_int ciphertext, cpp_int d, cpp_int n) {
  return multiMod(ciphertext, d, n);
}