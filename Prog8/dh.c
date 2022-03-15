#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


// a^m mod p
long long int compute(long long int a, long long int m, long long int p)
{
 return(((long long int) pow(a,m))%p);
}



int main()
{
	long long int p = 23;		// modulus
	long long int g = 5;		// base

	long long int a, b;	// a - Alice's Secret Key, b - Bob's Secret Key.
	long long int A, B;	// A - Alice's Public Key, B - Bob's Public Key

	a = 4;
	A = compute(g, a, p);
	b = 3;
	B = compute(g, b, p);

	long long int keyA = compute(B, a, p);
	long long int keyB = compute(A, b, p);

	printf("\nAlice's Secret Key is %lld\nBob's Secret Key is %lld\n\n", keyA, keyB);

	return 0;
}