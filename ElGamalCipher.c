#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

int gcd(int a, int b)
{
  if (a == 0)
    return b;
  if (b == 0)
    return a;

  if (a == b)
    return a;

  // a is greater
  if (a > b)
    return gcd(a - b, b);
  return gcd(a, b - a);
}

// Generating large random numbers
int gen_key(int q)
{
  int key = (rand() % (int)(15 - 5 + 1)) + 5;

  while (gcd(q, key) != 1)
  {
    key = (rand() % (int)(15 - 5 + 1)) + 5;
  }
  return key;
}

int power(int g, int key, int q)
{
  long int x = 1;
  int y = g;

  x = pow(g, key);
  if (x > q)
    x = x % q;
  return (int)x;
}

// Asymmetric encryption
int *encryptElGamal(char *msg, int q, int h, int g)
{
  int *en_msg = (int *)malloc(100 * sizeof(int));

  int k = gen_key(q); // Private key for sender
  int p = power(g, k, q);

  for (int i = 0; i < strlen(msg); i++)
    *(en_msg + i) = msg[i];
  int s = power(h, k, q);

  int i;
  for (i = 0; i < strlen(msg); i++)
  {
    int temp = (s * (int)(*(en_msg + i)));
    *(en_msg + i) = temp;
  }
  *(en_msg + i) = p;
  return en_msg;
}

int *decryptElGamal(int *en_msg, int p, int key, int q, int len)
{
  int *dr_msg = (int *)malloc(100 * sizeof(int));

  int h = power(p, key, q);

  for (int i = 0; i < len - 1; i++)
    *(dr_msg + i) = ((*(en_msg + i) / h));

  return dr_msg;
}
