// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

Card ace = Card(ACE, HEARTS);
Card two = Card(TWO, DIAMONDS);
Card three = Card(THREE, SPADES);   
Card four = Card(FOUR, CLUBS);
Card five = Card(FIVE, HEARTS);
Card six = Card(SIX, DIAMONDS);   
Card seven = Card(SEVEN, SPADES);
Card seven2 = Card(SEVEN, HEARTS);
Card eight = Card(EIGHT, CLUBS);
Card nine = Card(NINE, HEARTS);
Card ten = Card(TEN, DIAMONDS);
Card jack = Card(JACK, DIAMONDS);
Card jack2 = Card(JACK, HEARTS);
Card jack3 = Card(JACK, CLUBS);
Card jack4 = Card(JACK, SPADES);
Card queen = Card(QUEEN, CLUBS);
Card king = Card(KING, HEARTS);


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_default_init) {
    Card c;
    ASSERT_EQUAL(c.get_rank(), TWO);
    ASSERT_EQUAL(c.get_suit(), SPADES);
}

TEST(test_card_in_init) {
    Card c = Card(EIGHT, DIAMONDS);
    ASSERT_EQUAL(c.get_rank(), EIGHT);
    ASSERT_EQUAL(c.get_suit(), DIAMONDS);

    Card d = Card(JACK, HEARTS);
    ASSERT_EQUAL(d.get_rank(), JACK);
    ASSERT_EQUAL(d.get_suit(), HEARTS);
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
}

TEST(test_get_rank) {
    ASSERT_EQUAL(ace.get_rank(), ACE);
    ASSERT_EQUAL(two.get_rank(), TWO);
    ASSERT_EQUAL(three.get_rank(), THREE);
    ASSERT_EQUAL(four.get_rank(), FOUR);
    ASSERT_EQUAL(five.get_rank(), FIVE);
    ASSERT_EQUAL(six.get_rank(), SIX);
    ASSERT_EQUAL(seven.get_rank(), SEVEN);
    ASSERT_EQUAL(eight.get_rank(), EIGHT);
    ASSERT_EQUAL(nine.get_rank(), NINE);
    ASSERT_EQUAL(ten.get_rank(), TEN);
    ASSERT_EQUAL(jack.get_rank(), JACK);
    ASSERT_EQUAL(queen.get_rank(), QUEEN);
    ASSERT_EQUAL(king.get_rank(), KING);
}

TEST(test_get_suit) {
    ASSERT_EQUAL(ace.get_suit(), HEARTS);
    ASSERT_EQUAL(two.get_suit(), DIAMONDS);
    ASSERT_EQUAL(three.get_suit(), SPADES);
    ASSERT_EQUAL(four.get_suit(), CLUBS);
    ASSERT_EQUAL(five.get_suit(), HEARTS);
    ASSERT_EQUAL(six.get_suit(), DIAMONDS);
    ASSERT_EQUAL(seven.get_suit(), SPADES);
    ASSERT_EQUAL(eight.get_suit(), CLUBS);
    ASSERT_EQUAL(nine.get_suit(), HEARTS);
    ASSERT_EQUAL(ten.get_suit(), DIAMONDS);
    ASSERT_EQUAL(jack.get_suit(), DIAMONDS);
    ASSERT_EQUAL(queen.get_suit(), CLUBS);
    ASSERT_EQUAL(king.get_suit(), HEARTS);
}

