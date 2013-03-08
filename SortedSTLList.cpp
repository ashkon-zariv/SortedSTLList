#include <iostream>
#include <ctime>
#include <string>
#include <list>
#include <stack>
using namespace std;

class Card
{
public:
   enum State {deleted, active};
   enum Suit { clubs, diamonds, hearts, spades };  

private:
   char value;
   Suit suit;
   State state;
   bool errorFlag;
   static bool floatLargestToTop(Card array[], int top);
   static void swap(Card &a, Card &b);

protected:
   static char valueRanks[14];
   static Card::Suit suitRanks[4];
   static int numValsInOrderingArray;

public:
   Card(char value = 'A', Suit suit = spades);
   string toString();
   bool set(char value = 'A', Suit suit = spades);
   void setState(State state);

   char getVal();
   Suit getSuit();
   State getState();
   bool getErrorFlag();
   bool equals(Card card);
   int compareTo(Card &other);
   static void setRankingOrder( char valueOrderArr[], Suit suitOrdeArr[],
      int numCardsInOrderingArray);
   static int getSuitRank(Suit st);
   static int getValueRank(char val);
   static void arraySort(Card array[], int arraySize);
};

class CardWOrderStk: public Card
{
public:
   void pushOrdering();
   void popOrdering();
private:
   class OrderObject
   {
   public:
      static char CardWOrderStk::valueRanks[];
      static Card::Suit CardWOrderStk::suitRanks[];
      static int CardWOrderStk::numValsInOrderingArray;
   };
   static stack<OrderObject> OrderObjects;
};

char Card::valueRanks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T',
   'J', 'Q', 'K', 'A', 'X'};
Card::Suit Card::suitRanks[4] = {Card::clubs, Card::diamonds, Card::hearts,
   Card::spades};
int Card::numValsInOrderingArray = 13;

stack<CardWOrderStk::OrderObject> CardWOrderStk::OrderObjects;
char CardWOrderStk::OrderObject::valueRanks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T',
   'J', 'Q', 'K', 'A', 'X'};
Card::Suit CardWOrderStk::OrderObject::suitRanks[4] = {Card::clubs, Card::diamonds, Card::hearts,
   Card::spades};
int CardWOrderStk::OrderObject::numValsInOrderingArray = 13;


Card generateRandomCard(bool fixedSequence = true);
char turnIntIntoVal(int k);
Card::Suit turnIntIntoSuit(int k);

typedef list<Card> CardList;
void showList(CardList &mylist);
void insert(CardList &mylist, Card &c);
bool remove(CardList &mylist, Card &c);
bool removeAll(CardList &mylist, Card &c);
bool operator==(Card c1, Card c2);

/*int main()
{
   CardList list;
   Card cardsGened[6];

   for(int k = 0; k < 5; k++)
   {
      cardsGened[k] = generateRandomCard(false);
      insert(list, cardsGened[k]);
      insert(list, cardsGened[k]);
   }

   showList(list);
   
   for(int i = 0; i < 2; i++)
      while(remove(list, cardsGened[i]));

   showList(list);

   if(!removeAll(list, cardsGened[2]) || !removeAll(list, cardsGened[0]))
      cout << "Attempted remove failed" << endl;
   showList(list);
}*/

int main()
{
   CardList list1, list2;
   Card insrtcard;
   CardWOrderStk CardOrder;
   char valueOrder[] = {'3', '4', '5', '6', '7', '8', '9', 'T', 'J',
      'Q', 'K', 'A', '2'};
   Card::Suit suitOrder[] = {Card::diamonds, Card::clubs, 
      Card::hearts, Card::spades};
   int numVals = 13;

   for(int k = 0; k < 20; k++)
   {
      insrtcard = generateRandomCard(false);
      insert(list1, insrtcard);
      CardOrder.pushOrdering();
      Card::setRankingOrder(valueOrder, suitOrder, numVals);
      insert(list2, insrtcard);
      CardOrder.popOrdering();
   }

   showList(list1);
   showList(list2);
}

void insert(CardList &mylist, Card &c)
{
   list<Card>::iterator iter;

   for( iter = mylist.begin() ; iter != mylist.end() ; iter++)
      if ( c.compareTo(*iter) < 0)
         break;
   mylist.insert(iter, c);
}

bool remove(CardList &mylist, Card &c)
{
   list<Card>::iterator iter;
   for (iter = mylist.begin(); iter != mylist.end(); iter ++)
      if (c == *iter)
      {
         mylist.erase(iter);
         return true;
      }
   return false;
}

bool removeAll(CardList &mylist, Card &c)
{
   list<Card>::iterator iter;

   for (iter = mylist.begin(); iter != mylist.end(); iter ++)
   {
      if (c == *iter)
      {
         mylist.remove(c);
         return true;
      }
   }
   return false;
}

void showList(CardList &mylist)
{
   list<Card>::iterator iter;
   Card card;

   cout << endl << "__List Start__" << endl;

   for( iter = mylist.begin(); iter != mylist.end(); iter++)
   {
      card = *iter;
      cout << "[" << card.toString() << "] ";
   }
   
   cout << endl << "___List End___" << endl << endl;
}

