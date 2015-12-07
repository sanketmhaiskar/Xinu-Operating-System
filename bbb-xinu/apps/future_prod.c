#include <future.h>

int TEST;
uint future_prod(future *fut) {

  int i, j,status;
  j = (int)fut;
  for (i=0; i<1000; i++) {
    j += i;
  }
//j=5;
//j=TEST++;

status = future_set(fut, &j);
intmask mask;
mask=disable();
if (status < 1) {
    kprintf("future_set failed\n");
    restore(mask);
    return 1;
  }
  restore(mask);
  return OK;
}

