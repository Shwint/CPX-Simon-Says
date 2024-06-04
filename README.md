# CPX Simon-Says Game
DESCRIPTION: The game is basically simon-says with the lights of the LED’s representing the correct response. The game works by starting with a single press of the left button which activates the game and puts it in an idle mode. After this press the right button to begin where a single Neopixel will blink red and you use the left button to match the input by pressing it a corresponding amount of times. After a correct input the pattern repeats with one more additional point to input after the original. This goes on until the user fails to correctly input the code and the device will beep a corresponding number of times to the amount of successful inputs. 
After the game registers the game being ended the buzzer will sound in corresponding intervals to how many rounds were successfully completed.

RULES: Match the pattern of Neopixels shown with user inputs that match the pattern.

INPUTS: 
Buttons - Either activated or inactive with an imput of either 0 or 1 when pressed.
The Left button controls when the round is initilized and is what the user presses to give input primarily in the game.
The Right button controls when the pattern is displayed on the Neopixels

SlideSwitch - Controls if the game is in an idle state or not, when the switch is facing left and inactive the game functions as normal. When the slideswitch is facing right it ends the current round and plays the score and deactivates the game until switched back.

OUTPUTS:
LEDS - The LED's show as the points where the user has to match to as well as representing the current input that will be compared to the pattern to test for a correct response. 

BUZZER - The buzzer represents the score of the user at the end of the current game and sounds off a corresponding amount of times compared to the amount of rounds successfully completed.
