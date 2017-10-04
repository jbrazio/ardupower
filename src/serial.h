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

#ifndef __HWSERIAL_H__
#define __HWSERIAL_H__

#include <stdint.h>
#include <string.h>
#include "ringbuf.h"
#include "macro.h"

class serial
{
  /**
   * Disable the creation of an instance of this object.
   * This class should be used as a static class.
   */
  private:
    serial() {;}

  public:
    // Being a bit lazy here, this buffer should be private to the class
    // and have a set of wrappers around it.. adding it to the TODO list.
    static struct buffer_t
    {
      ringbuf<uint8_t, 16u> rx;
      ringbuf<uint8_t, 8u> tx;
    } buffer;

  public:
    static bool available();
    static char read();
    static void flush();
    static void process();
    static void setup();
    static void write(const char&);
};

#endif
