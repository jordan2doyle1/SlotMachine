//
//  SlotMachine.c
//
//  Created by Jordan Doyle.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "SlotMachine.h"

int placeBet(int credit);
char * getUserInput(char * input);
enum boolean contains_character(const char * string);
enum boolean invalidBet(int bet, int credit);
struct Slot pullSlotMachine(void);
enum face getRandomFace(void);
int evaluatePull(struct Slot slot, int credit, int bet);
enum boolean exitGame(int credit);
enum boolean invalidCharacter(char character);
void printEndMessage(int endCredit); 

int main(int argc, char const *argv[]) {
    printf("******** Welcome to my Slot Machine ********\n");
    
    int credit = STARTING_CREDIT;
    srand((int) time(0));
    
    while(credit > LOWEST_BET) {
        printf("\nYour available credit is %d\n", credit);
        
        int bet = placeBet(credit);
        if(bet == -1) return 0;
        
        struct Slot slot = pullSlotMachine();
        credit = evaluatePull(slot, credit, bet);
        printf("Current Credit Balance = %d\n", credit);
        
        if(exitGame(credit) == True) break;
    }
    
    printEndMessage(credit);
    return 0;
}

int placeBet(int credit) {
    int numberOfFails, bet = 0;
    
    for(numberOfFails = 0; numberOfFails < NUMBER_OF_TRIES; numberOfFails++) {
        char input[7];
        printf("How much do you want to bet? ");
        getUserInput(input);
        
        if (!contains_character(input))
            bet = atoi(input);
        
        if (invalidBet(bet, credit))
            printf("Invalid Bet: Must be geater than 2 credits and less than available credit.\n");
        else
            break;
    }
    
    if (numberOfFails == NUMBER_OF_TRIES) {
        printf("Input failed 3 times, please learn the rules and try again later!\n");
        return -1;
    }
    
    return bet;
}

char * getUserInput(char * input) {
    fgets(input, 7, stdin);
    input[strlen(input) - 1] = '\0';
    return input;
}

enum boolean contains_character(const char * string) {
    while (*string) {
        if (isdigit(*string++) == 0) {
            return True;
        }
    }
    return False;
}

enum boolean invalidBet(int bet, int credit) {
    if((bet >= LOWEST_BET) && (bet <= credit)) {
        return False;
    }
    return True;
}

struct Slot pullSlotMachine(void) {
    struct Slot slot = {.column1 = getRandomFace(), .column2 = getRandomFace(), .column3 = getRandomFace()};
    
    printf("\nYour selection: | %s | %s | %s | \n", faceNames[slot.column1], faceNames[slot.column2], faceNames[slot.column3]);

    return slot;
}

enum face getRandomFace(void) {
    return rand() % 3;
}

int evaluatePull(struct Slot slot, int credit, int bet) {
    if((slot.column1 == slot.column2) && (slot.column1 == slot.column3)) {
        credit = credit + bet;
        printf("\n*** All 3 the same - You won %d credits ***\n\n", bet);
    } else if((slot.column1 == slot.column2) || (slot.column1 == slot.column3) || (slot.column2 == slot.column3)) {
        int winnings = bet / 2;
        credit = credit + winnings;
        printf("\n*** Half House - You won %d credits ***\n\n", winnings);
    } else{
        credit = credit - bet;
        printf("\n*** You lost %d credits ***\n\n", bet);
    }
    
    return credit;
}

enum boolean exitGame(int credit) {
    int numberOfFails;
    char exitCharacter;
    
    for(numberOfFails = 0; numberOfFails < NUMBER_OF_TRIES; numberOfFails++) {
        char exitString[7];
        printf("Play again? ('y/n'): ");
        fgets(exitString, 3, stdin);
        exitString[1] = '\0';
        exitCharacter = exitString[0];
        
        if(invalidCharacter(exitCharacter))
            printf("Input not recognised, plese enter a 'Y' for Yes or 'N' for No! \n");
        else {
            if(exitCharacter == 'y' || exitCharacter == 'Y') {
                if (credit < 2) {
                    printf("Sorry but you ain't got no credit - Bye\n");
                    return True;
                }
                break;
            } else if (exitCharacter == 'n' || exitCharacter == 'N') {
                printf("Bye! Hope you had fun!!\n");
                return True;
            }
        }
    }
    
    if(numberOfFails == NUMBER_OF_TRIES) {
        printf("Input failed 3 times, please read instructions carefully and try again later!\n");
        return True;
    }
    
    return False;
}

enum boolean invalidCharacter(char character) {
    if(character == 'y' || character == 'Y' || character == 'n' || character == 'N') {
        return False;
    }
    return True;
}

void printEndMessage(int endCredit) {
    if(endCredit < STARTING_CREDIT) {
        printf("******** End of Game: Total amount LOST = %d credits *******\n", (STARTING_CREDIT - endCredit));
    } else if (endCredit > STARTING_CREDIT) {
        printf("******** End of Game: total amount WON = %d credits ********\n", (endCredit - STARTING_CREDIT));
    }
}
