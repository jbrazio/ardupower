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

#include <Arduino.h>
#include <avr/wdt.h>

#include "types.h"
#include "ardupower.h"
#include "utils.h"

millis_t utils::millis()
{
  #ifdef ARDUINO
    return ::millis();
  #else
    unsigned long m;
    uint8_t oldSREG = SREG;

    // disable interrupts while we read timer0_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to timer0_millis)
    cli();

    m = timer0_millis;
    SREG = oldSREG;
    return m;
  #endif
}

void utils::delay(uint32_t ms)
{
  uint32_t start = micros();

  while (ms > 0) {
    wdt_reset();
    while (ms > 0 && (micros() - start) >= 1000) {
      ms--;
      start += 1000;
    }
  }
}

int32_t utils::hexstr2long(const char* str)
{
  int32_t n = 0;
  n = strtol(str, NULL, 16);
  return (n);
}

uint32_t utils::hexstr2ulong(const char* str)
{
  uint32_t n = 0;
  n = strtoul(str, NULL, 16);
  return (n);
}
