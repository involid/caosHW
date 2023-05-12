#include <inttypes.h>
#include <limits.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <unistd.h>

const size_t HASH_BITS = 512;
const size_t HASH_SIZE = HASH_BITS / CHAR_BIT;

int main(int argc, char* argv[]) {
    // Initialize hash context
    SHA512_CTX sha512_context;
    SHA512_Init(&sha512_context);

    // Read bytes from stdin and pass them to hash function
    char buffer[HASH_SIZE];
    ssize_t read_result = read(STDIN_FILENO, buffer, sizeof(buffer));
    while (read_result > 0) {
        SHA512_Update(&sha512_context, buffer, read_result);

        read_result = read(STDIN_FILENO, buffer, sizeof(buffer));
    }

    // Get hash function result
    char hash[HASH_SIZE];
    SHA512_Final(hash, &sha512_context);

    // Print hash function result to stdout
    printf("0x");
    for (size_t i = 0; i < sizeof(hash); ++i) {
        printf("%02x", (uint8_t)hash[i]);
    }
    printf("\n");

    return 0;
}

