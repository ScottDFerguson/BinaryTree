// ------------------------------------------------ bintree.h -------------------------------------------------------
// Scott Ferguson CSS 343
// 10-11-2015
// 10-24-2015
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To provide the structure for bintree.cpp. This program is designed to use binary search trees
// --------------------------------------------------------------------------------------------------------------------
// Assumptions-Trees will be stored with each node having at most two children
// The root is the first node, with its left node being left, and right node being right
// Only Integers will be stored in the trees
// --------------------------------------------------------------------------------------------------------------------
#include "nodedata.h"

class BinTree 
{ 
   //Overloaded << operator
   //Displays contents of entire BST inorder
   friend ostream& operator<<(ostream&, const BinTree&);

//---------------------------------------------------------
public:

   // Constructors and destructor
   BinTree(); // constructor
   BinTree(const BinTree&); // Copies the passed in tree
   ~BinTree(); // Destructor

   // Functions that the BST can use
   bool isEmpty() const; 
   void makeEmpty(); 
   bool insert(NodeData*);
   bool retrieve(const NodeData &, NodeData*&) const;
   int getHeight(const NodeData &) const; 
   void displaySideways() const; 
   void bstreeToArray(NodeData* []); 
   void arrayToBSTree(NodeData* []); 

   //Overloaded operators
   BinTree& operator=(const BinTree&); 
   bool operator==(const BinTree&) const; 
   bool operator!=(const BinTree&) const;  
   
private:

   // Struct holds pointers to data and left/right ancestors
   struct Node
      {
         NodeData* data; // Pointer to data contained in NodeData
         Node* left, *right; // Left, right child pointers 
      };

   Node *root; // Root of the tree
   
   // Utility functions
   void copyTreeRecursively(Node*, Node*&) const; 
   void destroyTreeRecursively(Node*&); 
   bool checkEqualityRecursively(Node*, Node*) const; 
   void inOrderDisplay(Node*) const; 
   int getHeightRecursively(Node*, const NodeData &) const;  
   int NodeHeight(Node*) const; 
   void bstreeToArrayRecursively(Node*, NodeData* [], int&);    
   void arrayToBSTreeRecursively(Node *&, NodeData * [], int , int); 
   void sideways(Node*, int) const; 
};