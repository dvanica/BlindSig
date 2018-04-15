#include "RSA.h"
#include "BigInt.h"
#include "Person.h"
#include <cmath>
#include <iostream>
#include <random>
#define RAND_LIMIT32 0x7FFFFFFF
#define RAND_LIMIT16 0x7FFF

using namespace RSAUtil;

int main(int argc, char *argv[])
{
    // As Alice is the sender in this case,
    // we can generate her RSA object with parameters
    RSA aliceRSA(116531, 49999);
    Person alice(aliceRSA);
    Person bob;
    bob.shareModulusWith(&alice);
    bob.sharePublicKeyWith(&alice);
    std::cout << "Alice has obtained Bob's public key and Bob's modulus " << std::endl;

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<long long unsigned> distribution(0, RAND_LIMIT32);
    
    BigInt message(distribution(generator));
    
    message = message % alice.getModulus();
    std::cout << "Alice's Message to be Signed: " << message.toHexString() << std::endl;
    BigInt blindedMessage = alice.blindAndEncrypt(message);
    std::cout << "Alice sends Bob the blinded message:: " << blindedMessage.toHexString() << std::endl;

    BigInt signedBlindedMessage = bob.signMessage(blindedMessage);
    std::cout << "Bob's signed blinded message: " << signedBlindedMessage.toHexString() << std::endl;

    BigInt signedMessage = alice.unblindSignedMessage(signedBlindedMessage);
    std::cout << "Final message signed by Bob: " << signedMessage.toHexString() << std::endl;
 
    BigInt verifiedMessage = alice.verifyMessage(signedMessage);
    std::cout << "Verified message: " << verifiedMessage.toHexString() << std::endl;
}

/*
Output:
g++ -m32 -std=c++11 Proj6Q2.cpp -L. -lRSAutil -o proj6q2
Original Message: 0x3FE0 AA58 	Encrypted RSA2: 0x0003 42E4 18A1 	Decrypted RSA1: 0x3FE0 AA58 
*/