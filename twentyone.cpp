/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Markie Wagner
 * USC email: markiero@usc.edu
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

const char* type[13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */




void shuffle(int cards[])
{
  
   for(int i = 51; i > 0; i--)
  {
    int j = rand() % (i+1);  
    int array_val_store_one = cards[j]; 
    cards[j] = cards[i];
    cards[i] = array_val_store_one;
  }


}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
  char suites;

  if(id >= 0 && id <= 12)
  {
    suites = 'H';
  }

  if(id >= 13 && id <= 25)
  {
    suites = 'S';
  }

  if(id >= 26 && id <= 38)
  {
    suites = 'D';
  }

  if(id >= 39 && id <= 51)
  {
    suites = 'C';
  }


  cout << type[id % 13] << "-" << suites << " ";



}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */

int cardValue(int id)
{

  int numeric = value[id % 13];
  return numeric;

}


/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{


  /******** You complete ****************/
  for(int i = 0; i < numCards; i++)
  {
    printCard(i);
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
  int totalval = 0;

  for(int i = 0; i < numCards+1; i++)
  {

        int j =  hand[i];
        totalval += cardValue(j);
      
  }


  if(totalval > 21)
  {
      for(int i = 0; i < numCards+1; i++)
      {
        int j =  hand[i];
        if(cardValue(j) == 11)
        {

          totalval -= 10;
        }
      
      }

  }


  return totalval;

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

  // creates deck
  

  char stillplaying = 'y';

  while(stillplaying == 'y')
  {

    //initalize deck
    for (int q = 0; q < NUM_CARDS; q++)
    { 
      cards[q] = q;
    }

    
    bool playerbust = false;
    bool staying = false;
    char res;
    int plen = 1;
    int deck = 3;
    int dlen = 1;

    shuffle(cards);

    // for(int q = 0; q < NUM_CARDS; q++)
    // {
    //     cout << cards[q] << endl;
    // }


    phand[0] = cards[0];
    phand[1] = cards[2];
    dhand[0] = cards[1];
    dhand[1] = cards[3];


    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << endl;

    
       //say what cards player has
        cout << "Player: ";
        for(int b = 0; b < plen+1; b++)
        {
          printCard(phand[b]);
        }



      while(playerbust == false && staying == false && getBestScore(phand, plen) != 21)
      {

       

        //instruct
        cout << endl;

        cout << "Type 'h' to hit and 's' to stay:" << endl;

        cin >> res;



        //respond to instruction
        if(res == 's')
        {
          staying = true;
        }

        if(res == 'h')
        {

          plen = plen+1;
          deck += 1;
          phand[plen] = cards[deck];

        }

         //say what cards player has
        cout << "Player: ";
        for(int b = 0; b < plen+1; b++)
        {
          printCard(phand[b]);
        }


        

        //deal with result cards
        if(getBestScore(phand, plen) > 21)
        {

         

          cout << "Player busts" << endl;

          playerbust = true;
          cout << "Lose " << getBestScore(phand, plen) << " " << getBestScore(dhand, dlen) << endl;
        }

         if(getBestScore(dhand, dlen) == 21 && getBestScore(phand, plen) == 21)
        {

          playerbust = true;
          cout << "Tie " << getBestScore(phand, plen) << " " << getBestScore(dhand, dlen) << endl;
        }


      
      

      

    }



    

     

    

    //dealer now 

    if(playerbust != true)
    {
       //print out dealers hand
      cout << "Dealer: ";  
      for(int b = 0; b < dlen+1; b++)
      {
            printCard(dhand[b]);
      }

      cout << endl;


      //check if hand over 17 and checks for other hand conditions
      while(getBestScore(dhand, dlen) < 17 && getBestScore(dhand, dlen) <= 21)
      {

        if(getBestScore(dhand, dlen) <= 21 && getBestScore(dhand, dlen) <= 17)
        {
          dlen = dlen+1;
          deck += 1;
          dhand[dlen] = cards[deck];

         

        }

      }

      if(getBestScore(dhand, dlen) > 21)
      {


        cout << "Dealer: ";
          for(int b = 0; b < dlen+1; b++)
          {
              printCard(dhand[b]);
          }
        cout << endl;
        cout << "Dealer busts" << endl;
        cout << "Win" << " " << getBestScore(phand, plen) << " " << getBestScore(dhand, dlen) << endl;
        
      }


      //checks who won

      if(getBestScore(dhand, dlen) > 16 && getBestScore(dhand, dlen) <= 21)
      {
        if(getBestScore(dhand, dlen) > getBestScore(phand, plen))
        {
          cout << "Lose" << " " << getBestScore(phand, plen) << " " << getBestScore(dhand, dlen) << endl;
        }
        if(getBestScore(dhand, dlen) < getBestScore(phand, plen))
        {
          
          cout << "Win" << " " << getBestScore(phand, plen) << " " << getBestScore(dhand, dlen) << endl;
        }
        if(getBestScore(dhand, dlen) == getBestScore(phand, plen))
        {
          cout << "Tie" << " " << getBestScore(phand, plen) <<  " " << getBestScore(dhand, dlen) << endl;
        }

        }




    }

    cout << endl;
    cout << "Play again? [y/n]" << endl;
    cin >> stillplaying;


  }










  return 0;
}

