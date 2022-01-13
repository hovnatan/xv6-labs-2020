#include "kernel/types.h"
#include "kernel/fs.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  char ch;
  char buf[512];
  char *args[MAXARG];
  for (int i = 1; i < argc; ++i) {
    args[i - 1] = argv[i];
  }
  char *p = buf;
  while (read(0, &ch, 1) == 1) {
    if (ch == '\n') {
      *p++ = 0;
      if (fork() == 0) {
        args[argc - 1] = buf;
        args[argc] = 0;
        exec(argv[1], args);
      } else {
        p = buf;
        wait(0);
      }
    } else {
      *p++ = ch;
    }
  }
  exit(0);
}
