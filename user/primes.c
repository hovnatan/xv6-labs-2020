#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p[2];
  int in, out;
  pipe(p);
  in = p[0];
  out = p[1];
  int k;
  int n = 0;
  if (fork() == 0) {
    int i = 0;
    close(out);
    out = -1;
    while (1) {
      int n_read = read(in, &k, 4);
      if (n_read == 0) {
        wait(0);
        close(in);
        break;
      }
      if (n == 0) {
        n = k;
        printf("prime %d\n", n);
      }
      if (i != n) {
        if (out == -1) {
          pipe(p);
          if (fork() == 0) {
            in = p[0];
            close(p[1]);
            n = 0;
            i = 0;
            continue;
          } else {
            out = p[1];
            close(p[0]);
          }
        }
        write(out, &k, 4);
      } else {
        i = 0;
      }
      i += 1;
    }
  } else {
    close(in);
    for (int i = 2; i <= 35; ++i) {
      write(out, &i, 4);
    }
    close(out);
    wait(0);
  }

  exit(0);
}
