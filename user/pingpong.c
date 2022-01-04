#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p1[2];
  pipe(p1);
  int p2[2];
  pipe(p2);
  char c;
  if (fork() == 0) {
    int pid = getpid();
    read(p1[0], &c, 1);
    printf("%d: received ping\n", pid);
    write(p2[1], "h", 1);
  } else {
    write(p1[1], "h", 1);
    read(p2[0], &c, 1);
    wait(0);
    int pid = getpid();
    printf("%d: received pong\n", pid);
  }
  exit(0);
}
