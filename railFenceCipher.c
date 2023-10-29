#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// function to encrypt a message
char *encryptRailFence(char *text, int key)
{
	// create the matrix to cipher plain text
	// key = rows , length(text) = columns
	int text_length = strlen(text);
	char rail[key][text_length];

	// filling the rail matrix to distinguish filled
	// spaces from blank ones
	for (int i = 0; i < key; i++)
		for (int j = 0; j < text_length; j++)
			rail[i][j] = '\n';

	// to find the direction
	bool dir_down = false;
	int row = 0, col = 0;

	for (int i = 0; i < text_length; i++)
	{
		// check the direction of flow
		// reverse the direction if we've just
		// filled the top or bottom rail
		if (row == 0 || row == key - 1)
			dir_down = !dir_down;
		char ch = *(text + i);
		// fill the corresponding alphabet
		rail[row][col++] = ch;

		// find the next row using direction flag
		dir_down ? row++ : row--;
	}

	// now we can construct the cipher using the rail matrix
	char *result = (char *)malloc(200 * sizeof(char));
	int k = 0;
	for (int i = 0; i < key; i++)
		for (int j = 0; j < text_length; j++)
			if (rail[i][j] != '\n')
			{
				*(result + k) = rail[i][j];
				k++;
			}

	return result;
}

// This function receives cipher-text and key
// and returns the original text after decryption
char *decryptRailFence(char *cipher, int key)
{
	// create the matrix to cipher plain text
	// key = rows , length(text) = columns
	int cipher_length = strlen(cipher);
	char rail[key][cipher_length];

	// filling the rail matrix to distinguish filled
	// spaces from blank ones
	for (int i = 0; i < key; i++)
		for (int j = 0; j < cipher_length; j++)
			rail[i][j] = '\n';

	// to find the direction
	bool dir_down;

	int row = 0, col = 0;

	// mark the places with '*'
	for (int i = 0; i < cipher_length; i++)
	{
		// check the direction of flow
		if (row == 0)
			dir_down = true;
		if (row == key - 1)
			dir_down = false;

		// place the marker
		rail[row][col++] = '*';

		// find the next row using direction flag
		dir_down ? row++ : row--;
	}

	// now we can construct the fill the rail matrix
	int index = 0;
	for (int i = 0; i < key; i++)
		for (int j = 0; j < cipher_length; j++)
			if (rail[i][j] == '*' && index < cipher_length)
				rail[i][j] = cipher[index++];

	// now read the matrix in zig-zag manner to construct
	// the resultant text
	char *result = (char *)malloc(200 * sizeof(char));
	int k = 0;

	row = 0, col = 0;
	for (int i = 0; i < cipher_length; i++)
	{
		// check the direction of flow
		if (row == 0)
			dir_down = true;
		if (row == key - 1)
			dir_down = false;

		// place the marker
		if (rail[row][col] != '*')
		{
			*(result + k) = rail[row][col++];
			k++;
		}

		// find the next row using direction flag
		dir_down ? row++ : row--;
	}
	return result;
}
