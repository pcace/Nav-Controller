#include <Arduino.h>
#include <OneButton.h>
#include <Arduino.h>
#include <BleKeyboard.h>

#if CONFIG_IDF_TARGET_ESP32C3
  #define BUTTON_PIN_1 0
  #define BUTTON_PIN_2 1
  #define BUTTON_PIN_3 2
  #define BUTTON_PIN_4 3
  #define BUTTON_PIN_5 4
#else
  #define BUTTON_PIN_1 21
  #define BUTTON_PIN_2 32
  #define BUTTON_PIN_3 16
  #define BUTTON_PIN_4 2
  #define BUTTON_PIN_5 17
#endif

BleKeyboard bleKeyboard;

/**
 * Keyboard Map
 * 
 *             | Click      | Longpress  | DoubleClick
 * ------------|------------|------------|-------------
 * Button 1    | Arrow Up   |            | Arrow Up
 * Button 2    | Arrow Right| +          | Arrow Right
 * Button 3    | C (center) |            | D (direction)
 * Button 4    | Arrow Left | -          | Arrow Left
 * Button 5    | Arrow Down |            | Arrow Down
 */

OneButton buttons[] = {
  OneButton(BUTTON_PIN_1, true, true),
  OneButton(BUTTON_PIN_2, true, true),
  OneButton(BUTTON_PIN_3, true, true),
  OneButton(BUTTON_PIN_4, true, true),
  OneButton(BUTTON_PIN_5, true, true)
};

void onButtonPress(void* buttonIndex) {
  int index = (int)buttonIndex;
  Serial.print("Button ");
  Serial.print(index + 1);
  Serial.println(" pressed");

  if (bleKeyboard.isConnected()) {
    switch (index) {
      case 0:
        bleKeyboard.write(KEY_UP_ARROW);
        Serial.println("KEY_UP_ARROW");
        break;
      case 1:
        bleKeyboard.write(KEY_RIGHT_ARROW);
        Serial.println("KEY_RIGHT_ARROW");
        break;
      case 2:
        bleKeyboard.write('C');
        Serial.println('C');
        break;
      case 3:
        bleKeyboard.write(KEY_LEFT_ARROW);
        Serial.println("KEY_LEFT_ARROW");
        break;
      case 4:
        bleKeyboard.write(KEY_DOWN_ARROW);
        Serial.println("KEY_DOWN_ARROW");
        break;
    }
  }
}

void onButtonDoubleClick(void* buttonIndex) {
  int index = (int)buttonIndex;
  Serial.print("Button ");
  Serial.print(index + 1);
  Serial.println(" double-clicked");

  if (bleKeyboard.isConnected()) {
    switch (index) {
      case 0:
        bleKeyboard.write(KEY_UP_ARROW);
        Serial.println("KEY_UP_ARROW");
        break;
      case 1:
        bleKeyboard.write(KEY_RIGHT_ARROW);
        Serial.println("KEY_RIGHT_ARROW");
        break;
      case 2:
        bleKeyboard.write('D');
        Serial.println('D');
        break;
      case 3:
        bleKeyboard.write(KEY_LEFT_ARROW);
        Serial.println("KEY_LEFT_ARROW");
        break;
      case 4:
        bleKeyboard.write(KEY_DOWN_ARROW);
        Serial.println("KEY_DOWN_ARROW");
        break;
    }
  }
}

void onButtonLongPress(void* buttonIndex) {
  int index = (int)buttonIndex;
  Serial.print("Button ");
  Serial.print(index + 1);
  Serial.println(" long-pressed");

  if (bleKeyboard.isConnected()) {
    switch (index) {
      case 1:
        bleKeyboard.write(0x2b); // '+' 
        Serial.println('+');
        break;
      case 3:
        bleKeyboard.write(0x2f); // '-' 
        Serial.println('-');
        break;
    }
  }

}

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
  delay(1000);

  for (int i = 0; i < 5; i++) {
    buttons[i].attachClick(onButtonPress, (void*)i);
    buttons[i].attachDoubleClick(onButtonDoubleClick, (void*)i);
    buttons[i].attachLongPressStart(onButtonLongPress, (void*)i);
  }

  Serial.println("Buttons initialized.");
}

void loop() {
  for (int i = 0; i < 5; i++) {
    buttons[i].tick();
  }
  delay(10); 
}