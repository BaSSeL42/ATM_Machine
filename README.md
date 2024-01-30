# ATM Project

## Overview

This repository documents my work on an ATM (Automated Teller Machine) project, showcasing the integration of various embedded technologies to create a functional ATM system. The project utilizes SPI, UART, and I2C communication protocols for seamless interaction between different components.

## Idea Behind the Project

The idea behind this project stemmed from a desire to develop a comprehensive and functional ATM system that not only demonstrates proficiency in embedded systems but also addresses real-world challenges in secure transaction processing. By incorporating communication protocols such as SPI, UART, and I2C, along with features like EEPROM for secure card information storage, a keypad for user interaction, and an LCD display for feedback, the project aims to provide a holistic example of an embedded system in a financial transaction context.

## Features

- **Communication Protocols:**
  - **SPI (Serial Peripheral Interface):** Utilized for efficient communication between microcontroller and devices.
  This Project we used this protocol to make communication between ATM_MCU and CARD_MCU. 
  - **UART (Universal Asynchronous Receiver-Transmitter):** Employed for serial communication, facilitating data transfer between the CARD_MCU and Terminal.
  - **I2C (Inter-Integrated Circuit):** Used for communication between CARD_MCU and EEPROM for Storing card Information on it.

- **EEPROM for Card Information:**
  - Implemented EEPROM (Electrically Erasable Programmable Read-Only Memory) for secure storage of card information. This ensures persistent and reliable storage of essential data.

- **KeyPad Integration:**
  - Integrated a keypad for user input, providing a secure and convenient method for entering PINs and other information.

- **LCD Display:**
  - Utilized an LCD (Liquid Crystal Display) for presenting information to the user, including transaction details and prompts.

## Technologies Used

- **Programming Language:** C Language
- **Microcontroller:** ATMEGA32 Microcontroller
- **Communication Protocols:** SPI, UART, I2C
- **Storage:** EEPROM
- **Input:** Keypad , terminal via UART
- **Output:** LCD Display

## Project Photo

<img src="Project Pic\ATM_Project1.png" alt="ATM Project Photo" width="700"/>

## Project Structure

The project is organized into various directories, each corresponding to different aspects of the ATM system. The source code, schematics, and documentation are available for reference.

### Code

The `Code` folder contains the source code for the ATM project. You can explore the different directories and files to understand the implementation details.

```bash
atm_mcu/
|-- APP/
|   |-- main.c
|   |-- main.h
|-- Common/
|   |-- Bit_Math.h
|   |-- std_types.h
|-- HAL/
|   |-- Button/
|   |-- HLCD/
|   |-- HSPI/
|   |-- HTimer/
|   |-- ButtoKEYPAD_V2/
|-- MCAL/
|   |-- DIO/
|   |-- ExtInt/
|   |-- SPI/
|   |-- Timer
|   |-- ...
card_mcu/
|-- APP/
|   |-- main.c
|   |-- main.h
|-- Common/
|   |-- Bit_Math.h
|   |-- std_types.h
|-- HAL/
|   |-- HUART/
|   |-- HSPI/
|   |-- HTimer/
|   |-- EEPROM/
|-- MCAL/
|   |-- DIO/
|   |-- ExtInt/
|   |-- SPI/
|   |-- UART/
|   |-- Timer
|   |-- ...
README.md
```

### The ATM_MCU code -----> [Code](atm_mcu/)
### The CARD_MCU code ----> [Code](card_mcu/)

## Usage

To explore the project or contribute, follow these steps:

1. Clone the repository: `git clone https://github.com/BaSSeL42/ATM_Machine.git`
2. Navigate to the project directory: `cd ATM_Project`
3. Browse the source code, schematics, and documentation folders.

Feel free to provide feedback, report issues, or contribute to further development.

---
