/*--------------------HEADER FILES-----------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

/*--------------------LINKING FUNCTIONS-----------------*/
char *caesarCipher(char *, int, int);
char *encoder(char *);
char *cipheredIt(char *, char *);
char *decipheredIt(char *, char *);
char *encryptRailFence(char *, int);
char *decryptRailFence(char *, int);
bool encryptByPlayfairCipher(char str[], char key[], char *lastchar);
void decryptByPlayfairCipher(char str[], char key[], bool odd, char lastchar);
int gen_key(int);
int power(int, int, int);
int *encryptElGamal(char *, int, int, int);
int *decryptElGamal(int *, int, int, int, int);

/*--------------------MAIN FUNCTION-----------------*/
int main(void)
{
  char ans = 'y';
  do
  {
    printf("\n\n----ENCRPYTION-DECRYPTION----");
    printf("\n 1. Caesar Cipher ");
    printf("\n 2. Keyword Cipher ");
    printf("\n 3. PlayFair Cipher ");
    printf("\n 4. RailFence Cipher ");
    printf("\n 5. ElGamal Cipher ");

    int c;
    printf("\n\n Enter your Choice : ");
    scanf("%d", &c);

    char ch;
    ch = getchar();
    char *input = (char *)malloc(100 * sizeof(char));
    printf(" Enter the Input Message : ");
    fgets(input, 100, stdin);

    char *key = (char *)malloc(100 * sizeof(char));
    printf(" Enter the Character Key : ");
    fgets(key, 100, stdin);

    int numKey;
    printf(" Enter the numeric key : ");
    scanf("%d", &numKey);

    int flag;

    switch (c)
    {
    case 1:
      flag = 1;
      int shift = 4;
      int len = strlen(input);
      printf("\n\n -----Encrypting the message now.....\n");
      printf("Encrpypted Message is : ");
      char *res = caesarCipher(input, shift, len);
      printf("\n\n -----Decrypting the message now.....\n");
      printf("Dencrpypted Message is : ");
      res = caesarCipher(res, 26 - shift, len);
      break;

    case 2:
      flag = 1;
      char *encoded = encoder(key);
      printf("\n\n -----Encrypting the message now.....\n");
      printf("Encrpypted Message is : ");
      char *cipher = cipheredIt(input, encoded);
      for (int i = 0; i < strlen(cipher); i++)
        printf("%c", *(cipher + i));
      printf("\n\n -----Decrypting the message now.....\n");
      printf("Decrpypted Message is : ");
      char *decipher = decipheredIt(input, encoded);
      for (int i = 0; i < strlen(decipher); i++)
        printf("%c", *(decipher + i));

      break;

    case 3:
      flag = 1;
      char str[100];
      bool odd;
      char lastchar;
      strcpy(str, input);
      printf("\n\n -----Encrypting the message now.....\n");
      odd = encryptByPlayfairCipher(str, key, &lastchar);
      printf("Encrpypted Message is : ");
      if (odd == 1)
      {
        for (int i = 0; i < strlen(str) - 1; i++)
          printf("%c", str[i]);
      }
      else
      {
        for (int i = 0; i < strlen(str); i++)
          printf("%c", str[i]);
      }

      printf("\n\n -----Decrypting the message now.....\n");
      decryptByPlayfairCipher(str, key, odd, lastchar);
      printf("Dencrpypted Message is : ");
      if (odd == 1)
      {
        for (int i = 0; i < strlen(str) - 1; i++)
          printf("%c", str[i]);
      }
      else
      {
        for (int i = 0; i < strlen(str); i++)
          printf("%c", str[i]);
      }
      break;

    case 4:
      flag = 1;
      char *cipher4 = encryptRailFence(input, numKey);
      printf("\n\n -----Encrypting the message now.....\n");
      printf("Encrpypted Message is : ");
      for (int i = 0; i < strlen(cipher4); i++)
        printf("%c", *(cipher4 + i));

      printf("\n\n -----Decrypting the message now.....\n");
      printf("Decrpypted Message is : ");
      cipher4 = decryptRailFence(cipher4, numKey);
      for (int i = 0; i < strlen(cipher4); i++)
        printf("%c", *(cipher4 + i));
      break;

    case 5:
      flag = 1;
      int q = (rand() % (50 - 10 + 1)) + 10;
      int g = (rand() % (20 - 2 + 1)) + 2;
      int key5 = gen_key(q); // Private key for receiver

      printf("\nKindly note the Private Key for reciever = %d\n", key5);
      int h = power(g, key5, q);

      int *en_msg = encryptElGamal(input, q, h, g);
      printf("\n -----Encrypting the message now.....\n");
      printf("Encrpypted Message is : ");
      for (int i = 0; i < strlen(input); i++)
        printf("%d", *(en_msg + i));

      int p = *(en_msg + strlen(input));

      printf("\n\n -----Decrypting the message now.....\n");
      printf("Enter the reciever primary key(generated at time of encryption) to decrypt the message : ");
      scanf("%d", &key5);
      int *dr_msg = decryptElGamal(en_msg, p, key5, q, strlen(input));
      printf("Decrypted Message is : ");
      for (int i = 0; i < strlen(input); i++)
        printf("%c", *(dr_msg + i));
      break;
    }

    printf("\n\n Do you wish to continue? (Y/N) : ");
    ch = getchar();
    scanf("%c", &ans);

  } while (ans == 'y' || ans == 'Y');

  return 0;
}
