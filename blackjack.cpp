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

void distributeInicialCards(Card * card1, Card * card2, Card cards[52], int inGameCards[16], int * count, int userCards[11], int * countUser) {
    srand(time(0));
    int randomNum1 = rand() % 52;
    int randomNum2 = rand() % 52;

    while (randomNum1 == randomNum2) {
        randomNum2 = rand() % 52;
    }
    *card1 = cards[randomNum1];
    *card2 = cards[randomNum2];
    
    inGameCards[*count] = randomNum1;
    userCards[*countUser] = randomNum1;
    (*count)++;
    (*countUser)++;
    inGameCards[*count] = randomNum2;
    userCards[*countUser] = randomNum2;
    (*count)++;
    (*countUser)++;
}

bool checkWin(int * sum) {
    if (*sum == 21) {
        cout<<"You won!"<<endl;
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

void calculateSum(int * sum, int userCards[11], Card cards[52], int * countUser) {
    *sum = 0;
    for (int i=0;i<*countUser; i++) {
        *sum += cards[userCards[i]].value;
    }
}

void hitNewCard(int * count, int inGameCards[16], Card cards[52],int userCards[11], int * countUser) {
 // For some reason it suddently stopped working;
 // TODO;
}
void newRound(int * count,int inGameCards[16], Card cards[52],int userCards[11], int * countUser, int * sum) {
    int choice;
    cout<<endl<<"1 - Hit"<<endl;
    cout<<"2 - Stand"<<endl;
    cout<<"Select: ";
    cin>>choice;
    switch (choice) {
        case 1:
            hitNewCard(count, inGameCards, cards, userCards, countUser);
            calculateSum(sum, userCards,cards, count);
        break;
        case 2:
            //dealer's turn;
        break;
    }
}

int main() {
    int sum = 0, count = 0, countUser = 0, inGameCards[16], userCards[11];
    Card card1, card2, cards[52];
    deckCreation(cards);
    // Blackjack Game: Round 1
    distributeInicialCards(&card1,&card2,cards,inGameCards,&count,userCards, &countUser);

    printCard(card1);
    printCard(card2);

    calculateSum(&sum, userCards,cards, &count);
    cout<<"TOTAL: "<<sum<<endl;
    if (checkWin(&sum)) {
        return 0;
    }
    // Blackjack Game: Round 2
    newRound(&count, inGameCards, cards, userCards,&countUser, &sum);
    cout<<"TOTAL: "<<sum<<endl;
    if (checkWin(&sum)) {
        return 0;
    }
    return 0;
}
