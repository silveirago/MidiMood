/*
  Made by Gustavo Silveira, 2023.

  http://www.musiconerd.com
  http://www.youtube.com/musiconerd
  http://facebook.com/musiconerdmusiconerd
  http://instagram.com/musiconerd/
  http://www.gustavosilveira.net
  gustavosilveira@musiconerd.com

  If you are using for anything that's not for personal use don't forget to give credit.

  PS: Just change the value that has a comment like " //* "

*/

/////////////////////////////////////////////
// Choosing your board
// Define your board, choose:
// "ATMEGA328" if using ATmega328 - Uno, Mega, Nano...
// "ATMEGA32U4" if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
// "TEENSY" if using a Teensy board
// "BLEMIDI" if using BLE MIDI (ESP32)
// "DEBUG" if you just want to debug the code in the serial monitor

#define DEBUG 1  //* put here the uC you are using, like in the lines above followed by "1", like "ATMEGA328 1", "DEBUG 1", etc.

/////////////////////////////////////////////
// Are you using buttons?
#define USING_BUTTONS 1  //* comment if not using buttons

/////////////////////////////////////////////
// Are you using potentiometers?
#define USING_POTENTIOMETERS 1  //* comment if not using potentiometers

/////////////////////////////////////////////
// Are you using a multiplexer?
#define USING_MUX 1  //* comment if not using a multiplexer, uncomment if using it.


/////////////////////////////////////////////
// LIBRARIES
// -- Defines the MIDI library -- //



// if using with ATmega328 - Uno, Mega, Nano...
#ifdef ATMEGA328
#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE();
#endif

// if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
#ifdef ATMEGA32U4
#include <MIDIUSB.h>

#ifdef MIDI_DIN
#include <MIDI.h>  // adds the MIDI library to use the hardware serial with a MIDI cable
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midi2);
#endif  //MIDI_DIN

#endif  // ATMEGA32U4

#ifdef BLEMIDI
#include <BLEMidi.h>  // https://github.com/max22-/ESP32-BLE-MIDI
// Documentation: https://www.arduino.cc/reference/en/libraries/esp32-ble-midi/
char bleMIDIDeviceName[] = { "BLE Controller" };  // put here the name you want for your device
#endif


//////////////////////
// Add this lib if using a cd4067 multiplexer
#ifdef USING_MUX
#include <Multiplexer4067.h>  // Multiplexer CD4067 library >> https://github.com/sumotoy/Multiplexer4067
#endif


///////////////////////////////////////////
// MULTIPLEXERS
#ifdef USING_MUX

#define N_MUX 2  //* number of multiplexers
//* Define s0, s1, s2, s3, and x pins
#define s0 2
#define s1 4
#define s2 5
#define s3 6

#define x1 A0  // analog pin of the first mux
#define x2 A1  // analog pin of the first mux

// add more #define and the x number if you need

// *** IMPORTANT: if you want to add more than one mux! ***
// In the Setup tab, line 123, add another "pinMode(x2, INPUT_PULLUP);" if you want to add a second mux,
// and "pinMode(x3, INPUT_PULLUP);" for a third mux, and so on...

// Initializes the multiplexer
Multiplexer4067 mux[N_MUX] = {
  Multiplexer4067(s0, s1, s2, s3, x2),  // The SIG pin where the multiplexer is connnected
  Multiplexer4067(s0, s1, s2, s3, x1),  // The SIG pin where the multiplexer is connnected
  // ...
};
#endif

#ifdef USING_POTENTIOMETERS
// include the ResponsiveAnalogRead library
#include <ResponsiveAnalogRead.h>  // https://github.com/dxinteractive/ResponsiveAnalogRead
#endif

#ifdef USING_MACKIE
#include "MACKIE.h"
#endif

/////////////////////////////////////////////
// LED
byte ledPin = 3;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Types of MIDI messages to send - DO NOT TOUCH
byte NN = 0;  // Note number or MACKIE
byte CC = 1;  // Control change
byte T = 2;   // Toggle
byte PC = 3;  // Program Change
byte PB = 4;  // Pitch Bend

/////////////////////////////////////////////
// BUTTONS
#ifdef USING_BUTTONS

