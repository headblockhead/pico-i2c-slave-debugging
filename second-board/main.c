#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>

#define GPIO_I2C0_SDA 28
#define GPIO_I2C0_SCL 29
#define GPIO_I2C1_SDA 6
#define GPIO_I2C1_SCL 7

i2c_inst_t *slave_i2c_inst = i2c0;
uint8_t our_address = 0b00010111;

i2c_inst_t *master_i2c_inst = i2c1;
uint8_t their_address = 0b00010111;

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
  switch (event) {
  case I2C_SLAVE_RECEIVE:
    i2c_read_byte_raw(i2c); // Read the byte (ignored)
    break;
  case I2C_SLAVE_REQUEST:
    i2c_write_byte_raw(i2c, 0); // Send a dummy byte
    break;
  case I2C_SLAVE_FINISH:
    break;
  default:
    break;
  }
}

void i2c_devices_init(void) {
  // we are master on I2C1
  i2c_init(&i2c1_inst, 400000);
  // we are slave on I2C0
  /*i2c_init(&i2c0_inst, 400000);*/

  gpio_set_function(GPIO_I2C1_SDA, GPIO_FUNC_I2C);
  gpio_set_function(GPIO_I2C1_SCL, GPIO_FUNC_I2C);
  gpio_set_function(GPIO_I2C0_SDA, GPIO_FUNC_I2C);
  gpio_set_function(GPIO_I2C0_SCL, GPIO_FUNC_I2C);

  gpio_pull_up(GPIO_I2C1_SDA);
  gpio_pull_up(GPIO_I2C1_SCL);
  /*gpio_pull_up(GPIO_I2C0_SDA);*/
  /*gpio_pull_up(GPIO_I2C0_SCL);*/

  i2c_slave_init(slave_i2c_inst, our_address, &i2c_slave_handler);
}

void core0_main(void) {
  bool send = true;
  while (true) {
    if (send) {
      uint8_t send_buffer[10];
      memset(send_buffer, 0, 10);
      i2c_write_timeout_us(master_i2c_inst, their_address, send_buffer, 10,
                           false, 1000);
    } else {
      uint8_t send_buffer[1];
      memset(send_buffer, 0, 1);
      i2c_write_timeout_us(master_i2c_inst, their_address, send_buffer, 1,
                           false, 1000);

      uint8_t recv_buffer[9];
      memset(recv_buffer, 0, 9);
      i2c_read_timeout_us(master_i2c_inst, their_address, recv_buffer, 9, false,
                          1000);
    }
    sleep_ms(5);
    send = !send;
  }
}

int main(void) {
  gpio_init(15);
  gpio_set_dir(15, 1);
  gpio_put(15, 0);

  i2c_devices_init();

  core0_main();
}
