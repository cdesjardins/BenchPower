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

#ifndef UPSIDE_LIQUID_CRYSTAL_Hxx
#define UPSIDE_LIQUID_CRYSTAL_Hxx
#include <LiquidCrystal.h>

class UpsideLiquidCrystal : public LiquidCrystal
{
public:
    UpsideLiquidCrystal(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
    void mybegin(uint8_t cols, uint8_t rows);
    void writeStr(uint8_t x, uint8_t y, char* str);
protected:
    int _cols;
    int _rows;
private:
};

#endif