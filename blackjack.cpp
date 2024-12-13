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

void distributeCards(Card * card1, Card * card2, Card cards[52]) {
    srand(time(0));
    int randomNum1 = rand() % 52;
    int randomNum2 = rand() % 52;

    while (randomNum1 == randomNum2) {
        randomNum2 = rand() % 52;
    }
    *card1 = cards[randomNum1];
    *card2 = cards[randomNum2];
}

void checkInicialAces(Card * card1, Card * card2, bool * firstIsAce, bool * secondIsAce) {
    if (card1->face == "Ace") {
        *firstIsAce = true;
    }
    if (card2->face == "Ace") {
        *secondIsAce = true;
    }
}

bool checkWin(int * sum) {
    if (*sum == 21) {
        cout<<"You won!"<<endl;
        return true;
    }
    return false;
}

void calculateSum(int * sum, Card * card1, Card * card2) {
    *sum = card1->value+card2->value;
    if (*sum>21 && (card1->face == "Ace" || card2->face == "Ace")) {
        *sum -= 10;
    }
    cout<<"TOTAL: "<<*sum<<endl;
}

void printCard (Card card) {
    if (card.face == "Ace") {
        cout<<card.face<<" of "<<card.suit<<" | Value: 1 or 11"<<endl;
        return;
    }
    cout<<card.face<<" of "<<card.suit<<" | Value: "<<card.value<<endl;
}

int main() {
    bool firstIsAce = false;
    bool secondIsAce = false;
    int sum = 0, choice = 0;
    Card card1, card2, cards[52];
    deckCreation(cards);
    // Blackjack Game: Round 1
    distributeCards(&card1,&card2,cards);

    checkInicialAces(&card1,&card2,&firstIsAce,&secondIsAce);

    printCard(card1);
    printCard(card2);

    calculateSum(&sum, &card1, &card2);
    if (checkWin(&sum)) {
        return 0;
    }
    // Blackjack Game: Round 2


    return 0;
}
