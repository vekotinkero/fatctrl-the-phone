#include "Arduino.h"

//////////////////////////////////////////////////////
///   Defined MIDI commands and other constants    ///
/// http://www.midi.org/techspecs/midimessages.php ///
//////////////////////////////////////////////////////

#define NOTE_OFF       0x80    // 1000nnnn
#define NOTE_ON        0x90    // 1001nnnn
#define CONTROL_CHANGE 0xb0    // 1011nnnn 

const byte channel = 1;        // set Midi channel as 1
const byte velocity = 127;     // set velocity as 127

////////////////////////////////////////////////////
/// The format of the message to send via serial ///
////////////////////////////////////////////////////

typedef struct {
    uint8_t command;
    uint8_t channel;
    uint8_t data2;
    uint8_t data3;
} t_midiMsg;

t_midiMsg msg;

/////////////////
/// Functions ///
/////////////////

void noteOn(byte note) {
  msg.command = NOTE_ON;
  msg.channel = channel;
  msg.data2   = note;
  msg.data3   = velocity;
  
  Serial.write((uint8_t *)&msg, sizeof(msg));
}

void noteOff(byte note) {  
  msg.command = NOTE_OFF;
  msg.channel = channel;
  msg.data2   = note;
  msg.data3   = velocity;
  
  Serial.write((uint8_t *)&msg, sizeof(msg));
}

void controlChange(byte controlNumber, byte controlValue) {  
  msg.command = CONTROL_CHANGE;
  msg.channel = channel;
  msg.data2   = controlNumber;        //Control Number 
  msg.data3   = controlValue;         //Control Value
  
  Serial.write((uint8_t *)&msg, sizeof(msg));
}
