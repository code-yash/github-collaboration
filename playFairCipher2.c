#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Convert all the characters
// of a string to lowercase
void DtoLowerCase(char plain[], int ps)
{
    int i;
    for (i = 0; i < ps; i++)
    {
        if (plain[i] > 64 && plain[i] < 91)
            plain[i] += 32;
    }
}

// Remove all spaces in a string
// can be extended to remove punctuation
int DremoveSpaces(char *plain, int ps)
{
    int i, count = 0;
    for (i = 0; i < ps; i++)
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    plain[count] = '\0';
    return count;
}

// generates the 5x5 key square
void DgenerateKeyTable(char key[], int ks,
                       char keyT[5][5])
{
    int i, j, k, flag = 0, *dicty;

    // a 26 character hashmap
    // to store count of the alphabet
    dicty = (int *)calloc(26, sizeof(int));

    for (i = 0; i < ks; i++)
    {
        if (key[i] != 'j')
            dicty[key[i] - 97] = 2;
    }
    dicty['j' - 97] = 1;

    i = 0;
    j = 0;
    for (k = 0; k < ks; k++)
    {
        if (dicty[key[k] - 97] == 2)
        {
            dicty[key[k] - 97] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }
    for (k = 0; k < 26; k++)
    {
        if (dicty[k] == 0)
        {
            keyT[i][j] = (char)(k + 97);
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }
}

// Search for the characters of a digraph
// in the key square and return their position
void Dsearch(char keyT[5][5], char a,
             char b, int arr[])
{
    int i, j;

    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (keyT[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

// Function to find the modulus with 5
int Dmod5(int a)
{
    if (a < 0)
        a = a + 5;
    return (a % 5);
}

// Function to make the text fit for decryption
int Dprepare(char str[], int ptrs, bool odd, char lastchar)
{
    if (odd == 1)
    {
        str[--ptrs] = lastchar;
        str[++ptrs] = '\0';
    }

    return ptrs;
}

// Function to decrypt
void decrypt(char str[], char keyT[5][5], int ps)
{

    // for(int i=0;i<ps;i++)
    // {
    //   printf("%c",str[i]);
    // }

    int i, a[4];
    for (i = 0; i < ps; i += 2)
    {
        Dsearch(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2])
        {
            str[i] = keyT[a[0]][Dmod5(a[1] - 1)];
            str[i + 1] = keyT[a[0]][Dmod5(a[3] - 1)];
        }
        else if (a[1] == a[3])
        {
            str[i] = keyT[Dmod5(a[0] - 1)][a[1]];
            str[i + 1] = keyT[Dmod5(a[2] - 1)][a[1]];
        }
        else
        {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Function to call decrypt
void decryptByPlayfairCipher(char str[], char key[], bool odd, char lastchar)
{
    char ps, ks, keyT[5][5];

    // Key
    ks = strlen(key);
    ks = DremoveSpaces(key, ks);
    DtoLowerCase(key, ks);

    // ciphertext
    ps = strlen(str);
    DtoLowerCase(str, ps);
    ps = DremoveSpaces(str, ps);

    // tempstr
    char tempstr[ps + 1];
    strcpy(tempstr, str);
    tempstr[ps] = '\0';

    // prearing str for  decryption
    ps = Dprepare(tempstr, ps, odd, lastchar);
    // printf("\nps = %d\n",ps); 16

    // generate key table
    DgenerateKeyTable(key, ks, keyT);

    // decrypt
    decrypt(tempstr, keyT, ps);

    // if length of str is odd then we remove the last character
    if (odd == 1)
    {
        for (int i = 0; i < ps - 1; i++)
        {
            str[i] = tempstr[i];
        }
    }
    else
    {
        for (int i = 0; i < ps; i++)
        {
            str[i] = tempstr[i];
        }
    }
}
