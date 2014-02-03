#include "tree.h"
Tree::Tree()
{
  root = current = prev = NULL;
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

//returns the next node to have moves generated for it
Move Tree::getNext()//done
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

// data is the data we are putting in the tree
// next is if it should move to the sibling node or not
void Tree::insert( Move newState)
{//TODO
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
    
    root = new Node;
    root -> move = newState;
    current = prev = root;
    root -> p = NULL;
    root -> s = NULL;
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
    prev = current ->children[current -> numChildren];
    current -> numChildren= current -> numChildren + 1;
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

void Tree::clear()// done needs debugging and testing
{
  // if root is already null then it already empty
  if(root == NULL)
  {
    cout<<"the tree is already empty"<<endl;
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
}

ostream& operator<<(ostream& os, const Tree &tree)
{
/*
  if(tree.root == NULL || tree.current == NULL || tree.prev == NULL)
  {
    os<<"Something went wrong and the tree is empty";
  }
  else
  {
    Node *outCurrent = tree.root;
    int counter = 0;
    os<<"Tree output starting: \n";
    
    while(outCurrent != NULL)
    {
      os<<counter++<<": Children:"<<outCurrent -> numChildren<<", state: ";
      os<<outCurrent->board<<"\n";
    }
    
    os<<"Tree output done."<<endl;
    
  }
  
  
  
*/
  return os;
  
}
