#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Card {
    int value;
    string suit;
    string face;
};

void deckCreation(Card cards[52]) {
    string suits[] = {"hearts", "diamonds", "spades", "clubs"};
    string faces[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards[i * 13 + j] = {values[j], suits[i], faces[j]};
        }
    }
}

void distributeInitialCards(Card * card1, Card * card2, Card cards[52], bool inGameCards[52], int userCards[11], int * countUser) {
    int randomNum1 = rand() % 52;
    int randomNum2 = rand() % 52;

    while (randomNum1 == randomNum2) {
        randomNum2 = rand() % 52;
    }
    *card1 = cards[randomNum1];
    *card2 = cards[randomNum2];

    inGameCards[randomNum1] = true;
    userCards[*countUser] = randomNum1;
    (*countUser)++;
    inGameCards[randomNum2] = true;
    userCards[*countUser] = randomNum2;
    (*countUser)++;
}

void printCard(Card card) {
    if (card.face == "Ace") {
        cout << card.face << " of " << card.suit << " | Value: 1 or 11" << endl;
        return;
    }
    cout << card.face << " of " << card.suit << " | Value: " << card.value << endl;
}

void calculateSum(int *sum, int userCards[11], Card cards[52], int *countUser, bool *busted) {
    int aceCount = 0;
    *sum = 0;

    for (int i = 0; i < *countUser; i++) {
        *sum += cards[userCards[i]].value;
        if (cards[userCards[i]].face == "Ace") aceCount++;
    }

    while (*sum > 21 && aceCount > 0) {
        *sum -= 10;
        aceCount--;
    }

    if (*sum > 21) {
        *busted = true;
    }
}

void hitNewCard(bool inGameCards[52], Card cards[52], int userCards[11], int * countUser) {
    int randomNum;
    do {
        randomNum = rand() % 52;
    } while (inGameCards[randomNum] == true);

    inGameCards[randomNum] = true;
    userCards[*countUser] = randomNum;
    (*countUser)++;

    for (int i = 0; i < *countUser; i++) {
        printCard(cards[userCards[i]]);
    }
}

void showDealerCards(int dealerCards[5], Card cards[52], int *countDealer) {
    for (int i = 0; i < *countDealer; i++) {
        printCard(cards[dealerCards[i]]);
    }
}

void dealerNewCard(bool inGameCards[52], Card cards[52], int dealerCards[5], int * countDealer) {
    int randomNum;
    do {
        randomNum = rand() % 52;
    } while (inGameCards[randomNum] == true);

    inGameCards[randomNum] = true;
    dealerCards[*countDealer] = randomNum;
    (*countDealer)++;

    showDealerCards(dealerCards, cards, countDealer);
}

double placeBet(double * balance) {
    double bet;
    do {
        cout << "Balance: " << *balance << "$" << endl;
        cout << "Place bet: ";
        cin >> bet;
        if (bet > *balance) {
            cout << "Insufficient balance! Try again!" << endl << endl;
        }
        if (bet < 1) {
            cout << "The minimum bet is 1$" << endl << endl;
        }
    } while (bet > *balance || bet < 1);
    cout << endl;
    return bet;
}

void checkWin(int playerSum, int dealerSum, double *balance, double bet, bool playerBusted, bool dealerBusted) {
    if (playerBusted) {
        cout << "Busted! You lost." << endl;
        *balance -= bet;
    } else if (dealerBusted) {
        cout << "Dealer busted! You won!" << endl;
        *balance += bet;
    } else if (dealerSum > playerSum) {
        cout << "You lost! Dealer wins." << endl;
        *balance -= bet;
    } else if (dealerSum == playerSum) {
        cout << "It's a tie!" << endl;
    } else {
        cout << "You won!" << endl;
        *balance += bet;
    }
    cout << "Balance: " << *balance << endl << endl;
}

void runDealerTurn(bool inGameCards[52], Card cards[52], int dealerCards[5], int *countDealer, int *dealerSum, bool *dealerBusted) {
    while (*dealerSum < 17) {
        cout << "Dealer: " << endl;
        dealerNewCard(inGameCards, cards, dealerCards, countDealer);
        calculateSum(dealerSum, dealerCards, cards, countDealer, dealerBusted);
        cout << "DEALER TOTAL: " << *dealerSum << endl << endl;
        if (*dealerBusted) break;
    }
}

