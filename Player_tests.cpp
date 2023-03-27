// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_insertion) {
  Player * human = Player_factory("NotRobot", "Human");
  ostringstream oss1;
  oss1 << * human;
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  Player * alice = Player_factory("Alice", "Simple");
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  delete human;
  delete alice;
}

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_get_name) {
    Player * robert = Player_factory("Robert", "Human");
    ASSERT_EQUAL("Robert", robert->get_name());

    delete robert;
}

//round 1 make trump tests

//test when player doesn't make trump, they have 0 face cards  
TEST(test_simple_player_make_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(THREE, HEARTS));
  bob->add_card(Card(TWO, HEARTS));

  Card c(ACE, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    1,             
    trump          
  );

  ASSERT_FALSE(orderup);
  //ASSERT_NOT_EQUAL(trump, HEARTS);

  delete bob;
}

//test player does not make trump, they have 1 face card 
TEST(test_simple_player_make_trump2) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, SPADES));

  Card c(QUEEN, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    1,             
    trump          
  );

  ASSERT_FALSE(orderup);
  //ASSERT_NOT_EQUAL(trump, HEARTS);

  delete bob;
}

//test player does make trump, they have 2 face cards aready
TEST(test_simple_player_make_trump3) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  Card c(QUEEN, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    1,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

//test player does make trump, they have 3 face cards aready
TEST(test_simple_player_make_trump4) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  Card c(QUEEN, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    1,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

//test player does make trump, they have 2 face cards, 1 is leftbower
TEST(test_simple_player_make_trump5) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  Card c(QUEEN, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    1,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

//test player does not make trump, they have 1 leftbower
/*TEST(test_simple_player_make_trump6) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(THREE, HEARTS));

  Card c(QUEEN, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    1,             
    trump          
  );

  ASSERT_FALSE(orderup);
  ASSERT_NOT_EQUAL(trump, HEARTS);

  delete bob;
}*/

//test player does make trump, they have 2 face cards, 1 is rightbower
TEST(test_simple_player_make_trump7) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(ACE, HEARTS));

  Card c(QUEEN, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    1,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

//test player does make trump, they have 2 face cards, is rightbower and is left bower
TEST(test_simple_player_make_trump8) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(JACK, HEARTS));

  Card c(QUEEN, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    1,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

//round two make trump tests

//test player does not order up, they have 0 face cards of next suit, 0 of current suit
TEST(test_simple_player_make_trump9) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(ACE, DIAMONDS));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    false,          
    2,             
    trump          
  );

  ASSERT_FALSE(orderup);
  //ASSERT_NOT_EQUAL(trump, CLUBS);

  delete bob;
}

//test player does not order up, they have 0 face cards of next suit, 1 of current suit
TEST(test_simple_player_make_trump10) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(ACE, CLUBS));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    false,          
    2,             
    trump          
  );

  ASSERT_FALSE(orderup);
  //ASSERT_NOT_EQUAL(trump, CLUBS);

  delete bob;
}

//test player does not order up, they have 0 face cards of next suit, 2 of current suit
TEST(test_simple_player_make_trump11) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(KING, CLUBS));
  bob->add_card(Card(ACE, CLUBS));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    false,          
    2,             
    trump          
  );

  ASSERT_FALSE(orderup);
  //ASSERT_NOT_EQUAL(trump, CLUBS);

  delete bob;
}

//test player does order up, they have 1 face cards of next suit, 0 of current suit
TEST(test_simple_player_make_trump12) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, HEARTS));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    false,          
    2,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

//test player does order up, they have 2 face cards of next suit, 0 of current suit
TEST(test_simple_player_make_trump13) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(SEVEN, DIAMONDS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    false,          
    2,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

//test player does order up, they have 1 face card of next suit, is right bower
TEST(test_simple_player_make_trump14) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(SEVEN, DIAMONDS));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(ACE, HEARTS));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    false,          
    2,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

//test player does order up, they have 1 face card of next suit, is left bower
TEST(test_simple_player_make_trump15) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(SEVEN, DIAMONDS));
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(ACE, SPADES));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    false,          
    2,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

//screw the dealer test 1
TEST(test_simple_player_make_trump16) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(SEVEN, DIAMONDS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(ACE, HEARTS));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    2,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

//screw the dealer test 2
TEST(test_simple_player_make_trump17) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(SEVEN, CLUBS));
  bob->add_card(Card(TWO, CLUBS));
  bob->add_card(Card(THREE, CLUBS));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    2,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

//screw the dealer test 2
TEST(test_simple_player_make_trump18) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(SEVEN, SPADES));
  bob->add_card(Card(TWO, SPADES));
  bob->add_card(Card(THREE, SPADES));

  Card c(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bob->make_trump(
    c,    
    true,          
    2,             
    trump          
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

//test Lead Trick


//has no trump cards in hand
TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));


  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;

