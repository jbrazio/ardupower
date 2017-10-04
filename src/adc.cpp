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

#include <adc.h>

/**
 * @brief Static class member initialization
 */
volatile adc::adc_t adc::runtime = { 0, 0, -1 };

/**
 * @brief Analog to Digital Converter interrupt handler
 */
ISR(ADC_vect)
{
  adc::set();
}

bool adc::setup()
{
  if ((runtime.state & ADC_READY) == 1) return false;

  CRITICAL_SECTION_START
    // set ADC prescaler select to 128
    ADCSRA |= bit(ADPS2) | bit(ADPS1) | bit(ADPS0);

    // set ADC Enable
    ADCSRA |= bit(ADEN);

    // set ADC multiplexer selection to internal 1.1V
    ADMUX  |= bit(REFS1) | bit(REFS0);

    // set digital input disable register to A1-A5
    //DIDR0 |= bit(ADC5D) | bit(ADC4D) | bit(ADC3D) | bit(ADC2D) | bit(ADC1D);

    // mark adc runtime register as ready
    runtime.state |= ADC_READY;
  CRITICAL_SECTION_END

  return true;
}

/**
 * @brief Requests an ADC reading update of the active channel
 * @return Result of the operation as a boolean
 */
bool adc::update(const uint8_t& channel)
{
  if ((runtime.state & ADC_READY) == 0) return false;
  if ((runtime.state & ADC_REQ_READING) == 1) return false;

  CRITICAL_SECTION_START
    runtime.state &= ~ADC_REQ_READY;
    runtime.state |= ADC_REQ_READING;

    runtime.value = -1;                                   // reset last reading
    runtime.channel = channel;                            // store the active channel

    ADMUX = bit (REFS1) | bit (REFS0) | (channel & 0x07); // select aref 1.1V and the adc channel
    ADCSRA |= bit(ADSC) | bit(ADIE);                      // request an async ADC reading
  CRITICAL_SECTION_END

  return true;
}

/**
 * @brief Get the ADC value of the selected channel from cache
 * @return Cached ADC value
 */
int16_t adc::get()
{
  if ((runtime.state & ADC_READY) == 0) return -1;

  // wait until the pending ADC read request is finished
  while((runtime.state & ADC_REQ_READING) == 1) {
    __asm__ __volatile__ ("nop\n\t");
  }

  return runtime.value;
}

/**
 * @brief Set the ADC reading cache, should only be used by the ISR
 */
void adc::set()
{
  CRITICAL_SECTION_START
    runtime.value  = ADCW;
    runtime.state |= ADC_REQ_READY;
    runtime.state &= ~ADC_REQ_READING;
  CRITICAL_SECTION_END
}
