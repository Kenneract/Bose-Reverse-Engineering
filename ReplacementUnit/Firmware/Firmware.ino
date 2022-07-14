/* Author: Kennan (Kenneract)
 * Created: Jun.30.2022
 * Modified: Jul.14.2022
 * Hardware: Bose Console Recreation (Arduino Nano)
 * Purpose: Quick and rough firmware for the custom Bose console recreation.
 *          Reads IR remote and button commands, sends serial data to Bass Module,
 *          displays volume on 7-seg display, allows the control of volume,
 *          power, source, treble/bass compensation, & mute.
 *          
 * NOTES: -All IR data is interpreted as MSB-first
*/

//Include Libraries
#include <Arduino.h>
#define IR_INPUT_PIN 2 //Infrared receiver data pin
#define NO_LED_FEEDBACK_CODE //Suppress LED feedback for IR decoding
#include "TinyIRReceiver.hpp" //IRRemote
#include "FastLED.h"
#include "FastLED_RGBW.h"
#include "SoftwareSerialWithHalfDuplex.h"
#include "MemoryFree.h"



// Pin Definitions
const byte SERIAL_PIN = 4; //4800 baud SmartSpeaker serial connection
const byte IND_PIN = 3; //Green indicator LED
const byte RGB_PIN = 13; //SK6812 RGB indicator
// <ir pin at top>
const byte RELAY_PIN = A5; //Source-change relay
const byte PWR_BUT_PIN = A2; //Power button
const byte UP_BUT_PIN = A0; //Volume+ button
const byte DOWN_BUT_PIN = A1; //Volume- button
const byte DISPLAY_PINS[] = {6, 7, 8, 12, 11, 9, 10}; //7-seg pins (A,B,C,D,E,F,G, no DP)


// Config
const bool FAKE_SERIAL = false; //If should pretend all outgoing serial data is successful to prevent program lag while Bass Module is disconnected. FOR DEBUGGING ONLY
const byte RGB_BRIGHTNESS = 10; //RGB LED brightness (0-255)
const byte IND_BRIGHTNESS = 24; //Indicator LED brightness (0-255)
const unsigned int LOADING_ANIM_DELAY = 80; //Time (ms) between segment switches in the 7seg loading animation
//  Green indicator settings
const unsigned int IND_FLASH_TIME = 75; //time (ms) to flash the green indicator LED for
//    Speaker Settings Bounds
const int COMPENSATION_MAX = 14;
const int COMPENSATION_MIN = -14;
const int VOL_MAX = 100; 
const int VOL_MIN = 0;
//  Idle command
const unsigned int IDLE_CMD_INT = 800; //How often (in ms) that the Idle command should be sent to the Bass module
//  buttons
const byte BUTT_DEBOUNCE = 90; //milliseconds for button debounce time
//  7seg char display
const unsigned int DISPLAY_FLASH_TIME = 300; //Duration (ms) to illuminate each display character
const unsigned int DISPLAY_GAP_TIME = 80; //Duration (ms) between each display character
const unsigned int DISPLAY_RESET_TIME = 800; //Duration (ms) between display cycles
//  button-holding settings
const unsigned int BUTT_HOLD_TIME = 800; //How long (ms) a button must be held down for to count as "holding". Some buttons don't support holding.
const unsigned int BUTT_REPEAT_INT = 200; //How long (ms) between "press" calls when a button is "held" down. Some buttons don't support holding.
//    RGB colours
const CRGBW VOLUME_COLOUR = CRGBW(0,255,0,0);
const CRGBW MUTE_COLOUR = CRGBW(255,0,0,0);
const CRGBW BASS_COLOUR = CRGBW(255,0,255,0);
const CRGBW TREBLE_COLOUR = CRGBW(0,0,255,0);
//  Value mode settings
const byte NUM_MODES = 3; //0=volume, 1=bass comp., 2=treble comp.
//  IR receiver settings
const unsigned int IR_MIN_GAP = 200; //Time (ms) required between IR button presses to count as two different presses (MIN ~150)


