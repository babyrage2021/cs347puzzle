//Programmer: Ryan Hoffman
//Date: 2/2/14
//Description: cpp file for the tree class
#include "tree.h"
Tree::Tree(int of)
{
  root = current = prev = NULL;
  OUTFLAG = of;
}

Move Tree::getNext()//FIFO
{ 

  if(root == NULL || current == NULL || prev == NULL)
  {// no solution
    cout<<"Error in getNext() empty tree"<<endl;
    exit(EXIT_FAILURE);
  }
  else if( current -> s == NULL)
  {// no solution
    Move mv;
    mv.index = -10;
    return mv;
  }
  else
  {// otherwise return the sibling
    current = current-> s;  
  }
  
  return current -> move;
}

Move Tree::LIFO()// the new get next
{
  Move mv;
  
  if(current -> numChildren == 0 || current -> currentChild < 0)
  {//no (more) children to search
    if(root != current)
    {// if it is not root
      current = current -> p;
      mv = LIFO();
    }
    else
    {//root, search failed
      mv.index = -11;
    }
  
  }
  else
  {
    Node *temp = current;
    mv = current -> children[current->currentChild] -> move;
    current = current -> children[current->currentChild];//reassigns current
    temp -> currentChild--;
    if(temp -> currentChild <= -1)
    {
      temp -> currentChild = -5;// no more children to search
    }
    
  }

  return mv;
}

void Tree::insert( Move newState)
{
  if(OUTFLAG == 1)
  {
    cout<<"Tree::insert start: "<<newState<<". ";
  }
  
  if(root == NULL)
  {//empty tree
    if(OUTFLAG == 1)
    {
      cout<<"Empty tree. ";
    }
    
    current = prev = root = new Node;
    root -> move = newState;
    root -> p = root -> s = NULL;
    
    if(OUTFLAG == 1)
    {
      cout<<"added root to tree. ";
    }
  }
  else
  { 
    // sets up the new child
    current -> children.push_back(new Node);
    current -> children[current -> numChildren] -> move = newState;
    current -> children[current -> numChildren] -> p = current;
    current -> children[current -> numChildren] -> s = NULL;
    
    // assigns the previous sibling, and updates prev
    prev -> s = current -> children[current -> numChildren];
    prev = current -> children[current -> numChildren];
    current -> currentChild++;//changed here
    current -> numChildren++;//= current -> numChildren + 1;
    
    if(OUTFLAG == 1)
    {
      cout<<"node created. ";
      
    }
  }
  
  if(OUTFLAG == 1)
  {
    cout<<"Tree::insert() stop. "<<endl;
  }
  
}

void Tree::clear()
{
  // if root is already null then it already empty
  if(root == NULL)
  {
    return;
  }
  
  current = root;
  Node *previous;
  
  //scrolls though the nodes via the sibling pointer
  while(current != NULL)
  {//need to check for leaks
    previous = current;
    current = current -> s;
    delete previous;
  }
  
  previous = current = root = NULL;
}

void Tree::getMoveList(vector<Move>& list)
{
  if(current == NULL)
  {
    cout<<"there is no moves to get for the list"<<endl;
    return;
  }
  
  Node *temp = current;// ptr to get currents parents
  
  list.clear();
  
  do
  { 
    list.push_back(temp -> move);
    
    temp = temp -> p;
  }while(temp != NULL);
  
  list.pop_back(); //get rid of root node

  return;
}

//searches for a move. returns true if it found it
/*
bool Tree::search(Move &mv)
{
  Node* oldCurrent = current;
  if( mv == getNext())
  {
    return true;
  }
  else if( current -> s == NULL)
  {
    return false;
  }
  else
  {
    bool retVal = search(mv);
    current = oldCurrent; // resets the current variable
    return retVal;
  }
}

void Tree::graphInsert(Move newState)
{
  if(OUTFLAG == 1)
  {
    cout<<"Tree::insert start: "<<newState<<". ";
  }
  
  if(root == NULL)
  {//empty tree
    if(OUTFLAG == 1)
    {
      cout<<"Empty tree. ";
    }
    
    current = prev = root = new Node;
    root -> move = newState;
    root -> p = root -> s = NULL;
    
    if(OUTFLAG == 1)
    {
      cout<<"added root to tree. ";
    }
  }
  else if( search(newState) == false)
  {// was unable to find the move
    // sets up the new child
    current -> children.push_back(new Node);
    current -> children[current -> numChildren] -> move = newState;
    current -> children[current -> numChildren] -> p = current;
    current -> children[current -> numChildren] -> s = NULL;
    
    // assigns the previous sibling, and updates prev
    prev -> s = current -> children[current -> numChildren];
    prev = current -> children[current -> numChildren];
    current -> currentChild++;//changed here
    current -> numChildren++;//= current -> numChildren + 1;
    
    if(OUTFLAG == 1)
    {
      cout<<"node created. ";
    }
  }
  else
  {
    if(OUTFLAG == 1)
    {
      cout<<"found a repeat state in Tree::Gins()"<<endl;
    }
  
  }
  
  if(OUTFLAG == 1)
  {
    cout<<"Tree::insert() stop. "<<endl;
  }
  
  return;
}

// returns the next best move
Move Tree::getNextMove()
{




}*/