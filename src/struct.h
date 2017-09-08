/**
 * Ardupower - Remote controlled DC power strip
 * Copyright (C) 2017 João Brázio [joao@brazio.org]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <Arduino.h>
#include "ringbuf.h"
#include "enum.h"

struct serial_buffer_t
{
  ringbuf<uint8_t, SERIAL_RX_BUFFER_SIZE> rx;
  ringbuf<uint8_t, SERIAL_TX_BUFFER_SIZE> tx;
};

struct output_t
{
  uint8_t pin;
  output_type_t  type;
  output_state_t state;
  output_state_t on_boot;
};

#endif
