#ifndef _TLA2528_H
#define _TLA2528_H

#include "peripheral_i2c.h"

// Debug Printing via UART:
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#define UART_ID uart1
#define BAUD_RATE 115200
#define UART_RX_PIN 21
#define UART_TX_PIN 24

#define TLA2528_MAX_BUFFER_LENGTH 128

// TLA2528 OpCodes for I2C Operations
#define TLA2528_SINGLE_REGISTER_READ  0b00010000
#define TLA2528_SINGLE_REGISTER_WRITE 0b00001000
#define TLA2528_SET_BIT               0b00011000
#define TLA2528_CLEAR_BIT              0b00100000
#define TLA2528_CONT_REGISTER_READ    0b00110000
#define TLA2528_CONT_REGISTER_WRITE   0b00101000


class TLA2528 {
  protected:
	uint8_t device_address;
  public:
    // Constructor 
	TLA2528(PeripheralI2C *i2cController, uint8_t addr = 0x10);
    // Methods
    void debug_init();
    void send_test_message();
    void single_register_read(uint8_t reg_addr);
    void single_register_write(uint8_t reg_addr, uint8_t value);
    void set_register_bits(uint8_t reg_addr, uint8_t bits_to_set);
    void clear_register_bits(uint8_t reg_addr, uint8_t bits_to_clear);
    void continuous_register_read(uint8_t reg_addr, uint8_t num_bytes_to_read);
    void continuous_register_write(uint8_t reg_addr, uint8_t* byte_array_to_write, uint8_t num_bytes_to_write);

  private:	
	PeripheralI2C* i2c;
	unsigned char i2c_buffer[TLA2528_MAX_BUFFER_LENGTH];
};

#endif // _TLA2528_H
