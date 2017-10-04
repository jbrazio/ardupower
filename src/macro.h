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


#ifndef bit
  #define bit(b) (1UL << (b))
#endif

#ifndef cbi
  #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#ifndef min
  #define min(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef max
  #define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef abs
  #define abs(x) ((x)>0?(x):-(x))
#endif

#ifndef CRITICAL_SECTION_START
  #define CRITICAL_SECTION_START  const uint8_t SREG_cache = SREG; cli();
  #define CRITICAL_SECTION_END    SREG = SREG_cache;
#endif
