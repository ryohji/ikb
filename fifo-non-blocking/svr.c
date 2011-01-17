#include "fifoname.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /* for O_RDONLY & O_NONBLOCK */
#include <sys/select.h> /* for select */
#include <sys/time.h>   /* for timeval */
#include <stdio.h>

static int data_avail(int fd);

int main(void) {
  if (0 == mkfifo(fifoname, 0666)) {
    puts("[server] opening fifo...");
    int fd = open(fifoname, O_RDONLY | O_NONBLOCK);
    if (-1 != fd) {
      int retry = 10;
      while (retry-- && !data_avail(fd)) {
	puts("[server] waiting client request...");
	sleep(1);
      }
      if (data_avail(fd)) {
	int v;
	read(fd, &v, sizeof(v));
	printf("[server] recieves request: %d\n", v);
      } else {
	printf("[server] no data from client.\n");
      }
      puts("[server] close fifo.");
      close(fd);
    }
    puts("[server] remove fifo node.");
    unlink(fifoname);
  }
  return 0;
}

/* return 1, if given fd is ready to read, otherwise 0. */
static int data_avail(int fd) {
  fd_set rfds;
  struct timeval timeout = { .tv_sec = 0, .tv_usec = 0 }; /* 0 sec for polling */

  FD_ZERO(&rfds);
  FD_SET(fd, &rfds);

  /* 1st argument of select is highest fd number + 1, passed in 2nd .. 4th fd_sets. */
  return 0 < select(fd + 1, &rfds, NULL, NULL, &timeout) ? FD_ISSET(fd, &rfds) : 0;
}
