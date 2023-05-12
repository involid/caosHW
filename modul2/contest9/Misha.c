#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
 
int main() {	
	char file[PATH_MAX];
	struct stat st;
	while (fgets(file, PATH_MAX, stdin) != NULL) {
		for (int i = 0; i < PATH_MAX; ++i) {
			if (file[i] == '\n') {
				file[i] = '\0';
			}
			if (file[i] == '\0') {
				int ret = lstat(file, &st);
				char link[PATH_MAX];
				realpath(file, link);
				if (S_ISLNK(st.st_mode)) {
					printf("%s\n", link);
				} else if (S_ISREG(st.st_mode)) {
					char new_link[PATH_MAX];
					strcpy(new_link, "link_to_");
					strcat(new_link, file);
					symlink(link, new_link);
				}
				break;
			}
		}
 
	}
}