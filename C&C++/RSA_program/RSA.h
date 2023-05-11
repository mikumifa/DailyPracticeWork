#include <iostream>
#include <cstring>

const int BLOCK_SIZE = 32;

void xor_block(char *block1, char *block2)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        block1[i] ^= block2[i];
    }
}

void encrypt_block(char *block, char *key)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] ^= key[i];
    }
}

void decrypt_block(char *block, char *key)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] ^= key[i];
    }
}

void cbc_encrypt(char *plaintext, char *key, char *iv, int size)
{
    for (int i = 0; i < size; i += BLOCK_SIZE)
    {
        xor_block(plaintext + i, iv);
        encrypt_block(plaintext + i, key);
        memcpy(iv, plaintext + i, BLOCK_SIZE);
    }
}

void cbc_decrypt(char *ciphertext, char *key, char *iv, int size)
{
    for (int i = 0; i < size; i += BLOCK_SIZE)
    {
        char temp[BLOCK_SIZE];
        memcpy(temp, ciphertext + i, BLOCK_SIZE);
        decrypt_block(ciphertext + i, key);
        xor_block(ciphertext + i, iv);
        memcpy(iv, temp, BLOCK_SIZE);
    }
}