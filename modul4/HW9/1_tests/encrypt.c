#include <openssl/conf.h>
#include <openssl/evp.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char* password = argv[1];

    int plaintext_fd = open("text.txt", O_RDONLY);
    int ciphertext_fd = open("text_encrypt.txt", O_WRONLY | O_CREAT, 0644);

    // Allocate memory for key and iv
    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];

    // Create salt
    unsigned char salt[8];
    for (int i = 0; i < 8; ++i) {
        salt[i] = (unsigned char)rand();
    }

    // Save salt into cipher
    write(ciphertext_fd, "Salted__", 8);
    write(ciphertext_fd, salt, 8);

    // Generating a key and an initial vector from
    // a password of arbitrary length and an 8-byte salt
    EVP_BytesToKey(
        EVP_aes_256_cbc(), // encryption algorithm
        EVP_sha256(),  // password hashing algorithm
        salt, // salt
        password, strlen(password), // password
        1, // number of hashing iterations
        key, // result: a key of the desired length
        iv // result: the initial vector of the desired length
    );

    // Creating a context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    // Initial stage: initialization
    EVP_EncryptInit(
        ctx, // context for storing state
        EVP_aes_256_cbc(), // encryption algorithm
        key, // key of the desired size
        iv // initial value of the desired size
    );


    const int BUFFER_SIZE = 1024;
    const int BLOCK_SIZE = 16;

    char buffer[BUFFER_SIZE];
    unsigned char buffer_crypt[BUFFER_SIZE + BLOCK_SIZE];

    int read_result = read(plaintext_fd, buffer, BUFFER_SIZE);
    while (read_result > 0) {
        int ciphertext_len;
        EVP_EncryptUpdate(ctx, buffer_crypt, &ciphertext_len,
                          buffer, read_result);
        write(ciphertext_fd, buffer_crypt, ciphertext_len);

        read_result = read(plaintext_fd, buffer, BUFFER_SIZE);
    }

    int ciphertext_final_len;
    EVP_EncryptFinal_ex(ctx, buffer_crypt, &ciphertext_final_len);
    write(ciphertext_fd, buffer_crypt, ciphertext_final_len);


    EVP_CIPHER_CTX_free(ctx);

    close(plaintext_fd);
    close(ciphertext_fd);

    return 0;
}