//has no trump cards in hand

  Player * bob2 = Player_factory("Bob2", "Simple");
  bob2->add_card(Card(NINE, SPADES));
  bob2->add_card(Card(TEN, SPADES));
  bob2->add_card(Card(JACK, SPADES));
  bob2->add_card(Card(KING, SPADES));
  bob2->add_card(Card(ACE, SPADES));

  bob2->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led2 = bob2->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades2(ACE, SPADES);
  ASSERT_EQUAL(card_led2, ace_spades2); //check led card

  delete bob2;

//has 1 trump card in hand

  Player * bob3 = Player_factory("Bob3", "Simple");
  bob3->add_card(Card(NINE, SPADES));
  bob3->add_card(Card(TEN, HEARTS));
  bob3->add_card(Card(JACK, SPADES));
  bob3->add_card(Card(KING, SPADES));
  bob3->add_card(Card(ACE, SPADES));

  bob3->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led3 = bob3->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades3(ACE, SPADES);
  ASSERT_EQUAL(card_led3, ace_spades3); //check led card

  delete bob3;

//has 2 trump card in hand

  Player * bob4 = Player_factory("Bob4", "Simple");
  bob4->add_card(Card(NINE, SPADES));
  bob4->add_card(Card(TEN, HEARTS));
  bob4->add_card(Card(JACK, HEARTS));
  bob4->add_card(Card(KING, SPADES));
  bob4->add_card(Card(ACE, SPADES));

  bob4->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led4 = bob4->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades4(ACE, SPADES);
  ASSERT_EQUAL(card_led4, ace_spades4); //check led card

  delete bob4;

//has 3 trump card in hand
  Player * bob5 = Player_factory("Bob5", "Simple");
  bob5->add_card(Card(NINE, SPADES));
  bob5->add_card(Card(TEN, HEARTS));
  bob5->add_card(Card(JACK, HEARTS));
  bob5->add_card(Card(KING, HEARTS));
  bob5->add_card(Card(ACE, SPADES));

  bob5->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led5 = bob5->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades5(ACE, SPADES);
  ASSERT_EQUAL(card_led5, ace_spades5); //check led card

  delete bob5;

//has 4 trump card in hand
  Player * bob6 = Player_factory("Bob6", "Simple");
  bob6->add_card(Card(NINE, HEARTS));
  bob6->add_card(Card(TEN, HEARTS));
  bob6->add_card(Card(JACK, HEARTS));
  bob6->add_card(Card(KING, HEARTS));
  bob6->add_card(Card(ACE, SPADES));

  bob6->add_and_discard(
    Card(SEVEN, HEARTS) // upcard
  );

  // Bob leads
  Card card_led6 = bob6->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card jack_hearts6(JACK, HEARTS);
  ASSERT_EQUAL(card_led6, jack_hearts6); //check led card

  delete bob6;


//has 5 trump card in hand, right bower
  Player * bob7 = Player_factory("Bob7", "Simple");
  bob7->add_card(Card(NINE, HEARTS));
  bob7->add_card(Card(TEN, HEARTS));
  bob7->add_card(Card(JACK, HEARTS));
  bob7->add_card(Card(KING, HEARTS));
  bob7->add_card(Card(ACE, HEARTS));

  bob7->add_and_discard(
    Card(SEVEN, HEARTS) // upcard
  );

  // Bob leads
  Card card_led7 = bob7->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card c7(JACK, HEARTS);
  ASSERT_EQUAL(card_led7, c7); //check led card

  delete bob7;

//has 5 trump card in hand, right bower
  Player * bob8 = Player_factory("Bob8", "Simple");
  bob8->add_card(Card(NINE, HEARTS));
  bob8->add_card(Card(TEN, HEARTS));
  bob8->add_card(Card(JACK, HEARTS));
  bob8->add_card(Card(KING, HEARTS));
  bob8->add_card(Card(ACE, HEARTS));

  bob8->add_and_discard(
    Card(SEVEN, DIAMONDS) // upcard
  );

  // Bob leads
  Card card_led8 = bob8->lead_card(DIAMONDS);

  // Verify the card Bob selected to lead
  Card c8(ACE, HEARTS);
  ASSERT_EQUAL(card_led8, c8); //check led card

  delete bob8;

//has 5 trump card in hand, left bower
  Player * bob9 = Player_factory("Bob9", "Simple");
  bob9->add_card(Card(NINE, HEARTS));
  bob9->add_card(Card(TEN, HEARTS));
  bob9->add_card(Card(JACK, DIAMONDS));
  bob9->add_card(Card(KING, HEARTS));
  bob9->add_card(Card(ACE, HEARTS));

  bob9->add_and_discard(
    Card(SEVEN, HEARTS) // upcard
  );

  // Bob leads
  Card card_led9 = bob9->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card c9(JACK, DIAMONDS);
  ASSERT_EQUAL(card_led9, c9); //check led card

  delete bob9;

