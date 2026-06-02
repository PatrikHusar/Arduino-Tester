#include "display.h"

void Display::displayText(String text1, String text2, uint8_t switchMode, U8GLIB_SSD1306_128X64 display)
{
    display.firstPage();
    do
    {
        display.setFont(u8g_font_7x13);
        display.setPrintPos(1, 10);
        display.print(baseComponent::modeToStr(switchMode));
        display.setPrintPos(1, 30);
        display.print(text1);
        display.setPrintPos(1, 50);
        display.print(text2);
    }
    while (display.nextPage());
}