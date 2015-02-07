/////////////////////////////////
/////// VADEN PUHELIN 1.0 ///////
/////////////////////////////////
/// - 12 buttons from C to B ////
/// - 2 octave buttons       ////
/// - a potentiometer        ////
/////////////////////////////////

/*
Original Uno firmware flipped with Arduino-usbmidi-0.1.hex
http://hunt.net.nz/users/darran/
*/

#include <Keypad.h>
#include "midi_commands.h"

/////////////////
/// Constants ///
/////////////////

const byte ROWS = 4;           //four rows
const byte COLS = 4;           //three columns

///////////////////////////
/// The Keypad and Pins ///
///////////////////////////

/* This keypad holds values from 0-12 in ASCII characters, starting from the bottom
   conversion from char to int is done by subtracting '0' (48) */
   
char keys[ROWS][COLS] = {      // keypad in ASCII characters, http://www.asciitable.com/
  { '9', ':', ';', ' ' },      // 9,10,11
  { '6', '7', '8', '+'},       // 6,7,8
  { '3', '4', '5', ' '},       // 3,4,5
  { '0', '1', '2', '-'}        // 0,1,2
};

// Pins are connected to an old PCB inside the phone
byte rowPins[ROWS] = {9, 8, 7, 6};    // 6, 8, 10, 12
byte colPins[COLS] = {4, 3, 2, 5};    // 5, 3, 1,

byte potPin = 5;    // select the input pin for the potentiometer

/////////////////
/// Variables ///
/////////////////

int reading = 0;            // variable to store the readingue coming from the potentiometer
int previousReading = 0;    // variable of reading from the last loop
int val = 0;

byte analogThreshold = 2;   // noise threshold for analog inputs

byte Oct = 36;              // default octave C2
byte CC_val = 0;            // Control Change value

/////////////////
/// Functions ///
/////////////////

void check_Buttons();
bool potInUse();
void pot_Action();

//Construct The Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/////////////
/// SETUP ///
/////////////

void setup()
{
  //Serial.begin(9600);  //open serial port @ debug speed
  Serial.begin(115200);  //open serial port @ midi speed
  delay(200);
}

/////////////////
/// MAIN LOOP ///
/////////////////

void loop()
{
  check_Buttons();
  potInUse();
  pot_Action();
  delay(2);
}

/////////////////////
/// Check Buttons ///
/////////////////////

void check_Buttons() {
  // Fills keypad.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (keypad.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {     // Scan the whole key list.
      if (keypad.key[i].stateChanged) {      // Only find keys that have changed state.
        switch (keypad.key[i].kstate) {      // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
          case PRESSED:
            
            if (keypad.key[i].kchar == '+') {         // Check octave buttons
              //Serial.println("OCTAVE UP.");         // Add an octave, 12
              Oct += 12;
              break;
            }
            if (keypad.key[i].kchar == '-') {
              //Serial.println("OCTAVE DOWN.");       // Subtract an octave, 12
              Oct -= 12;
              break;
            }
            
            else {
              
              /*
              Serial.print("Note ");
              Serial.print(keypad.key[i].kchar - '0');
              Serial.println(" ON.");
              */
              
              noteOn(Oct + (keypad.key[i].kchar - '0'));    // release note
              break;
            }
          case RELEASED:
            if ((keypad.key[i].kchar == '+') || (keypad.key[i].kchar == '-')) break;       // Check octave buttons
            
            else {
              
              /*
              Serial.print("Note ");
              Serial.print(keypad.key[i].kchar - '0');
              Serial.println(" OFF."); 
              */
              
              noteOff(Oct + (keypad.key[i].kchar - '0'));    // release note
              break;
            }
        }
      }
    }
  }
}

///////////////////////////
/// CHECK POTENTIOMETER ///
///////////////////////////

bool potInUse() {
  reading = analogRead(potPin);                             // read the input pin
  if (abs(previousReading - reading) > analogThreshold) {   // check if the input has changed
    previousReading = reading;                              // return true if pot is used
    return true;
  }
  else return false;
}

////////////////////////////
/// POTENTIOMETER ACTION ///
////////////////////////////

void pot_Action() {
  CC_val = map(reading, 0, 1008, 0, 127);       // scale it to use it with MIDI CC
  if (potInUse()) {                             // check if the input has changed
    controlChange(48, CC_val);                  // CC48: General Purpose Controller 1 LSB
    //Serial.println(CC_val);                   // debug value
  }
}