// Global Varables
//  console state
bool busy = false; //If unit is busy (and thus not ready for any inputs)
//  speaker state (THESE ARE DEFAULT SETTINGS)
int curVol = 20; //Current volume setting
int curBass = 14; //Current bass compensation setting
int curTreb = 6; //Current treble compensation setting
bool subAwake = false; //If the bass module is online
bool isMute = false; //If the bass module is muted
byte curSource = 0; //Index of the current source (0=main, 1=alternate)
//  idle cmd sender
unsigned long lastSentIdle = 0; //last millis() when an Idle command was sent to Bass module
//  7seg loading anim
bool loadingRunning = false; //if the loading animation should be running
byte loadingStage = 0; //current stage of the loading anim
unsigned long loadingChange = 0; //last millis() that the loading anim was updated 
//  hardware button handling
bool lastButt = false; //Last known button state (true= any pressed)
bool buttRecognized = false; //If current button press has been recognized
//  button-holding
unsigned long buttInit = 0; //Time of the last initial button press
unsigned long lastButtonRepeat = 0; //millis() of the last time a "repeat" button press occured (from holding down button)
//  7seg char display
bool displayRunning = false; //If the display is currently showing some value
bool displayInfinite = false; //If the display should cycle infinitely until interrupted.
byte displayNumChars = 0; //How long the current display message is
char displayBuffer[24]; //Buffer of characters for the display system (only displays first displayNumChars chars)
byte displayNextInd = 0; //Index of currently displayed character
bool displayOn = false; //If the display is currently illuminated (showing ANYTHING)
unsigned long displayLastChange = 0; //millis() when the display's state was last changes
//  green indicator LED
bool indFlashing = false; //If the green indicator LED is currently flashing
unsigned long indFlashStart = 0; //The millis() when the indicator flash started
//  Value modes
byte curMode = 0; //0=volume, 1=bass comp., 2=treble comp.
//  IR button parsing
byte lastIRData = 0x00; //The most recently received IR command byte
unsigned long lastIRParse = 0; //The millis() of when the last IR command was processed

// Global Objects
SoftwareSerialWithHalfDuplex subSerial(SERIAL_PIN, SERIAL_PIN, false, false); //Software serial for bass module
volatile struct TinyIRReceiverCallbackDataStruct sCallbackData; //IR data callback
CRGBW leds[1];
CRGB *ledsRGB = (CRGB *) &leds[0];


//Returns the least-significant digit of the given number. (unused)
//Accepts 109 to -109
byte getLeastSigDig(int val) {
  unsigned int v = abs(val);
  for (int i=100; i>0; i-=10) {
    if (v >= i) {return v-i;}
  }//for
  return v;
}//getLeastSigDig(int)



//Updates the loading animation (if its running)
void handleLoadingAnimation() {
  if (loadingRunning) {
    if (millis()-loadingChange > LOADING_ANIM_DELAY) {
      loadingChange = millis();
      loadingStage++;
      if (loadingStage==6) {loadingStage=0;}
      switch(loadingStage) {
        case 0:
          setSegments(1,0,0,0,0,0,0);
          break;
        case 1:
          setSegments(0,1,0,0,0,0,0);
          break;
        case 2:
          setSegments(0,0,1,0,0,0,0);
          break;
        case 3:
          setSegments(0,0,0,1,0,0,0);
          break;
        case 4:
          setSegments(0,0,0,0,1,0,0);
          break;
        case 5:
          setSegments(0,0,0,0,0,1,0);
          break;
      }//switch
    }//if (should update)
  }//if (running)
}//handleLoadingAnimation()

//Starts/stops the loading animation
void setLoadingAnimation(bool state) {
  if (loadingRunning == state) {return;}
  loadingRunning = state;
  if (state) {
    loadingStage=0;
    displayStopText();
  } else {
    clearDisplay();
  }//if
}//setLoadingAnimation(bool)

void setRGB(CRGBW col) {
  leds[0] = col;
  FastLED.show();
}//setRGB(CRGBW)

//Updates the 7 segments of the 7seg display
void setSegments(bool a, bool b, bool c, bool d, bool e, bool f, bool g) {
  digitalWrite(DISPLAY_PINS[0], !a);
  digitalWrite(DISPLAY_PINS[1], !b);
  digitalWrite(DISPLAY_PINS[2], !c);
  digitalWrite(DISPLAY_PINS[3], !d);
  digitalWrite(DISPLAY_PINS[4], !e);
  digitalWrite(DISPLAY_PINS[5], !f);
  digitalWrite(DISPLAY_PINS[6], !g);
}//setSegments()

