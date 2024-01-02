#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct card_s {
    char suit; // 1 = Heart, 2 = Diamond, 3 = Club, 4 = Spade
    int face;
    struct card_s* next;
} card;

// converts suit into string
char* convert_suit(char cmp) {
    char* suit;
    suit = (char*)malloc((10 * sizeof(char)) + 1);
    if (suit != 0) {
        switch (cmp) {
        case '1':
            strcpy(suit, "Heart");
            break;

        case '2':
            strcpy(suit, "Diamond");
            break;

        case '3':
            strcpy(suit, "Club");
            break;

        case '4':
            strcpy(suit, "Spade");
            break;

        default:
            strcpy(suit, "ERROR");
            break;
        }
    }
    return suit;
}


// j is equal to suit and i is equal to the deck
void deck_create(card* headpointer) { // creates a deck of cards usings loops
    // (0-4)suits(j)and each has ace -king
    card* temp = headpointer;

    for (int j = 0; j < 4; j++) {
        for (int i = 1; i <= 10; i++) {
            if (j == 0) {   // if statement for the deck heart
                if (i == 1) { // ace for heart
                    temp->face = 1;
                    temp->suit = '1'; // heart is 1
                }
                else {
                    temp->face = i; // store face from 2-10
                    temp->suit = '1';
                }
            }
            else if (j == 1) { // deck for diamond
                if (i == 1) {      // ace for diamond
                    temp->face = 1;
                    temp->suit = '2'; // diamond
                }

                else {
                    temp->face = i;
                    temp->suit = '2';
                }
            }
            else if (j == 2) { // deck of clubs
                if (i == 1) {      // ace for club
                    temp->face = 1;
                    temp->suit = '3'; // club
                }

                else {
                    temp->face = i;
                    temp->suit = '3';
                }
            }
            else if (j == 3) { // deck of spades
                if (i == 1) {      // ace for spades
                    temp->face = 1;
                    temp->suit = '4'; // spade
                }

                else {
                    temp->face = i; // store face from 2-10
                    temp->suit = '4';
                }
            }
            temp->next = (card*)malloc(sizeof(card));
            temp = temp->next;
        }

    } // end of loop
  //  temp->next = (card *)malloc(sizeof(card));
    temp->face = 11; // for the queen
    temp->suit = '1';
    temp->next = NULL;
}

// prints current cards in list
void print_cards(card* pt, char enter[50]) {
    // int count = 0;
    printf("\n%s: \n", enter);
    if (pt == NULL) {
        printf("Empty\n");

    }

    while (pt != NULL) {
        if (pt->face == 11) {
            printf("\tQueen %s\n", convert_suit(pt->suit));
        }
        else if (pt->face == 1) {
            printf("\tAce %s\n", convert_suit(pt->suit));
        }
        else {
            printf("\t%d %s\n", pt->face, convert_suit(pt->suit));
        }
        pt = pt->next;
        if ((pt == NULL) /* || (pt->face < 1)*/) {
            break;
        }
        /*count++;
        if (count == 10) {
            printf("\n");
            count = 0;
        }*/
    }

}

//shuffle/swaps cards
void shuffle(card* headpointer, int numcards) { // shuffles cards
    srand((int)time(0));
    int k;
    card* ptr1;
    card* ptr2;
    char temp1, temp2;

    for (int i = 0; i < 1000; i++) {
        ptr1 = headpointer;
        for (int j = 0; j < (numcards - 1); j++) {
            ptr2 = headpointer;
            k = rand() % numcards;
            for (int m = 0; m < k; m++) {
                ptr2 = ptr2->next;
            }
            temp1 = ptr1->face;
            temp2 = ptr1->suit;

            ptr1->face = ptr2->face;
            ptr1->suit = ptr2->suit;

            ptr2->face = temp1;
            ptr2->suit = temp2;

            ptr1 = ptr1->next;
        }
    }
}

//designates cards unto desired decks
void deal_card(card* headpointer, card* usrhand, card* comphand) {
    //41 cards in the deck
    card* temp1 = usrhand;
    card* temp2 = comphand;
    card* trackptr = headpointer;

    for (int i = 1; i <= 41; i++) {
        if (i % 2 == 0) {    //ck if even
            temp1->face = trackptr->face;
            temp1->suit = trackptr->suit;


            if (trackptr->next->next == NULL) {
                temp1->next = NULL;
            }
            else {
                temp1->next = (card*)malloc(sizeof(card));
                temp1 = temp1->next;
            }
        }
        else {
            temp2->face = trackptr->face;
            temp2->suit = trackptr->suit;

            if (trackptr->next == NULL) {
                temp2->next = NULL;
            }
            else {
                temp2->next = (card*)malloc(sizeof(card));
                temp2 = temp2->next;
            }

        }
        trackptr = trackptr->next;
        if (trackptr == NULL) {
            break;
        }
    }
    temp1 = NULL;
    temp2 = NULL;
    //free(temp1);
    //free(temp2);

}

