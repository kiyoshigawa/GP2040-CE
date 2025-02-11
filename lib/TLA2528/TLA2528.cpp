#include "TLA2528.h"

TLA2528::TLA2528(PeripheralI2C *i2cController, uint8_t addr) {
    i2c = i2cController;
    device_address = addr;
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

void TLA2528::single_register_read(uint8_t reg_addr){
    i2c_buffer[0] = TLA2528_SINGLE_REGISTER_READ;
    i2c_buffer[1] = reg_addr;
    i2c->write(device_address, i2c_buffer, 2);
    i2c->read(device_address, i2c_buffer, 1);
    //Figure out how to handle read byte. Return value? Assume it's in place and read from class buffer?
}

void TLA2528::single_register_write(uint8_t reg_addr, uint8_t value){
    i2c_buffer[0] = TLA2528_SINGLE_REGISTER_WRITE;
    i2c_buffer[1] = reg_addr;
    i2c_buffer[2] = value;
    i2c->write(device_address, i2c_buffer, 3);
}

void TLA2528::set_register_bits(uint8_t reg_addr, uint8_t bits_to_set){
    i2c_buffer[0] = TLA2528_SET_BIT;
    i2c_buffer[1] = reg_addr;
    i2c_buffer[2] = bits_to_set;
    i2c->write(device_address, i2c_buffer, 3);

}

void TLA2528::clear_register_bits(uint8_t reg_addr, uint8_t bits_to_clear){
    i2c_buffer[0] = TLA2528_CLEAR_BIT;
    i2c_buffer[1] = reg_addr;
    i2c_buffer[2] = bits_to_clear;
    i2c->write(device_address, i2c_buffer, 3);

}

void TLA2528::continuous_register_read(uint8_t reg_addr, uint8_t num_bytes_to_read){
    if(num_bytes_to_read >= TLA2528_MAX_BUFFER_LENGTH){
        return; //handle error somehow, can't read more than buffer can hold
    }
    i2c_buffer[0] = TLA2528_CONT_REGISTER_READ;
    i2c_buffer[1] = reg_addr;
    //This hasn't been done yet. Figure out how buffer will work
}

void TLA2528::continuous_register_write(uint8_t reg_addr, uint8_t* byte_array_to_write, uint8_t num_bytes_to_write){
    if(num_bytes_to_write >= TLA2528_MAX_BUFFER_LENGTH){
        return; //handle error somehow, can't write more than buffer can hold
    }
    i2c_buffer[0] = TLA2528_CONT_REGISTER_WRITE;
    i2c_buffer[1] = reg_addr;
    //This hasn't been done yet. Figure out how buffer will work
}

void TLA2528::send_test_message() {
    // //read status buffer
    single_register_read(0x00);
    // // set brownout bit:
    set_register_bits(0x00, 0x01);
    // //read status again to ensure the 0th bit is 0 now:
    single_register_read(0x00);
}
