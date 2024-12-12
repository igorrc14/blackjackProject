#include <iostream>
using namespace std;

struct Card {
    int value;
    string suit;
    string face;
};

void deckCreation(Card cards[52]) {
    // Hearts
    cards[0] = {2, "hearts", "2"};
    cards[1] = {3, "hearts", "3"};
    cards[2] = {4, "hearts", "4"};
    cards[3] = {5, "hearts", "5"};
    cards[4] = {6, "hearts", "6"};
    cards[5] = {7, "hearts", "7"};
    cards[6] = {8, "hearts", "8"};
    cards[7] = {9, "hearts", "9"};
    cards[8] = {10, "hearts", "10"};
    cards[9] = {10, "hearts", "Jack"};
    cards[10] = {10, "hearts", "Queen"};
    cards[11] = {10, "hearts", "King"};
    cards[12] = {1, "hearts", "Ace"};

    // Diamonds
    cards[13] = {2, "diamonds", "2"};
    cards[14] = {3, "diamonds", "3"};
    cards[15] = {4, "diamonds", "4"};
    cards[16] = {5, "diamonds", "5"};
    cards[17] = {6, "diamonds", "6"};
    cards[18] = {7, "diamonds", "7"};
    cards[19] = {8, "diamonds", "8"};
    cards[20] = {9, "diamonds", "9"};
    cards[21] = {10, "diamonds", "10"};
    cards[22] = {10, "diamonds", "Jack"};
    cards[23] = {10, "diamonds", "Queen"};
    cards[24] = {10, "diamonds", "King"};
    cards[25] = {1, "diamonds", "Ace"};

    // Spades
    cards[26] = {2, "spades", "2"};
    cards[27] = {3, "spades", "3"};
    cards[28] = {4, "spades", "4"};
    cards[29] = {5, "spades", "5"};
    cards[30] = {6, "spades", "6"};
    cards[31] = {7, "spades", "7"};
    cards[32] = {8, "spades", "8"};
    cards[33] = {9, "spades", "9"};
    cards[34] = {10, "spades", "10"};
    cards[35] = {10, "spades", "Jack"};
    cards[36] = {10, "spades", "Queen"};
    cards[37] = {10, "spades", "King"};
    cards[38] = {1, "spades", "Ace"};

    // Clubs
    cards[39] = {2, "clubs", "2"};
    cards[40] = {3, "clubs", "3"};
    cards[41] = {4, "clubs", "4"};
    cards[42] = {5, "clubs", "5"};
    cards[43] = {6, "clubs", "6"};
    cards[44] = {7, "clubs", "7"};
    cards[45] = {8, "clubs", "8"};
    cards[46] = {9, "clubs", "9"};
    cards[47] = {10, "clubs", "10"};
    cards[48] = {10, "clubs", "Jack"};
    cards[49] = {10, "clubs", "Queen"};
    cards[50] = {10, "clubs", "King"};
    cards[51] = {1, "clubs", "Ace"};
}

int main() {
    Card cards[52];
    deckCreation(cards);
    
    return 0;
}