int count_cards(card* deck) {
    card* temp = deck;
    int count = 0;

    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

// checks for matching cards & removes them
card* check_match(card* headpointer) {
    int flag = 0;
    card* ckpt = headpointer, * target = headpointer->next; // initializes pointers
    card* prevt = headpointer, * prevck = headpointer, * temp = NULL;

    //checks if deck is only 1 card
    if (count_cards(headpointer) == 1) {
        return headpointer;
    }

    while (ckpt != NULL) {     // if target same as ckpt then removes them

        while (target != NULL) { // first loop checks each card, second loop checks
            // if that card has match
            if (ckpt->face == target->face) {
                prevck = headpointer;
                prevt = headpointer;
                //------Deals with Deleting Headpointer------//
                if (ckpt == headpointer) {
                    if (ckpt->next == target) { // checks if match is next to headp
                        if (ckpt->face == 11) {
                            printf("Removed Queen of %s and Queen of %s\n", convert_suit((ckpt->suit)), convert_suit((target->suit)));
                        }
                        else {
                            printf("Removed %d of %s and %d of %s\n", ckpt->face, convert_suit((ckpt->suit)), target->face, convert_suit((target->suit)));
                        }

                        temp = target->next;
                        free(headpointer);
                        headpointer = temp;
                        free(target);
                        flag = 1;

                    }
                    else { // if match is NOT next to headp
                        if (ckpt->face == 11) {
                            printf("Removed Queen of %s and Queen of %s\n", convert_suit((ckpt->suit)), convert_suit((target->suit)));
                        }
                        else {
                            printf("Removed %d of %s and %d of %s\n", ckpt->face, convert_suit((ckpt->suit)), target->face, convert_suit((target->suit)));
                        }
                        temp = headpointer->next;
                        free(headpointer);
                        headpointer = temp;
                        // sets prevt to be previous to target
                        prevt = headpointer;
                        while (prevt->next != target) {
                            prevt = prevt->next;
                        }
                        prevt->next = target->next;
                        free(target);
                        flag = 1;
                    }
                    break;
                    //count = 0;
                }

                //------Deletes Matches After Header------//
                printf("Removed %d of %s and %d of %s\n", ckpt->face, convert_suit((ckpt->suit)), target->face, convert_suit((target->suit)));

                while (prevck->next != ckpt) { // finds node previous to ckpt
                    prevck = prevck->next;
                }

                if (ckpt->next ==
                    target) { // checks if deleting 2 cards next to eachother
                    if (target->next == NULL) { // checks if deleting last 2 cards
                        prevck->next = NULL;
                        free(target);
                        free(ckpt);
                        ckpt = NULL, target = NULL;
                    }
                    else {
                        prevck->next = target->next;
                        free(ckpt);
                        ckpt = prevck;
                        free(target);
                        target = ckpt->next;
                    }

                }
                else {
                    while (prevt->next != target) { // finds node previous to target
                        prevt = prevt->next;
                    }
                    if (target->next == NULL) { // checks if deleting last card
                        if (((ckpt->next)->next) ==
                            target) { // checks if matches are one away from eachother
                            prevck->next = prevt;
                            prevt->next = NULL;
                            free(ckpt);
                            free(target);
                            ckpt = NULL, target = NULL;
                        }
                        else {
                            prevt->next = NULL;
                            free(target);
                            prevck->next = ckpt->next;
                            free(ckpt);
                            ckpt = prevck;
                            target = NULL;
                        }
                    }
                    else {
                        prevck->next = ckpt->next;
                        free(ckpt);
                        ckpt = prevck;
                        prevt->next = target->next;
                        free(target);
                        target = ckpt->next;
                    }
                }
                flag = -1;
                break;
            }

            target = target->next;
        } // end of inside loop

        if (flag == 0) { // normally increments ckpt & target
            ckpt = ckpt->next;
            if (ckpt == NULL) {
                target = NULL;
            }
            else {
                target = ckpt->next;
            }
        }
        else if (flag == 1) { // If headp was moved, moves ckpt to new headp
            if (headpointer == NULL) {
                // printf("Empty Hand!\n");
                return NULL;
            }
            ckpt = headpointer;
            target = headpointer->next;
        }         // flag is -1 when done searching
        flag = 0; // resets flag for next loop
    }           // end of outside loop

    return headpointer;
}

void choose_cards(card* takedeck, card* removedeck, int play) {
    int option = 1, removecount = count_cards(removedeck);
    card* temp = takedeck, * target = removedeck, * prev = removedeck, * removetrack = removedeck->next, * removetemp = removedeck;

    if (play == 1) {
        srand((int)time(0));
        option = (rand() % removecount) + 1;
        printf("Computer chose card %d\n", option);
        if (removedeck->face == 0) {
            return;
        }
    }
    else {
        printf("Computer has %d cards\n", removecount);
        for (int i = 1; i <= removecount; i++) {
            printf(" %d ", i);
        }
        printf("Choose between (1 - %d)", removecount);
        scanf("%d", &option);

        while (option > removecount || option <= 0) {
            printf("Computer only has %d\nChoose again\n", removecount);
            scanf("%d", &option);
        }
    }

    //finds target
    for (int i = 1; i < option; i++) {
        target = target->next;
    }

    //to add target card
    while (temp->next != NULL) {
        temp = temp->next;
    }
    //creates new card for takehand
    temp->next = (card*)malloc(sizeof(card));
    temp = temp->next;
    temp->face = target->face;
    temp->suit = target->suit;
    temp->next = NULL;


    //remove target card
    if (option == 1 && removecount > 1) {
        //copies new hand onto existing one
        for (int i = 1; i < removecount; i++) {
            removetemp->suit = removetrack->suit;
            removetemp->face = removetrack->face;

            removetrack = removetrack->next;
            if (removetrack == NULL) {
                removetemp->next = NULL;
                break;
            }
            else {
                removetemp = removetemp->next;
            }
        }
    }
    else if (option == 1 && removecount == 1) {

        target->face = NULL;
        target->suit = NULL;
    }
    else {
        while (prev->next != target) {
            prev = prev->next;
        }
        if (target->next == NULL || count_cards(removedeck) == 2) {
            prev->next = NULL;
        }
        else {
            prev->next = target->next;
        }
    }


}


int main(void) {
    int turn = 0;      //1 for user's turn, 0 for computer's
    char name[50], option = 'e';
    card* headDeck = NULL;
    card* usrDeck = NULL;
    card* compDeck = NULL;

    printf("Enter name: ");
    scanf("%s", name);

    while (option != 'q' && option != 'Q') {
        headDeck = (card*)malloc(sizeof(card));
        usrDeck = (card*)malloc(sizeof(card));
        compDeck = (card*)malloc(sizeof(card));

        deck_create(headDeck);
        shuffle(headDeck, 41);
        //print_cards(headDeck, "Deck");


        //strcpy(name, "Blank");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nHello %s let's play Losing Queen\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", name);
        deal_card(headDeck, usrDeck, compDeck);

        print_cards(usrDeck, name);
        printf("\nRemoving %s's matches...\n", name);
        usrDeck = check_match(usrDeck);
        print_cards(usrDeck, name);      //remove this before submitting

        printf("\nRemoving Computer's matches...\n");
        compDeck = check_match(compDeck);
        //print_cards(compDeck, "Computer (REMOVE THIS)");
        printf("\nComputer has %d cards\n", count_cards(compDeck));

        if (count_cards(usrDeck) > count_cards(compDeck)) {
            printf("\n%s starts\n", name);
            turn = 1; //user goes
        }
        else {
            printf("Computer starts\n");
            turn = 0;  //computer goes
            //pause();
        }



        //pause();
        //----------------------------Game Starts----------------------------------------------//
        while ((count_cards(usrDeck) >= 1) && (count_cards(compDeck) >= 1)) {
            switch (turn) {
            case 1: //user goes
                printf("\n\n..........................\n");  //separates each turn
                printf("%s's Turn\n", name);
                choose_cards(usrDeck, compDeck, 0);
                if (compDeck->face == 0) {
                    break;
                }
                usrDeck = check_match(usrDeck);
                if (usrDeck == NULL || usrDeck->face == 0) {
                    printf("%s has no cards\n", name);
                    break;
                }
                else {
                    shuffle(usrDeck, count_cards(usrDeck));
                }
                turn = 0; //computer goes next
                print_cards(usrDeck, name);
                //print_cards(compDeck, "Computer");
                printf("..........................\n");  //separates each turn
                break;

            case 0: //computer goes
                printf("\n\n..........................\n");  //separates each turn
                printf("Computer's Turn\n");
                choose_cards(compDeck, usrDeck, 1);
                if (usrDeck == NULL || usrDeck->face == 0) {
                    break;
                }
                //print_cards(usrDeck, name);
                //print_cards(compDeck, "Computer");
                compDeck = check_match(compDeck);
                //print_cards(usrDeck, name);
                //print_cards(compDeck, "Computer");
                if (compDeck == NULL || compDeck->face == 0 || count_cards(compDeck) == 0) {
                    printf("Computer has no cards\n");
                    break;
                }
                else if (usrDeck == NULL || usrDeck->face == 0) {
                    break;
                }
                else {
                    printf("Computer has %d cards\n", count_cards(compDeck));
                    shuffle(compDeck, count_cards(compDeck));
                }

                //print_cards(compDeck, "Computer");

                turn = 1; //user goes next
                printf("..........................\n");  //separates each turn
                //pause();
                break;

            default:
                printf("Error");
                break;
            }
            if (usrDeck == NULL || compDeck == NULL || compDeck->face == 0 || usrDeck->face == 0) {
                break;
            }

        }

        //checks who has 0 cards and declares winner
        if (usrDeck == NULL || usrDeck->face == 0) {
            printf("%s Wins!\n", name);
        }
        else if (compDeck == NULL || compDeck->face == 0) {
            printf("Computer Wins!\n");
        }
        printf("Play again? Enter q or Q to quit\n");

        free(usrDeck);
        free(compDeck);
        free(headDeck);

        scanf(" %c", &option);
    }//end of while loop

    printf("Bye!\n");
    return 0;
}



