# MidiMood

For a detailed tutorial, visit: 

- Making Music with Arduino: https://go.musiconerd.com/making-music-with-arduino
- Curso Fazendo Música com Arduino em Português: https://go.musiconerd.com/curso-completo
- Build process video: https://youtu.be/aLhOO-UiMg4

This repository contains the code for a custom MIDI controller project called MidiMood, built using an ATmega32U4 microcontroller (or similar). The project is designed to handle potentiometers, buttons, and other controls to send MIDI messages via USB, BLE, or standard MIDI protocols.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Files Description](#files-description)
- [Setup Instructions](#setup-instructions)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [License](#license)

## Overview

MidiMood is a comprehensive MIDI controller implementation that supports various input methods (buttons, potentiometers, encoders) and output methods (USB MIDI, BLE MIDI). The controller is designed to be highly customizable, supporting multiple microcontroller platforms including ATmega32U4, ATmega328, and Teensy.

## Features

- **USB MIDI Support**: Send and receive MIDI messages over USB.
- **BLE MIDI Support**: Use Bluetooth Low Energy (BLE) for wireless MIDI communication.
- **Potentiometer and Button Handling**: Capture input from potentiometers and buttons and convert them into MIDI messages.
- **Multiplexer Support**: Extend the number of inputs using multiplexers.
- **Debugging Support**: Debugging messages can be enabled via serial communication.
- **Multi-platform**: Supports ATmega32U4, ATmega328, and Teensy microcontrollers.



## Files Description

- **_MidiMood.ino**: The main Arduino sketch that initializes the MIDI controller and runs the main loop.
- **A_POTENTIOMETERS.ino**: Contains the logic for reading potentiometer values and converting them into MIDI Control Change messages.
- **B_BUTTONS.ino**: Handles the button inputs, converting them into MIDI Note On/Off or Control Change messages.
- **FUNCTIONS.ino**: Helper functions used throughout the project, including handling MIDI messages and other utility functions.
- **LOOP.ino**: The main loop where the program checks for inputs and sends out MIDI messages.
- **MACKIE.h**: Defines constants for Mackie Control Universal (MCU) protocol, used for controlling DAWs.
- **Z_ATMEGA32U4.ino**: Microcontroller-specific setup code for ATmega32U4-based boards.
- **Z_SETUP.ino**: General setup code, initializing pins, and configuring input/output modes.

## Material

* Arduino Pro Micro: https://amzn.to/2Vcz3Nz
* Wires: https://amzn.to/2xugvPF
* Bare Copper Wire (optional) 18-24-gauge: https://amzn.to/2FVuDpe
* 26 Rotary potentiometer b10k: https://amzn.to/3ckRKUY
* 26 Knobs
* Spacers M3 35mm: https://amzn.to/2z15BkN
* M3 screws: https://amzn.to/2RHtfJw
* Multiplexer CD4067: https://amzn.to/303jJVe
* 11 Toggle switch: https://amzn.to/3hDmORR
* 1 led
* 1 led support
* 1 resistor 1k ohm

## Setup Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/midi-controller-project.git
cd midi-controller-project
```

### 2. Install Arduino IDE

Make sure you have the Arduino IDE installed on your computer. You can download it from the [official website](https://www.arduino.cc/en/software).

### 3. Open the Project

Open the `_MidiMood.ino` file in the Arduino IDE. This file serves as the entry point to the project.

### 4. Select Your Board

In the Arduino IDE, select the appropriate board based on your microcontroller:
- For ATmega32U4 boards (e.g., Arduino Leonardo), select **Arduino Leonardo**.
- For ATmega328 boards (e.g., Arduino Uno), select **Arduino Uno**.
- For Teensy boards, select the correct Teensy model.

### 5. Upload the Code

Connect your microcontroller to your computer via USB and upload the code using the **Upload** button in the Arduino IDE.

## Dependencies

- **ResponsiveAnalogRead**: Library for smoothing analog readings from potentiometers.
- **MIDI Library**: To handle MIDI communication over USB and serial.
- **BLE MIDI**: For Bluetooth MIDI communication (if using BLE).

You can install these libraries using the Arduino Library Manager.

## Usage

Once the code is uploaded, your MIDI controller will be recognized by your computer or mobile device as a MIDI device. You can start using it to send MIDI messages to your DAW or other MIDI-compatible software.

### Debugging

If you want to see debugging messages, enable the `DEBUG` flag in the code. This will allow you to monitor the MIDI messages and other details via the serial monitor in the Arduino IDE.
