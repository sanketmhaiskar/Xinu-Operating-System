#include <future.h>

uint future_cons(future *fut) {

  int i, status;
  status = future_get(fut, &i);
  if (status < 1) {
    kprintf("future_get failed\n");
    return 1;
  }
  intmask mask;
  mask = disable();
  kprintf("\nIt produced %d\n", i);
  restore(mask);
return OK;
}
