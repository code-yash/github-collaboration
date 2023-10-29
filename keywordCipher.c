#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function that encodes key
char *encoder(char *key)
{
	char *encoded = (char *)malloc(26 * sizeof(char));
	int k = 0;
	bool arr[26] = {0};
	int key_size = strlen(key);

	for (int i = 0; i < key_size; i++)
	{
		char ch = *(key + i);
		int x = (int)(ch);
		if (ch >= 'A' && ch <= 'Z')
		{
			// To check whether the character is inserted
			// earlier in the encoded string or not
			if (arr[x - 65] == 0)
			{
				*(encoded + k) += ch;
				k++;
				arr[x - 65] = 1;
			}
		}
		else if (ch >= 'a' && ch <= 'z')
		{
			if (arr[x - 97] == 0)
			{
				*(encoded + k) += (char)(x - 32); // ch;( for case senstivity in output----do not delete it)
				k++;
				arr[x - 97] = 1;
			}
		}
	}

	// This loop inserts the remaining
	// characters in the encoded string.
	for (int i = 0; i < 26; i++)
	{
		if (arr[i] == 0)
		{
			arr[i] = 1;
			*(encoded + k) += (char)(i + 65);
			k++;
		}
	}
	return encoded;
}

// Function that generates encodes(cipher) the message
char *cipheredIt(char *msg, char *encoded)
{
	char *cipher = (char *)malloc(strlen(msg) * sizeof(char));

	int msg_size = strlen(msg);
	for (int i = 0; i < msg_size; i++)
	{
		char ch = *(msg + i);
		int x = (int)(ch);

		if (ch >= 'a' && ch <= 'z')
		{
			int pos = x - 97;
			*(cipher + i) += *(encoded + pos);
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			int pos = x - 65;
			*(cipher + i) += *(encoded + pos);
		}
		else
		{
			*(cipher + i) += ch;
		}
	}
	return cipher;
}

// This function will decode the message
char *decipheredIt(char *msg, char *encoded)
{
	char *plaintext = (char *)malloc(26 * sizeof(char));
	for (int i = 0; i < 26; i++)
	{
		*(plaintext + i) = (char)(i + 65);
	}

	char *decipher = (char *)malloc(strlen(msg) * sizeof(char));

	// This loop deciphered the message.
	// Spaces, special characters and numbers remain same.
	for (int i = 0; i < strlen(msg); i++)
	{
		if (msg[i] >= 'a' && msg[i] <= 'z')
		{
			int pos = msg[i] - 97;
			*(decipher + i) = *(plaintext + pos);
		}
		else if (msg[i] >= 'A' && msg[i] <= 'Z')
		{
			int pos = msg[i] - 65;
			*(decipher + i) = *(plaintext + pos);
		}
		else
		{
			*(decipher + i) = msg[i];
		}
	}
	return decipher;
}
