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
#include "cmd.h"
#include "print.h"
#include "ardupower.h"
#include "utils.h"
#include "relay.h"

extern output_t output[NUM_OF_CHANNELS];

void cmd::process(const char* buffer)
{
  int8_t n;
  char str[6];
  memset(&str, 0, sizeof(str));

  switch (buffer[0]) {
    case 'O':
      switch (buffer[1]) {
        case 'C': // Power cycle
        case 'D': // Output Disable
        case 'E': // Output Enable
          strncpy(str, buffer + 2, 2);
          n = (uint8_t) utils::hexstr2long(str);

          if (n >= 0 && n < NUM_OF_CHANNELS) {
            switch (buffer[1]) {
              case 'C':
                relay::power(&output[n], PWRCYCLE);
                break;

              case 'D':
                relay::power(&output[n], PWROFF);
                break;

              case 'E':
                relay::power(&output[n], PWRON);
                break;
            }
          }
          break;

        default:
          ;

      } break;

    default:
      serial::println::PGM(PSTR("Ardupower " ARDUPOWER_VERSION " ['$' for help]"));
      break;
  }
}
