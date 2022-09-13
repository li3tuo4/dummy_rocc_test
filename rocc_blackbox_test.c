// The following is a RISC-V program to test the functionality of the
// dummy RoCC accelerator.
// Compile with riscv64-unknown-elf-gcc dummy_rocc_test.c
// Run with spike --extension=dummy_rocc pk a.out

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "rocc.h"

int main() {
  uint64_t x = 123, y = 456, z = 0;
  uint64_t temp = 0;
  uint64_t result = 0;
  uint64_t zero = 0;
  printf("Start rocc blackbox test!\n");

  // Test 0: 0 + 0 = 0
  ROCC_INSTRUCTION_DSS(3, result, zero, zero, 0 /*dontcare*/) 
  assert(result == 0);

  // Test 1: 123 + 456 = 579
  ROCC_INSTRUCTION_DSS(3, result, x, y, 0 /*dontcare*/) 
  assert(result == 123 + 456);

  printf("success!\n");
}