const byte N_BUTTONS = 6 + 5;                                    //*  total numbers of buttons. Number of buttons in the Arduino + number of buttons on multiplexer 1 + number of buttons on multiplexer 2... (DON'T put Octave and MIDI channel (bank) buttons here)
const byte N_BUTTONS_ARDUINO = 5;                                //* number of buttons connected straight to the Arduino
const byte BUTTON_ARDUINO_PIN[N_BUTTONS] = { 7, 8, 9, 10, 16 };  //* pins of each button connected straight to the Arduino

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifdef USING_MUX                                 // Fill if you are using mux, otherwise just leave it
const byte N_BUTTONS_PER_MUX[N_MUX] = { 0, 6 };  //* number of buttons in each mux (in order)
const byte BUTTON_MUX_PIN[N_MUX][16] = {
  //* pin of each button of each mux in order
  {},                         //* pins of the first mux
  { 10, 11, 12, 13, 14, 15 }  //* pins of the second
  // ...
};

int buttonMuxThreshold = 850;

#endif  //USING_MUX

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// What type of message do you want to send?
// Note Number - Control Change - Toggle - Program Change

// NN: Note number or MACKIE
// CC: Control change
// T: Toggle
// PC: Program Change

//* Put here the type of message you want to send, in the same order you declared the button pins
// "NN" for Note Number | "CC" for Control Change | "T" for Note Number but in toggle mode | "PC" for Program Change
byte MESSAGE_TYPE[N_BUTTONS] = { CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC };

//* Put here the number of the message you want to send, in the right order, no matter if it's a note number, CC (or MACKIE), Program Change
byte MESSAGE_VAL[N_BUTTONS] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90 };


// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifdef USING_BANKS_WITH_BUTTONS

//#define USING_MUX_BANK_BUTTON_PIN 1; // Define if you are using the bank buttons on the Mux pin. It has to be the first mux.
const byte BANK_BUTTON_PIN[2] = { 16, 10 };  //* first will decrease MIDI chennel and second will increase

#endif  //USING_BANKS_WITH_BUTTONS

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// debounce
unsigned long debounceDelay = 50;  //* the debounce time; increase if the output flickers

#endif  // USING_BUTTONS


/////////////////////////////////////////////
// POTENTIOMETERS

#ifdef USING_POTENTIOMETERS

const byte N_POTS = 16 + 10 + 0;  //* total numbers of pots (slide & rotary). Number of pots in the Arduino + number of pots on multiplexer 1 + number of pots on multiplexer 2...

const byte N_POTS_ARDUINO = 0;  //* number of pots connected straight to the Arduino
// If using the Arduino declare as "A1, A2"
// If using ESP32 only use the GPIO number as "11, 10"
const byte POT_ARDUINO_PIN[N_POTS_ARDUINO] = {};  //* pins of each pot connected straight to the Arduino (don't use "A" if you are using ESP32, only the number)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifdef USING_MUX
const int N_POTS_PER_MUX[N_MUX] = { 16, 10 };  //* number of pots in each multiplexer (in order)
const int POT_MUX_PIN[N_MUX][16] = {
  //* pins of each pot of each mux in the order you want them to be

  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },  // pins of the first mux
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }                       // pins of the second mux
  // ...
};
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define USING_CUSTOM_CC_N 1  //* comment if not using CUSTOM CC NUMBERS, uncomment if using it.
#ifdef USING_CUSTOM_CC_N

// What type of message do you want to send?
// Control Change - Pitch Bend

// CC: Control change
// PB: Pitch Bend

//* Put here the type of message you want to send, in the same order you declared the button pins
// "CC" for Control Change | "PB" for Pitch Bend
byte MESSAGE_TYPE_POT[N_POTS] = { CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC, CC };

byte POT_CC_N[N_POTS] = { 14, 15, 5, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 74, 29, 73, 71, 30, 31, 32, 33, 34, 7 };  // Add the CC NUMBER of each pot you want

#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int TIMEOUT = 300;       //* Amount of time the potentiometer will be read after it exceeds the varThreshold
const byte varThreshold = 10;  //* Threshold for the potentiometer signal variation - Increase if using ESP32
// For varThreshold I usually use "8" for normal Arduino and "30" for ESP32

// put here the min and max reading in the potCState
// in the potMin put a little bit more and in the potMax put a little bit less
// IMPORTANT:
// Regular Arduinos have 10 bit resolution: 0 - 1023
// ESP32 boards have 12 bit resolution: 0 - 4095
const int potMin = 20;
const unsigned int potMax = 940;

#endif  // USING_POTENTIOMETERS

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/////////////////////////////////////////////
// MIDI CHANNEL
byte POT_MIDI_CH = 0;  //* MIDI channel to be used
byte BUTTON_MIDI_CH = 0;
byte ENCODER_MIDI_CH = 1;

byte NOTE = 36;      //* Lowest NOTE to be used - if not using custom NOTE NUMBER
byte CC_NUMBER = 1;  //* Lowest MIDI CC to be used - if not using custom CC NUMBER
