#ifndef display_H
#define display_H

#include <Arduino.h>
#include <U8glib.h>
#include "components/baseComponent.h"

class Display
{
    public:
        static void displayText(String text1, String text2, uint8_t switchMode, U8GLIB_SSD1306_128X64 display);
};
#endif