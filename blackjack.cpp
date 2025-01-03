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

void distributeInicialCards(Card * card1, Card * card2, Card cards[52], bool inGameCards[52], int userCards[11], int * countUser) {
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

void printCard (Card card) {
    if (card.face == "Ace") {
        cout<<card.face<<" of "<<card.suit<<" | Value: 1 or 11"<<endl;
        return;
    }
    cout<<card.face<<" of "<<card.suit<<" | Value: "<<card.value<<endl;
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
        cout << "Busted!" << endl;
        *busted = true;
    }
}

void hitNewCard (bool inGameCards[52], Card cards[52], int userCards[11], int * countUser) {
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

void dealerNewCard(bool inGameCards[52], Card cards[52], int dealerCards[5], int * countDealer ) {
    int randomNum;
    do {
        randomNum = rand() % 52;
    } while (inGameCards[randomNum] == true);

    inGameCards[randomNum] = true;

    dealerCards[*countDealer] = randomNum;
    (*countDealer)++;

    showDealerCards(dealerCards,cards,countDealer);
}

double placeBet(double * balance) {
    double bet;
    do {
        cout<<"Balance: "<<*balance<<"$"<<endl;
        cout<<"Place bet: ";
        cin>>bet;
        if (bet>*balance) {
            cout<<"Insufficient balance! Try again!"<<endl<<endl;
        }
        if (bet<1) {
            cout<<"The minimum bet is 1$"<<endl<<endl;
        }
    } while (bet>*balance || bet<1);
    cout<<endl;
    return bet;
}

void checkWin(int playerSum, int dealerSum, double *balance, double bet, bool playerBusted, bool dealerBusted) {
    if (playerBusted) {
        cout << "Busted!" << endl;
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
    cout<<"Balance: "<<*balance<<endl<<endl;
}

int main() {
    srand(time(0));
    bool playAgain = true;
    double balance = 1000;

    while (playAgain) {
        int sum = 0, countUser = 0, userCards[11], choice = 1, dealerSum = 0, dealerCards[5], countDealer = 0;
        double bet = placeBet(&balance);
        bool inGameCards[52], busted = false, dealerBusted = false;
        for (int i = 0; i < 52; i++) {
            inGameCards[i] = false;
        }
        Card card1, card2, dealerCard, cards[52];
        deckCreation(cards);

        // Blackjack Game: Round 1
        distributeInicialCards(&card1, &card2, cards, inGameCards, userCards, &countUser);
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

        // Blackjack Game: Round 2 and over
        while (choice < 2) {
            if (sum != 21) {
                cout << endl << "1 - Hit" << endl;
                cout << "2 - Stand" << endl;
                cout << "3 - Surrender" << endl;
                cout << "Select: ";
                cin >> choice;
                cout << endl;
            } else {
                choice = 2;
            }
            if (choice == 1) {
                hitNewCard(inGameCards, cards, userCards, &countUser);
                calculateSum(&sum, userCards, cards, &countUser, &busted);
                cout<<"TOTAL: "<<sum<<endl;
                cout<<"============================="<<endl;
                cout<<"Dealer: "<<endl;
                showDealerCards(dealerCards, cards, &countDealer);
                cout<<"DEALER TOTAL: " << dealerSum <<endl<<endl;
                if (sum == 21) choice = 2;
                if (busted) {
                    break;
                }
            }
            if (choice == 2) {
                while (dealerSum < 17) {
                    cout<<"Dealer: " << endl;
                    dealerNewCard(inGameCards, cards, dealerCards, &countDealer);
                    calculateSum(&dealerSum, dealerCards, cards, &countDealer, &dealerBusted);
                    cout<<"DEALER TOTAL: " << dealerSum << endl << endl;
                    if (busted) break;
                }
            }
            if (choice == 3) {
                cout<<"You lost!";
            }
            if (choice < 1 || choice > 3) {
                cout<<endl << "Invalid option. Try again!";
            }
        }
        checkWin(sum, dealerSum,&balance,bet,busted,dealerBusted);
        if (balance == 0) {
            cout<<"You ran out of balance! Game over!"<<endl;
            break;
        }
        cout<<endl << "Do you want to play again?\n1 - Yes" << endl;
        cout<<"2 - No" << endl;
        cout<<"Select: ";
        int playAgainChoice;
        cin >> playAgainChoice;
        playAgain = (playAgainChoice == 1);

        cout<<endl<<endl;
    }

    return 0;
}
