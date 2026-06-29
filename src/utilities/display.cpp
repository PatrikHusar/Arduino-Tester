#include "display.h"

void Display::displayText(String text1, String text2, uint8_t switchMode, U8G2_SSD1306_128X64_NONAME_F_HW_I2C display)
{
    display.firstPage();
    do
    {
        display.setFont(u8g2_font_7x13_tr);
        display.setCursor(1, 10);
        display.print(baseComponent::modeToStr(switchMode));
        display.setCursor(1, 30);
        display.print(text1);
        display.setCursor(1, 50);
        display.print(text2);
    }
    while (display.nextPage());
}