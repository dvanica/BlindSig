# BlindSigdanielle@Scipio:~/Project 2  Library Files Updated$ g++ -c -std=c++11 -m32 BigInt.cpp RSA.cpp Person.cpp
danielle@Scipio:~/Project 2  Library Files Updated$ ar rc libRSAutil.a BigInt.o RSA.o Person.o 
danielle@Scipio:~/Project 2  Library Files Updated$ ranlib libRSAutil.a
danielle@Scipio:~/Project 2  Library Files Updated$ g++ -m32 -std=c++11 BlindSig.cpp -L. -l RSAutil -o blindSig
danielle@Scipio:~/Project 2  Library Files Updated$ ./blindSig
