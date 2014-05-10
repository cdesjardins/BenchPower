/* 
    Copyright (C) 2014 Chris Desjardins - cjd@chrisd.info
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>
#include "UpsideLiquidCrystal.h"

static byte s_one[8] = 
{
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B00110,
  B00100,
};

static byte s_two[8] = 
{
  B11111,
  B00010,
  B00100,
  B01000,
  B10000,
  B10001,
  B01110,
};

static byte s_three[8] = 
{
  B01110,
  B10001,
  B10000,
  B01000,
  B00100,
  B01000,
  B11111,
};

static byte s_four[8] = 
{
  B01000,
  B01000,
  B11111,
  B01001,
  B01010,
  B01100,
  B01000,
};

static byte s_five[8] = 
{
  B01110,
  B10001,
  B10000,
  B10000,
  B01111,
  B00001,
  B11111,
};

static byte s_six[8] = 
{
  B01110,
  B10001,
  B10001,
  B01111,
  B00001,
  B00010,
  B01100,
};

static byte s_seven[8] = 
{
  B00100,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B11111,
};

static byte s_nine[8] = 
{
  B00110,
  B01000,
  B10000,
  B11110,
  B10001,
  B10001,
  B01110,
};

UpsideLiquidCrystal::UpsideLiquidCrystal(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
    : LiquidCrystal(rs, enable, d0, d1, d2, d3)
{
    
}
void UpsideLiquidCrystal::mybegin(uint8_t cols, uint8_t rows)
{
    _cols = cols;
    _rows = rows;
    begin(cols, rows);
    createChar(0, s_one);
    createChar(1, s_two);
    createChar(2, s_three);
    createChar(3, s_four);
    createChar(4, s_five);
    createChar(5, s_six);
    createChar(6, s_seven);
    createChar(7, s_nine);
}

/*
** Print my string with voltage and current upside down
** due to the fact that the LCD display is mounted in the
** upside down orientation.
*/
void UpsideLiquidCrystal::writeStr(uint8_t x, uint8_t y, char* str)
{
    int i = strlen(str) - 1;
    if (i > _cols)
    {
        i = _cols;
    }
    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        setCursor(_cols - (x + i) - 1, _rows - y - 1);
        switch (str[i])
        {
            default:
                write(str[i]);
                break;
            case '1':
                write(byte(0));
                break;            
            case '2':
                write(byte(1));
                break;            
            case '3':
                write(byte(2));
                break;            
            case '4':
                write(byte(3));
                break;            
            case '5':
                write(byte(4));
                break;            
            case '6':
                write(byte(5));
                break;            
            case '7':
                write(byte(6));
                break;            
            case '9':
                write(byte(7));
                break;
            case '.':
                write(byte(0xb0));
                break;
            case 'V':
                write(byte(0xd7));
                break;
        }
    }
}
