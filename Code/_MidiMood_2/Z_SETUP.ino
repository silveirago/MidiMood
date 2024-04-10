void setup() {
  // Baud Rate
  // use if using with ATmega328 (uno, mega, nano...)
  // 31250 for MIDI class compliant | 115200 for Hairless MIDI
  int baudRate = 115200;

#ifdef MIDI_DIN
  baudRate = 31250;
#endif

  //////////// ATMEGA32U4 Setup ////////////
#ifdef ATMEGA32U4
#ifdef DEBUG
  while (!Serial) {
    Serial.println("waiting...");
  }
  Serial.println();
#endif

#ifdef MIDI_DIN
  Serial1.begin(31250);
  midi2.begin();

  // Midi in
  midi2.begin();
  midi2.turnThruOff();
  midi2.setHandleControlChange(myHandleControlChange);
  midi2.setHandleNoteOn(myHandleNoteOn);
  midi2.setHandleNoteOff(myHandleNoteOff);
  midi2.setHandlePitchBend(myHandlePitchBend);
#endif
#endif  // ATMEGA32U4

  //////////// ATMEGA328 Setup ////////////
#ifdef ATMEGA328
  POT_MIDI_CH++;
  BUTTON_MIDI_CH++;
  ENCODER_MIDI_CH++;

  Serial.begin(baudRate);

  // Midi in
  MIDI.begin();
  MIDI.turnThruOff();
  MIDI.setHandleControlChange(myHandleControlChange);
  MIDI.setHandleNoteOn(myHandleNoteOn);
  MIDI.setHandleNoteOff(myHandleNoteOff);
  MIDI.setHandlePitchBend(myHandlePitchBend);
#endif

  //////////// BLE MIDI Setup ////////////
#ifdef BLEMIDI
  Serial.begin(baudRate);
  Serial.println("Initializing bluetooth");
  BLEMidiServer.begin(bleMIDIDeviceName);  // the name of the device
  Serial.println("Waiting for connections...");
  // BLEMidiServer.enableDebugging();  // Uncomment if you want to see some debugging output from the library (not much for the server class...)
#endif

  //////////// TEENSY Setup ////////////
#ifdef TEENSY
#ifdef DEBUG
  while (!Serial) {
    Serial.println("waiting...");
  }
  Serial.println();
#endif  // DEBUG
#endif

#ifdef DEBUG
  Serial.begin(baudRate);
  Serial.println("Debug mode");
  Serial.println();
#endif

  //////////// Buttons Setup ////////////
#ifdef USING_BUTTONS
  // Initialize buttons with pull up resistors
  for (int i = 0; i < N_BUTTONS_ARDUINO; i++) {
    pinMode(BUTTON_ARDUINO_PIN[i], INPUT_PULLUP);
  }
#endif

  //////////// Potentiometer Setup ////////////
#ifdef USING_POTENTIOMETERS
  for (int i = 0; i < N_POTS; i++) {
    responsivePot[i] = ResponsiveAnalogRead(0, true, snapMultiplier);
    responsivePot[i].setAnalogResolution(potMax + 1);  // sets the resolution
  }
#endif

  //////////// Multiplexers Setup ////////////
#ifdef USING_MUX
  // Initialize the multiplexers
  for (int i = 0; i < N_MUX; i++) {
    mux[i].begin();
  }
   pinMode(x1, INPUT_PULLUP);
   pinMode(x2, INPUT_PULLUP);
#endif

  //////////// LED Setup ////////////
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 100);
}
