#pragma once

#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/mutex.h>
#include <pico/stdlib.h>

enum com_type {
  COM_TYPE_WANT_PACKET,
  COM_TYPE_PACKET,
};

// master_i2c_inst is the i2c_inst_t that the master talks on
// slave_i2c_inst is the i2c_inst_t that the slave listens on
void communication_init(i2c_inst_t *master_i2c_inst,
                        i2c_inst_t *slave_i2c_inst);

void communication_task(mutex_t *i2c_mutex, bool usb_present);
