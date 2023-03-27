// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include <sstream>
#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <array>
#include <cstring>
#include <algorithm>
#include <vector>
#include "Player.h"
using namespace std;

class Game {
public:

  Game(vector<Player*> people, int numPoints, bool shuff, istream& pack_input) {
    players = people;
    pointsNeededToWin = numPoints;
    ifShuffle = shuff;
    Pack pack(istream& pack_input);
    dealerIndex = 0;
    hand = 0;
  }

  void play(){
    while ((team1score < pointsNeededToWin) && 
    (team2score < pointsNeededToWin)) {
      cout << "Hand " << hand << "\n" << *players[dealerIndex] << " deals" << endl;
      shuffle();
      deal();
      makeTrump();
      cout << endl;
      play_hand();
      cout << *players[0] << " and " << *players[2] 
      << " have " << team1score << " points\n";
      cout << *players[1] << " and " << *players[3] 
      << " have " << team2score << " points\n";
      cout << endl;
      dealerIndex = ((dealerIndex+ 1) % 4);
      hand++;
      pack.reset();
    }

    if (team1score >= pointsNeededToWin) {
      cout << *players[0] << " and " << *players[2] << " win!" << endl;
    }
    else {
      cout << *players[1] << " and " << *players[3] << " win!" << endl;
    }
    
    for (size_t i = 0; i < players.size(); ++i) {
      delete players[i];
    }
  }

private:
  vector<Player*> players;
  Pack pack;
  int hand = 0;
  int pointsNeededToWin;
  int team1score = 0;
  int team2score = 0;
  int trickScoreTeam1 = 0;
  int trickScoreTeam2 = 0;
  int dealerIndex;
  Card currentCard;
  //Card trumpCard;
  Card upCard;
  Suit orderUpSuit;
  //Suit trump;
  vector <Card> currentTrick;
  int winnerIndex;
  Card winningCard;
  vector <Player*> team1;
  vector <Player*> team2;
  int winningCardIndex;
  int roundsPassed;
  int orderUpPlayerIndex;
  int orderUpTeam;
  bool team1WonRound;
  bool team2WonRound;
  bool ifShuffle;
  bool isDealer;
  
  void determine_teams() {
    for(int i = 0; i < players.size(); i++){
      if( (i % 2) == 0){
        team1.push_back(players[i]);
      }
      else{
        team2.push_back(players[i]);
      }
    }
  }

  void trickScoreIncrement() {
    if(winnerIndex % 2 == 0){
      trickScoreTeam1++;
    }
    else{
      trickScoreTeam2++;
    }
  }

  void shuffle(){
    if (ifShuffle == true) {
      pack.shuffle();
    }
  }

  void deal(){
    for(int i = 0; i < 3; ++i){
      players[(dealerIndex+1) % 4]->add_card(pack.deal_one());
    }
    for(int i = 0; i < 2; ++i){
      players[(dealerIndex+2) % 4]->add_card(pack.deal_one());
    }
    for(int i = 0; i < 3; ++i){
      players[(dealerIndex+3) % 4]->add_card(pack.deal_one());
    }
    for(int i = 0; i < 2; ++i){
      players[(dealerIndex) % 4]->add_card(pack.deal_one());
    }
    for(int i = 0; i < 2; ++i){
      players[(dealerIndex+1) % 4]->add_card(pack.deal_one());
    }
    for(int i = 0; i < 3; ++i){
      players[(dealerIndex+2) % 4]->add_card(pack.deal_one());
    }
    for(int i = 0; i < 2; ++i){
      players[(dealerIndex+3) % 4]->add_card(pack.deal_one());
    }
    for(int i = 0; i < 3; ++i){
      players[(dealerIndex) % 4]->add_card(pack.deal_one());
    }
  }

  void teamOrderedUp(){
    if(orderUpPlayerIndex % 2 == 0){
      orderUpTeam = 1;
    }
    else{
      orderUpTeam = 2;
    }
  }


  void determineOrderUpTeam(){
    if(orderUpPlayerIndex % 2 == 0){
      orderUpTeam = 1;
      }
    else{
      orderUpTeam = 2;
    }
  }

