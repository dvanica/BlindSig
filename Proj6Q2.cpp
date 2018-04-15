#include "RSA.h"
#include "BigInt.h"
#include <cmath>
#include <iostream>
#define RAND_LIMIT32 0x7FFFFFFF
using namespace RSAUtil;

const unsigned long primes[10] = {100853, 102197, 179426873, 179427749, 182044217, 182045033, 182045597, 195372299, 197403571, 198491063};
const unsigned long nonprimes[20] = {198489624, 198490330, 198488866, 198488438, 198491320, 40000, 102005, 48125, 800055, 181481550, 198489624, 198490330, 198488866, 198488438, 198491320, 40000, 102005, 48125, 800055, 181481550};
void messageDemo(RSA myRSA)
{
    unsigned long int *a;
    unsigned long int arr[4];
    a = &arr[0];
    BigInt message, cipher, deciphered;

    message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
    message.toULong(a, 4);
    cipher = myRSA.encrypt(message);
    deciphered = myRSA.decrypt(cipher);
    std::cout << *a << std::endl;
    std::cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
}

void withPQArgRSA(const unsigned long *pvals, int num)
{
    RSA *rsaArray[5];
    for (int i = 0; i < num; i++)
    {
        rsaArray[i] = new RSA(pvals[2*i], pvals[2*i+1]);
        messageDemo(*rsaArray[i]);
    }
}

void withPArgRSA(const unsigned long *pvals, int num)
{
    RSA *rsaArray[5];
    for (int i = 0; i < num; i++)
    {
        rsaArray[i] = new RSA(pvals[i]);
        messageDemo(*rsaArray[i]);
    }
}

void noArgRSA(int num)
{
    RSA *rsaArray[10];
    for (int i = 0; i < num; i++)
    {
        rsaArray[i] = new RSA();
        messageDemo(*rsaArray[i]);
    }
}

int main(int argc, char *argv[])
{
    RSA RSA1;
    RSA RSA2;
    BigInt modulus = RSA1.getModulus();
    RSA2.setPublicKey(RSA1.getPublicKey());
    RSA2.setN(modulus);

    BigInt message = int(((double)std::rand()/RAND_MAX)*RAND_LIMIT32);
    BigInt encrypted = RSA2.encrypt(message);
    BigInt decrypted = RSA1.decrypt(encrypted);

    std::cout << "Original Message: " << message.toHexString() << "\tEncrypted RSA2: " << encrypted.toHexString() << "\tDecrypted RSA1: " << decrypted.toHexString() << std::endl;

}

/*
Output:
g++ -m32 -std=c++11 Proj6Q2.cpp -L. -lRSAutil -o proj6q2
Original Message: 0x3FE0 AA58 	Encrypted RSA2: 0x0003 42E4 18A1 	Decrypted RSA1: 0x3FE0 AA58 
*/  