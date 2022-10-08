# 1 "c:\\Coding\\CKP_v1\\main\\main.ino"
// for arduino Leonardo board
# 3 "c:\\Coding\\CKP_v1\\main\\main.ino" 2
# 4 "c:\\Coding\\CKP_v1\\main\\main.ino" 2
# 5 "c:\\Coding\\CKP_v1\\main\\main.ino" 2

# 7 "c:\\Coding\\CKP_v1\\main\\main.ino" 2

# 9 "c:\\Coding\\CKP_v1\\main\\main.ino" 2
# 10 "c:\\Coding\\CKP_v1\\main\\main.ino" 2
# 11 "c:\\Coding\\CKP_v1\\main\\main.ino" 2
# 12 "c:\\Coding\\CKP_v1\\main\\main.ino" 2
# 13 "c:\\Coding\\CKP_v1\\main\\main.ino" 2




int rotpinA = 0;
int rotpinB = 1;

volatile int previous = 0;
volatile int counter = 0;

const byte keyH[4 /* number of horiznal keys*/] = {15,14,16,10}; // metrix pins
const byte keyV[5 /* number of vertical keys*/] = {9,8,7,6,5};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(20 /* number of neopixels*/, 4 /* neopixel data pin*/, ((1 << 6) | (1 << 4) | (0 << 2) | (2)) /*|< Transmit as G,R,B*/ + 0x0000 /*|< 800 KHz data transmission*/);

LiquidCrystal lcd(3 /* LCD RS*/, 2 /* LCD E*/, 15 /* LCD D4*/, 14 /* LCD D5*/, 16 /* LCD D6*/, 10 /* LCD D7*/);

bool isKeyPressed[5 /* number of vertical keys*/][4 /* number of horiznal keys*/] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}; // key press flags
bool isToggledKey[5 /* number of vertical keys*/][4 /* number of horiznal keys*/] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}; // key toggle flags

signed char mouseSpeed = 1 /* mouseSpeed default value (MS_MAX ~ MS_MIN)*/; // mouse move speed  (-128 ~ 127)
signed char wheelSpeed = 2 /* wheelSpeed default value (WS_MAX ~ WS_MIN)*/; // mouse wheel speed (-128 ~ 127)
unsigned int repeatSpeed = 10 /* repeatSpeed default value (RS_MAX ~ RS_MIN)*/; // delay value in repeat mode (1 ~ 65535ms)

String uartString = "";
byte kset = 0; // keyset number
unsigned int modekey_time = 0; // count modekey pressed time

byte lcd_time = 0; // lcd display time
String lcd_varname = ""; // lcd display var
int lcd_var = 0; // lcd display var

unsigned int timeCount = 0; // timer count

/**

 * @brief Construct a new ISR object

 * timer int (1kHz = 1ms)

 */
# 51 "c:\\Coding\\CKP_v1\\main\\main.ino"

