#include "fifoname.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /* for O_RDONLY & O_NONBLOCK */
#include <stdio.h>

int main(void) {
  puts("[client] opening fifo...");
  const int fd = open(fifoname, O_WRONLY);
  if (-1 != fd) {
    int request = 0xdeadbeaf;
    puts("[client] writing request...");
    write(fd, &request, sizeof(request));
    close(fd);
  }
  puts("[client] exit.");
  return 0;
}
