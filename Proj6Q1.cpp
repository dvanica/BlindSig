#include "RSA.h"
#include "BigInt.h"
#include <cmath>
#include <iostream>
#define RAND_LIMIT32 0x7FFFFFFF
using namespace RSAUtil;

const unsigned long primes[10] = {100853, 102197, 102563, 102841, 85889, 87299, 87973, 88867, 89519, 90053};
const unsigned long nonprimes[20] = {89624, 90330, 88866, 88438, 91320, 40000, 72005, 48125, 80055, 41550, 48624, 49330, 48866, 48838, 49130, 40000, 60205, 48125, 80055, 48150};
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
    for (int i = 0; i < num; i++)
    {
        RSA rsa(pvals[2*i], pvals[2*i+1]);
        messageDemo(rsa);
    }
}

void withPArgRSA(const unsigned long *pvals, int num)
{
    RSA *rsaArray[5];
    for (int i = 0; i < num; i++)
    {
        RSA rsa(pvals[i]);
        messageDemo(rsa);
    }
}

void noArgRSA(int num)
{
    RSA *rsaArray[10];
    for (int i = 0; i < num; i++)
    {
        RSA rsa;
        messageDemo(rsa);
    }
}

int main(int argc, char *argv[])
{
    std::cout << "No-arg RSA - 10 Objects" << std::endl;
    noArgRSA(10);
    std::cout << "Prime P-only Arg RSA - 5 Objects" << std::endl;
    withPArgRSA(primes, 5);
    std::cout << "Prime P-Q Arg RSA - 5 Objects" << std::endl;
    withPQArgRSA(primes, 5);
    std::cout << "Non-Prime P-Q Arg RSA - 10 Objects " << std::endl;
    withPQArgRSA(nonprimes, 10);
}

/*
g++ -m32 -std=c++11 Proj6Q1.cpp -L. -lRSAutil -o proj6q1
./proj6q1
Output:
No-arg RSA - 10 Objects
1883658350
message: 0x7046 586E 	cipher: 0x0001 746E D06D 	deciphered: 0x7046 586E 
700259301
message: 0x29BD 1BE5 	cipher: 0x74DE FF6E 	deciphered: 0x29BD 1BE5 
700259301
message: 0x29BD 1BE5 	cipher: 0x74DE FF6E 	deciphered: 0x29BD 1BE5 
700259301
message: 0x29BD 1BE5 	cipher: 0x74DE FF6E 	deciphered: 0x29BD 1BE5 
700259301
message: 0x29BD 1BE5 	cipher: 0x74DE FF6E 	deciphered: 0x29BD 1BE5 
700259301
message: 0x29BD 1BE5 	cipher: 0x74DE FF6E 	deciphered: 0x29BD 1BE5 
700259301
message: 0x29BD 1BE5 	cipher: 0x74DE FF6E 	deciphered: 0x29BD 1BE5 
1470100510
message: 0x579F F41E 	cipher: 0x0001 86F4 40C2 	deciphered: 0x579F F41E 
1470100510
message: 0x579F F41E 	cipher: 0x0001 86F4 40C2 	deciphered: 0x579F F41E 
1470100510
message: 0x579F F41E 	cipher: 0x0001 86F4 40C2 	deciphered: 0x579F F41E 
Prime P-only Arg RSA - 5 Objects
1665058801
message: 0x633E C7F1 	cipher: 0x2638 29B4 	deciphered: 0x633E C7F1 
1665058801
message: 0x633E C7F1 	cipher: 0x0002 B703 6941 	deciphered: 0x633E C7F1 
755240963
message: 0x2D04 1003 	cipher: 0x781D 9031 	deciphered: 0x2D04 1003 
755240963
message: 0x2D04 1003 	cipher: 0x0001 2357 1696 	deciphered: 0x2D04 1003 
755240963
message: 0x2D04 1003 	cipher: 0x1EF6 1080 	deciphered: 0x2D04 1003 
Prime P-Q Arg RSA - 5 Objects
457492351
message: 0x1B44 C77F 	cipher: 0x0001 AA42 5FFB 	deciphered: 0x1B44 C77F 
457492351
message: 0x1B44 C77F 	cipher: 0x2076 41DD 	deciphered: 0x1B44 C77F 
457492351
message: 0x1B44 C77F 	cipher: 0x33D1 AD40 	deciphered: 0x1B44 C77F 
149260627
message: 0x08E5 8953 	cipher: 0x0001 0E6B 6096 	deciphered: 0x08E5 8953 
149260627
message: 0x08E5 8953 	cipher: 0x0001 14D7 19BF 	deciphered: 0x08E5 8953 
Non-Prime P-Q Arg RSA - 10 Objects 
149260627
message: 0x08E5 8953 	cipher: 0x0001 3B99 A9AB 	deciphered: 0x0001 3630 1053 
149260627
message: 0x08E5 8953 	cipher: 0x8CDC DD0B 	deciphered: 0x0001 0DC0 9923 
149260627
message: 0x08E5 8953 	cipher: 0x4786 FBBB 	deciphered: 0x639D B949 
149260627
message: 0x08E5 8953 	cipher: 0x4C90 246B 	deciphered: 0x1C3C 78A9 
149260627
message: 0x08E5 8953 	cipher: 0x4CA7 37A5 	deciphered: 0xA29C 5563 
149260627
message: 0x08E5 8953 	cipher: 0x4643 537B 	deciphered: 0x30DB B45B 
1986466304
message: 0x7667 1200 	cipher: 0x6300 A21C 	deciphered: 0x35BF 390C 
1986466304
message: 0x7667 1200 	cipher: 0x159E 6680 	deciphered: 0x6DBB F080 
1986466304
message: 0x7667 1200 	cipher: 0xACA6 EE9E 	deciphered: 0x8351 58EA 
1986466304
message: 0x7667 1200 	cipher: 0x57DF D8B2 	deciphered: 0xDA5F F736 


*/