//Displays the given character on the 7seg display.
//Accepts numbers, symbols, & UPPERCASE letters.
void showCharacter(char c) {
  switch(c) {
    case '0':
      setSegments(1,1,1,1,1,1,0);
      break;
    case '1':
    case 'I':
      setSegments(0,1,1,0,0,0,0);
      break;
    case '2':
    case 'Z':
      setSegments(1,1,0,1,1,0,1);
      break;
    case '3':
      setSegments(1,1,1,1,0,0,1);
      break;
    case '4':
      setSegments(0,1,1,0,0,1,1);
      break;
    case '5':
    case 'S':
      setSegments(1,0,1,1,0,1,1);
      break;
    case '6':
      setSegments(1,0,1,1,1,1,1);
      break;
    case '7':
      setSegments(1,1,1,0,0,0,0);
      break;
    case '8':
      setSegments(1,1,1,1,1,1,1);
      break;
    case '9':
      setSegments(1,1,1,1,0,1,1);
      break;
    case '-':
      setSegments(0,0,0,0,0,0,1);
      break;
    case 'A':
      setSegments(1,1,1,0,1,1,1);
      break;
    case 'B':
      setSegments(0,0,1,1,1,1,1);
      break;
    case 'C':
      setSegments(1,0,0,1,1,1,0);
      break;
    case 'D':
      setSegments(0,1,1,1,1,0,1);
      break;
    case 'E':
      setSegments(1,0,0,1,1,1,1);
      break;
    case 'F':
      setSegments(1,0,0,0,1,1,1);
      break;
    case 'G':
      setSegments(1,0,1,1,1,1,0);
      break;
    case 'H':
      setSegments(0,1,1,0,1,1,1);
      break;
    case 'J':
      setSegments(0,1,1,1,1,0,0);
      break;
    case 'K':
      setSegments(1,0,1,0,1,1,1);
      break;
    case 'L':
      setSegments(0,0,0,1,1,1,0);
      break;
    case 'M':
      setSegments(1,0,1,0,1,0,0);
      break;
    case 'N':
      setSegments(0,0,1,0,1,0,1);
      break;
    case 'O':
      setSegments(0,0,1,1,1,0,1);
      break;
    case 'P':
      setSegments(1,1,0,0,1,1,1);
      break;
    case 'Q':
      setSegments(1,1,1,0,0,1,1);
      break;
    case 'R':
      setSegments(0,0,0,0,1,0,1);
      break;
    case 'T':
      setSegments(0,0,0,1,1,1,1);
      break;
    case 'U':
      setSegments(0,1,1,1,1,1,0);
      break;
    case 'V':
      setSegments(0,0,1,1,1,0,0);
      break;
    case 'W':
      setSegments(0,1,0,1,0,1,0);
      break;
    case 'X':
      setSegments(0,0,1,0,0,1,1);
      break;
    case 'Y':
      setSegments(0,1,1,1,0,1,1);
      break;
    default:
      setSegments(0,0,0,0,0,0,0);
      break;
  }//switch
}//showCharacter

//Turns the 7seg display off
void clearDisplay() {
  setSegments(0,0,0,0,0,0,0);
}//displayOff()

//Handles the green indicator flash animation (if enabled).
//Should be run in loop()
void handleIndicatorFlash() {
  if (indFlashing) {
    if (millis()-indFlashStart > IND_FLASH_TIME) {
      indFlashing=false;
      analogWrite(IND_PIN, 0);
    }//if
  }//if(flashing)
}//handleIndicatorFlash()

//Flashes the green indicator
void flashIndicator() {
  indFlashStart=millis();
  indFlashing=true;
  analogWrite(IND_PIN, IND_BRIGHTNESS);
}//flashIndicator()


//Set if the unit is "busy" or not
//Unit ignores user input while busy.
void setBusy(bool state) {
  if (state == busy) {return;}
  busy=state;
  setLoadingAnimation(state);
}//setBusy