# 51 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
extern "C" void __vector_21 /* Timer/Counter0 Compare Match A */ (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_21 /* Timer/Counter0 Compare Match A */ (void) 
# 51 "c:\\Coding\\CKP_v1\\main\\main.ino"
                      {
  timeCount++;
  if (timeCount < repeatSpeed) {
    return;
  }

  byte i; // keyH
  byte j; // keyV
  for(i=0; i<4 /* number of horiznal keys*/; i++) { // key checking
    for(j=0; j<5 /* number of vertical keys*/; j++) {
      if (keySets[kset][j][4 /* number of horiznal keys*/] & (0x40>>(i*2))) { // if repeat mode
        if (keySets[kset][j][4 /* number of horiznal keys*/] & (0x80>>(i*2))) { // if toggle mode
          if (isToggledKey[j][i]) { // if toggle flag on
            keyHandle(keySets[kset][j][i], true); // click a key
            keyHandle(keySets[kset][j][i], false);
          }
        } else if (isKeyPressed[j][i]) { // not toggle mode & key flag on
          keyHandle(keySets[kset][j][i], true); // click a key
          keyHandle(keySets[kset][j][i], false);
        }
      }
    }
  }
  timeCount = 0;
}

void setup(void) {
  byte i;

  for(i=0; i<4 /* number of horiznal keys*/; i++) { // pin set
    pinMode(keyH[i], 0x1);
    digitalWrite(keyH[i], 1);
  }
  for(i=0; i<5 /* number of vertical keys*/; i++) {
    pinMode(keyV[i], 0x2);
  } // pin set end

  // other funtion set
  BootKeyboard.begin();
  //Consumer.begin();
  Mouse.begin();
  SurfaceDial.begin();

  lcd.createChar(1, lcd_char_num_lock);
  lcd.createChar(2, lcd_char_cap_lock);
  lcd.createChar(3, lcd_char_scr_lock);
  lcd.createChar(4, lcd_char_locked);
  lcd.createChar(5, lcd_char_unlocked);
  lcd.createChar(7, lcd_char_rhythm);
  lcd.begin(16,2);
  lcd.print(" Custom keypad  ");
  lcd.setCursor(0, 1);
  lcd.print("   by Cremmy    ");

  Serial.begin(9600);
  pixels.begin();
  // other funtion set end

  // timer set (1kHz = 1ms)
  
# 110 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
 (*(volatile uint8_t *)((0x24) + 0x20)) 
# 110 "c:\\Coding\\CKP_v1\\main\\main.ino"
        = 0; //TCCR0A initialize
  
# 111 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
 (*(volatile uint8_t *)((0x25) + 0x20)) 
# 111 "c:\\Coding\\CKP_v1\\main\\main.ino"
        = 0; //TCCR0B initialize
  
# 112 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
 (*(volatile uint8_t *)((0x26) + 0x20)) 
# 112 "c:\\Coding\\CKP_v1\\main\\main.ino"
       = 0; //TCNT0 initialize

  
# 114 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
 (*(volatile uint8_t *)((0x27) + 0x20))
# 114 "c:\\Coding\\CKP_v1\\main\\main.ino"
      = 250;
  
# 115 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
 (*(volatile uint8_t *)((0x25) + 0x20)) 
# 115 "c:\\Coding\\CKP_v1\\main\\main.ino"
        |= (1<<
# 115 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
               3
# 115 "c:\\Coding\\CKP_v1\\main\\main.ino"
                    );
  
# 116 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
 (*(volatile uint8_t *)((0x25) + 0x20)) 
# 116 "c:\\Coding\\CKP_v1\\main\\main.ino"
        |= (1<<
# 116 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
               1
# 116 "c:\\Coding\\CKP_v1\\main\\main.ino"
                   ) | (1<<
# 116 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
                           0
# 116 "c:\\Coding\\CKP_v1\\main\\main.ino"
                               );
  
# 117 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
 (*(volatile uint8_t *)(0x6E)) 
# 117 "c:\\Coding\\CKP_v1\\main\\main.ino"
        |= (1<<
# 117 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
               1
# 117 "c:\\Coding\\CKP_v1\\main\\main.ino"
                     );

  pinMode(rotpinA, 0x2);
  pinMode(rotpinB, 0x2);

  attachInterrupt(((rotpinA) == 0 ? 2 : ((rotpinA) == 1 ? 3 : ((rotpinA) == 2 ? 1 : ((rotpinA) == 3 ? 0 : ((rotpinA) == 7 ? 4 : -1))))), Rotery_changed, 1);
  attachInterrupt(((rotpinB) == 0 ? 2 : ((rotpinB) == 1 ? 3 : ((rotpinB) == 2 ? 1 : ((rotpinB) == 3 ? 0 : ((rotpinB) == 7 ? 4 : -1))))), Rotery_changed, 1);

  pixels.setPixelColor(0, pixels.Color(15,15,15));
  pixels.show();
  for(byte i=1; i<20; i++) {
    delay(50);
    pixels.setPixelColor(i-1, pixels.Color(0,0,0));
    pixels.setPixelColor(i, pixels.Color(15,15,15));
    pixels.show();
  }
  pixels.setPixelColor(19, pixels.Color(0,0,0));
  pixels.show();

  keysetChange(kset);

  
# 138 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
 __asm__ __volatile__ ("sei" ::: "memory")
# 138 "c:\\Coding\\CKP_v1\\main\\main.ino"
      ;
  // timer set end
}

//////////////////////////////// main loop start ////////////////////////////////
void loop(void) {
  byte i; // keyH
  byte j; // keyV

  while(Serial.available()) { //데이터가 오면
    
# 148 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
   (*(volatile uint8_t *)(0x6E))
# 148 "c:\\Coding\\CKP_v1\\main\\main.ino"
   &=(0<<
# 148 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
   1
# 148 "c:\\Coding\\CKP_v1\\main\\main.ino"
   ); //disable timer int
    uartString = Serial.readStringUntil('\n');
    commandCheck(uartString);
    
# 151 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
   (*(volatile uint8_t *)(0x6E))
# 151 "c:\\Coding\\CKP_v1\\main\\main.ino"
   |=(1<<
# 151 "c:\\Coding\\CKP_v1\\main\\main.ino" 3
   1
# 151 "c:\\Coding\\CKP_v1\\main\\main.ino"
   ); //enable timer int
  }

  for(i=0; i<4 /* number of horiznal keys*/; i++) {
    digitalWrite(keyH[i], 1);
  }

  for(i=0; i<4 /* number of horiznal keys*/; i++){ // key checking
    digitalWrite(keyH[i], 0);
    for(j=0; j<5 /* number of vertical keys*/; j++){
      if (keySets[kset][j][4 /* number of horiznal keys*/] & (0x40>>(i*2))) { // if repeat mode
        if (keySets[kset][j][4 /* number of horiznal keys*/] & (0x80>>(i*2))) { // if toggle mode
          toggleRepeat(keyV[j], i, j, kset);
        } else {
          keyRepeat(keyV[j], i, j, kset);
        }
      } else {
        if (keySets[kset][j][4 /* number of horiznal keys*/] & (0x80>>(i*2))) { // if toggle mode
          keyToggle(keyV[j], i, j, kset);
        } else {
          keyCheck(keyV[j], i, j, kset);
        }
      }
    }
    digitalWrite(keyH[i], 1);
  } // key checking end
  //delay(1);

  byte keyleds = BootKeyboard.getLeds(); // lock key checking
  lcd.setCursor(8, 0);
  lcd.write((keyleds & LED_NUM_LOCK) ? '\4' : '\5');
  lcd.setCursor(11, 0);
  lcd.write((keyleds & LED_CAPS_LOCK) ? '\4' : '\5');
  lcd.setCursor(14, 0);
  lcd.write((keyleds & LED_SCROLL_LOCK) ? '\4' : '\5');
  // lock key checking end

  if(isKeyPressed[0][0]) { // mode key hold checking // 0, 150, 300, 450
    modekey_time++;
    if(modekey_time > 600) {
      keysetSelect();
      /*

      kset++;

      if (kset >= KEYSET_MAX) kset = 0;

      keysetChange(kset);

      modekey_time = 0;

      */
# 198 "c:\\Coding\\CKP_v1\\main\\main.ino"
    } else if (modekey_time == 450) {
      LCD_printSet("   holding..    ", 0);
    } else if (modekey_time == 300) {
      LCD_printSet("   holding.     ", 0);
    } else if (modekey_time == 150) {
      LCD_printSet("   holding      ", 0);
    }
  } else modekey_time = 0;
  // mode key hold checking end

  if(lcd_time > 0) { // lcd time checking
    if(lcd_time==255) {
      lcd.setCursor(0, 1);
      lcd.print(modeString[kset]);
      lcd_time = 0;
    } else if(lcd_time==1) {
      LCD_varPrint(lcd_varname, lcd_var);
      lcd_time++;
    } else {
      lcd_time++;
    }
  } // lcd time checking end

  if(counter >= 4) { // rotery checking
    keyHandle(0xB5 /* con_volume_up*/, true);
    keyHandle(0xB5 /* con_volume_up*/, false);
    counter -= 4;
  } else if(counter <= -4) {
    keyHandle(0xB6 /* con_volume_down*/, true);
    keyHandle(0xB6 /* con_volume_down*/, false);
    counter += 4;
  } // rotery checking end

  Neo_keyLight_KB(); // neopixel display
  // neopixel display end
}
//////////////////////////////// main loop end ////////////////////////////////

/**

 * @brief select keyset by key input

 */
# 239 "c:\\Coding\\CKP_v1\\main\\main.ino"
void keysetSelect(void) {
  Keyboard.releaseAll();
  Mouse.releaseAll();
  Neo_keyLight_OFF();
  for(byte i=0; i<5 /* number of vertical keys*/; i++){
    for(byte j=0; j<4 /* number of horiznal keys*/; j++){
      isKeyPressed[i][j] = false;
      isToggledKey[i][j] = false;
    }
  }

  lcd.home();
  lcd.print(" Enter mode num ");
  lcd.setCursor(0, 1);
  lcd.print(" (00~15)   (__) ");
  lcd.setCursor(12, 1);
  delay(500);
  byte setnum1 = 0;
  byte setnum2 = 0;
  byte setnum = 0;
  byte keynumnum = 0;

  while(1) {
    byte keynum = 99;
    byte key = keyInput();
    switch(key) {
      case 'q': // 0
      keynum = 0;
      break;
      case 'm': // 1
      keynum = 1;
      break;
      case 'n': // 2
      keynum = 2;
      break;
      case 'o': // 3
      keynum = 3;
      break;
      case 'i': // 4
      keynum = 4;
      break;
      case 'j': // 5
      keynum = 5;
      break;
      case 'k': // 6
      keynum = 6;
      break;
      case 'e': // 7
      keynum = 7;
      break;
      case 'f': // 8
      keynum = 8;
      break;
      case 'g': // 9
      keynum = 9;
      break;
      case 'p': // enter
      if(keynumnum>1) {
        if(setnum < 16 /* number of key sets*/) {
          keysetChange(setnum);
        } else if(setnum == 99){
          keyTestMode();
          keysetChange(0);
        } else {
          keysetChange(0);
        }
        lcd.noCursor();
        return;
      }
      case 't': // backspace
      if(keynumnum == 2) {
        lcd.setCursor(13, 1);
        lcd.write('_');
        keynumnum = 1;
        setnum2 = 0;
      } else if(keynumnum == 1) {
        lcd.setCursor(12, 1);
        lcd.write('_');
        keynumnum = 0;
        setnum1 = 0;
      } else {
        //none
      }
      delay(100);
      break;
      default:
        delay(10);
      break;
    }
    if(keynum != 99) { // 숫자가 입력됐으면
      if(keynumnum != 0) {
        setnum2 = keynum;
        keynumnum = 2;
        lcd.setCursor(13, 1);
      } else {
        setnum1 = keynum;
        keynumnum = 1;
        lcd.setCursor(12, 1);
      }
      lcd.write(keynum + '0');
      setnum = setnum1 * 10 + setnum2;
      lcd.home();
      if(keynumnum == 2){
        if(setnum < 16 /* number of key sets*/) {
          lcd.print(modeString[setnum]);
        } else if(setnum == 99) {
          lcd.print("      ????      ");
        } else {
          lcd.print(" invaild number ");
        }
      } else {
        lcd.print(" Enter mode num ");
      }
      delay(100);
    }
  }
}

/**

 * @brief change keyset

 * 

 * @param keyset byte, 0 ~ KEYSET_MAX

 */
# 362 "c:\\Coding\\CKP_v1\\main\\main.ino"
void keysetChange(byte keyset) {
  repeatSpeed = 1 /* mouseSpeed default value (MS_MAX ~ MS_MIN)*/;
  lcd.begin(16,2);
  lcd.print("M:_    \1_ \2_ \3_ ");
  lcd.setCursor(2, 0);
  lcd.print(keyset);
  LCD_print(modeString[keyset]);
  kset = keyset;
  delay(500);
}

/////////////// key function ///////////////
/**

 * @brief chack and press a key once

 * 

 * @param key byte, if 0, key is pressed

 * @param keyposH byte, 0 ~ KEYS_H

 * @param keyposV byte, 0 ~ KEYS_V

 * @param keyset byte, 0 ~ KEYSET_MAX

 */
# 382 "c:\\Coding\\CKP_v1\\main\\main.ino"
void keyCheck(byte key, byte keyposH, byte keyposV, byte keyset) {
  if (!digitalRead(key)) { // if pressed
    if (!isKeyPressed[keyposV][keyposH]) { // if first detacted
      keyHandle(keySets[keyset][keyposV][keyposH], true); // press a key
      isKeyPressed[keyposV][keyposH] = true;
    }
  } else if (isKeyPressed[keyposV][keyposH]) { // if key released
    keyHandle(keySets[keyset][keyposV][keyposH], false); // release a key
    isKeyPressed[keyposV][keyposH] = false;
  }
}

/**

 * @brief click a key

 * 

 * @param key byte, if 0, key is pressed

 * @param keyposH byte, 0 ~ KEYS_H

 * @param keyposV byte, 0 ~ KEYS_V

 * @param keyset byte, 0 ~ KEYSET_MAX

 */
# 402 "c:\\Coding\\CKP_v1\\main\\main.ino"
void keyRepeat(byte key, byte keyposH, byte keyposV, byte keyset) {
  if (!digitalRead(key)) { // if pressed
    isKeyPressed[keyposV][keyposH] = true;
  } else {
    isKeyPressed[keyposV][keyposH] = false;
  }
}

/**

 * @brief chack and toggle key

 * 

 * @param key byte, if 0, key is pressed

 * @param keyposH byte, 0 ~ KEYS_H

 * @param keyposV byte, 0 ~ KEYS_V

 * @param keyset byte, 0 ~ KEYSET_MAX

 */
# 418 "c:\\Coding\\CKP_v1\\main\\main.ino"
void keyToggle(byte key, byte keyposH, byte keyposV, byte keyset) {
  bool TK = isToggledKey[keyposV][keyposH]; // previous state

  if (!digitalRead(key)) { // if pressed
    if (!isKeyPressed[keyposV][keyposH]) { // if first detacted
      isToggledKey[keyposV][keyposH] = !TK; // toggle state
      keyHandle(keySets[keyset][keyposV][keyposH], !TK);
      isKeyPressed[keyposV][keyposH] = true;
    }
  } else { // if not pressed
    isKeyPressed[keyposV][keyposH] = false;
  }
}

/**

 * @brief toggle & click a key

 * 

 * @param key byte, if 0, key is pressed

 * @param keyposH byte, 0 ~ KEYS_H

 * @param keyposV byte, 0 ~ KEYS_V

 * @param keyset byte, 0 ~ KEYSET_MAX

 */
# 440 "c:\\Coding\\CKP_v1\\main\\main.ino"
void toggleRepeat(byte key, byte keyposH, byte keyposV, byte keyset) {
  bool TK = isToggledKey[keyposV][keyposH]; // previous state

  if (!digitalRead(key)) { // if pressed
    if (!isKeyPressed[keyposV][keyposH]) { // if first detacted
      isToggledKey[keyposV][keyposH] = !TK; // toggle state
      isKeyPressed[keyposV][keyposH] = true;
    }
  } else { // if not pressed
    isKeyPressed[keyposV][keyposH] = false;
  }
}

/**

 * @brief check keycode and execute correct function

 * 

 * @param keycode unsigned char, 0~255

 * @param pressed bool, if true, key is pressed

 */
# 459 "c:\\Coding\\CKP_v1\\main\\main.ino"
void keyHandle(unsigned char keycode, bool pressed) {
  if (keycode < 0x20) {
    sp_Normal(keycode, pressed);
  } else if (keycode > 0xB3 && keycode < 0xC1) {
    sp_Consumer(keycode, pressed);
  } else if (keycode > 0xEB && keycode < 0xF0) {
    sp_Surface(keycode, pressed);
  } else if (keycode > 0xFB) {
    sp_Function(keycode, pressed);
  } else {
    if (pressed) Keyboard.press(keycode);
    else Keyboard.release(keycode);
  }
}

/**

 * @brief special keycode by mouse, repeat speed, and user function

 * 

 * @param keycode unsigned char, 0x01 ~ 0x1F (31)

 * @param pressed bool, if true, key is pressed

 */
# 480 "c:\\Coding\\CKP_v1\\main\\main.ino"
void sp_Normal(byte keycode, bool pressed) {
  if (pressed) {
    switch(keycode) {
      case 0x01 /* left_mouse*/: // left_mouse
        Mouse.press((1 << 0));
      break;
      case 0x02 /* right_mouse*/: // right_mouse
        Mouse.press((1 << 1));
      break;
      case 0x03 /* middle_mouse*/: // middle_mouse
        Mouse.press((1 << 2));
      break;
      case 0x04 /* mouse_button_4 (prev)*/: // mouse_button_4
        Mouse.press((1 << 3));
      break;
      case 0x05 /* mouse_button_5 (next)*/: // mouse_button_5
        Mouse.press((1 << 4));
      break;
      case 0x08 /* mouse_up*/: // mouse_up
        Mouse.move(0, -mouseSpeed, 0);
      break;
      case 0x09 /* mouse_down*/: // mouse_down
        Mouse.move(0, mouseSpeed, 0);
      break;
      case 0x0A /* mouse_left*/: // mouse_left
        Mouse.move(-mouseSpeed, 0, 0);
      break;
      case 0x0B /* mouse_right*/: // mouse_right
        Mouse.move(mouseSpeed, 0, 0);
      break;
      case 0x0C /* mouse_ul*/: // mouse_ul
        Mouse.move(-mouseSpeed, -mouseSpeed, 0);
      break;
      case 0x0D /* mouse_ur*/: // mouse_ur
        Mouse.move(mouseSpeed, -mouseSpeed, 0);
      break;
      case 0x0E /* mouse_dl*/: // mouse_dl
        Mouse.move(-mouseSpeed, mouseSpeed, 0);
      break;
      case 0x0F /* mouse_dr*/: // mouse_dr
        Mouse.move(mouseSpeed, mouseSpeed, 0);
      break;
      case 0x10 /* mouse_wheel_up*/: // mouse_wheel_up
        Mouse.move(0, 0, wheelSpeed);
      break;
      case 0x11 /* mouse_wheel_down*/: // mouse_wheel_down
        Mouse.move(0, 0, -wheelSpeed);
      break;
      case 0x12 /* mouse_faster*/: // mouse_faster
        if (mouseSpeed < 120 /* mouseSpeed max value (~ 127)*/) mouseSpeed += 1 /* mouseSpeed change value (1 ~ MS_MIN)*/;
        LCD_printSet("mouse:", mouseSpeed);
      break;
      case 0x13 /* mouse_slower*/: // mouse_slower
        if (mouseSpeed > 1 /* mouseSpeed min value (0 ~)*/) mouseSpeed -= 1 /* mouseSpeed change value (1 ~ MS_MIN)*/;
        LCD_printSet("mouse:", mouseSpeed);
      break;
      case 0x14 /* mouse_wheel_faster*/: // mouse_wheel_faster
        if (wheelSpeed < 20 /* wheelSpeed max value (~ 127)*/) wheelSpeed += 1 /* wheelSpeed change value (1 ~ WS_MIN)*/;
        LCD_printSet("wheel:", wheelSpeed);
      break;
      case 0x15 /* mouse_wheel_slower*/: // mouse_wheel_slower
        if (wheelSpeed > 1 /* wheelSpeed min value (0 ~)*/) wheelSpeed -= 1 /* wheelSpeed change value (1 ~ WS_MIN)*/;
        LCD_printSet("wheel:", wheelSpeed);
      break;
      case 0x16 /* repeat_faster*/: // repeat_faster
        if (repeatSpeed > 10 /* repeatSpeed min value (1 ~)*/) repeatSpeed -= 1 /* repeatSpeed change value (1 ~ RS_MIN)*/;
        LCD_printSet("delay:", repeatSpeed);
      break;
      case 0x17 /* repeat_slower*/: // repeat_slower
        if (repeatSpeed < 500 /* repeatSpeed max value (~ 65535)*/) repeatSpeed += 1 /* repeatSpeed change value (1 ~ RS_MIN)*/;
        LCD_printSet("delay:", repeatSpeed);
      break;
      case 0x18 /* function_01*/: // func_01
        func_01();
      break;
      case 0x19 /* function_02*/: // func_02
        func_02();
      break;
      case 0x1A /* function_03*/: // func_03
        func_03();
      break;
      case 0x1B /* function_04*/: // func_04
        func_04();
      break;
      case 0x1C /* function_05*/: // func_05
        func_05();
      break;
      case 0x1D /* function_06*/: // func_06
        func_06();
      break;
      case 0x1E /* function_07*/: // func_07
        func_07();
      break;
      case 0x1F /* function_08*/: // func_08
        func_08();
      break;
    }
  } else {
    switch(keycode) {
      case 0x01 /* left_mouse*/: // left_mouse
        Mouse.release((1 << 0));
      break;
      case 0x02 /* right_mouse*/: // right_mouse
        Mouse.release((1 << 1));
      break;
      case 0x03 /* middle_mouse*/: // middle_mouse
        Mouse.release((1 << 2));
      break;
      case 0x04 /* mouse_button_4 (prev)*/: // mouse_button_4
        Mouse.release((1 << 3));
      break;
      case 0x05 /* mouse_button_5 (next)*/: // mouse_button_5
        Mouse.release((1 << 4));
      break;
    }
  }
}

/**

 * @brief special keycode by consumer key

 * 

 * @param keycode unsigned char, 0xB4 ~ 0xC0 (13)

 * @param pressed bool, if true, key is pressed

 */
# 604 "c:\\Coding\\CKP_v1\\main\\main.ino"
void sp_Consumer(byte keycode, bool pressed) {
  if (pressed) {
    switch(keycode) {
      case 0xB4 /* con_volume_mute*/: // con_volume_mute
        Consumer.press(MEDIA_VOLUME_MUTE);
        Consumer.release(MEDIA_VOLUME_MUTE);
      break;
      case 0xB5 /* con_volume_up*/: // con_volume_up
        Consumer.press(MEDIA_VOLUME_UP);
      break;
      case 0xB6 /* con_volume_down*/: // con_volume_down
        Consumer.press(MEDIA_VOLUME_DOWN);
      break;
      case 0xB7 /* con_media_play_pause*/: // con_media_play_pause
        Consumer.press(MEDIA_PLAY_PAUSE);
        Consumer.release(MEDIA_PLAY_PAUSE);
      break;
      case 0xB8 /* con_media_stop*/: // con_media_stop
        Consumer.press(MEDIA_STOP);
        Consumer.release(MEDIA_STOP);
      break;
      case 0xB9 /* con_media_next*/: // con_media_next
        Consumer.press(MEDIA_NEXT);
        Consumer.release(MEDIA_NEXT);
      break;
      case 0xBA /* con_media_prev*/: // con_media_prev
        Consumer.press(MEDIA_PREV);
        Consumer.release(MEDIA_PREV);
      break;
      case 0xBB /* con_calculator*/: // con_calculator
        Consumer.press(CONSUMER_CALCULATOR);
        Consumer.release(CONSUMER_CALCULATOR);
      break;
      case 0xBC /* con_email*/: // con_email
        Consumer.press(CONSUMER_EMAIL_READER);
        Consumer.release(CONSUMER_EMAIL_READER);
      break;
      case 0xBD /* con_browser_home*/: // con_browser_home
        Consumer.press(CONSUMER_BROWSER_HOME);
        Consumer.release(CONSUMER_BROWSER_HOME);
      break;
      case 0xBE /* con_browser_back*/: // con_browser_back
        Consumer.press(CONSUMER_BROWSER_BACK);
        Consumer.release(CONSUMER_BROWSER_BACK);
      break;
      case 0xBF /* con_browser_forward*/: // con_browser_forward
        Consumer.press(CONSUMER_BROWSER_FORWARD);
        Consumer.release(CONSUMER_BROWSER_FORWARD);
      break;
      /*

      case C_FI: // con_find

        Consumer.press(HID_CONSUMER_AC_FIND);

        Consumer.release(HID_CONSUMER_AC_FIND);

      break;

      */
# 659 "c:\\Coding\\CKP_v1\\main\\main.ino"
    }
  } else {
    switch(keycode) {
      case 0xB5 /* con_volume_up*/: // con_volume_up
        Consumer.release(MEDIA_VOLUME_UP);
      break;
      case 0xB6 /* con_volume_down*/: // con_volume_down
        Consumer.release(MEDIA_VOLUME_DOWN);
      break;
    }
  }
}

/**

 * @brief special keycode by surface dial

 * 

 * @param keycode unsigned char, 0xEC ~ 0xEF (4)

 * @param pressed bool, if true, key is pressed

 */
# 678 "c:\\Coding\\CKP_v1\\main\\main.ino"
void sp_Surface(byte keycode, bool pressed) {
  if (pressed) {
    switch(keycode) {
      case 0xEC /* surface_button*/ : // surface_button
        SurfaceDial.press();
      break;
      case 0xED /* surface_clockwise*/: // surface_clockwise
        SurfaceDial.rotate(10);
      break;
      case 0xEE /* surface_counter_clockwise*/: // surface_counter_clockwise
        SurfaceDial.rotate(-10);
      break;
    }
  } else {
    if(keycode == 0xEC /* surface_button*/) {
      SurfaceDial.release();
    }
  }
}

/**

 * @brief special keycode by special function

 * 

 * @param keycode unsigned char, 0xFC ~ 0xFF (4)

 * @param pressed bool, if true, key is pressed

 */
# 704 "c:\\Coding\\CKP_v1\\main\\main.ino"
void sp_Function(byte keycode, bool pressed) {
  if (pressed) {
    switch(keycode) {
      case 0xFC /* special_function_01*/: // special_function_01
        sp_func_01();
      break;
      case 0xFD /* special_function_02*/: // special_function_02
        sp_func_02();
      break;
      case 0xFE /* special_function_03*/: // special_function_03
        sp_func_03();
      break;
      case 0xFF /* special_function_04*/: // special_function_04
        sp_func_04();
      break;
    }
  }
}

/////////////// lcd function ///////////////
/**

 * @brief set string to print (about 1s)

 * 

 * @param msg String

 * @param var int

 */
# 730 "c:\\Coding\\CKP_v1\\main\\main.ino"
void LCD_printSet(String msg, int var) {
  lcd_varname = msg;
  lcd_var = var;
  lcd_time = 1;
}

/**

 * @brief print string at (0,1) + var

 * 

 * @param msg String

 * @param var int

 */
# 742 "c:\\Coding\\CKP_v1\\main\\main.ino"
void LCD_varPrint(String msg, int var) {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(msg);
  lcd.print(var);
}

/**

 * @brief print string at (0,1)

 * 

 * @param msg String

 */
# 755 "c:\\Coding\\CKP_v1\\main\\main.ino"
void LCD_print(String msg) {
  lcd.setCursor(0, 1);
  lcd.print(msg);
}

/////////////// neopixel function ///////////////
byte Neo_bright[20] = {0,};
byte Neo_count = 0;
byte Neo_count2 = 0;
byte Neo_ranset[20] = {1, 8, 12, 15, 14, 10, 9, 17, 0, 7, 13, 5, 2, 19, 11, 4, 6, 18, 3, 16};

/**

 * @brief turn off leds all

 */
# 769 "c:\\Coding\\CKP_v1\\main\\main.ino"
void Neo_keyLight_OFF(void) {
  for(byte i=0; i<20; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
}

/**

 * @brief turn on leds by fixed color

 */
# 779 "c:\\Coding\\CKP_v1\\main\\main.ino"
void Neo_keyLight_NN(void) {
  for(byte i=0; i<20; i++) {
    pixels.setPixelColor(i, pixels.Color(15 /* PIXEL_BRIGHTMAX*/,15 /* PIXEL_BRIGHTMAX*/,15 /* PIXEL_BRIGHTMAX*/));
  }
  pixels.show();
}

/**

 * @brief turn on leds by rainbow

 */
# 789 "c:\\Coding\\CKP_v1\\main\\main.ino"
void Neo_keyLight_NR(void) {
  for(byte i=0; i<4; i++) {
    pixels.setPixelColor(i, pixels.Color(15 /* PIXEL_BRIGHTMAX*/,0,0));
    pixels.setPixelColor(i+4, pixels.Color(15 /* PIXEL_BRIGHTMAX*/,15 /* PIXEL_BRIGHTMAX*/,0));
    pixels.setPixelColor(i+8, pixels.Color(0,15 /* PIXEL_BRIGHTMAX*/,0));
    pixels.setPixelColor(i+12, pixels.Color(0,15 /* PIXEL_BRIGHTMAX*/,15 /* PIXEL_BRIGHTMAX*/));
    pixels.setPixelColor(i+16, pixels.Color(0,0,15 /* PIXEL_BRIGHTMAX*/));
  }
  pixels.show();
}

/**

 * @brief random light

 */
# 803 "c:\\Coding\\CKP_v1\\main\\main.ino"
void Neo_keyLight_RN(void) {
  byte pnum = Neo_ranset[Neo_count2];
  Neo_bright[pnum] = 15 /* PIXEL_BRIGHTMAX*/;

  for(byte i=0; i<20; i++) {
    byte b = Neo_bright[i];
    pixels.setPixelColor(i, pixels.Color(b,b,b));
    if(Neo_count == 20) {
      if (b > 0) {
        Neo_bright[i] -= 1;
      }
    }
  }
  if(Neo_count2 == 20) {
    Neo_count2 = 0;
  }
  if(Neo_count == 20) {
    Neo_count = 0;
    Neo_count2++;
  }
  Neo_count++;
  pixels.show();
}

/**

 * @brief turn on led pressed key only

 */
# 830 "c:\\Coding\\CKP_v1\\main\\main.ino"
void Neo_keyLight_KB(void) {
  byte pnum = 0;
  for(byte i=0; i<5; i++) {
    for(byte j=0; j<4; j++) {
      if(isKeyPressed[i][j]) {
        Neo_bright[pnum] = 15 /* PIXEL_BRIGHTMAX*/;
      }
      pnum++;
    }
  }
  for(byte i=0; i<20; i++) {
    byte b = Neo_bright[i];
    pixels.setPixelColor(i, pixels.Color(b,b,b));
    if(Neo_count == 20) {
      if (b > 0) {
        Neo_bright[i] -= 1;
      }
    }
  }
  if(Neo_count == 20) {
    Neo_count = 0;
  }
  Neo_count++;
  pixels.show();
}

/**

 * @brief turn on led if key is pressed

 */
# 859 "c:\\Coding\\CKP_v1\\main\\main.ino"
void Neo_keyLight_KA(void) {
  Neo_bright[0] = 0;
  for(byte i=0; i<5; i++) {
    for(byte j=0; j<4; j++) {
      if(isKeyPressed[i][j]) {
        Neo_bright[0] = 1;
      }
    }
  }
  byte b = Neo_bright[0] ? 15 /* PIXEL_BRIGHTMAX*/ : 0;
  for(byte i=0; i<20; i++) {
    pixels.setPixelColor(i, pixels.Color(b,b,b));
  }
  pixels.show();
}

/////////////// serial function ///////////////
/**

 * @brief check if String is command

 * 

 * @param str String

 */
# 881 "c:\\Coding\\CKP_v1\\main\\main.ino"
void commandCheck(String str) {
  Serial.println(str);
  if(str == "SAVE") {
    LCD_print("   SAVING...    ");
    eepromSave();
  } else if(str == "LOAD") {
    LCD_print("   LOADING...   ");
    eepromLoad();
  } else if(str == "PRINT") {
    LCD_print("  PRINTING...   ");
    printData();
  } else if(str == "SETMODE") {
    LCD_print("  SETTING MODE  ");
    setKey();
  } else {
    Serial.println("No command!");
  }
  LCD_print(modeString[kset]);
}

/**

 * @brief save 'keySets' data to EEPROM

 */
# 904 "c:\\Coding\\CKP_v1\\main\\main.ino"
void eepromSave(void) {
  unsigned int address = 0;
  byte data = 0;

  for(byte i=0; i<16 /* number of key sets*/; i++) { // save key set
    for(byte j=0; j<5 /* number of vertical keys*/; j++) {
      for(byte k=0; k<4 /* number of horiznal keys*/+1; k++) {
        data = keySets[i][j][k];
        EEPROM.write(address, data);
        address++;
      }
    }
  }

  for(byte i=0; i<16 /* number of key sets*/; i++) { // save string
    for(byte j=0; j<16; j++) {
      data = modeString[i][j];
      EEPROM.write(address, data);
      address++;
    }
  }

  Serial.println("Save complete!");
  Serial.println(String(address)+" of 1024 bytes used");
}

/**

 * @brief load 'keySets' data from EEPROM

 */
# 933 "c:\\Coding\\CKP_v1\\main\\main.ino"
void eepromLoad(void) {
  unsigned int address = 0;

  for(byte i=0; i<16 /* number of key sets*/; i++) { // load key set
    for(byte j=0; j<5 /* number of vertical keys*/; j++) {
      for(byte k=0; k<4 /* number of horiznal keys*/+1; k++) {
        keySets[i][j][k] = EEPROM.read(address);
        address++;
      }
    }
  }

  for(byte i=0; i<16 /* number of key sets*/; i++) { // load string
    for(byte j=0; j<16; j++) {
      modeString[i][j] = EEPROM.read(address);
      address++;
    }
  }

  Serial.println(String(address)+" bytes Load complete!");
}

/**

 * @brief print 'keySets' data at serial

 */
# 958 "c:\\Coding\\CKP_v1\\main\\main.ino"
void printData(void) {
  Serial.println("Paste this list at 'keySets'");

  for(byte i=0; i<16 /* number of key sets*/; i++) {
    Serial.print("{");
    for(byte j=0; j<5 /* number of vertical keys*/; j++) {
      Serial.print("{");
      for(byte k=0; k<4 /* number of horiznal keys*/+1; k++) {
        char buf[5];
        sprintf(buf, "0x%02X", keySets[i][j][k]);
        Serial.print(buf);
        if(k != 4) {
          Serial.print(",");
        }
      }
      Serial.print("}");
      if(j != 4) {
        Serial.print(",");
      }
    }
    Serial.print("}");
    if(i != 16 /* number of key sets*/-1) {
      Serial.print(",");
    } else {
      Serial.print(" ");
    }
    Serial.println("// "+String(i));
  }

  Serial.println("Paste this list at 'modeString'");
  for(byte i=0; i<16 /* number of key sets*/; i++) {
    Serial.print("\"");
    for(byte j=0; j<16; j++) {
      Serial.print(modeString[i][j]);
    }
    Serial.print("\"");
    if(i != 16 /* number of key sets*/-1) {
      Serial.print(",");
    } else {
      Serial.print(" ");
    }
    Serial.println("// "+String(i));
  }
}

/**

 * @brief get data by serial and save to 'keysets'

 */
# 1006 "c:\\Coding\\CKP_v1\\main\\main.ino"
void setKey(void) {
  String str = "";
  Serial.println("Enter key set number (00~"+String(16 /* number of key sets*/-1)+")");

  byte keyset_num = 0;
  while(1) {
    keyset_num = 0;
    str = "";
    while(!Serial.available());
    while(Serial.available()) {
      str = Serial.readStringUntil('\n');
      Serial.println(str);
    }
    if(str[0]>='0' && str[0]<='9') {
      keyset_num += 10*(str[0]-'0');
      if(str[1]>='0' && str[1]<='9') {
        keyset_num += (str[1]-'0');
        if(keyset_num < 16 /* number of key sets*/) {
          break;
        }
      }
    }
    Serial.println("ERROR! Please re-enter");
  }
  Serial.println("key set "+String(keyset_num)+" selected");

  Serial.println("Enter key set config in hex");
  Serial.println("Ex: 0x50,0x61,0xEB,0xDF,0x00");

  byte strpose;
  byte buf[4 /* number of horiznal keys*/+1] = {0,};
  bool isError = false;
  for(byte i=0; i<5 /* number of vertical keys*/; i++) {
    Serial.println("Enter Row "+String(i));
    while(1) {
      for(byte j=0; j<4 /* number of horiznal keys*/+1; j++) { //버퍼 초기화
        buf[j] = 0;
      }
      str = "";
      while(!Serial.available());
      while(Serial.available()) {
        str = Serial.readStringUntil('\n');
        //Serial.println(str);
      }
      strpose = 0;
      for(byte j=0; j<4 /* number of horiznal keys*/+1; j++) {
        //공백무시하고 시작위치 찾아서...
        isError = true;
        for(byte k=strpose; k<255; k++) {
          if(str[k] == '0' && str[k+1] == 'x') {
            strpose = k+2;
            isError = false;
            break;
          }
        }
        if(isError) break;
        //하나씩 숫자로 변환
        for(byte k=0; k<2; k++) {
          buf[j] = buf[j] << 4;
          if(str[strpose]>='0' && str[strpose]<='9') {
            buf[j] += str[strpose]-'0';
          } else if (str[strpose]>='A' && str[strpose]<='F') {
            buf[j] += str[strpose]-'A'+0x0A;
          } else isError = true;
          strpose++;
        }
      }
      //에러 체크
      if(!isError) break;
      else Serial.println("ERROR! Please re-enter");
    }

    //저장
    for(byte j=0; j<4 /* number of horiznal keys*/+1; j++) {
      keySets[keyset_num][i][j] = buf[j];
    }

    //체크
    for(byte k=0; k<4 /* number of horiznal keys*/+1; k++) {
      char buf[5];
      sprintf(buf, "0x%02X", keySets[keyset_num][i][k]);
      Serial.print(buf);
      if(k != 4) {
        Serial.print(",");
      }
    }
    Serial.println();
    Serial.println("Row "+String(i)+" saved!");

  }
  Serial.println("key set "+String(keyset_num)+" saved!");
}

/////////////// other function ///////////////
/**

 * @brief check key input a~t (but NO keyboard output)

 */
# 1103 "c:\\Coding\\CKP_v1\\main\\main.ino"
unsigned char keyInput(void) {
  byte i;
  byte j;
  for(i=0; i<4 /* number of horiznal keys*/; i++) {
    digitalWrite(keyH[i], 1);
  }
  for(i=0; i<4 /* number of horiznal keys*/; i++){ // key checking
    digitalWrite(keyH[i], 0);
    for(j=0; j<5 /* number of vertical keys*/; j++){
      if(!digitalRead(keyV[j])) {
        return 'a'+i + j*4;
      }
    }
    digitalWrite(keyH[i], 1);
  } // key checking end
  return 0;
}

/**

 * @brief key test mode

 */
# 1124 "c:\\Coding\\CKP_v1\\main\\main.ino"
void keyTestMode(void) {
  lcd.home();
  lcd.print(" key test mode  ");
  lcd.setCursor(0, 1);
  lcd.print(" key test mode  ");
  delay(500);
  lcd.clear();
  lcd.cursor();
    while(1) {
    byte key = keyInput();
    switch(key) {
      case 'q': // 0
        lcd.write('0');
      break;
      case 'm': // 1
        lcd.write('1');
      break;
      case 'n': // 2
        lcd.write('2');
      break;
      case 'o': // 3
        lcd.write('3');
      break;
      case 'i': // 4
        lcd.write('4');
      break;
      case 'j': // 5
        lcd.write('5');
      break;
      case 'k': // 6
        lcd.write('6');
      break;
      case 'e': // 7
        lcd.write('7');
      break;
      case 'f': // 8
        lcd.write('8');
      break;
      case 'g': // 9
        lcd.write('9');
      break;
      case 'p': // enter
        lcd.write('n');
      break;
      case 'h': // +
        lcd.write('+');
      break;
      case 'd': // -
        lcd.write('-');
      break;
      case 'c': // *
        lcd.write('*');
      break;
      case 'b': // /
        lcd.write('/');
      break;
      case 'a': // mode
        lcd.noCursor();
        return;
      break;
      default:
        delay(10);
      break;
    }
    if(key && (key != 'a')) {
      delay(100);
    }
  }
}

/**

 * @brief if rotery pin changed

 */
# 1197 "c:\\Coding\\CKP_v1\\main\\main.ino"
void Rotery_changed(void) {
  int A = digitalRead(rotpinA);
  int B = digitalRead(rotpinB);

  int current = (A << 1) | B;
  int combined = (previous << 2) | current;

  if(combined == 0b0010 ||
     combined == 0b1011 ||
     combined == 0b1101 ||
     combined == 0b0100) {
    counter++;
  }

  if(combined == 0b0001 ||
     combined == 0b0111 ||
     combined == 0b1110 ||
     combined == 0b1000) {
    counter--;
  }

  previous = current;
}

/////////////// user function ///////////////

/**

 * @brief user function 01

 */
# 1226 "c:\\Coding\\CKP_v1\\main\\main.ino"
void func_01(void) {
}

/**

 * @brief user function 02

 */
# 1232 "c:\\Coding\\CKP_v1\\main\\main.ino"
void func_02(void) {
}

/**

 * @brief user function 03

 */
# 1238 "c:\\Coding\\CKP_v1\\main\\main.ino"
void func_03(void) {
}

/**

 * @brief user function 04

 */
# 1244 "c:\\Coding\\CKP_v1\\main\\main.ino"
void func_04(void) {
}

/**

 * @brief user function 05

 */
# 1250 "c:\\Coding\\CKP_v1\\main\\main.ino"
void func_05(void) {
}

/**

 * @brief user function 06

 */
# 1256 "c:\\Coding\\CKP_v1\\main\\main.ino"
void func_06(void) {
}

/**

 * 

 * @brief user function 07

 */
# 1263 "c:\\Coding\\CKP_v1\\main\\main.ino"
void func_07(void) {
  Keyboard.press(0x80);
  Keyboard.press('s');
  Keyboard.release(0x80);
  Keyboard.release('s');
}

/**

 * @brief user function 08

 */
# 1273 "c:\\Coding\\CKP_v1\\main\\main.ino"
void func_08(void) {
}

/**

 * @brief special function 01

 */
# 1279 "c:\\Coding\\CKP_v1\\main\\main.ino"
void sp_func_01(void) {
  Keyboard.print("00");
}

/**

 * @brief special function 02

 */
# 1286 "c:\\Coding\\CKP_v1\\main\\main.ino"
void sp_func_02(void) {
}

/**

 * @brief special function 03

 */
# 1292 "c:\\Coding\\CKP_v1\\main\\main.ino"
void sp_func_03(void) {
}

/**

 * @brief special function 04

 */
# 1298 "c:\\Coding\\CKP_v1\\main\\main.ino"
void sp_func_04(void) {
}
