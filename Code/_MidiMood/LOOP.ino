void loop() {

#ifdef ATMEGA32U4

  // it will read MIDI incoming messages if using ATMEGA32U4
  MIDIread();

#ifdef MIDI_DIN
  midi2.read();
#endif

#endif

#ifdef ATMEGA328
  MIDI.read();
#endif

#ifdef TEENSY

  // usbMIDI.read() needs to be called rapidly from loop().  When
  // each MIDI messages arrives, it return true.  The message must
  // be fully processed before usbMIDI.read() is called again.
  if (usbMIDI.read()) {
    processMIDI();
  }

#endif

  buttons();
  potentiometers();
}