void playHand(bool inGameCards[52], Card cards[52], int handCards[11], int *countHand, int *handSum, bool *handBusted, double *bet, double *balance) {
    int choice = 1;

    while (choice < 2) {
        if (*handSum == 21) {
            choice = 2;
            break;
        }

        cout << endl << "1 - Hit" << endl;
        cout << "2 - Stand" << endl;
        if (*countHand == 2 && *bet * 2 <= *balance) {
            cout << "3 - Double" << endl;
        }
        cout << "Select: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            hitNewCard(inGameCards, cards, handCards, countHand);
            calculateSum(handSum, handCards, cards, countHand, handBusted);
            cout << "TOTAL: " << *handSum << endl;
            cout << "=============================" << endl;
            if (*handSum == 21) choice = 2;
            }
        }
        if (choice == 3 && *countHand == 2 && *bet * 2 <= *balance) {
            *balance -= *bet;
            *bet *= 2;
            cout << "Bet doubled to " << *bet << "$" << endl;
            hitNewCard(inGameCards, cards, handCards, countHand);
            calculateSum(handSum, handCards, cards, countHand, handBusted);
            cout << "TOTAL: " << *handSum << endl;
            cout << "=============================" << endl;
            choice = 2;
        }
    }
}

int main() {
    srand(time(0));
    bool playAgain = true;
    double balance = 1000;

    while (playAgain) {
        int sum = 0, countUser = 0, userCards[11];
        int dealerSum = 0, dealerCards[5], countDealer = 0;
        double bet = placeBet(&balance);
        bool inGameCards[52], busted = false, dealerBusted = false;

        for (int i = 0; i < 52; i++) inGameCards[i] = false;

        Card card1, card2, cards[52];
        deckCreation(cards);

        distributeInitialCards(&card1, &card2, cards, inGameCards, userCards, &countUser);
        printCard(card1);
        printCard(card2);

        calculateSum(&sum, userCards, cards, &countUser, &busted);
        cout << "TOTAL: " << sum << endl;
        cout << "=============================" << endl;
        cout << "Dealer: " << endl;
        dealerNewCard(inGameCards, cards, dealerCards, &countDealer);
        calculateSum(&dealerSum, dealerCards, cards, &countDealer, &dealerBusted);
        cout << "DEALER TOTAL: " << dealerSum << endl;
        cout << "=============================" << endl;

        bool canSplit = (card1.face == card2.face) && (bet * 2 <= balance);
        bool splitPerformed = false;

        if (canSplit) {
            cout << "You have a pair! Do you want to split?" << endl;
            cout << "1 - Yes\n2 - No\nSelect: ";
            int splitChoice;
            cin >> splitChoice;

            if (splitChoice == 1) {
                splitPerformed = true;
                balance -= bet;
                int h1C[11], h2C[11], c1 = 1, c2 = 1, s1, s2;
                bool b1 = false, b2 = false;
                double bt1 = bet, bt2 = bet;

                h1C[0] = userCards[0]; h2C[0] = userCards[1];

                int r1, r2;
                do { r1 = rand() % 52; } while (inGameCards[r1]); inGameCards[r1] = true; h1C[c1++] = r1;
                do { r2 = rand() % 52; } while (inGameCards[r2]); inGameCards[r2] = true; h2C[c2++] = r2;

                calculateSum(&s1, h1C, cards, &c1, &b1);
                calculateSum(&s2, h2C, cards, &c2, &b2);

                cout << "\n=== HAND 1 ===" << endl;
                for(int i=0; i<c1; i++) printCard(cards[h1C[i]]);
                playHand(inGameCards, cards, h1C, &c1, &s1, &b1, &bt1, &balance);

                cout << "\n=== HAND 2 ===" << endl;
                for(int i=0; i<c2; i++) printCard(cards[h2C[i]]);
                playHand(inGameCards, cards, h2C, &c2, &s2, &b2, &bt2, &balance);

                if (!b1 || !b2) runDealerTurn(inGameCards, cards, dealerCards, &countDealer, &dealerSum, &dealerBusted);

                cout << "\n=== RESULTS ===" << endl;
                cout << "Hand 1: "; checkWin(s1, dealerSum, &balance, bt1, b1, dealerBusted);
                cout << "Hand 2: "; checkWin(s2, dealerSum, &balance, bt2, b2, dealerBusted);
            }
        }

        if (!splitPerformed) {
            playHand(inGameCards, cards, userCards, &countUser, &sum, &busted, &bet, &balance);
            if (!busted) runDealerTurn(inGameCards, cards, dealerCards, &countDealer, &dealerSum, &dealerBusted);
            checkWin(sum, dealerSum, &balance, bet, busted, dealerBusted);
        }

        if (balance <= 0) {
            cout << "You ran out of balance! Game over!" << endl;
            break;
        }
        cout << "Play again? (1-Yes, 2-No): ";
        int pg; cin >> pg; playAgain = (pg == 1);
        cout << endl << endl;
    }
    return 0;
}