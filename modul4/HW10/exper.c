/* strtok example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>

int main ()
{
  char str[] = "exper/ulala/A:exper/ulala/B:exper/ulala/C";
  char * pch;
  //printf ("%s\n", str);
  pch = strtok (str,":");
  char buff[300];
  while (pch != NULL)
  {
    bzero(buff, 300);
    char* x = realpath(pch, buff);
    //printf("%s   %s   %s\n", buff, x, pch);
    pch = strtok (NULL, ":");
  }
  bzero(buff, 300);
  char* x = realpath("/home/involid/mhernoc/caosHW/modul4/HW10/exper/ulala/A/a.txt", buff);
  //printf("%s   %s\n", buff, x);


  struct stat st;
  int xx = stat(buff, &st);
  printf("%ld\n", st.st_mtime);
  stat("/home/involid/mhernoc/caosHW/modul4/HW10/exper/ulala/B/a.txt", &st);
  printf("%ld\n", st.st_mtime);
  return 0;
}