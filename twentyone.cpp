/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Sophia Akhavan
 * USC email: sakhavan@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  int temp;
  int j;
  for(int i=51; i>0; i--){
    j=rand()%(i+1); //0<=j<=i
    temp=cards[i];
    cards[i]=cards[j];
    cards[j]=temp;
  }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id) //id is whatever card between 0-51
{
  /******** You complete ****************/
  int modten=id%13;
  int divten=id/13;

  for(int i=0; i<13;i++){
    if(modten==i){
      cout<<type[i]<<"-";
    }
  }
  for(int i=0; i<4; i++){
    if(divten==i){
      cout<<suit[i];
    }
  }
  cout << " ";
  
}


/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  return value[id%13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for(int i=0; i<numCards; i++){
    printCard(hand[i]);
    cout << " ";
  }
  cout << endl;

}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int score=0;
  int ace=0;
  for(int i=0; i<numCards; i++){
    score+=cardValue(hand[i]);
    if(cardValue(hand[i])==11){
      ace++;
    }
  }
  while(ace>0 && score>21){
    score-=10;
    ace--;
  }
  return score;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  char yn;
  int flag=0;
  while(flag==0){
    for(int i=0; i<52; i++){ //initialize cards
      cards[i]=i;
    }
    int phandsize=2;
    int dhandsize=2;
    shuffle(cards);
    for(int i=0; i<2;i++){ //give 2 cards to player and dealer in alternating order
      phand[i]=cards[2*i]; //cards at 0,2 (1st and 3rd cards)
      dhand[i]=cards[(2*i)+1];//cards at 1,3 (2nd and 4th cards)
    }
    cout << "Dealer: " << "?" << " ";
    printCard(dhand[1]);
    cout << endl;
    cout << "Player: ";
    printHand(phand,2);
    while(getBestScore(phand,phandsize)<21){
      char hs;
      cout << "Type 'h' to hit and 's' to stay:" << endl;
      cin >> hs;
      if(hs=='h'){
        phand[phandsize]=cards[phandsize+2]; //5th card into 3rd element of phand
        phandsize++;
        cout << "Player: ";
        printHand(phand,phandsize);
      }
      else break;
    }
    if(getBestScore(phand,phandsize)>21){ //if player busts
      cout << "Player busts" << endl;
      cout << "Lose " << getBestScore(phand,phandsize) << " ";
      cout << getBestScore(dhand,dhandsize) << endl;
    }
    else if(getBestScore(phand,phandsize)<=21){ //if player has not busted and chose 's'
      while(getBestScore(dhand,dhandsize)<17){//dealer has not busted
        dhand[dhandsize]=cards[dhandsize+phandsize]; //dealer draws from deck
        dhandsize++;
      }
      cout << "Dealer: ";
      printHand(dhand,dhandsize);
      if(getBestScore(dhand,dhandsize)>21){ //dealer busts
        cout << "Dealer busts" << endl;
        cout << "Win ";
        cout << getBestScore(phand,phandsize) << " " << getBestScore(dhand,dhandsize);
        cout << endl;
      }
      //if neither player nor dealer bust and player score > dealer score
      else if(getBestScore(phand,phandsize)>getBestScore(dhand,dhandsize)){
        cout << "Win ";
        cout << getBestScore(phand,phandsize) << " " << getBestScore(dhand,dhandsize);
        cout << endl;
      }
      //if neither bust and player score < dealer score
      else if(getBestScore(phand,phandsize)<getBestScore(dhand,dhandsize)){
        cout << "Lose ";
        cout << getBestScore(phand,phandsize) << " ";
        cout << getBestScore(dhand,dhandsize) << endl;
      }
      //if tied
      else{
        cout << "Tie ";
        cout << getBestScore(phand,phandsize) << " " << getBestScore(dhand,dhandsize);
        cout << endl;
      }
    }
    cout << "Play again? [y/n]" << endl;
    cin >> yn;
    if(yn == 'n'){
      flag=1;
    }
  }



  return 0;
}