//Flashes the provided text on the display once.
// !!! MAX 24 CHARS !!!
void displayText(char txt[], byte len) {
  if (busy) {return;}
  for (int i=0; i<len; i++) {
    displayBuffer[i] = txt[i];
  }//for
  displayNumChars = len;
  displayRunning=true;
  displayInfinite=false;
  displayNextInd = 0;
}//setDisplayText()

//Repeatedly displays the provided text on the display. Call displayStopText() to stop.
void displayHoldText(char txt[], byte len) {
  displayText(txt, len);
  displayInfinite=true;
}//displayHoldText(char[], byte)

//Converts a single digit (0-9) to its corresponding ASCII character
char numToChar(byte val) {
  return val+48;
}//numToChar()

//Flashes the provided number on the display once.
void displayText(int val) {
  if (busy) {return;}
  //convert number to chars & find length
  unsigned int value = abs(val);
  unsigned long divv = 1;
  unsigned int digitCount = 1;
  //  count number of digits
  while (divv <= value/10) {
    digitCount++;
    divv *= 10;
  }//while
  displayNumChars = digitCount;
  //  add negative to buffer
  byte pos = 0;
  if (val<0) {
    displayBuffer[0] = '-';
    pos++;
    displayNumChars++;
  }//if
  //  isolate each digit
  while ( digitCount > 0) {
    //save cur digit
    displayBuffer[pos] = numToChar(value/divv);
    pos++;
    //move to next digit
    value %= divv;
    divv /= 10;
    digitCount--;
  }//while
  //reset stuff
  displayRunning=true;
  displayInfinite=false;
  displayNextInd = 0;
}//displayText(int)

//Repeatedly displays the provided number on the display. Call displayStopText() to stop.
void displayHoldText(int val) {
  displayText(val);
  displayInfinite=true;
}//displayHoldText(int)


//Stops any ongoing text on the display
void displayStopText() {
  displayRunning=false;
  clearDisplay();
}//displayStopText()

//If enabled, updates/refreshes the digit display. Should be run in loop().
void handleDisplayUpdate() {
  if (displayRunning) {
    if (displayOn) {
      //waiting to turn digit back off
      if (millis() - displayLastChange > DISPLAY_FLASH_TIME) {
        clearDisplay();
        displayOn = false;
        displayLastChange = millis();
      }//if
    } else if (displayNextInd == displayNumChars) {
      //In reset mode (wait for long period before reset, or just terminate)
      if (millis() - displayLastChange > DISPLAY_RESET_TIME) {
        displayNextInd = 0;
        if (!displayInfinite) {
          displayRunning = false;
        }//if
      }//if
    } else {
      //waiting to display new digit
      if (millis() - displayLastChange > DISPLAY_GAP_TIME) {
        showCharacter(displayBuffer[displayNextInd]);
        displayNextInd++;
        displayOn = true;
        displayLastChange = millis();
      }//if
    }//if
  }//if(enabled)
}//handleDisplayUpdate()

//Checks hardware button states
//Lazy design; can only handle ONE BUTTON AT A TIME
//  Button priority (decreasing): Power, Up, Down
void handleButtons() {
  if (busy) {return;} //divert if busy
  bool pwrButt = !digitalRead(PWR_BUT_PIN);
  bool upButt = !digitalRead(UP_BUT_PIN);
  bool downButt = !digitalRead(DOWN_BUT_PIN);
  if (pwrButt || upButt || downButt) {
    if (!lastButt) {
      lastButt=true;
      buttInit=millis();
      lastButtonRepeat=millis();
    } else if (millis()-buttInit > BUTT_DEBOUNCE) {
      if (!buttRecognized) {
        buttRecognized=true;
        if (pwrButt) {
          onPowerPress();
        } else if (upButt) {
          onUpPress();
        } else {
          onDownPress();
        }//if(which button)
      } else {
        if (millis()-buttInit > BUTT_HOLD_TIME) {
          if (millis()-lastButtonRepeat > BUTT_REPEAT_INT) {
            if (upButt) {
              onUpPress();
            } else if (downButt) {
              onDownPress();
            }//if(which button)
            lastButtonRepeat = millis();
          }//if(time to repeat press)
        }//if(held long enough)
      }//if (butt action not recognized)
    }//if (debounce over
  } else {
    lastButt=false;
    buttRecognized=false;
  }//if (any pressed)
}//handleButtons()



