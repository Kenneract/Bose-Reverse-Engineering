//Extension of BoseFirmware; contains general SmartSpeaker interface stuff.

/*
Sends the given data over the serial line and waits for the expected response.

Returns 0 if expected response was received, 1 if response timed out, and 2 if an unexpected response is received.
*/
byte rawSend(byte* data, byte dataBytes, byte* expectedResponse, byte responseBytes) {
  if (FAKE_SERIAL) {return 0;} //fake success
  //Send the data
  Serial.print(F("SEND: "));
  for (byte i=0; i<dataBytes; i++) {
    subSerial.write(data[i]);
    Serial.print(data[i], HEX);
    Serial.print(F(" "));
  }//for
  Serial.print(F("  RECV: "));
  //Wait for BassModule to process
  asyncDelay(20); //20ms
  //Process response
  byte respIndex=0;
  while (respIndex < responseBytes) {
    //Wait for serial response (timeout = 15ms)
    unsigned long startTime = millis();
    while ((!subSerial.available()) && millis()-startTime < 15) {}
    //Divert if timeout
    if (!subSerial.available()) {
      Serial.print(F("[respTimeout]"));
      return 1; //1=timeout
    }//if(timeout)
    //Process current byte
    byte rd = subSerial.read();
    Serial.print(rd, HEX);
    Serial.print(F("/"));
    Serial.print(expectedResponse[respIndex], HEX);
    Serial.print(F(" "));
    if (rd != expectedResponse[respIndex]) {
      flushSubSerial();
      Serial.print(F("[badResp]"));
      return 2; //2=incorrect response
    }//if (invalid response)
    //Check if done
    respIndex++;
    if (respIndex == responseBytes) {
      flushSubSerial();
      return 0;
    }//if (full response received)
  }//while (full response not received)
}//rawSend(byte[], byte, byte[], byte)

void flushSubSerial() {
  while(subSerial.available()) {subSerial.read();}
}//flushSubSerial()

/*
 * Sends the given data over the serial line and waits for the expected response.
 * Attempts to re-send the data if no or an invalid response is received (to a limit).
 * Returns true if successful, false otherwise.
 */
bool rdtSend(byte* data, byte dataBytes, byte* expectedResponse, byte responseBytes) {
  byte tries = 3;
  bool success = false;
  while (tries>0) {
    success = 0==rawSend(data, dataBytes, expectedResponse, responseBytes);
    Serial.println();
    if (success) {return true;}
    tries--;
    delay(5);
  }//while()
  return false;
}//rdtSend(byte*, byte, byte*, byte)

// rdtSend overload; default expected response of 0x00 (OK)
bool rdtSend(byte* data, byte dataBytes) {
  byte d[] = {0x00};
  return rdtSend(data, dataBytes, d, 1);
}//rdtSend(byte*, byte)

/*
 * Given a blank 4-byte array, and the 1st and 3rd byte of the command,
 * fills the array with the four bytes representing a standard command.
 */
void make4BCommand(byte* arr, byte a, byte b) {
  arr[0] = a;
  arr[1] = 0;
  arr[2] = b;
  arr[3] = b ^ a;
}//make4bCommand

// SmartSpeaker API
// Sets the volume to the given value (0 to 100)
bool subSetVolume(byte val) {
  //Derive values
  byte v = 100-val;
  //Generate command
  byte d[4];
  make4BCommand(d, 2, v);
  //Send command
  return rdtSend(d, 4);
}//subSetVolume(byte)

// SmartSpeaker API
// Mutes the Bass Module
bool subMute() {
  byte d[] = {0x02, 0x00, 0x78, 0x7A};
  return rdtSend(d, 4);
}//subMute

// SmartSpeaker API
// Sets the bass compensation to the given value (-14 to 14)
bool subSetBass(int val) {
  //Derive value
  byte v = 80+val;
  if (val<0) {v = 63-val;}
  //Generate command
  byte d[4];
  make4BCommand(d, 4, v);
  //Send command
  return rdtSend(d, 4);
}//subSetBass(int)

