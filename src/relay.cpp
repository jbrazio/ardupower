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
#include "relay.h"
#include "ardupower.h"

void relay::init(output_t *output)
{
  pinMode(output->pin, OUTPUT);
  relay::power(output, output->on_boot);
}

void relay::power(output_t *output, output_state_t state)
{
  switch (state)
  {
    case PWRON:
    case PWROFF:
      switch (output->type)
      {
        case NORMALLY_OPEN:
          digitalWrite(output->pin, (state == PWRON) ? HIGH : LOW);
          break;

        case NORMALLY_CLOSED:
          digitalWrite(output->pin, (state == PWRON) ? LOW : HIGH);
          break;

        default:
          ; // do nothing
      }

      output->state = state;
      break;

    case PWRCYCLE:
      if (output->state == PWRON) {
        digitalWrite(output->pin, ! digitalRead(output->pin));
        output->state = state;
      }
      break;

    default:
      ; // do nothing
  }
}
