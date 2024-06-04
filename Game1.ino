#include <Adafruit_CircuitPlayground.h>

const int numPixels = 10; // Number of pixels on the Circuit Playground
int sequence[100]; // Sequence of colors
int playerInput[100]; // Player's input
int currentRound = 0;
bool gameStarted = false;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  randomSeed(analogRead(0));
  CircuitPlayground.setBrightness(50);
}

void loop() {
  if (CircuitPlayground.leftButton()) {
    startGame();
  }

  if (gameStarted) {
    displaySequence();
    if (!getPlayerInput()) {
      endGame();
    } else {
      currentRound++;
      delay(1000); // Small delay before the next round
    }
  }
}

void startGame() {
  currentRound = 1;
  gameStarted = true;
  generateSequence();
}

void generateSequence() {
  for (int i = 0; i < 100; i++) {
    sequence[i] = random(numPixels);
  }
}

void displaySequence() {
  for (int i = 0; i < currentRound; i++) {
    CircuitPlayground.setPixelColor(sequence[i], 255, 0, 0); // Display red color for simplicity
    delay(500);
    CircuitPlayground.clearPixels();
    delay(500);
  }
}

bool getPlayerInput() {
  for (int i = 0; i < currentRound; i++) {
    playerInput[i] = getPlayerColor();
    if (playerInput[i] != sequence[i]) {
      return false;
    }
  }
  return true;
}

int getPlayerColor() {
  int color = -1;
  while (!CircuitPlayground.leftButton()) {
    if (CircuitPlayground.rightButton()) {
      color = (color + 1) % numPixels;
      CircuitPlayground.setPixelColor(color, 0, 255, 0); // Display green for selection
      delay(200);
    }
  }
  CircuitPlayground.clearPixels();
  delay(200); // Debounce delay
  return color;
}

void endGame() {
  gameStarted = false;
  // Output score
  for (int i = 0; i < currentRound; i++) {
    CircuitPlayground.playTone(1000, 200);
    delay(400);
  }
  CircuitPlayground.clearPixels();
  delay(1000); // Delay before restarting
}
