#include <Arduino.h>
#include <U8g2lib.h>
#include "components/baseComponent.h"
#include "components/diode.h"
#include "components/transistor.h"
#include "components/resistor.h"
#include "utilities/button.h"
#include "utilities/display.h"

uint8_t switchButtonPin = 20;
Button switchButton;
Diode diode;
Transistor transistor;
Resistor resistor;
uint8_t pins[4] = {5, 6, 7, 10};
uint8_t analogPins[3] = {0, 1, 3};
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE, 9, 8);
String text1;
String text2;
float VCC = 3.3;
float fixedVCC = 3.0;
uint8_t switchMode = 0;
unsigned long lastMeasuredTime = 0;
uint8_t lastSwitchMode = 0;

void setup()
{
	display.begin();
    switchButton.init(switchButtonPin);
}

void loop()
{
	switchButton.checkPinButtonPressed(switchMode, 2);
	if (switchMode != lastSwitchMode)
	{
		lastSwitchMode = switchMode;
		Display::displayText(baseComponent::componentAllowedPins(switchMode), "", switchMode, display);
	}
	if (millis() - lastMeasuredTime > 1000)
	{
		lastMeasuredTime = millis();
		baseComponent::testComponent(switchMode, text1, text2, &transistor, &diode, &resistor, pins, analogPins, VCC, fixedVCC);
		Display::displayText(text1, text2, switchMode, display);
	}
}
