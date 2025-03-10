#include <neorv32.h>

int main(void) {
  // Optionally, set up the UART to print a confirmation message
  if (neorv32_uart0_available()) {
    neorv32_uart0_setup(19200, 0);
    neorv32_uart0_printf("Writing 0x0000000B to address 0x40000000\n");
  }


  // Loop forever (or perform additional tasks)
  while (1){
    neorv32_cpu_store_unsigned_word(0x40000000, 0x0000000B);
    neorv32_cpu_delay_ms(250);   // wait 250ms using busy wait
    neorv32_cpu_store_unsigned_word(0x40000000, 0x00000002);
    neorv32_cpu_delay_ms(250);   // wait 250ms using busy wait
  }
  

  return 0;
}
