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

#include "serial.h"

/**
 * @brief Static class member initialization
 */
serial::buffer_t serial::buffer;

/**
 * @brief USART RX interrupt handler
 */
ISR(USART_RX_vect)
{
  // read a byte from the incoming stream
  uint8_t c = UDR0;

  // check for parity errors and filter for ASCII chars
  // TODO: trigger an alarm on buffer overflow
  if (bit_is_clear(UCSR0A, UPE0)) {
    serial::buffer.rx.enqueue(c);
  } /* else { discard byte } */
}

/**
 * @brief USART TX interrupt handler
 */
ISR(USART_UDRE_vect)
{
  // turn off Data Register Empty Interrupt
  // to stop tx-streaming if this concludes the transfer
  if (serial::buffer.tx.empty()) { UCSR0B &= ~bit(UDRIE0); }

  else {
    // send a byte from the buffer
    UDR0 = serial::buffer.tx.dequeue();
    UCSR0A |= bit(TXC0);
  }
}

/**
 * @brief Checks if the RX queue has data
 * @return Boolean value representing the state of the RX queue
 */
bool serial::available()
{
  return (! buffer.rx.empty());
}

/**
 * @brief Read a char from the RX queue
 * @return A byte (char) from the queue
 */
char serial::read()
{
  CRITICAL_SECTION_START
    const char c = (buffer.rx.empty()) ? 0XFF : buffer.rx.dequeue();
  CRITICAL_SECTION_END

  return c;
}

/**
 * @brief Flushes the TX queue
 */
void serial::flush()
{
  CRITICAL_SECTION_START
    while (bit_is_set(UCSR0B, UDRIE0) || bit_is_clear(UCSR0A, TXC0))
    {
      if (bit_is_clear(SREG, SREG_I) && bit_is_set(UCSR0B, UDRIE0)) {
        if (bit_is_set(UCSR0A, UDRE0)) {
          // send a byte from the buffer
          UDR0 = buffer.tx.dequeue();
          UCSR0A |= bit(TXC0);

          // turn off Data Register Empty Interrupt
          // to stop tx-streaming if this concludes the transfer
          if (buffer.tx.empty()) { UCSR0B &= ~bit(UDRIE0); }
        }
      }
    }
  CRITICAL_SECTION_END
}

/**
 * @brief Parses the incoming byte stream, should only be used by the ISR
 */
void serial::process()
{
  #define CMD_BUFFER_SZ 16

  static size_t pos = 0;
  static char   cmd[CMD_BUFFER_SZ];

  while(available())
  {
    char c = read();

    switch(c) {
      case ':':
        pos = 0;                         // reset the buffer pointer
        memset(&cmd, 0, sizeof(buffer)); // clears the buffer
        break;

      case '#':
        //cmd::process(cmd); // process the data
        break;

      default:
        cmd[pos] = c;                     // store char in buffer
        pos = (pos + 1) % CMD_BUFFER_SZ;  // increase buffer pointer
        break;
    }
  }
}

/**
 * @brief Initializes the USART
 */
void serial::setup()
{
  CRITICAL_SECTION_START
    // Defines the speed at which the serial line will operate.
    // The default settings are: 8-bit, no parity, 1 stop bit.
    const uint16_t UBRR0_value = ((F_CPU / (8L * 9600)) - 1) /2;
    UCSR0A &= ~bit(U2X0); // baud doubler off

    // set baudrate
    UBRR0H = UBRR0_value >> 8;
    UBRR0L = UBRR0_value;

    // enable rx and tx
    UCSR0B |= bit(RXEN0);
    UCSR0B |= bit(TXEN0);

    // enable interrupt on complete reception of a byte
    UCSR0B |= bit(RXCIE0);
  CRITICAL_SECTION_END
}

/**
 * @brief Adds a byte to the TX queue when free space is available
 * @details Take note this method can block program flow when the queue is full
 */
void serial::write(const char& c)
{
  // wait until there is space in the buffer
  while (!buffer.tx.enqueue(c)) serial::flush();

  // Enable Data Register Empty Interrupt
  // to make sure tx-streaming is running
  UCSR0B |= bit(UDRIE0);
}
