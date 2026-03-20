# Simon Memory Game – Embedded Systems Implementation
**Field:** Embedded Systems / Human-Computer Interaction (HCI)  
**Platform:** Arduino (C/C++ Framework)
**Target Hardware:** ATmega328P based Microcontrollers

## 1. Project Overview
This project presents a robust implementation of the classic "Simon" electronic memory game. It was developed to demonstrate core principles of embedded systems design, focusing on hardware-software interfacing, state machine logic, and memory-efficient programming.

The system challenges the user to replicate a pseudo-random sequence of visual signals (LEDs). Each successful round increments the sequence length, increasing cognitive load and testing the user's short-term memory capacity.

## 2. Technical Specifications & Features
* **Memory Optimization:** The firmware utilizes `uint8_t` data types for pin and sequence management to minimize the SRAM footprint, a critical practice in resource-constrained embedded environments.
* **Input Handling & Debouncing:** Implements software-based debouncing logic within the input polling loop to ensure reliable button press detection and prevent mechanical contact chatter.
* **Entropy Generation:** Utilizes a floating analog input (`analogRead(0)`) to seed the `randomSeed()` function. This captures environmental electromagnetic noise to ensure a non-deterministic game sequence upon every system boot.
* **Visual Feedback System:** Integrated specialized routines for system initialization (`startAnimation`), victory (`triggerVictory`), and error states (`triggerGameOver`).

## 3. Hardware Architecture & Circuit Design

### 3.1 Component List
| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| Arduino Uno/Nano | 1 | Central Processing Unit (MCU) |
| LEDs (Green, Red, Blue) | 3 | Output signals for sequence display |
| Push-buttons | 3 | User input via Active-Low logic |
| Resistors (220Ω) | 3 | Current limiting for LED protection |

### 3.2 Wiring Diagram (Pinout)
The following schematic describes the physical interfacing between the MCU and the peripheral components:

```text
       +-----------------------+
       |       ARDUINO         |
       |                       |
       |   D3  [OUTPUT]  ----[ R ]---> LED (Green)  ---+
       |   D4  [OUTPUT]  ----[ R ]---> LED (Red)    ---+--- GND
       |   D5  [OUTPUT]  ----[ R ]---> LED (Blue)   ---+
       |                       |
       |   D8  [INPUT_PULLUP]  <--------- Button (G) ------ GND
       |   D9  [INPUT_PULLUP]  <--------- Button (R) ------ GND
       |   D10 [INPUT_PULLUP]  <--------- Button (B) ------ GND
       |                       |
       |   A0  [FLOATING]      (Antenna for Random Seed)
       +-----------------------+
       *Note: [R] represents a 220 Ohm resistor.
