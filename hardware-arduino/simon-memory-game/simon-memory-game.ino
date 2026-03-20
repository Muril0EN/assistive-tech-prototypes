/**
 * @file simon-memory-game.ino
 * @author Seu Nome
 * @brief A robust implementation of the Simon Memory Game for Arduino.
 * @version 1.0
 * @date 2024 (Update to your date)
 * * LICENSE: MIT
 */

/* -------------------------------
   HARDWARE CONFIGURATION
--------------------------------*/

// Using uint8_t to optimize memory usage (8-bit vs 16-bit int)
const uint8_t LED_PINS[] = {3, 4, 5};
const uint8_t BUTTON_PINS[] = {8, 9, 10};

#define NUM_ELEMENTS 3
#define MAX_SEQUENCE 10

// Timing Constants (ms)
const unsigned int T_STAY_ON    = 800;
const unsigned int T_GAP        = 200;
const unsigned int T_DEBOUNCE   = 50;  // Standard debounce time

/* -------------------------------
   GAME STATE VARIABLES
--------------------------------*/

uint8_t gameSequence[MAX_SEQUENCE];
uint8_t currentRound = 0;

/* -------------------------------
   CORE FUNCTIONS
--------------------------------*/

void setup() {
    Serial.begin(9600);
    
    // Initialize Hardware
    for (uint8_t i = 0; i < NUM_ELEMENTS; i++) {
        pinMode(LED_PINS[i], OUTPUT);
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }

    // Seed entropy using floating analog input
    randomSeed(analogRead(0));

    Serial.println(F("System Initialized. Starting Jenius Game..."));
    
    startAnimation();
    generateFullSequence();
}

void loop() {
    currentRound++;

    // Win Condition
    if (currentRound > MAX_SEQUENCE) {
        triggerVictory();
        while (true); 
    }

    Serial.print(F("Current Level: "));
    Serial.println(currentRound);

    displaySequence();

    // Check Player Performance
    if (!processPlayerInput()) {
        triggerGameOver();
        while (true);
    }

    delay(1000); // Inter-round pause
}

/* -------------------------------
   LOGIC IMPLEMENTATION
--------------------------------*/

/**
 * Pre-generates the entire sequence to ensure deterministic 
 * memory allocation during the game.
 */
void generateFullSequence() {
    for (uint8_t i = 0; i < MAX_SEQUENCE; i++) {
        gameSequence[i] = random(0, NUM_ELEMENTS);
    }
}

/**
 * Plays the sequence up to the current round level.
 */
void displaySequence() {
    for (uint8_t i = 0; i < currentRound; i++) {
        uint8_t colorIdx = gameSequence[i];
        executeBlink(colorIdx, T_STAY_ON);
        delay(T_GAP);
    }
}

/**
 * Handles blocking input and basic debounce logic.
 * @return The index of the pressed button.
 */
int captureButtonPress() {
    while (true) {
        for (uint8_t i = 0; i < NUM_ELEMENTS; i++) {
            if (digitalRead(BUTTON_PINS[i]) == LOW) {
                delay(T_DEBOUNCE); // Simple software debounce
                executeBlink(i, 300); // Visual feedback for the press
                return i;
            }
        }
    }
}

/**
 * Validates player sequence against the stored game sequence.
 */
bool processPlayerInput() {
    for (uint8_t i = 0; i < currentRound; i++) {
        int userSelection = captureButtonPress();
        
        if (userSelection != gameSequence[i]) {
            return false;
        }
    }
    return true;
}

/* -------------------------------
   VISUAL FEEDBACK (UI)
--------------------------------*/

void executeBlink(uint8_t index, unsigned int duration) {
    digitalWrite(LED_PINS[index], HIGH);
    delay(duration);
    digitalWrite(LED_PINS[index], LOW);
}

void startAnimation() {
    for (uint8_t i = 0; i < 2; i++) {
        for (uint8_t j = 0; j < NUM_ELEMENTS; j++) digitalWrite(LED_PINS[j], HIGH);
        delay(200);
        for (uint8_t j = 0; j < NUM_ELEMENTS; j++) digitalWrite(LED_PINS[j], LOW);
        delay(200);
    }
}

void triggerVictory() {
    Serial.println(F("Status: Victory!"));
    // Rapid cycling for victory
    for (uint8_t i = 0; i < 20; i++) {
        digitalWrite(LED_PINS[i % NUM_ELEMENTS], HIGH);
        delay(50);
        digitalWrite(LED_PINS[i % NUM_ELEMENTS], LOW);
    }
}

void triggerGameOver() {
    Serial.println(F("Status: Game Over."));
    // Red-only blink (assuming LED 0 is Red)
    for (uint8_t i = 0; i < 5; i++) {
        digitalWrite(LED_PINS[0], HIGH);
        delay(100);
        digitalWrite(LED_PINS[0], LOW);
        delay(100);
    }
}
