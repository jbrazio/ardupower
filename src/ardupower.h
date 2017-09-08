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

#ifndef __ARDUPOWER_H__
#define __ARDUPOWER_H__

// ----------------------------------------------------------------------------
// Unique identifier ----------------------------------------------------------
// ----------------------------------------------------------------------------

// You should generate a random UID for each Ardupower as this will help you
// identify each node. Try the following online tool:
// https://www.uuidgenerator.net/version4
#define ARDUPOWER_UID "53b897f6-cb6e-4709-81ff-70c82af243b4"

// ----------------------------------------------------------------------------
// Program info and version ---------------------------------------------------
// ----------------------------------------------------------------------------
#define ARDUPOWER_VERSION "0.1a"
#define ARDUPOWER_VERSION_BUILD "20170908"


// ----------------------------------------------------------------------------
// Environment preparation ----------------------------------------------------
// ----------------------------------------------------------------------------
#ifdef ARDUINO
  #undef SERIAL_RX_BUFFER_SIZE
  #undef SERIAL_TX_BUFFER_SIZE
  #undef SERIAL_BAUDRATE
  #undef SERIAL_NO_DATA
  #undef COMMAND_BUFFER_SIZE
#endif


// ----------------------------------------------------------------------------
// Motor driver configuration -------------------------------------------------
// ----------------------------------------------------------------------------
#define NUM_OF_CHANNELS 8

#define CHANNEL01 { 9, NORMALLY_CLOSED, PWRUNKNOWN, PWROFF }
#define CHANNEL02 { 8, NORMALLY_CLOSED, PWRUNKNOWN, PWROFF }
#define CHANNEL03 { 7, NORMALLY_CLOSED, PWRUNKNOWN, PWROFF }
#define CHANNEL04 { 6, NORMALLY_CLOSED, PWRUNKNOWN, PWROFF }
#define CHANNEL05 { 5, NORMALLY_CLOSED, PWRUNKNOWN, PWROFF }
#define CHANNEL06 { 4, NORMALLY_CLOSED, PWRUNKNOWN, PWROFF }
#define CHANNEL07 { 3, NORMALLY_CLOSED, PWRUNKNOWN, PWROFF }
#define CHANNEL08 { 2, NORMALLY_CLOSED, PWRUNKNOWN, PWROFF }


// ----------------------------------------------------------------------------
// SERIAL PORT configuration --------------------------------------------------
// ----------------------------------------------------------------------------

// Defines the max number of received chars over the serial line that can be
// waiting to be processed, if the buffer gets full incoming data will be lost.
#define SERIAL_RX_BUFFER_SIZE 16

// Defines the max number of chars waiting to be sent over the serial line.
#define SERIAL_TX_BUFFER_SIZE 64

// Defines the speed at which the serial line will operate.
// The default settings are: 8-bit, no parity, 1 stop bit.
#define SERIAL_BAUDRATE       9600

// Defines the char which will represent a null buffer value, do not change this.
#define SERIAL_NO_DATA        0xff

// Defines the max length of a received command string.
#define COMMAND_BUFFER_SIZE   16


// ----------------------------------------------------------------------------
// Temperature sensor configuration -------------------------------------------
// ----------------------------------------------------------------------------
#define THERMISTOR_NOMINAL_TEMP      25.0
#define THERMISTOR_BCOEFFICIENT    3950.0
#define THERMISTOR_NOMINAL_VAL    10000.0
#define THERMISTOR_SERIESRESISTOR 10000.0

#endif
