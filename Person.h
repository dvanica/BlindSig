#include "BigInt.h"
#include "RSA.h"

#ifndef Person_H_
#define Person_H_

namespace RSAUtil
{
class Person
{
  private:
    RSA rsa;
    BigInt randomNumber;
    BigInt inverse;
    BigInt encryptedRand;

  public:
    Person();
    Person(RSA rsa);
    void shareModulusWith(Person * shareTo);
    void sharePublicKeyWith(Person * shareTo);
    BigInt getModulus();
    void setN(BigInt B);
    /**
     * Generate random number
     * Generate inverse w/respect to modulus
     * Encrypt random number    
     * Multiples message by encrypted random number, mod N
     * */
    BigInt blindAndEncrypt(BigInt message);
    /**
     * Simple decryption with RSA
     * */
    BigInt signMessage(BigInt message);
    /**
     * Simple encryption with RSA to verify
     * */
    BigInt verifyMessage(BigInt message);
    /**
     * Multiply message with the inverse, modulus N
     * */
    BigInt unblindSignedMessage(BigInt message);
};
}

#endif