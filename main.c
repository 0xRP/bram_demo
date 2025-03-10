#include <neorv32.h>
#include <stdint.h>

int main(void) {
  if (neorv32_uart0_available()) {
    neorv32_uart0_setup(19200, 0);
    neorv32_uart0_printf(
        "10 configuraciones (valores) empezando en 0xE0000000...\n");
  }

  uint32_t src_base = 0xE0000000;
  uint32_t dst_addr = 0x40000000;
  uint32_t i;

  for (i = 0; i < 10; i++) {
    uint32_t value = 0x0 + i; // For i=0: 0x00, for i=9: 0xFF.
    neorv32_cpu_store_unsigned_word(src_base + (i * 4), value);

    if (neorv32_uart0_available()) {
      neorv32_uart0_printf("Escritura en BRAM de %u en %x\n", value,
                           src_base + (i * 4));
    }
  }

  while (1) {
    for (i = 0; i < 10; i++) {
      uint32_t pos = src_base + (i * 4);
      uint32_t value = neorv32_cpu_load_unsigned_word(pos);

      neorv32_uart0_printf("Lectura de BRAM de la pos. %x, obtenido: %u\n", pos,
                           value);

      neorv32_cpu_store_unsigned_word(dst_addr, value);

      neorv32_cpu_delay_ms(500);
    }
  }

  return 0;
}
