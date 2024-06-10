//
//  SlotMachine.h
//
//  Created by Jordan Doyle.
//

#define NUMBER_OF_TRIES 3
#define LOWEST_BET 2
#define STARTING_CREDIT 10

enum boolean {
    False,
    True,
};

enum face {
    Orange,
    Apple,
    Pear,
};

struct Slot {
    enum face column1;
    enum face column2;
    enum face column3;
};

const char* faceNames[] = {"ORANGE", "APPLE", "PEAR"};

/*
 * Asks the user how many credits they would like to bet and checks that the entered value is valid.
 * Input is validated using the methods 'contains_character' and 'invalid_bet' given there current credits.
 * The amount the player wants to bet is returned or -1, if they failed to enter a valid integer
 */
int placeBet(int credit);

/*
 * Takes user input from the player and returns the entered string
 */
char * getUserInput(char * input);

/*
 * Checks if the provided string contains any alphabetic characters. Returns True if an alphabetic character
 * exists in the string, False if all characters are digits
 */
enum boolean contains_character(const char *string);

/*
 * Checks if the provided integer is between 2 and the players available credit. Returns True if the provided
 * bet is invalid and False if the bet is valid, i.e. 2 < bet < credit
 */
enum boolean invalidBet(int bet, int credit);

/*
 * Generates 3 random numbers between the 0 and 2 that represent a Slot Face using the method 'getRandomFace'.
 * Returns an instance of the Slot struct containing 3 random faces which can be 'Orange', 'Apple', or 'Pear'
 */
struct Slot pullSlotMachine(void);

/*
 * Returns a random number between 0 and 2 which represents a slot face from the face enum.
 */
enum face getRandomFace(void);

/*
 * Determines how much the player has won or lost based on the amount that they have bet and the combination of
 * slot faces generated and stored in the slot structurre. Returns the players updated credit amount.
 */
int evaluatePull(struct Slot slot, int credit, int bet);

/*
 * Asks the player if they want to keep playing and validates the users input. Returns True if the player enters
 * 'n' to exit the game and False if 'y' is entered to continue betting. True is also returned if the player fails
 to enter a valid option.
 */
enum boolean exitGame(int credit);

/*
 * Checks if the character entered by the player is a valid character i.e. 'y', 'Y', 'n' or 'N'. 
 */
enum boolean invalidCharacter(char character);

/*
 * Prints a message diplayed before exiting the game. The message tells the user that the game is over and how many
 * credits they have won/lost.
 */
void printEndMessage(int endCredit); 
