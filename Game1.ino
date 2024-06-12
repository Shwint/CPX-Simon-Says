#include <Adafruit_CircuitPlayground.h>

const int numPixels = 10; // Number of pixels on the Circuit Playground
int sequence[100];        // Sequence of colors
int playerInput[100];     // Player's input
int currentRound = 0;     // Current round of the game
bool gameStarted = false; // Flag to indicate if the game has started or not

void setup() {
  Serial.begin(9600);                      // Initialize serial communication for debugging
  CircuitPlayground.begin();               // Initialize Circuit Playground board
  randomSeed(analogRead(0));               // Seed the random number generator
  CircuitPlayground.setBrightness(50);     // Set the brightness of the Circuit Playground LEDs
}

void loop() {
  // Check if SlideSwitch is facing right to end the game
  if (CircuitPlayground.slideSwitch()) {
    endGame(); // End the game
    // Wait until SlideSwitch is turned back to left position
    while (CircuitPlayground.slideSwitch()) {}
    return; // Exit loop until SlideSwitch is turned back
  }

  // Check if left button is pressed to start the game
  if (CircuitPlayground.leftButton()) {
    startGame(); // Start the game
  }

  // If the game has started
  if (gameStarted) {
    displaySequence(); // Display the sequence of colors
    if (!getPlayerInput()) { // Check if player's input is correct
      endGame(); // End the game if player's input is incorrect
    } else {
      currentRound++; // Increment current round
      delay(1000);    // Small delay before the next round
    }
  }
}

// Function to start the game
void startGame() {
  currentRound = 1; // Set current round to 1
  gameStarted = true; // Set gameStarted flag to true
  generateSequence(); // Generate the sequence of colors
}

// Function to generate a random sequence of colors
void generateSequence() {
  for (int i = 0; i < 100; i++) {
    sequence[i] = random(numPixels); // Assign a random color to each element of the sequence array
  }
}

// Function to display the sequence of colors
void displaySequence() {
  for (int i = 0; i < currentRound; i++) {
    CircuitPlayground.setPixelColor(sequence[i], 255, 0, 0); // Display red color for simplicity
    delay(500); // Delay to display the color
    CircuitPlayground.clearPixels(); // Clear the pixels
    delay(500); // Delay before displaying the next color
  }
}

// Function to get player's input
bool getPlayerInput() {
  for (int i = 0; i < currentRound; i++) {
    playerInput[i] = getPlayerColor(); // Get player's color input
    if (playerInput[i] != sequence[i]) { // Check if player's input matches the sequence
      return false; // Return false if input is incorrect
    }
  }
  return true; // Return true if input is correct
}

// Function to get player's color input
int getPlayerColor() {
  int color = -1; // Initialize color variable
  while (!CircuitPlayground.leftButton()) { // Wait until left button is pressed
    if (CircuitPlayground.rightButton()) { // If right button is pressed
      color = (color + 1) % numPixels; // Cycle through colors
      CircuitPlayground.setPixelColor(color, 0, 255, 0); // Display green for selection
      delay(200); // Debounce delay
    }
  }
  CircuitPlayground.clearPixels(); // Clear pixels after input
  delay(200); // Debounce delay
  return color; // Return selected color
}

// Function to end the game
void endGame() {
  gameStarted = false; // Set gameStarted flag to false
  // Output score
  for (int i = 0; i < currentRound; i++) {
    CircuitPlayground.playTone(1000, 200); // Play a tone
    delay(400); // Delay between tones
  }
  CircuitPlayground.clearPixels(); // Clear pixels
  delay(1000); // Delay before restarting
}
