// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//EFFECTS returns player's name
class SimplePlayer : public Player {
  
  private:
  string playerName;
  vector<Card> hand;

  public:

  SimplePlayer(const string &name_in) {
    playerName = name_in;
  }

  //EFFECTS returns player's name
  const std::string & get_name() const {
    return playerName;
  }
  
  void add_card(const Card &c) {
    hand.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit. If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer, int round, 
    Suit &order_up_suit) const {
      int numTrump = 0;
      if(round == 1){
        for(int i = 0; i < hand.size(); i++){            
          if(hand[i].is_face_or_ace() 
          && hand[i].is_trump(upcard.get_suit())){
            numTrump++;
          }
        }
          
        if(numTrump >= 2){
          order_up_suit = upcard.get_suit();
          return true;
        }
        else{
          return false;
        }

      }
      else if(round == 2 && is_dealer == false) {          
        for(int i = 0; i < hand.size(); i++){
          if(hand[i].is_face_or_ace() && 
          hand[i].is_trump(Suit_next(upcard.get_suit()))){
            numTrump++;                
          }
        }
        
        if(numTrump >= 1){
          order_up_suit = Suit_next(upcard.get_suit());
          return true;
        }
        else{
          return false;
        }
      } 
      else{
        order_up_suit = Suit_next(upcard.get_suit());
        return true;
      }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) {
    Card smallest = hand[0];
    add_card(upcard);
    int smallestPosition = 0;

    for(int i = 0; i < hand.size(); i++){
      if(Card_less(hand[i], smallest, upcard.get_suit())){
        smallest = hand[i];
        smallestPosition = i;
      }
    }
    hand.erase(hand.begin() + smallestPosition);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  //  not reaching the last value

  Card lead_card(Suit trump) {
    bool onlyHasTrump = true;
    Card largest = hand[0];
    int largestPosition = 0;
    int firstNonTrump = 0; 

    for(int i = 0; i < hand.size(); i++){
      if(!(hand[i].is_trump(trump))){
        onlyHasTrump = false;
        firstNonTrump = i;
        break;
      }
    }

    if(onlyHasTrump){
      for(int i = 0; i < hand.size(); i++){
        if((Card_less(largest, hand[i], trump))){
          largest = hand[i];
          largestPosition = i;
        }
      }
    }
    else{
      largest = hand[firstNonTrump]; 
      largestPosition  = firstNonTrump;
      for(int i = 0; i < hand.size(); i++){
        if((Card_less(largest, hand[i], trump)) 
        && (!(hand[i].is_trump(trump)))){
          largest = hand[i];
          largestPosition = i;
        }
      }
    }

    hand.erase(hand.begin() + largestPosition);
    return largest;
  }

  Card play_card(const Card &led_card, Suit trump) {
    Card play = hand[0];
    int discardIndex = 0;
    vector<Card> leadCards;
    for (int i = 0; i < hand.size(); i++) {
      Suit first = hand[i].get_suit(trump);
      Suit second = led_card.get_suit(trump);

      if (first == second) {
        leadCards.push_back(hand[i]);
      }
    }
    if (leadCards.size() == 0) {
      for (int j = 0; j < hand.size(); j++) {
        if (Card_less(hand[j], play, led_card, trump)) {
          play = hand[j];
          discardIndex = j;
        }
      }
    }
    else {
      play = leadCards[0];
      for (int j = 0; j < leadCards.size(); j++) {
        if (Card_less(play, leadCards[j], led_card, trump)) {
          play = leadCards[j];
        }
      }
      for(int i = 0; i < hand.size(); i++) {
        if(hand[i] == play) {
          discardIndex = i;
        }
      }
    }
    
    hand.erase(hand.begin() + discardIndex);
    return play;
  }

static const int MAX_HAND_SIZE = 5;
};

class HumanPlayer : public Player {
  
  private:
  string playerName;
  vector<Card> hand;

  public:

  HumanPlayer(const string &name_in) {
    playerName = name_in;
  }

  //EFFECTS returns player's name
  const std::string & get_name() const {
    return playerName;
  }
  
  void add_card(const Card &c) {
    hand.push_back(c);
    std::sort(hand.begin(), hand.end());
  }

  void print_hand() const {
    for (size_t i=0; i < hand.size(); ++i)
      cout << "Human player " << playerName << "'s hand: "
          << "[" << i << "] " << hand[i] << "\n";
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit. If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer, int round, 
    Suit &order_up_suit) const {
      print_hand();
      cout << "Human player " << playerName 
      << ", please enter a suit, or \"pass\":\n";

      string decision;
      cin >> decision;

      if(decision != "pass"){
        order_up_suit = string_to_suit(decision);
        return true;
      }
      else{
        return false;
      }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) {
    int decision;
    print_hand();

    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << playerName 
    << ", please select a card to discard:\n";
    cin >> decision;
    hand.push_back(upcard);

    if(decision == -1){
      hand.pop_back();
    }
    else{
      hand.erase(hand.begin() + decision);
    }
    std::sort(hand.begin(), hand.end());
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(Suit trump) {
    print_hand();
    int decision;
    cout << "Human player " << playerName << ", please select a card:\n";
    cin >> decision;
    Card decisionCard = hand[decision];

    hand.erase(hand.begin() + decision);
    return decisionCard;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, Suit trump) {
    //std::sort(hand.begin(), hand.end());
    print_hand();
    int decision;
    cout << "Human player " << playerName << ", please select a card:\n";
    cin >> decision;
    Card decisionCard = hand[decision];

    hand.erase(hand.begin() + decision);
    return decisionCard;
  }
};

  //EFFECTS: Returns a pointer to a player with the given name and strategy
  //To create an object that won't go out of scope when the function returns,
  //use "return new Simple(name)" or "return new Human(name)"
  //Don't forget to call "delete" on each Player* after the game is over
  //EFFECTS: Prints player's name to os

  Player * Player_factory(const std::string &name, 
  const std::string &strategy){
    if(strategy == "Simple"){
      return new SimplePlayer( name);
    }
    else {
      return new HumanPlayer(name);
    }

    assert(false);
    return nullptr;
  }

  std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
  }
