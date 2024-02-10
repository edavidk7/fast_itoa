#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "fast_itoa.h"

size_t naive(int32_t value, char *dest) {
  size_t idx = 0;
  if (value < 0) {
    dest[idx++] = '-';
    value = -value;
  }
  int32_t divisor = 1000000000;
  int32_t digit;
  int32_t leading_zero = 1;
  while (divisor) {
    digit = value / divisor;
    value %= divisor;
    divisor /= 10;
    if (digit || !leading_zero) {
      dest[idx++] = '0' + digit;
      leading_zero = 0;
    }
  }
  return idx;
}

int main(int argc, char **argv) {
  int s = time(NULL);
  int n = 10;
  int opt;
  while ((opt = getopt(argc, argv, "n:s:")) != -1) {
    switch (opt) {
    case 'n':
      n = atoi(optarg);
      break;
    case 's':
      s = atoi(optarg);
      break;
    default:
      fprintf(stderr, "Usage: %s [-n] <number of repeats> [-s] <random seed>\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  printf("testing with n = %d, s = %d\n", n, s);
  srand(s);
  char buf[11];
  int32_t *values = malloc(n * sizeof(int32_t));
  for (int i = 0; i < n; i++) {
    values[i] = rand();
  }
  // fast itoa test
  unsigned long long start = clock_gettime_nsec_np(CLOCK_MONOTONIC);
  for (int i = 0; i < n; i++) {
    int2a(values[i], buf);
  }
  unsigned long long end = clock_gettime_nsec_np(CLOCK_MONOTONIC);
  printf("fast_itoa: %llu ns\n", end - start);
  printf("fast_itoa: %llu ns per call\n", (end - start) / n);
  // snprintf test
  start = clock_gettime_nsec_np(CLOCK_MONOTONIC);
  for (int i = 0; i < n; i++) {
    sprintf(buf, "%d", values[i]);
  }
  end = clock_gettime_nsec_np(CLOCK_MONOTONIC);
  printf("snprintf: %llu ns\n", end - start);
  printf("snprintf: %llu ns per call\n", (end - start) / n);
  // naive test
  start = clock_gettime_nsec_np(CLOCK_MONOTONIC);
  for (int i = 0; i < n; i++) {
    naive(values[i], buf);
  }
  end = clock_gettime_nsec_np(CLOCK_MONOTONIC);
  printf("naive: %llu ns\n", end - start);
  printf("naive: %llu ns per call\n", (end - start) / n);
  free(values);
  return 0;
}
