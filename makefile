build:
	g++ -c -std=c++11 -m32 BigInt.cpp RSA.cpp Person.cpp
	ar rc libRSAutil.a BigInt.o RSA.o Person.o
	ranlib libRSAutil.a
	g++ -m32 -std=c++11 BlindSig.cpp -L. -l RSAutil -o blindSig
	rm *.o