//Called when the power button (hardware or remote) is pressed
void onPowerPress() {
  Serial.println(F("K:PWR"));
  flashIndicator();
  if (subAwake) {
    powerDownSequence();
  } else {
    powerUpSequence();
  }//if
}//onPowerPress()

//Called when the UP button (hardware or remote) is pressed
void onUpPress() {
  Serial.println(F("K:UP"));
  flashIndicator();
  switch(curMode) {
    case 0:
      raiseVolume();
      break;
    case 1:
      raiseBassComp();
      break;
    case 2:
      raiseTrebleComp();
      break;
  }//switch
}//onUpPress()

//Called when the DOWN button (hardware or remote) is pressed
void onDownPress() {
  Serial.println(F("K:DOWN"));
  flashIndicator();
  switch(curMode) {
    case 0:
      lowerVolume();
      break;
    case 1:
      lowerBassComp();
      break;
    case 2:
      lowerTrebleComp();
      break;
  }//switch
}//onDownPress()




//Decrements the bass compensation, sends the serial command, and displays new value (if changed)
void lowerBassComp() {
  //divert if no change
  if (curBass == COMPENSATION_MIN) {return;}
  //decrement
  curBass--;
  if (curBass < COMPENSATION_MIN) {curBass = COMPENSATION_MIN;}
  //send command
  subSetBass(curBass);
  //set display
  displayHoldText(curBass);
}//lowerBassComp()

//Increments the bass compensation, sends the serial command, and displays new value (if changed)
void raiseBassComp() {
  //divert if no change
  if (curBass == COMPENSATION_MAX) {return;}
  //increment
  curBass++;
  if (curBass > COMPENSATION_MAX) {curBass = COMPENSATION_MAX;}
  //send command
  subSetBass(curBass);
  //set display
  displayHoldText(curBass);
}//raiseBassComp()

//Decrements the treble compensation, sends the serial command, and displays new value (if changed)
void lowerTrebleComp() {
  //divert if no change
  if (curTreb == COMPENSATION_MIN) {return;}
  //decrement
  curTreb--;
  if (curTreb < COMPENSATION_MIN) {curTreb = COMPENSATION_MIN;}
  //send command
  subSetTreble(curTreb);
  //set display
  displayHoldText(curTreb);
}//lowerTrebleComp()

//Increments the treble compensation, sends the serial command, and displays new value (if changed)
void raiseTrebleComp() {
  //divert if no change
  if (curTreb == COMPENSATION_MAX) {return;}
  //increment
  curTreb++;
  if (curTreb > COMPENSATION_MAX) {curTreb = COMPENSATION_MAX;}
  //send command
  subSetTreble(curTreb);
  //set display
  displayHoldText(curTreb);
}//raiseTrebleComp()

//Decrements the volume, sends the serial command, and displays new value
void lowerVolume() {
  //decrement
  curVol--;
  if (curVol < VOL_MIN) {curVol = VOL_MIN;}
  //send command
  if (subAwake && !isMute) {subSetVolume(curVol);}
  //set display
  if (isMute) {
    displayHoldText(curVol);
  } else {
    displayText(curVol);
  }//if(muted)
}//lowerVolume()

//Increments the volume, sends the serial command, and displays new value
void raiseVolume() {
  //increment
  curVol++;
  if (curVol > VOL_MAX) {curVol = VOL_MAX;}
  //send command
  if (subAwake && !isMute) {subSetVolume(curVol);}
  //set display
  if (isMute) {
    displayHoldText(curVol);
  } else {
    displayText(curVol);
  }//if(muted)
}//raiseVolume()

//Changes the current audio source
//Blocks until done
void setSource(byte ind) {
  bool alreadyMute = isMute;
  if (!isMute) {subMute();} //mute
  asyncDelay(500); //pause
  //change relay
  switch(ind) {
    case 0:
      digitalWrite(RELAY_PIN, LOW);
      break;
    case 1:
      digitalWrite(RELAY_PIN, HIGH);
      break;
  }//switch
  asyncDelay(600); //pause
  if (!alreadyMute) {subSetVolume(curVol);} //unmute
  curSource=ind; //update index
}//setSource(byte)


