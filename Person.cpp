#include "RSA.h"
#include "BigInt.h"
#include "Person.h"
#include <cmath>
#include <iostream>
#define RAND_LIMIT16 0x7FFF
using namespace RSAUtil;

Person::Person()
{
    Person::rsa;
}

Person::Person(RSA rsa)
{
    Person::rsa = rsa;
}

BigInt Person::getModulus() {
    return rsa.getModulus();
}

void Person::shareModulusWith(Person shareTo)
{
    std::cout << "Old modulus: " << shareTo.rsa.getModulus().toHexString() << "and " << Person::rsa.getModulus().toHexString() << std::endl;
    shareTo.rsa.setN(Person::rsa.getModulus());
    std::cout << "New modulus: " << shareTo.rsa.getModulus().toHexString() << std::endl;
}

void Person::sharePublicKeyWith(Person shareTo)
{
    std::cout << "Old Public Key: " << shareTo.rsa.getPublicKey().toHexString() << std::endl;
    shareTo.rsa.setPublicKey(Person::rsa.getPublicKey());
    std::cout << "New Public Key: " << shareTo.rsa.getPublicKey().toHexString() << std::endl;
}

BigInt Person::blindAndEncrypt(BigInt message)
{

    Person::randomNumber = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT16);
    //randomNumber * inverse = 1 mod getModulus()
    Person::inverse = modInverse(Person::randomNumber, Person::rsa.getModulus());
    Person::encryptedRand = Person::rsa.encrypt(Person::randomNumber);

    BigInt returnValue = (Person::encryptedRand * message) % Person::rsa.getModulus();
    return returnValue;
}

BigInt Person::signMessage(BigInt message)
{
    return Person::rsa.decrypt(message);
    ;
}

BigInt Person::verifyMessage(BigInt message)
{
    return Person::rsa.encrypt(message);
}

BigInt Person::unblindSignedMessage(BigInt message)
{
    BigInt invertedMsg = (message * Person::inverse) % Person::rsa.getModulus();
    return invertedMsg;
}
