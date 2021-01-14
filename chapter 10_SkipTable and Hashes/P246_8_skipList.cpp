#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include "dictionary.h"
#include "skipNode.h"
#include "myExceptions.h"

using namespace std;

template <class K, class E>
class skipList : public dictionary<K, E>
{
public:
   skipList(K, int maxPairs = 10000, float prob = 0.5);
   ~skipList();

   bool empty() const { return dSize == 0; }
   int size() const { return dSize; }
   pair<const K, E> *find(const K &) const;
   void erase(const K &);
   void insert(const pair<const K, E> &);
   void output(ostream &out) const;

protected:
   float cutOff;      // used to decide level number
   int level() const; // generate a random level number
   int levels;        // max current nonempty chain
   int dSize;         // number of pairs in dictionary
   int maxLevel;      // max permissible chain level
   K tailKey;         // a large key
   skipNode<K, E> *search(const K &) const;
   // search saving last nodes seen
   skipNode<K, E> *headerNode; // header node pointer
   skipNode<K, E> *tailNode;   // tail node pointer
   skipNode<K, E> **last;      // last[i] = last node seen on level i
};

template <class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{
   cutOff = prob * RAND_MAX;
   maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
   levels = 0;
   dSize = 0;
   tailKey = largeKey;

   pair<K, E> tailPair;
   tailPair.first = tailKey;
   headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
   tailNode = new skipNode<K, E>(tailPair, 0);
   last = new skipNode<K, E> *[maxLevel + 1];

   for (int i = 0; i <= maxLevel; i++)
      headerNode->next[i] = tailNode;
}

template <class K, class E>
skipList<K, E>::~skipList()
{ // Delete all nodes and array last.
   skipNode<K, E> *nextNode;

   // delete all nodes by following level 0 chain
   while (headerNode != tailNode)
   {
      nextNode = headerNode->next[0];
      delete headerNode;
      headerNode = nextNode;
   }
   delete tailNode;

   delete[] last;
}

template <class K, class E>
pair<const K, E> *skipList<K, E>::find(const K &theKey) const
{
   if (theKey >= tailKey)
      return NULL;

   skipNode<K, E> *beforeNode = headerNode;
   for (int i = levels; i >= 0; i--)
      while (beforeNode->next[i]->element.first < theKey)
         beforeNode = beforeNode->next[i];

   // check if next node has theKey
   if (beforeNode->next[0]->element.first == theKey)
      return &beforeNode->next[0]->element;

   return NULL; // no matching pair
}

template <class K, class E>
int skipList<K, E>::level() const
{
   int lev = 0;
   while (rand() <= cutOff)
      lev++;
   return (lev <= maxLevel) ? lev : maxLevel;
}

template <class K, class E>
skipNode<K, E> *skipList<K, E>::search(const K &theKey) const
{
   skipNode<K, E> *beforeNode = headerNode;
   for (int i = levels; i >= 0; i--)
   {
      while (beforeNode->next[i]->element.first < theKey)
         beforeNode = beforeNode->next[i];
      last[i] = beforeNode; // last level i node seen
   }
   return beforeNode->next[0];
}

template <class K, class E>
void skipList<K, E>::insert(const pair<const K, E> &thePair)
{
   if (thePair.first >= tailKey) // key too large
   {
      ostringstream s;
      s << "Key = " << thePair.first << " Must be < " << tailKey;
      throw illegalParameterValue(s.str());
   }
   
   skipNode<K, E> *theNode = search(thePair.first);

   int theLevel = level(); // level of new node
   // fix theLevel to be <= levels + 1
   if (theLevel > levels)
   {
      theLevel = ++levels;
      last[theLevel] = headerNode;
   }

   // get and insert new node just after theNode
   skipNode<K, E> *newNode = new skipNode<K, E>(thePair, theLevel + 1);
   for (int i = 0; i <= theLevel; i++)
   { // insert into level i chain
      newNode->next[i] = last[i]->next[i];
      last[i]->next[i] = newNode;
   }

   dSize++;
   return;
}

template <class K, class E>
void skipList<K, E>::erase(const K &theKey)
{                         // Delete the pair, if any, whose key equals theKey.
   if (theKey >= tailKey) // too large
      return;
   while (1)
   {
      // see if matching pair present
      skipNode<K, E> *theNode = search(theKey);
      if (theNode->element.first != theKey) // not present
         return;

      // delete node from skip list
      for (int i = 0; i <= levels &&
                      last[i]->next[i] == theNode;
           i++)
         last[i]->next[i] = theNode->next[i];

      // update levels
      while (levels > 0 && headerNode->next[levels] == tailNode)
         levels--;

      delete theNode;
      dSize--;
   }
}

template <class K, class E>
void skipList<K, E>::output(ostream &out) const
{ // Insert the dictionary pairs into the stream out.
   // follow level 0 chain
   for (skipNode<K, E> *currentNode = headerNode->next[0];
        currentNode != tailNode;
        currentNode = currentNode->next[0])
      out << currentNode->element.first << " "
          << currentNode->element.second << "  ";
}

// overload <<
template <class K, class E>
ostream &operator<<(ostream &out, const skipList<K, E> &x)
{
   x.output(out);
   return out;
}

int main()
{
   skipList<int, int> z(1000);
   pair<int, int> p;

   p.first = 2;
   p.second = 10;
   z.insert(p);
   p.first = 10;
   p.second = 50;
   z.insert(p);
   p.first = 6;
   p.second = 30;
   z.insert(p);
   p.first = 6;
   p.second = 35;
   z.insert(p);
   p.first = 8;
   p.second = 40;
   z.insert(p);
   p.first = 1;
   p.second = 5;
   z.insert(p);
   p.first = 12;
   p.second = 60;
   z.insert(p);
   cout << "数对为： " << z << endl;
   cout << "大小是： " << z.size() << endl;

   cout << "关键值为1的值是" << z.find(1)->second << endl;
   cout << "关键字为6的一个值是" << z.find(6)->second << endl;
   cout << "关键字为12的一个值是" << z.find(12)->second << endl;

   z.erase(1);
   z.erase(2);
   z.erase(6);
   z.erase(12);
   cout << "删除关键字 1, 2, 6, 12" << endl;
   cout << "数对是： " << z << endl;
   cout << "大小为： " << z.size() << endl;
}