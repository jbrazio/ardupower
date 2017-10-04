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

#include <avr/interrupt.h>
#include "macro.h"

namespace timer
{
  namespace one
  {
    /**
     * @brief Timer one setup
     * @details Timer 1 is used as the main thread heartbeat
     */
    inline void setup() {
      CRITICAL_SECTION_START
        // set output compare register A to 16 Hz
        OCR1A = 0xF42;

        // set waveform generation mode to CTC
        TCCR1B |= bit(WGM12);

        // set clock select to 256 (from prescaler)
        TCCR1B |= bit(CS12);

        // set output compare A match interrupt enable
        TIMSK1 |= bit(OCIE1A);
      CRITICAL_SECTION_END
    }
  }
}

ISR(TIMER1_COMPA_vect)
{
  ;;
}