bool operator==(Card c1, Card c2)
{
   if(c1.compareTo(c2) == 0)
      return true;
   return false;
}
   
Card generateRandomCard(bool fixedSequence)
{
   static bool firstTime = true;
   Card::Suit suit;
   char val;

   int suitSelector, valSelector;


   if (firstTime)
   {
      firstTime = false;
      if (fixedSequence)
         srand(1);
      else
         srand(time(NULL));
   }

   suitSelector = rand() % 4;
   valSelector = rand() % 13;

   suit = turnIntIntoSuit(suitSelector);
   val = turnIntIntoVal(valSelector);

   return Card(val, suit);
}

void CardWOrderStk::pushOrdering()
{
   OrderObject orderobj;
   OrderObjects.push(orderobj);
}

void CardWOrderStk::popOrdering()
{
   OrderObject orderobj;
   OrderObjects.top() = orderobj;
   setRankingOrder(orderobj.valueRanks, orderobj.suitRanks,
      orderobj.numValsInOrderingArray);
   OrderObjects.pop();
}

Card::Suit turnIntIntoSuit(int k)
{
   return (Card::Suit) k;
}

char turnIntIntoVal(int k)
{
   k++;
   switch(k)
   {
   case 1:
      return 'A';
   case 10:
      return 'T';
   case 11:
      return 'J';
   case 12:
      return 'Q';
   case 13:
      return 'K';
   default:
      return '0' + k;
   }
}

Card::Card(char value, Suit suit)
{
   set(value, suit);
}

string Card::toString()
{
   string retVal;
   char strVal[2];

   if (errorFlag)
      return "** illegal **";
   if (state == deleted)
      return "( deleted )";

   if (value != 'X')
   {
      strVal[0] = value;
      strVal[1] = '\0';
      retVal = string(strVal);

      if (suit == spades)
         retVal += " of Spades";
      else if (suit == hearts)
         retVal += " of Hearts";
      else if (suit == diamonds)
         retVal += " of Diamonds";
      else if (suit == clubs)
         retVal += " of Clubs";
   }
   else
   {
      retVal = "joker";

      if (suit == clubs)
         retVal += " 1";
      else if (suit == diamonds)
         retVal += " 2";
      else if (suit == hearts)
         retVal += " 3";
      else if (suit == spades)
         retVal += " 4";
   }

   return retVal;
}

bool Card::set(char value, Suit suit)
{
   char upVal;
   upVal = toupper((int)value);

   if (
      upVal == 'A' || upVal == 'K'
      || upVal == 'Q' || upVal == 'J'
      || upVal == 'T' || upVal == 'X'
      || (upVal >= '2' && upVal <= '9')
      )
   {
      errorFlag = false;
      state = active;
      this->suit = suit;
      this->value = upVal;
      return true;
   }
   else
   {
      errorFlag = true;
      return false;
   }
}

void Card::setState( Card::State state)
{
   this->state = state;
}

char Card::getVal()
{
   return value;
}

Card::Suit Card::getSuit()
{
   return suit;
}

Card::State Card::getState()
{
   return state;
}

bool Card::getErrorFlag()
{
   return errorFlag;
}

bool Card::equals(Card card)
{
   if (this->value != card.value)
      return false;
   if (this->suit != card.suit)
      return false;
   if (this->deleted != card.deleted)
      return false;
   if (this->state != card.state)
      return false;
   return true;
}

void Card::setRankingOrder( char valueOrderArr[], Suit suitOrdeArr[],
      int numValsInOrderingArray  )
{
   int k;
   if (numValsInOrderingArray  < 0 || numValsInOrderingArray  > 13)
      return;

   Card::numValsInOrderingArray = numValsInOrderingArray;

   for (k = 0; k < numValsInOrderingArray ; k++)
      Card::valueRanks[k] = valueOrderArr[k];

   for (k = 0; k < 4; k++)
      Card::suitRanks[k] = suitOrdeArr[k];
}

int Card::getSuitRank(Suit st)
{
   int k;

   for (k = 0; k < 4; k++)
      if (suitRanks[k] == st)
         return k;
   return 0;
}

int Card::getValueRank(char val)
{
   int k;

   for (k = 0; k < numValsInOrderingArray; k++)
      if (valueRanks[k] == val)
         return k;
   return 0;
}

void Card::arraySort(Card array[], int arraySize)
{
    for (int k = 0; k < arraySize; k++)
       if (!floatLargestToTop(array, arraySize - 1 - k))
          return;
}

bool Card::floatLargestToTop(Card array[], int top)
{
   bool changed = false;
   
   for (int k = 0; k < top; k++)
      if (array[k].compareTo(array[k+1]) > 0)
      {
         swap(array[k], array[k+1]);
         changed = true;
      };
   return changed;
}

void Card::swap(Card &a, Card &b)
{
   Card temp;

   temp = a;
   a = b;;
   b = temp;
}

int Card::compareTo(Card &other)
{
   if (this->value == other.value)
      return (getSuitRank(this->suit) - getSuitRank(other.suit) );

   return (getValueRank(this->value) - getValueRank(other.value));
}