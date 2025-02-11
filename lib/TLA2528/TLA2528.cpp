#include "TLA2528.h"

TLA2528::TLA2528(PeripheralI2C *i2cController, uint8_t addr) {
    i2c = i2cController;
    address = addr;
    debug_init();
}

void TLA2528::debug_init() {
    // Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, "UART TLA2528->debug_init() Debug Enabled!\r\n");
}

void TLA2528::send_test_message() {
    //read status buffer
    i2c_buffer[0] = TLA2528_SINGLE_REGISTER_READ;
    i2c_buffer[1] = 0x00; // register 0
    i2c->write(address, i2c_buffer, 2);
    i2c->read(address, i2c_buffer, 1);

    // set brownout bit:
    i2c_buffer[0] = TLA2528_SET_BIT;
    i2c_buffer[1] = 0x00; // register 0
    i2c_buffer[2] = 0x01; // set bit 1 to 1
    i2c->write(address, i2c_buffer, 3);

    //read status again to ensure the 0th bit is 0 now:
    i2c_buffer[0] = TLA2528_SINGLE_REGISTER_READ;
    i2c_buffer[1] = 0x00; // register 0
    i2c->write(address, i2c_buffer, 2);
    i2c->read(address, i2c_buffer, 1);
}
