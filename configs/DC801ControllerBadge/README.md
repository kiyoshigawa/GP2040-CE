# GP2040 Configuration for the DC801 Controller Badge

Basic pin setup for the DC801 Controller Badge.

Since I am using GPIO pins 00 and 01 for I2C on this controller badge, I've reserved pins 21 and 24 for UART Debugging. The default built-in debug functionality of the library seems to only work with pins 00 and 01, so in order to debug things, I have just been using the pico UART libraries directly. Add the below to any file you need UART debug printing in:

```c++
// Debug Printing via UART:
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart1
#define BAUD_RATE 115200
#define UART_TX_PIN 24
#define UART_RX_PIN 21

// Set up our UART with the required speed.
uart_init(UART_ID, BAUD_RATE);
// Set the TX and RX pins by using the function select on the GPIO
// Set datasheet for more information on function select
gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

// Send out a string, with CR/LF conversions
uart_puts(UART_ID, " UART Debug Enabled!\r\n");
```