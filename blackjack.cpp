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

bool checkWin(int * sum) {
    if (*sum == 21) {
        return true;
    }
    return false;
}

void printCard (Card card) {
    if (card.face == "Ace") {
        cout<<card.face<<" of "<<card.suit<<" | Value: 1 or 11"<<endl;
        return;
    }
    cout<<card.face<<" of "<<card.suit<<" | Value: "<<card.value<<endl;
}

void calculateSum(int * sum, int userCards[11], Card cards[52], int * countUser, bool * busted) {
    *sum = 0;
    for (int i=0;i<*countUser; i++) {
        *sum += cards[userCards[i]].value;
        if (*sum > 21 && cards[userCards[i]].face == "Ace") {
            *sum-=10;
        }
    }
    if (*sum > 21) {
        cout<<"Busted!"<<endl;
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

int main() {
    srand(time(0));
    bool inGameCards[52], busted = false;
    for (int i = 0; i<52; i++) {
        inGameCards[i] = false;
    }
    int sum = 0, countUser = 0, userCards[11], choice = 1;
    Card card1, card2, cards[52];
    deckCreation(cards);
    // Blackjack Game: Round 1;
    distributeInicialCards(&card1,&card2,cards,inGameCards,userCards, &countUser);

    printCard(card1);
    printCard(card2);

    calculateSum(&sum, userCards,cards,&countUser, &busted);
    cout<<"TOTAL: "<<sum<<endl;
    if (checkWin(&sum)) {
        cout<<"You won!"<<endl;
        return 0;
    }
    // Blackjack Game: Round 2 and over;
    while (choice < 2) {
        cout<<endl<<"1 - Hit"<<endl;
        cout<<"2 - Stand"<<endl;
        cout<<"3 - Surrender"<<endl;
        cout<<"Select: ";
        cin>>choice;
        cout<<endl;
        if (choice == 1) {
            hitNewCard(inGameCards, cards, userCards, &countUser);
            calculateSum(&sum, userCards,cards, &countUser, &busted);
            cout<<"TOTAL: "<<sum<<endl;
            if (checkWin(&sum)) {
                cout<<"You won!"<<endl;
                break;
            }

        }
        if (choice == 2) {
            //dealer's turn
        }
        if (choice == 3) {
            cout<<"You lost!";
        }
        if (choice < 1 || choice > 3) {
            cout<<endl<<"Invalid option. Try again!";
        }
        if (busted) {
            break;
        }
    }

    return 0;
}
