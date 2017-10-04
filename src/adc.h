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

#include <stdint.h>
#include <avr/interrupt.h>
#include "macro.h"

#define ADC_READY         bit(0)  // bitmask 00000001
#define ADC_REQ_READING   bit(1)  // bitmask 00000010
#define ADC_REQ_READY     bit(2)  // bitmask 00000100

class adc
{
  /**
   * Disable the creation of an instance of this object.
   * This class should be used as a static class.
   */
  private:
    adc() {;}

  protected:
    static volatile struct adc_t
    {
      uint8_t state,
              channel;
      int16_t value;
    } runtime;

  public:
    static bool setup();
    static bool update(const uint8_t&);
    static int16_t get();
    static void set();
};
