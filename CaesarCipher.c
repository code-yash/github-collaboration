#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>

char* caesarCipher (char* str,int s, int len)
{
  char* result=(char*)malloc(200*sizeof(char));
 
    for (int i = 0;i < len; i++)
    {   char c = *(str+i);
        int x = (int) c;
        if (isupper(c))
        {
           *(result+i) = (char)((x + s - 65)%26 + 65);
        }

        else if(islower(c))
        { 
        *(result+i) = (char)((x + s - 97)%26 +97);
        }

        else
        {
          *(result+i) = c;
        }

    }
    for (int i = 0; i < len; i++)
    printf("%c", *(result + i));

    return result;
    
}