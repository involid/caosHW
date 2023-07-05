#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const size_t MAX_SIZE = 4096;
const char program_code[] = "main.c";
const char program[] = "main.o";
const char executable[] = "./main.o";

int main() {
  char expression[MAX_SIZE];

  fgets(expression, sizeof(expression), stdin);

  char *delimiter = strchr(expression, '\n');
  if (delimiter != NULL) {
    *delimiter = '\0';
  }

  FILE *fp = fopen(program_code, "w");

  fprintf(fp,
          "#include <stdio.h>\n"
          "int main()\n"
          "{\n"
          "   printf(\"%%d\\n\", (%s));\n"
          "   return 0;\n"
          "}\n",
          expression);
  fclose(fp);

  pid_t pid = fork();
  if (pid > 0) {
    int wstatus;
    waitpid(pid, &wstatus, 0);
  } else {
    execlp("gcc", "gcc", "-o", program, program_code, NULL);
  }

  pid = fork();
  if (pid > 0) {
    int wstatus;
    waitpid(pid, &wstatus, 0);
  } else {
    execl(executable, executable, NULL);
  }

  remove(program_code);
  remove(program);
  return 0;
}