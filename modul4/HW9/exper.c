#include <openssl/err.h>
#include <openssl/evp.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char* password = argv[1];
    EVP_CIPHER_CTX* ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(ctx);

    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned char* salt = NULL;
    EVP_BytesToKey(
        EVP_aes_256_cbc(), // encryption algorithm
        EVP_sha256(),  // password hashing algorithm
        salt, // salt
        (unsigned char*)password, strlen(password), // password
        1, // number of hashing iterations
        key, // result: a key of the desired length
        iv // result: the initial vector of the desired length
    );
    
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        ERR_print_errors_fp(stderr);
        return 1;
    }
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    
    unsigned char buffer[1024];
    unsigned char answer[1024];
    int text_len = 0;
    int len;
    ssize_t read_result = read(STDIN_FILENO, buffer, sizeof(buffer));
    while (read_result > 0) {
        EVP_DecryptUpdate(ctx, buffer, &len, buffer, read_result);
        write(STDOUT_FILENO, buffer, len);
        read_result = read(STDIN_FILENO, buffer, sizeof(buffer));
    }
    if (1 != EVP_DecryptFinal(ctx, answer, &len)) { }
    write(STDOUT_FILENO, answer, len);
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}