void powerUpSequence() {
  setBusy(true);
  //send startup commands
  subPowerOn();
  //set source
  setSource(curSource);
  //set volume & compensations
  subSetBass(curBass);
  subSetTreble(curTreb);
  subSetVolume(curVol);
  //delay for a second
  asyncDelay(200);
  subAwake = true;
  setBusy(false);
  //set mode
  asyncDelay(500);
  setMode(0);
}//powerUpSequence()

void powerDownSequence() {
  setMode(0);
  setBusy(true);
  //send manual IDLE command to make sure wake sub
  subSendIdle(false);
  //send shutdown commands
  subPowerOff();
  digitalWrite(RELAY_PIN, LOW); //send relay into lowest-power state
  subAwake = false;
  asyncDelay(2000); //delay for a decent second
  setBusy(false);
  isMute = false; //always set mute to false
  setRGB(CRGBW(0,0,0,0));
}//powerDownSequence

void muteSequence() {
  if (isMute) {return;}
  isMute = true;
  subMute();
  setMode(0);
}//muteSequence()

void unMuteSequence() {
  if (!isMute) {return;}
  isMute = false;
  subSetVolume(curVol);
  setMode(0);
}//unMuteSequence()





//Sets the current mode (dictates what the up/down buttons do
void setMode(byte mode) {
  curMode=mode;
  switch(mode) {
    case 0:
      if (isMute) {
        setRGB(MUTE_COLOUR);
        displayHoldText(curVol);
      } else {
        setRGB(VOLUME_COLOUR);
        displayText(curVol);
      }//if
      break;
    case 1:
      setRGB(BASS_COLOUR);
      displayHoldText(curBass);
      break;
    case 2:
      setRGB(TREBLE_COLOUR);
      displayHoldText(curTreb);
      break;
  }//switch
}//setMode(byte)

//Cycles to the next mode
void nextMode() {
  curMode++;
  if (curMode == NUM_MODES) {curMode=0;}
  setMode(curMode);
}//nextMode()



//Called when the remote's mute button is pressed
void onMutePress() {
  if (subAwake) {
    Serial.println(F("K:MUTE"));
    flashIndicator();
    if (isMute) {
      unMuteSequence();
    } else {
      muteSequence();
    }//if
  }//if
}//onMutePress()

//Called when the remote's system button is pressed
void onSystemPress() {
  if (subAwake) {
    Serial.println(F("K:SYSTEM"));
    flashIndicator();
    nextMode();
  }//if
}//onSystemPress()

//Called when the remote's exit button is pressed
void onExitPress() {
  if (subAwake) {
    Serial.println(F("K:EXIT"));
    flashIndicator();
    setMode(0);
  }//if
}//onExitPress()

//Called when the remote's AUX button is pressed
void onAuxPress() {
  if (subAwake) {
    Serial.println(F("K:AUX"));
    flashIndicator();
    setBusy(true);
    setSource(1);
    setBusy(false);
    setMode(0);
  }//if
}//onAuxPress()

//Called when the remote's CBL/SAT button is pressed
void onCBLSATPress() {
  if (subAwake) {
    Serial.println(F("K:CBLSAT"));
    flashIndicator();
    setBusy(true);
    setSource(0);
    setBusy(false);
    setMode(0);
  }//if
}//onCBLSATPress()





void setup() {
  //Set pinmodes
  pinMode(IND_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PWR_BUT_PIN, INPUT_PULLUP);
  pinMode(UP_BUT_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUT_PIN, INPUT_PULLUP);
  for (byte i=0; i<8; i++) {
    pinMode(DISPLAY_PINS[i], OUTPUT);
    digitalWrite(DISPLAY_PINS[i], HIGH);
  }//for

  //Init RGB
  FastLED.addLeds<WS2812B, RGB_PIN, RGB>(ledsRGB, getRGBWsize(1));
  FastLED.setBrightness(RGB_BRIGHTNESS);
  FastLED.show();
  setRGB(CRGBW(0,0,0,0));

  Serial.begin(9600);
  Serial.println(F("START " __FILE__ " from " __DATE__));

  initPCIInterruptForTinyReceiver(); //begin IR receiver
  
  subSerial.begin(4800); //begin software serial
  Serial.println("Bose replacement booted.");

  //ensure bass module shut down
  powerDownSequence();
  
}//setup()