  void makeTrump() {
    upCard = pack.deal_one();
    cout << upCard << " turned up" << endl;
    orderUpSuit = upCard.get_suit();
    int round = 1;
    //bool checkIfTrump = false;

    while(round <= 2){
      for(int i = 1; i < dealerIndex + players.size() + 2; ++i){
        
        if(i % 4 == dealerIndex){
          isDealer = true;
        }
        else{
          isDealer = false;
        }

        if(players[(dealerIndex + i) % 4]->make_trump(upCard, isDealer, round, orderUpSuit)){
          cout << *players[(dealerIndex + i) % 4] << " orders up " << orderUpSuit << endl;
          players[dealerIndex]->add_and_discard(upCard);
          determineOrderUpTeam();
        }
        else{
          cout << players[(dealerIndex + i) % 4]->get_name() << " passes" << endl;
        }
      }
      round++;
    }  

    /*
    for (int i = 1; i < dealerIndex + players.size() + 2; ++i) {
      if(times < 4 && ((dealerIndex + i) % 4 != dealerIndex)){
        checkIfTrump = players[(dealerIndex + i) % 4]->make_trump(upCard, 
        false, 1, orderUpSuit);
      }
      else if (times >= 4 && ((dealerIndex + i) % 4 != dealerIndex)) {
        checkIfTrump = players[(dealerIndex + i) % 4]->make_trump(upCard,
         false, 2, orderUpSuit);
      }
      else if (times < 4 && ((dealerIndex + i) % 4 == dealerIndex)) {
        checkIfTrump = players[(dealerIndex + i) % 4]->make_trump(upCard,
         true, 1, orderUpSuit);
      }
      else {
        checkIfTrump = players[(dealerIndex + i) % 4]->make_trump(upCard,
         true, 2, orderUpSuit);
      }

      if (checkIfTrump && times < 4) {
        orderUpPlayerIndex = ((dealerIndex + i) % 4);
        cout << *players[(dealerIndex + i) % 4] << " orders up " << orderUpSuit << endl;
        players[dealerIndex]->add_and_discard(upCard);
        determineOrderUpTeam();
        times++;
        break;
      }
      else if (!(checkIfTrump) && times < 4) {
        cout << players[(dealerIndex + i) % 4]->get_name() << " passes" << endl;
        times++;
      }
      else if (checkIfTrump && times < 4) {
        orderUpPlayerIndex = ((dealerIndex + i) % 4);
        cout << *players[(dealerIndex + i) % 4] << " orders up " << orderUpSuit << endl;
        players[dealerIndex]->add_and_discard(upCard);
        determineOrderUpTeam();
        times++;
        break;
      }
      else if (!(checkIfTrump) && times < 4) {
        cout << players[(dealerIndex + i) % 4]->get_name() << " passes" << endl;
        times++;
      }
      else if (checkIfTrump) {
        orderUpPlayerIndex = ((dealerIndex + i) % 4);
        cout << *players[(dealerIndex + i) % 4] << " orders up " << orderUpSuit << endl;
        determineOrderUpTeam();
        break;
      }
      else if (!(checkIfTrump)) {
        cout << players[(dealerIndex + i) % 4]->get_name() << " passes" << endl;
      }
      else{
        orderUpPlayerIndex = ((dealerIndex + i) % 4);
        cout << *players[(dealerIndex + i) % 4] << " orders up " << orderUpSuit << endl;
        determineOrderUpTeam();
      }
    }
    */
  }

/*
    while(round <= 2){
      for(int i = 1; i < dealerIndex + players.size() + 2; ++i){
        
        if(i % 4 == dealerIndex){
          isDealer = true;
        }
        else{
          isDealer = false;
        }

        if(players[(dealerIndex + i) % 4]->make_trump(upCard, isDealer, round, orderUpSuit)){
          cout << *players[(dealerIndex + i) % 4] << " orders up " << orderUpSuit << endl;
          players[dealerIndex]->add_and_discard(upCard);
          determineOrderUpTeam();
        }
        else{
          cout << players[(dealerIndex + i) % 4]->get_name() << " passes" << endl;
        }
      }
      round++;
    }  
*/

  void determineWinningCard(Card ledCard) {
    winningCard = currentTrick[0];
    winningCardIndex = 0;
    for (int i = 1; i < currentTrick.size(); i++) {
      if(Card_less(winningCard, currentTrick[i], ledCard, orderUpSuit)) {
        winningCard = currentTrick[i];
        winningCardIndex = i;
      }
    }
  }

