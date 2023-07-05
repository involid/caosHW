#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void *
memmem(const void *l, size_t l_len, const void *s, size_t s_len);
/*{
	register char *cur, *last;
	const char *cl = (const char *)l;
	const char *cs = (const char *)s;

	if (l_len == 0 || s_len == 0)
		return NULL;

	if (l_len < s_len)
		return NULL;

	if (s_len == 1)
		return memchr(l, (int)*cs, l_len);

	last = (char *)cl + l_len - s_len;

	for (cur = (char *)cl; cur <= last; cur++)
		if (cur[0] == cs[0] && memcmp(cur, cs, s_len) == 0)
			return cur;

	return NULL;
}
*/

int main(int argc, char* argv[]) {
    char* filepath = argv[1];
    char* pattern = argv[2];

    int input_fd = open(filepath, O_RDWR | O_CREAT, 0666);
    if (input_fd == -1) {
        return 0;
    }

    struct stat st;
    fstat(input_fd, &st);
    off_t file_size = st.st_size;

    if (file_size != 0) {
        void* file_begin = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, input_fd, 0);

        void* found = file_begin;
        off_t off = 0;
        off_t pattern_sz = strlen(pattern);
        
        while ((found = memmem(found, file_size - off, pattern, pattern_sz)) != NULL) {
            off = found - file_begin;
            printf("%d ", off);
            ++found;
        }
        
        munmap(file_begin, file_size);
    }

    close(input_fd);

    return 0;
}