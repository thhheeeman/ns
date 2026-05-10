#include <bits/stdc++.h>
using namespace std;

int power(int base, int expo, int m) {
    int res = 1;
    base = base % m;

    while (expo > 0) {
        if (expo & 1)
            res = (res * 1LL * base) % m;

        base = (base * 1LL * base) % m;
        expo = expo / 2;
    }
    return res;
}

int modInverse(int e, int phi) {
    for (int d = 2; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

void generateKeys(int &e, int &d, int &n) {
    int p = 7919;
    int q = 1009;

    n = p * q;
    int phi = (p - 1) * (q - 1);

    for (e = 2; e < phi; e++) {
        if (__gcd(e, phi) == 1)
            break;
    }

    d = modInverse(e, phi);
}

int encrypt(int m, int e, int n) {
    return power(m, e, n);
}

int decrypt(int c, int d, int n) {
    return power(c, d, n);
}

int main() {
    int e, d, n;

    generateKeys(e, d, n);

    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";

    int M = 123;
    cout << "Original Message: " << M << endl;

    int C = encrypt(M, e, n);
    cout << "Encrypted Message: " << C << endl;

    int decrypted = decrypt(C, d, n);
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}