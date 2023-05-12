#include <openssl/err.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 2048
#define MAXANSWERSIZE 2048
#define SALTSIZE 8

int main(int argc, char* argv[])
{
    char* password = argv[1];
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

    unsigned char buff[BUFFSIZE];
    read(STDIN_FILENO, buff, sizeof("salted__") - 1 + SALTSIZE);
    unsigned char* salt = buff + sizeof("salted__") - 1;

    if (!EVP_BytesToKey(
            EVP_aes_256_cbc(),
            EVP_sha256(),
            salt,
            (unsigned char*)password,
            strlen(password),
            1,
            key,
            iv)) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        abort();
    }

    if (EVP_DecryptInit(ctx, EVP_aes_256_cbc(), key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        ERR_print_errors_fp(stderr);
        abort();
    }

    const int chiper_block_sz = EVP_CIPHER_block_size(EVP_aes_256_cbc());
    char answer[MAXANSWERSIZE + chiper_block_sz];

    int len;
    int readed = read(STDIN_FILENO, buff, BUFFSIZE);
    while (readed > 0) {
        if (EVP_DecryptUpdate(ctx, answer, &len, buff, readed) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            ERR_print_errors_fp(stderr);
            abort();
        }
        if (write(STDOUT_FILENO, answer, len) == -1) {
            perror("write");
        }
        readed = read(STDIN_FILENO, buff, BUFFSIZE);
    }
    if (EVP_DecryptFinal(ctx, answer, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        ERR_print_errors_fp(stderr);
        abort();
    }
    if (write(STDOUT_FILENO, answer, len) == -1) {
        perror("write");
    }

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}