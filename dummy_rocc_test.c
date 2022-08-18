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
  //x: x10, y: x11, z: x12
  //hold rd = x0
  uint64_t temp = 0;

  // load x into accumulator 2 (funct=0)
  //asm volatile ("custom0 x0, %0, 2, 0" : : "r"(x));
  ROCC_INSTRUCTION_R_R_I(0, temp, x, 2, 0, 0, 10)

  /*
  // read it back into z (funct=1) to verify it
  asm volatile ("custom0 %0, x0, 2, 1" : "=r"(z));
  */
  ROCC_INSTRUCTION_R_R_I(0, z, temp, 2, 1, 12, 0)
  assert(z == x);

  /*
  // accumulate 456 into it (funct=3)
  asm volatile ("custom0 x0, %0, 2, 3" : : "r"(y));
  */
  ROCC_INSTRUCTION_R_R_I(0, temp, y, 2, 3, 0, 11)

  /*
  // verify it
  asm volatile ("custom0 %0, x0, 2, 1" : "=r"(z));
  */
  ROCC_INSTRUCTION_R_R_I(0, z, temp, 2, 1, 12, 0)
  assert(z == x+y);
  
  /*
  // do it all again, but initialize acc2 via memory this time (funct=2)
  asm volatile ("custom0 x0, %0, 2, 2" : : "r"(&x));
  asm volatile ("custom0 x0, %0, 2, 3" : : "r"(y));
  asm volatile ("custom0 %0, x0, 2, 1" : "=r"(z));
  */
  ROCC_INSTRUCTION_R_R_I(0, temp, &x, 2, 2, 0, 13)
  ROCC_INSTRUCTION_R_R_I(0, temp, y, 2, 3, 0, 11)
  ROCC_INSTRUCTION_R_R_I(0, z, temp, 2, 1, 12, 0)

  assert(z == x+y);

  printf("success!\n");
}