/*
 * This is the function is called if a complete command was received
 * It runs in an ISR context with interrupts enabled, so functions like delay() etc. are working here
 * 
 * Do not run anything time-consuming in here!! Just pass the data out to a non-ISR context
 */
void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  if (busy) {return;}
  // Copy data for main loop
  sCallbackData.Address = aAddress;
  sCallbackData.Command = aCommand;
  sCallbackData.isRepeat = isRepeat;
  sCallbackData.justWritten = true;
}//handleReceivedTinyIRData()



//Run continuously EVEN WHILE USING AN ASYNC DELAY.
//Only small operations like playing animations should be run in here.
// *** DO NOT PUT ANYTHING IN HERE THAT USES asyncDelay() ***
void asyncLoop() {
  handleLoadingAnimation();
  handleDisplayUpdate();
  handleIndicatorFlash();
}//asyncLoop()

//Like delay(), but avoids blocking code in asyncLoop()
void asyncDelay(unsigned long t) {
  unsigned long strt = millis();
  while (millis()-strt < t) {
    asyncLoop();
  }//while(waiting)
}//asyncDelay






//Reads the IR callback data and
// calls button-press functions.
// Can only handle a single held-down button at a time.
void handleInfrared() {
  if (sCallbackData.justWritten) {
    sCallbackData.justWritten = false;
    //divert if data is invalid
    if (sCallbackData.Address != 0x4BBA) {return;} //note Addr bytes are reversed here
    if (sCallbackData.Command != 0x03 && sCallbackData.Command != 0x02 && 
        sCallbackData.Command != 0x4C && sCallbackData.Command != 0x01 && 
        sCallbackData.Command != 0x15 && sCallbackData.Command != 0x0F && 
        sCallbackData.Command != 0x70 && sCallbackData.Command != 0x30) {return;}
    //valid data; parse it                             
    if (millis()-lastIRParse > IR_MIN_GAP || sCallbackData.Command != lastIRData) {
      //unique data; call button function
      lastIRData = sCallbackData.Command;
      lastIRParse = millis();
      buttInit = millis();
      lastButtonRepeat=millis();
      switch(lastIRData) {
        case 0x4C: //power
          onPowerPress(); 
          break;
        case 0x01: //mute
          onMutePress();
          break;
        case 0x15: //cbl/sat
          onCBLSATPress();
          break;
        case 0x0F: //aux
          onAuxPress();
          break;
        case 0x70: //system
          onSystemPress();
          break;
        case 0x30: //exit
          onExitPress();
          break;
        case 0x03: //volUP
          onUpPress();
          break;
        case 0x02://volDOWN
          onDownPress();
          break;
      }//switch
    } else {
      //potentially repeat code
      if (sCallbackData.Command == lastIRData) {
        lastIRParse = millis(); //reset parse timer 
        if (millis()-buttInit > BUTT_HOLD_TIME) {
          if (millis()-lastButtonRepeat > BUTT_REPEAT_INT) {
            lastButtonRepeat=millis();
            switch(lastIRData) {
              case 0x03: //volUP
                onUpPress();
                break;
              case 0x02: //volDOWN
                onDownPress();
                break;
            }//switch
          }//if(repeat int reached)
        }//if(hold thresh reached
      }//if(repeat data)
    }//if (unique data)
  }//if (not read buffer)
}//handleInfrared()


// Repeatedly sends the IDLE command to the
// Bass Module at a fixed interval.
void handleIdleCommands() {
  if (millis()-lastSentIdle > IDLE_CMD_INT) {
    Serial.print("IDLE: ");
    subSendIdle(subAwake);
    lastSentIdle = millis();
  }//if
}//handleIdleCommands()


unsigned long lastMil = millis();
// Run continuously
void loop() {
  asyncLoop(); //Async functions
  handleButtons(); //Check buttons
  handleInfrared(); //Check infrared
  handleIdleCommands(); //Handle IDLE commands

  //memory monitoring
  if (millis() - lastMil > 2000) {
    lastMil = millis();
    //Serial.print(freeMemory());
    //Serial.println(F("b"));
  }//if
}//loop()
