// Fig. 10.16: fig10_16.c
// Representing cards with bit fields in a struct
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CARDS 52

// bitCard structure definition with bit fields
struct bitCard {
	unsigned int face : 4; // 4 bits; 0-15        
	unsigned int suit : 2; // 2 bits; 0-3         
	unsigned int color : 1; // 1 bit; 0-1          
};

typedef struct bitCard Card; // new type name for struct bitCard   

void fillDeck(Card * const wDeck); // prototype
void deal(const Card * const wDeck); // prototype

void shuffle(Card* const wDeck);
// shuffle cards
void shuffle(Card* const wDeck)
{
	// loop through wDeck randomly swapping Cards
	for (size_t i = 0; i < CARDS; ++i) {
		size_t j = rand() % CARDS;
		Card temp = wDeck[i];
		wDeck[i] = wDeck[j];
		wDeck[j] = temp;
	}
}

int main(void)
{
	Card deck[CARDS]; // create array of Cards

	fillDeck(deck);
	shuffle(deck);

	puts("Card values 0-12 correspond to Ace through King");
	puts("Suit values 0-3 correspond Hearts, Diamonds, Clubs and Spades");
	puts("Color values 0-1 correspond to red and black\n");
	deal(deck);
}

// initialize Cards
void fillDeck(Card * const wDeck)
{
	// loop through wDeck
	for (size_t i = 0; i < CARDS; ++i) {
		wDeck[i].face = i % (CARDS / 4);
		wDeck[i].suit = i / (CARDS / 4);
		wDeck[i].color = i / (CARDS / 2);
	}
}

// output cards in two-column format; cards 0-25 indexed with 
// k1 (column 1); cards 26-51 indexed with k2 (column 2)
void deal(const Card * const wDeck)
{
	// initialize array of pointers
	const char* face[] = { "Ace", "Deuce", "Three", "Four", "Five",
	   "Six", "Seven", "Eight", "Nine", "Ten",
	   "Jack", "Queen", "King" };

	// initialize array of pointers
	const char* suit[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	const char* color[] = { "Black:", "Red:"};


	printf("%-6s%-6s%-15s%-6s%-6s%s\n", "Card", "Suit", "Color",
		"Card", "Suit", "Color");

	// loop through wDeck
	for (size_t k1 = 0, k2 = k1 + 26; k1 < CARDS / 2; ++k1, ++k2) {
		printf("%-6s%-6s of %-15s",
			color[wDeck[k1].color], face[wDeck[k1].face], suit[wDeck[k1].suit]);
		printf("%-6s%-6s of %s\n",
			color[wDeck[k2].color], face[wDeck[k2].face], suit[wDeck[k2].suit]);
	}
}




/**************************************************************************
* (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
* Pearson Education, Inc. All Rights Reserved.                           *
*                                                                        *
* DISCLAIMER: The authors and publisher of this book have used their     *
* best efforts in preparing the book. These efforts include the          *
* development, research, and testing of the theories and programs        *
* to determine their effectiveness. The authors and publisher make       *
* no warranty of any kind, expressed or implied, with regard to these    *
* programs or to the documentation contained in these books. The authors *
* and publisher shall not be liable in any event for incidental or       *
* consequential damages in connection with, or arising out of, the       *
* furnishing, performance, or use of these programs.                     *
*************************************************************************/
