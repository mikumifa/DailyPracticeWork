#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int BLOCK_SIZE = 8;

vector<string> split(const string &str, int block_size)
{
    vector<string> blocks;
    for (int i = 0; i < str.length(); i += block_size)
    {
        blocks.push_back(str.substr(i, block_size));
    }
    return blocks;
}

string pad(const string &str, int block_size)
{
    int pad_len = block_size - str.length() % block_size;
    string padded_str = str;
    for (int i = 0; i < pad_len; i++)
    {
        padded_str += '\0';
    }
    return padded_str;
}

string encrypt_block(const string &block, const string &key, const string &iv)
{
    string xored_block = block;
    for (int i = 0; i < block.length(); i++)
    {
        xored_block[i] ^= iv[i];
    }
    string encrypted_block = xored_block;
    for (int i = 0; i < block.length(); i++)
    {
        encrypted_block[i] ^= key[i];
    }
    return encrypted_block;
}

string decrypt_block(const string &block, const string &key, const string &iv)
{
    string decrypted_block = block;
    for (int i = 0; i < block.length(); i++)
    {
        decrypted_block[i] ^= key[i];
    }
    string xored_block = decrypted_block;
    for (int i = 0; i < block.length(); i++)
    {
        xored_block[i] ^= iv[i];
    }
    return xored_block;
}

string encrypt(const string &plaintext, const string &key, const string &iv)
{
    string padded_plaintext = pad(plaintext, BLOCK_SIZE);
    vector<string> blocks = split(padded_plaintext, BLOCK_SIZE);
    string ciphertext;
    string prev_block = iv;
    for (const auto &block : blocks)
    {
        string encrypted_block = encrypt_block(block, key, prev_block);
        ciphertext += encrypted_block;
        prev_block = encrypted_block;
    }
    return ciphertext;
}

string decrypt(const string &ciphertext, const string &key, const string &iv)
{
    vector<string> blocks = split(ciphertext, BLOCK_SIZE);
    string plaintext;
    string prev_block = iv;
    for (const auto &block : blocks)
    {
        string decrypted_block = decrypt_block(block, key, prev_block);
        plaintext += decrypted_block;
        prev_block = block;
    }
    return plaintext;
}

int main()
{
    string key = "secretkey";
    string iv = "01234567";

    string plaintext = "the quick brown fox jumps over the lazy dog";
    string ciphertext = encrypt(plaintext, key, iv);
    string decrypted_plaintext = decrypt(ciphertext, key, iv);
    cout << "Plaintext: " << plaintext << endl;
    cout << "Decrypted plaintext: " << decrypted_plaintext << endl;
    plaintext = "AAAAAAAAAAAAAAAAAAAAAAAA";
    ciphertext = encrypt(plaintext, key, iv);
    decrypted_plaintext = decrypt(ciphertext, key, iv);
    cout << "Plaintext: " << plaintext << endl;
    cout << "Decrypted plaintext: " << decrypted_plaintext << endl;
    plaintext = "55555555555555555assssssss";
    ciphertext = encrypt(plaintext, key, iv);
    decrypted_plaintext = decrypt(ciphertext, key, iv);
    cout << "Plaintext: " << plaintext << endl;
    cout << "Decrypted plaintext: " << decrypted_plaintext << endl;

    return 0;
}