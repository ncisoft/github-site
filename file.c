#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char buf[20480000];
void __count_buf(int *_count, unsigned char *buf, ssize_t nr, ssize_t base)
{
  unsigned char *cp = buf;
  unsigned char *cp_last = cp + nr;
  while (cp < cp_last)
    {
      cp++;
      _count[*cp++] ++;
    }

  printf("process: %ld\n", base + nr); 

}
void __count(int fd)
{
  int _count[256];
  ssize_t nr, size = 0;

  bzero(_count, sizeof(_count));
    while ((nr=read(fd, buf, sizeof(buf))) > 0) 
    {
     __count_buf(_count, buf, nr, size);
     size += nr;
    } 
  close(fd);
}

void __count_mmap(int fd)
{
  struct stat _st;
  unsigned char *content;
  int _count[256];
  ssize_t nread, size;


  fstat(fd, &_st);
  content = (unsigned char *)mmap(NULL, _st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (content == MAP_FAILED)
    {
      printf("mmap call fail\n");
      return;
    }
  size = 0;
  while (size < _st.st_size)
    {
      nread = (_st.st_size - size > sizeof(buf)) ? sizeof(buf) : _st.st_size - size; 
      __count_buf(_count, content+size, nread, size);
      size += nread;
    }

  printf("file size is %ld %p\n", _st.st_size, content);
}

int main()
{
  int fd = open( "5G.bin", O_RDONLY | O_DIRECT);
  if (fd < 0) 
    {
      printf("open file fail\n");
      return 1;
    }

  __count_mmap(fd);
  return 0;
}