//has 5 trump card in hand., no bowers
  Player * bob10 = Player_factory("Bob10", "Simple");
  bob10->add_card(Card(NINE, HEARTS));
  bob10->add_card(Card(TEN, HEARTS));
  bob10->add_card(Card(TWO, HEARTS));
  bob10->add_card(Card(KING, HEARTS));
  bob10->add_card(Card(ACE, HEARTS));

  bob10->add_and_discard(
    Card(SEVEN, HEARTS) // upcard
  );

  // Bob leads
  Card card_led10 = bob10->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card c10(ACE, HEARTS);
  ASSERT_EQUAL(card_led10, c10); //check led card

  delete bob10;
}

TEST(test_simple_player_play_card) {
    Player* sam = Player_factory("Sam", "Simple");
    sam->add_card(Card(NINE, SPADES));
    sam->add_card(Card(TEN, SPADES));
    sam->add_card(Card(JACK, SPADES));
    sam->add_card(Card(QUEEN, SPADES));
    sam->add_card(Card(KING, SPADES));

    Card led = Card(ACE, SPADES);

    Card card_played = sam->play_card(led, HEARTS);

    ASSERT_EQUAL(card_played, Card(KING, SPADES));
    delete sam;

    Player* sam2 = Player_factory("Sam2", "Simple");
    sam2->add_card(Card(NINE, SPADES));
    sam2->add_card(Card(TEN, SPADES));
    sam2->add_card(Card(JACK, HEARTS));
    sam2->add_card(Card(QUEEN, HEARTS));
    sam2->add_card(Card(KING, HEARTS));

    Card led2 = Card(ACE, SPADES);

    Card card_played2 = sam2->play_card(led2, SPADES);

    ASSERT_EQUAL(card_played2, Card(TEN, SPADES));
    delete sam2;

    Player* sam3 = Player_factory("Sam3", "Simple");
    sam3->add_card(Card(NINE, SPADES));
    sam3->add_card(Card(TEN, SPADES));
    sam3->add_card(Card(JACK, SPADES));
    sam3->add_card(Card(QUEEN, SPADES));
    sam3->add_card(Card(KING, SPADES));

    Card led3 = Card(ACE, HEARTS);

    Card card_played3 = sam3->play_card(led3, HEARTS);

    ASSERT_EQUAL(card_played3, Card(NINE, SPADES));
    delete sam3;

    Player* sam4 = Player_factory("Sam4", "Simple");
    sam4->add_card(Card(NINE, SPADES));
    sam4->add_card(Card(TEN, HEARTS));
    sam4->add_card(Card(JACK, CLUBS));
    sam4->add_card(Card(QUEEN, DIAMONDS));
    sam4->add_card(Card(KING, SPADES));

    Card led4 = Card(ACE, DIAMONDS);

    Card card_played4 = sam4->play_card(led4, CLUBS);

    ASSERT_EQUAL(card_played4, Card(QUEEN, DIAMONDS));
    delete sam4;

    Player* sam5 = Player_factory("Sam5", "Simple");
    sam5->add_card(Card(NINE, DIAMONDS));
    sam5->add_card(Card(TEN, DIAMONDS));
    sam5->add_card(Card(JACK, CLUBS));
    sam5->add_card(Card(QUEEN, DIAMONDS));
    sam5->add_card(Card(KING, DIAMONDS));

    Card led5 = Card(ACE, DIAMONDS);

    Card card_played5 = sam5->play_card(led5, CLUBS);

    ASSERT_EQUAL(card_played5, Card(KING, DIAMONDS));
    delete sam5;

    Player* sam6 = Player_factory("Sam6", "Simple");
    sam6->add_card(Card(NINE, DIAMONDS));
    sam6->add_card(Card(TEN, DIAMONDS));
    sam6->add_card(Card(JACK, CLUBS));
    sam6->add_card(Card(QUEEN, DIAMONDS));
    sam6->add_card(Card(KING, SPADES));

    Card led6 = Card(ACE, SPADES);

    Card card_played6 = sam6->play_card(led6, SPADES);

    ASSERT_EQUAL(card_played6, Card(JACK, CLUBS));
    delete sam6;

    Player* sam7 = Player_factory("Sam7", "Simple");
    sam7->add_card(Card(NINE, DIAMONDS));
    sam7->add_card(Card(TEN, DIAMONDS));
    sam7->add_card(Card(JACK, DIAMONDS));
    sam7->add_card(Card(QUEEN, DIAMONDS));
    sam7->add_card(Card(KING, DIAMONDS));

    Card led7 = Card(ACE, DIAMONDS);

    Card card_played7 = sam7->play_card(led7, DIAMONDS);

    ASSERT_EQUAL(card_played7, Card(JACK, DIAMONDS));
    delete sam7;
}

TEST_MAIN()