// SmartSpeaker API
// Sets the treble compensation to the given value (-14 to 14)
bool subSetTreble(int val) {
  //Derive value
  byte v = 48+val;
  if (val<0) {v = 31-val;}
  //Generate command
  byte d[4];
  make4BCommand(d, 4, v);
  //Send command
  return rdtSend(d, 4);
}//subSetTreble(int)

// SmartSpeaker API
// Sends the required commands to wake the Bass Module (mimic console in AUX mode)
// Blocks until powered on.
bool subPowerOn() {
  bool r = true;
  byte d4[4];
  make4BCommand(d4, 0x01, 0x00); //01 00 00 01
  r = rdtSend(d4, 4) && r ;
  make4BCommand(d4, 0x0B, 0x12); //0B 00 12 19
  byte respA[] = {0x00, 0x0C, 0x00, 0x30, 0x31, 0x30, 0x34, 0x30, 0x30, 0x09};
  r = rdtSend(d4, 4, respA, 10) && r;
  byte d5[] = {0x0E, 0x00, 0x00, 0x00, 0x0E}; // 0E 00 00 00 0E
  r = rdtSend(d5, 5) && r;
  make4BCommand(d4, 0x0D, 0x02); //0D 00 02 0F
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x03, 0x10); //03 00 10 13
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x03, 0x30); //03 00 30 33
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x04, 0x35); //04 00 35 31
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x04, 0x5E); //04 00 5E 5A
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x04, 0x01); //04 00 01 05
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x06, 0x00); //06 00 00 06
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x06, 0x10); //06 00 10 16
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x08, 0x06); //08 00 06 0E
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x09, 0x10); //09 00 10 19
  r = rdtSend(d4, 4) && r;
  r = subMute() && r; //02 00 78 7A
  make4BCommand(d4, 0x0B, 0xF2); //0B 00 F2 F9
  byte respB[] = {0x0, 0x0C, 0x00, 0x00, 0x0C};
  r = rdtSend(d4, 4, respB, 5) && r;
  make4BCommand(d4, 0x0F, 0x00); //0F 00 00 0F
  r = rdtSend(d4, 4) && r;
  //SKIPPING 3 COMMANDS: VOL10, VOL5, MUTE (we're already muted)
  r = rdtSend(d5, 5) && r; // 0E 00 00 00 0E
  //SKIPPING A 0D 00 02 0F & 02 00 63 61 COMMAND
  make4BCommand(d4, 0x0D, 0x02); //0D 00 02 0F
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x05, 0x05); //05 00 05 00
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x06, 0x10); //06 00 10 16
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x04, 0x01); //05 00 01 05
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x06, 0x00); //06 00 00 06
  r = rdtSend(d4, 4) && r;
  make4BCommand(d4, 0x09, 0x13); //09 00 13 1A
  r = rdtSend(d4, 4) && r;
  //VOLUME RAMP UP
  return r;
}//subPowerOn()

// SmartSpeaker API
// Sends the required commands to shut down the Bass Module
// Blocks until powered off.
bool subPowerOff() {
  //mute
  bool r = subMute();
  if (!r) {return false;}
  //pwr down
  byte d[] = {0x01, 0x00, 0x80, 0x81};
  return rdtSend(d, 4);
}//subPowerOff()

// SmartSpeaker API
// Sends the idle/keepalive command and checks response.
bool subSendIdle(bool subOn) {
  byte d[] = {0x0B, 0x00, 0x00, 0x0B};
  if (subOn) {
    byte r[] = {0x00, 0x0C, 0x00, 0x00, 0x0C};
    return rdtSend(d, 4, r, 5);
  } else {
    byte r[] = {0x00, 0x0C, 0x00, 0xF0, 0xFC};
    return rdtSend(d, 4, r, 5);
  }//if
}//subSendIdle
