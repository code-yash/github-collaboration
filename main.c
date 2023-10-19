/*--------------------HEADER FILES-----------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>

/*--------------------MAIN FUNCTION-----------------*/
int main(void)
{
  char ans='y';
  do
  {
    printf("\n\n ----ENCRPYTION-DECRYPTION---- ");
    printf("\n 1. Caesar Cipher ");
    printf("\n 2. Keyword Cipher ");
    printf("\n 3. PlayFair Cipher ");
    printf("\n 4. RailFence Cipher ");
    printf("\n 5. ElGamal Cipher ");

    int c;
    printf("\n\n Enter your Choice : ");
    scanf("%d",&c);

    /* Code Implementation Here */

    printf("\n\n Do you wish to continue? (Y/N) : ");
    ch=getchar();
    scanf("%c",&ans);

  }while(ans == 'y' || ans=='Y');

return 0;
}


