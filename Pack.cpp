// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;


// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
  int i = 0;
  next  = 0;

  for (int s = SPADES; s <= DIAMONDS; ++s) {
    Suit suit = static_cast<Suit>(s);
    for (int r = NINE; r <= ACE; ++r) {
        Rank rank = static_cast<Rank>(r);
        cards[i]= Card(rank, suit);
        i++;
    }
  }
}


// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    Card c;
    int i = 0;
    next = 0;
    int count = 0;

    while (count < 24){
        pack_input >> c;
        cards[i] = c;
        i++;
        count++;
    }
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    //assert_true(next < Pack.size());

    Card c;
    c = cards[next];
    next++;

    return c;

    //another option to code
    // next++;
    // return cards[next - 1];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.

void Pack::shuffle() {

  int numTimesShuffled = 0;
  array<Card, (PACK_SIZE / 2)> firstHalf;
  array<Card, (PACK_SIZE / 2)> secondHalf;

  int k = 0;
  int m = 0;

  while(numTimesShuffled < 7){
    for(int i = 0; i < (cards.size() / 2); i++){
      firstHalf[i] = cards[i];
    }
    int j = 0;
    for(int i = (PACK_SIZE / 2); i < cards.size(); i++){
      secondHalf[j] = cards[i];
      j++;
    }  
    for(int i = 0; i < cards.size(); i++){
      if(i % 2 == 0){
        cards[i] = secondHalf[k];
        k++;
      }
      else{
        cards[i] = firstHalf[m];
        m++;
      }
    } 
    numTimesShuffled++;
    k = 0;
    m = 0;
  }
  reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if(next >= PACK_SIZE){
        return true;
    }
    else{
        return false;
    }
}