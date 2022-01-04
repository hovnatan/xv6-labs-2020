#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    char* error_txt = "Error no arguments";
    write(2, error_txt, strlen(error_txt));
    exit(1);
  }
  int n = atoi(argv[1]);
  sleep(n);
  exit(0);
}