TEST(test_get_suit_with_trump) {
    ASSERT_EQUAL(ace.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(two.get_suit(HEARTS), DIAMONDS);
    ASSERT_EQUAL(three.get_suit(HEARTS), SPADES);
    ASSERT_EQUAL(four.get_suit(HEARTS), CLUBS);
    ASSERT_EQUAL(five.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(six.get_suit(HEARTS), DIAMONDS);
    ASSERT_EQUAL(seven.get_suit(HEARTS), SPADES);
    ASSERT_EQUAL(eight.get_suit(HEARTS), CLUBS);
    ASSERT_EQUAL(nine.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(ten.get_suit(HEARTS), DIAMONDS);
    ASSERT_EQUAL(jack.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(jack2.get_suit(HEARTS), HEARTS);
    ASSERT_EQUAL(queen.get_suit(HEARTS), CLUBS);
    ASSERT_EQUAL(king.get_suit(HEARTS), HEARTS);
}

TEST(test_is_face_or_ace) {
    ASSERT_TRUE(ace.is_face_or_ace());
    ASSERT_FALSE(two.is_face_or_ace());
    ASSERT_FALSE(four.is_face_or_ace());
    ASSERT_FALSE(six.is_face_or_ace());
    ASSERT_FALSE(eight.is_face_or_ace());
    ASSERT_FALSE(ten.is_face_or_ace());
    ASSERT_TRUE(jack.is_face_or_ace());
    ASSERT_TRUE(king.is_face_or_ace());
    ASSERT_TRUE(queen.is_face_or_ace());
    
}

TEST(test_is_right_bower) {
    Card c = Card(JACK, SPADES);
    Card d = Card(JACK, HEARTS);
    Card e = Card(JACK, CLUBS);
    Card f = Card(JACK, DIAMONDS);
    Card g = Card(QUEEN, SPADES);
    Card h = Card(TEN, SPADES);

    ASSERT_TRUE(c.is_right_bower(SPADES));
    ASSERT_TRUE(d.is_right_bower(HEARTS));
    ASSERT_FALSE(e.is_right_bower(SPADES));
    ASSERT_FALSE(f.is_right_bower(SPADES));
    ASSERT_FALSE(g.is_right_bower(SPADES));
    ASSERT_FALSE(h.is_right_bower(SPADES));
}

TEST(test_is_left_bower) {
    Card c = Card(JACK, SPADES);
    Card d = Card(JACK, HEARTS);
    Card e = Card(JACK, CLUBS);
    Card f = Card(JACK, DIAMONDS);
    Card g = Card(QUEEN, SPADES);
    Card h = Card(TEN, SPADES);
    
    ASSERT_TRUE(c.is_left_bower(CLUBS));
    ASSERT_FALSE(c.is_left_bower(SPADES));
    ASSERT_TRUE(d.is_left_bower(DIAMONDS));
    ASSERT_TRUE(e.is_left_bower(SPADES));
    ASSERT_TRUE(f.is_left_bower(HEARTS));
    ASSERT_FALSE(g.is_left_bower(SPADES));
    ASSERT_FALSE(h.is_left_bower(SPADES));       
}

TEST(test_is_trump) {
    Card c = Card(JACK, SPADES);
    Card d = Card(JACK, HEARTS);
    Card e = Card(JACK, CLUBS);
    Card f = Card(JACK, DIAMONDS);
    Card g = Card(QUEEN, SPADES);
    Card h = Card(TEN, SPADES);
    Card i = Card(SEVEN, HEARTS);

    ASSERT_TRUE(c.is_trump(SPADES));
    ASSERT_TRUE(d.is_trump(HEARTS));
    ASSERT_TRUE(e.is_trump(SPADES));
    ASSERT_FALSE(f.is_trump(SPADES));
    ASSERT_FALSE(c.is_trump(HEARTS));
    ASSERT_TRUE(g.is_trump(SPADES));
    ASSERT_TRUE(h.is_trump(SPADES));
    ASSERT_FALSE(i.is_trump(DIAMONDS));
    ASSERT_TRUE(f.is_trump(HEARTS));
    ASSERT_TRUE(d.is_trump(DIAMONDS));
    ASSERT_TRUE(c.is_trump(CLUBS));
}

TEST(test_print_to_stream){
    Card c = Card(TEN, DIAMONDS);
    ostringstream out;
    out << c;
    stringstream os ("Ten of Diamonds");
    ASSERT_EQUAL(out.str(), os.str());

    
    Card d = Card(JACK, HEARTS);
    ostringstream out2;
    out2 << d;
    stringstream os2 ("Jack of Hearts");
    ASSERT_EQUAL(out2.str(), os2.str());


    Card e = Card(KING, CLUBS);
    ostringstream out3;
    out3 << e;
    stringstream os3 ("King of Clubs");
    ASSERT_EQUAL(out3.str(), os3.str());
}

TEST(test_take_from_stream){
    istringstream ins ("Ten of Diamonds");
    Card c;
    ins >> c;
    Card correct = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(c, correct);

    istringstream ins1 ("Jack of Spades");
    Card d;
    ins1 >> d;
    Card correct1 = Card(JACK, SPADES);
    ASSERT_EQUAL(d, correct1);
    
    istringstream ins2 ("Three of Hearts");
    Card e;
    ins2 >> e;
    Card correct2 = Card(THREE, HEARTS);
    ASSERT_EQUAL(e, correct2);
}

// (Diamonds > Clubs > Hearts > Spades)

TEST(test_operator_less_than){
    Card lhs = Card(SEVEN, SPADES);
    Card rhs = Card(NINE, HEARTS);
    ASSERT_TRUE(lhs < rhs);

    Card lhs1 = Card(SEVEN, SPADES);
    Card rhs1 = Card(SEVEN, HEARTS);
    ASSERT_TRUE(lhs1 < rhs1); 

    Card lhs2 = Card(KING, DIAMONDS);
    Card rhs2 = Card(KING, SPADES);
    ASSERT_FALSE(lhs2 < rhs2);

    Card lhs3 = Card(QUEEN, DIAMONDS);
    Card rhs3 = Card(QUEEN, DIAMONDS);
    ASSERT_FALSE(lhs3 < rhs3);

    Card lhs4 = Card(JACK, DIAMONDS);
    Card rhs4 = Card(JACK, DIAMONDS);
    ASSERT_FALSE(lhs4 < rhs4);

    Card lhs5 = Card(JACK, HEARTS);
    Card rhs5 = Card(JACK, CLUBS);
    ASSERT_TRUE(lhs5 < rhs5);
    
    Card lhs6 = Card(JACK, SPADES);
    Card rhs6 = Card(QUEEN, HEARTS);
    ASSERT_TRUE(lhs6 < rhs6);

    Card lhs7 = Card(QUEEN, SPADES);
    Card rhs7 = Card(JACK, HEARTS);
    ASSERT_FALSE(lhs7 < rhs7);

    Card lhs8 = Card(QUEEN, SPADES);
    Card rhs8 = Card(NINE, SPADES);
    ASSERT_FALSE(lhs8 < rhs8);

    //do we need to chcek if jack is higher than king?
}

TEST(test_operator_less_than_equal_to){
    Card lhs = Card(SEVEN, SPADES);
    Card rhs = Card(NINE, HEARTS);
    ASSERT_TRUE(lhs <= rhs);

    Card lhs1 = Card(SEVEN, SPADES);
    Card rhs1 = Card(SEVEN, HEARTS);
    ASSERT_TRUE(lhs1 <= rhs1); 

    Card lhs2 = Card(KING, DIAMONDS);
    Card rhs2 = Card(KING, SPADES);
    ASSERT_FALSE(lhs2 <= rhs2);

    Card lhs3 = Card(QUEEN, DIAMONDS);
    Card rhs3 = Card(QUEEN, DIAMONDS);
    ASSERT_TRUE(lhs3 <= rhs3);

    Card lhs4 = Card(JACK, DIAMONDS);
    Card rhs4 = Card(JACK, DIAMONDS);
    ASSERT_TRUE(lhs4 <= rhs4);

    Card lhs5 = Card(JACK, HEARTS);
    Card rhs5 = Card(JACK, CLUBS);
    ASSERT_TRUE(lhs5 <= rhs5);
    
    Card lhs6 = Card(JACK, SPADES);
    Card rhs6 = Card(QUEEN, HEARTS);
    ASSERT_TRUE(lhs6 <= rhs6);

    Card lhs7 = Card(QUEEN, SPADES);
    Card rhs7 = Card(JACK, HEARTS);
    ASSERT_FALSE(lhs7 <= rhs7);

    Card lhs8 = Card(QUEEN, SPADES);
    Card rhs8 = Card(NINE, SPADES);
    ASSERT_FALSE(lhs8 <= rhs8);

    //do we need to chcek if jack is higher than king?
}

TEST(test_operator_greater_than) {
   Card lhs = Card(SEVEN, SPADES);
   Card rhs = Card(NINE, HEARTS);
   ASSERT_FALSE(lhs > rhs);


   Card lhs2 = Card(SEVEN, SPADES);
   Card rhs2 = Card(SEVEN, HEARTS);
   ASSERT_FALSE(lhs2 > rhs2); 

  Card lhs3 = Card(TWO, CLUBS);
   Card rhs3 = Card(TWO, DIAMONDS);
   ASSERT_FALSE(lhs3 > rhs3); 


   Card lhs4 = Card(KING, DIAMONDS);
   Card rhs4 = Card(KING, SPADES);
   ASSERT_TRUE(lhs4 > rhs4);


   Card lhs5 = Card(JACK, SPADES);
   Card rhs5 = Card(QUEEN, HEARTS);
   ASSERT_FALSE(lhs5 > rhs5);


   Card lhs6 = Card(QUEEN, SPADES);
   Card rhs6 = Card(JACK, HEARTS);
   ASSERT_TRUE(lhs6 > rhs6);
}

TEST(test_operator_greater_than_equal_to){
    Card lhs = Card(SEVEN, SPADES);
    Card rhs = Card(NINE, HEARTS);
    ASSERT_FALSE(lhs >= rhs);

    Card lhs1 = Card(SEVEN, SPADES);
    Card rhs1 = Card(SEVEN, HEARTS);
    ASSERT_FALSE(lhs1 >= rhs1); 

    Card lhs2 = Card(KING, DIAMONDS);
    Card rhs2 = Card(KING, SPADES);
    ASSERT_TRUE(lhs2 >= rhs2);

    Card lhs3 = Card(QUEEN, DIAMONDS);
    Card rhs3 = Card(QUEEN, DIAMONDS);
    ASSERT_TRUE(lhs3 >= rhs3);

    Card lhs4 = Card(JACK, DIAMONDS);
    Card rhs4 = Card(JACK, DIAMONDS);
    ASSERT_TRUE(lhs4 >= rhs4);

    Card lhs5 = Card(JACK, HEARTS);
    Card rhs5 = Card(JACK, CLUBS);
    ASSERT_FALSE(lhs5 >= rhs5);
    
    Card lhs6 = Card(JACK, SPADES);
    Card rhs6 = Card(QUEEN, HEARTS);
    ASSERT_FALSE(lhs6 >= rhs6);

    Card lhs7 = Card(QUEEN, SPADES);
    Card rhs7 = Card(JACK, HEARTS);
    ASSERT_TRUE(lhs7 >= rhs7);

    Card lhs8 = Card(QUEEN, SPADES);
    Card rhs8 = Card(NINE, SPADES);
    ASSERT_TRUE(lhs8 >= rhs8);

    //do we need to chcek if jack is higher than king?
}

TEST(test_operator_equal_to) {
   Card lhs = Card(SEVEN, SPADES);
   Card rhs = Card(NINE, HEARTS);
   ASSERT_FALSE(lhs == rhs);


   Card lhs2 = Card(SEVEN, HEARTS);
   Card rhs2 = Card(SEVEN, HEARTS);
   ASSERT_TRUE(lhs2 == rhs2); 
   
   Card lhs3 = Card(TWO, CLUBS);
   Card rhs3 = Card(TWO, DIAMONDS);
   ASSERT_FALSE(lhs3 == rhs3); 


   Card lhs4 = Card(KING, DIAMONDS);
   Card rhs4 = Card(KING, DIAMONDS);
   ASSERT_TRUE(lhs4 == rhs4);


   Card lhs5 = Card(JACK, SPADES);
   Card rhs5 = Card(QUEEN, HEARTS);
   ASSERT_FALSE(lhs5 == rhs5);


   Card lhs6 = Card(TWO, SPADES);
   Card rhs6 = Card(TWO, SPADES);
   ASSERT_TRUE(lhs6 == rhs6);
}


TEST(test_operator_not_equal){
    Card lhs = Card(SEVEN, SPADES);
    Card rhs = Card(NINE, HEARTS);
    ASSERT_TRUE(lhs != rhs);

    Card lhs1 = Card(SEVEN, SPADES);
    Card rhs1 = Card(SEVEN, HEARTS);
    ASSERT_TRUE(lhs1 != rhs1); 

    Card lhs2 = Card(KING, DIAMONDS);
    Card rhs2 = Card(KING, SPADES);
    ASSERT_TRUE(lhs2 != rhs2);

    Card lhs3 = Card(QUEEN, DIAMONDS);
    Card rhs3 = Card(QUEEN, DIAMONDS);
    ASSERT_FALSE(lhs3 != rhs3);

    Card lhs4 = Card(JACK, DIAMONDS);
    Card rhs4 = Card(JACK, DIAMONDS);
    ASSERT_FALSE(lhs4 != rhs4);

    Card lhs5 = Card(JACK, HEARTS);
    Card rhs5 = Card(JACK, CLUBS);
    ASSERT_TRUE(lhs5 != rhs5);
    
    Card lhs6 = Card(JACK, SPADES);
    Card rhs6 = Card(QUEEN, HEARTS);
    ASSERT_TRUE(lhs6 != rhs6);

    Card lhs7 = Card(QUEEN, SPADES);
    Card rhs7 = Card(JACK, HEARTS);
    ASSERT_TRUE(lhs7 != rhs7);

    Card lhs8 = Card(QUEEN, SPADES);
    Card rhs8 = Card(NINE, SPADES);
    ASSERT_TRUE(lhs8 != rhs8);

    Card lhs9 = Card(JACK, DIAMONDS);
    Card rhs9 = Card(JACK, HEARTS);
    ASSERT_TRUE(lhs9 != rhs9);
}


// (Diamonds > Clubs > Hearts > Spades)

TEST(test_card_less){
    ASSERT_TRUE(Card_less(ace, two, DIAMONDS));
    ASSERT_FALSE(Card_less(ace, two, CLUBS));
    ASSERT_FALSE(Card_less(ace, two, HEARTS));

    ASSERT_FALSE(Card_less(jack, jack2, DIAMONDS));
    ASSERT_FALSE(Card_less(ace, two, HEARTS));

    ASSERT_TRUE(Card_less(king, jack4, SPADES));
    ASSERT_TRUE(Card_less(king, jack4, CLUBS));
    ASSERT_FALSE(Card_less(king, jack4, HEARTS));
    ASSERT_FALSE(Card_less(king, jack4, DIAMONDS));

    ASSERT_TRUE(Card_less(seven, seven2, CLUBS));
    ASSERT_FALSE(Card_less(seven, seven2, SPADES));
}

TEST(test_card_less_with_led) {
    Card a = Card(NINE, SPADES);
    Card b = Card(KING, DIAMONDS);
    Card led_card = Card(QUEEN, SPADES);
    ASSERT_FALSE(Card_less(a, b, led_card, HEARTS));

    Card c = Card(NINE, HEARTS);
    Card d = Card(JACK, CLUBS);
    Card led_card2 = Card(QUEEN, SPADES);
    ASSERT_FALSE(Card_less(c, d, led_card2, HEARTS));
    
    Card e = Card(TEN, SPADES);
    Card f = Card(JACK, DIAMONDS);
    Card led_card3 = Card(QUEEN, SPADES);
    ASSERT_TRUE(Card_less(e, f, led_card3, HEARTS));

    Card g = Card(JACK, SPADES);
    Card h = Card(KING, DIAMONDS);
    Card led_card4 = Card(QUEEN, CLUBS);
    ASSERT_FALSE(Card_less(g, h, led_card4, SPADES));

    Card i = Card(KING, SPADES);
    Card j = Card(TEN, DIAMONDS);
    Card led_card5 = Card(QUEEN, DIAMONDS);
    ASSERT_TRUE(Card_less(i, j, led_card5, CLUBS));

    Card k = Card(KING, SPADES);
    Card l = Card(JACK, SPADES);
    Card led_card6 = Card(QUEEN, DIAMONDS);
    ASSERT_TRUE(Card_less(k, l, led_card6, CLUBS));

    Card m = Card(KING, SPADES);
    Card n = Card(NINE, HEARTS);
    Card led_card7 = Card(TEN, HEARTS);
    ASSERT_TRUE(Card_less(m, n, led_card7, CLUBS));

    Card o = Card(JACK, HEARTS);
    Card p = Card(JACK, DIAMONDS);
    Card led_card8 = Card(TEN, CLUBS);
    ASSERT_TRUE(Card_less(o, p, led_card8, DIAMONDS));    
}

TEST_MAIN()