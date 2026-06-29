#ifndef display_H
#define display_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "components/baseComponent.h"

class Display
{
    public:
        static void displayText(String text1, String text2, uint8_t switchMode, U8G2_SSD1306_128X64_NONAME_F_HW_I2C display);
};
#endif