  void play_hand() {
    winnerIndex = (dealerIndex + 1) % 4;
    for (int tricks = 0; tricks < 5; tricks++) {
      Card card_led = players.at(winnerIndex)->lead_card(orderUpSuit);
      cout << card_led << " led by " << *players.at((winnerIndex)) << endl;
      currentTrick.push_back(card_led);

      Card card_played;
      for (int i = 1; i < players.size(); i++) {
        card_played = players.at((winnerIndex + i) % 4)->play_card(card_led,
         orderUpSuit);
        cout << card_played << " played by " << *players.at(((winnerIndex + i) % 4)) 
        << endl;
        currentTrick.push_back(card_played);
      }
      determineWinningCard(card_led);

      winnerIndex = (winnerIndex + winningCardIndex) % 4;
      cout << *players[winnerIndex] << " takes the trick" << endl << endl;
      trickScoreIncrement();
      currentTrick.clear();
    }
    overallScoreIncrement();
    roundsPassed++;
    trickScoreTeam1 = 0;
    trickScoreTeam2 = 0;
  }

  void whoTakesTrick() {
    if (winnerIndex == 0) {
      cout << *players[0] << " takes the trick" << endl;
    }
    else if (winnerIndex == 1) {
      cout << *players[1] << " takes the trick" << endl;
    }
    else if (winnerIndex == 2) {
      cout << *players[2] << " takes the trick" << endl;
    }
    else if (winnerIndex == 3) {
      cout << *players[3] << " takes the trick" << endl;
    }
  }

  void whichTeamWon(){
    if(trickScoreTeam1 > trickScoreTeam2){
      team1WonRound = true;
      team2WonRound = false;
      cout << *players[0] << " and " << *players[2] <<
      " win the hand" << endl;
      }
    else{
      team2WonRound = true;
      team1WonRound = false;
      cout << *players[1] << " and " << *players[3] <<
      " win the hand" << endl;
    }
  }

  void overallScoreIncrement(){
    whichTeamWon();
    if(team1WonRound && orderUpTeam == 1){
      if(trickScoreTeam1 == 3 || trickScoreTeam1 == 4){
        team1score++;
      }
      else{
        team1score+=2;
        cout << "march!" << endl;
      }
    }
    else if (team2WonRound && orderUpTeam == 2){
      if(trickScoreTeam2 == 3 || trickScoreTeam2 == 4){
        team2score++;
      }
      else{
        team2score+=2;
        cout << "march!" << endl;
      }
    }
    else if (team1WonRound && orderUpTeam == 2){
      team1score+=2;
      cout << "euchred!" << endl;
    }
    else if (team2WonRound && orderUpTeam == 1){
      team2score+=2;
      cout << "euchred!" << endl;
    }
  }

 bool winGame() {
   return team1score >= pointsNeededToWin || team2score >= pointsNeededToWin;
   }
};


int main(int argc, char **argv) {
  string pack_filename = argv[1];
  ifstream stream(pack_filename);
  stream.open(pack_filename);
  if(!stream.is_open()) {
    cout << "Error opening " << pack_filename << endl;
    return -1;
  }
  bool noShuffle;
  if(strcmp(argv[2], "shuffle") == 0) {
    noShuffle = true;
  }
  else {
    noShuffle = false;
  }
  int pointsToWin = stoi(argv[3]);
  string p0Name = argv[4];
  string p0Type = argv[5];

  string p1Name = argv[6];
  string p1Type = argv[7];
  
  string p2Name = argv[8];
  string p2Type = argv[9];
  
  string p3Name = argv[10];
  string p3Type = argv[11];

  Player * p0 = Player_factory(p0Name, p0Type);
  Player * p1 = Player_factory(p1Name, p1Type);
  Player * p2 = Player_factory(p2Name, p2Type);
  Player * p3 = Player_factory(p3Name, p3Type);
  vector<Player*> p;
  p.push_back(p0);
  p.push_back(p1);
  p.push_back(p2);
  p.push_back(p3);

  if(pointsToWin < 1 || pointsToWin > 100) {
    cout << "Number of points Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" << endl;
     return -1;
  }

  if (argc != 12) {
    cout << "# arguments Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" << endl;
     return -1;
  }


  if(strcmp(argv[2], "shuffle") != 0 && strcmp(argv[2], "noshuffle") != 0) {
    cout << "shuffle Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" << endl;
    return -1;
  }

  ifstream file(pack_filename);
  if (!file.is_open()) {
    cout << "Error opening " << pack_filename << endl;
  }

  for (int i = 0; i < argc; i++) {
    cout << argv[i] << " ";
  }
  cout << endl;

  Game euchre(p, pointsToWin, noShuffle, stream);
  euchre.play();

}