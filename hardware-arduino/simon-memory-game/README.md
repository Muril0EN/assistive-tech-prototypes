# Simon Memory Game – Embedded Systems Implementation
**Field:** Embedded Systems / Human-Computer Interaction (HCI)  
**Platform:** Arduino (C/C++ based Framework)

## 1. Project Overview
This project implements a robust version of the classic "Simon" electronic memory game. It was developed to demonstrate core principles of embedded systems design, including hardware-software interfacing, state machine logic, and memory-efficient programming.

The system challenges the user to replicate a pseudo-random sequence of visual signals (LEDs). Each successful round increments the sequence length, increasing cognitive load and testing the user's short-term memory.

## 2. Technical Specifications & Features
* **Memory Optimization:** Implementation uses `uint8_t` data types for pin and sequence management to minimize the SRAM footprint, a critical practice in resource-constrained environments.
* **Input Handling:** Features software-based debouncing logic to ensure reliable button press detection.
* **Entropy Generation:** Utilizes floating analog input (`analogRead(0)`) to seed the `randomSeed()` function, ensuring a non-deterministic game experience upon every boot.
* **Visual Feedback:** Integrated animations for system initialization, victory, and error states.

## 3. Hardware Architecture
The circuit consists of a microcontroller interfaced with a user-interaction layer:

| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| Arduino Uno/Nano | 1 | Central Processing Unit |
| LEDs (R, G, B) | 3 | Output signals for sequence display |
| Push-buttons | 3 | User input with internal `INPUT_PULLUP` resistors |
| Resistors | 3 | Current limiting (220Ω for LEDs) |

## 4. Logical Flow (State Machine)
The software operates following a synchronous flow:
1.  **Initialization:** Hardware I/O configuration and random seed generation.
2.  **Display Phase:** Iterates through the stored array and activates LEDs based on predefined timing constants.
3.  **Input Phase:** Blocks execution until user input is received, comparing it real-time with the sequence array.
4.  **Evaluation:** Determines if the system transitions to the next difficulty level or triggers the `GameOver` routine.

## 5. How to Deploy
1.  Clone this repository.
2.  Ensure the folder name `simon-memory-game` matches the `.ino` file.
3.  Open in **Arduino IDE 2.x** or **VS Code (PlatformIO)**.
4.  Compile and upload to any ATmega328P based board.

## 6. Future Improvements (Academic Outlook)
* **Interrupt-Driven Input:** Transition from polling to hardware interrupts for improved power efficiency.
* **Difficulty Scaling:** Implementing a dynamic timing algorithm ($T_{blink} = f(Round)$) to increase difficulty exponentially.
* **Data Logging:** Exporting player performance metrics via UART for behavioral analysis.

---
**Author:** [Seu Nome]  
**Objective:** Portfolio for PhD Application - UK Universities.
