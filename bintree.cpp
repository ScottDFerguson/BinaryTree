// ------------------------------------------------ bintree.cpp -------------------------------------------------------
// Scott Ferguson CSS 343
// 10-11-2015
// 10-24-2015
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To provide the functions for bintree.h. This program is designed to use binary search trees
// --------------------------------------------------------------------------------------------------------------------
// Assumptions-Trees will be stored with each node having at most two children
// The root is the first node, with its left node being left, and right node being right
// Only Integers will be stored in the trees
// --------------------------------------------------------------------------------------------------------------------
// Note: displaySideways, and sideways were functions given in the supporting files zip folder, they remain 
// completely unchanged
// --------------------------------------------------------------------------------------------------------------------

#include "bintree.h"

// ------------------------------------BinTree()-----------------------------------------------------------------------
// Description: Constructor for the BST
// sets the root to equal Null
// --------------------------------------------------------------------------------------------------------------------
BinTree::BinTree() :root(NULL){ 
} // eoBinTree()

// ------------------------------------BinTree(BinTree)----------------------------------------------------------------
// Description: Constructor for the BST
// calls copyTreeRecursively(Node*, Node*&) to make a deep copy of the tree
// --------------------------------------------------------------------------------------------------------------------
BinTree::BinTree(const BinTree& tree){
   copyTreeRecursively(tree.root, root); // call a recursive function to copy the tree
} // eoBinTree(BinTree)

// -----------------------------------~BinTree()-----------------------------------------------------------------------
// Description: Destructor for the BST
// calls makeEmpty() to delete the tree
// --------------------------------------------------------------------------------------------------------------------
BinTree::~BinTree() {
   makeEmpty(); // call a recursive function to delete the tree
} // eo~BinTree()


// ------------------------------------isEmpty()-----------------------------------------------------------------------
// Description: checks to see if the tree is empty
// --------------------------------------------------------------------------------------------------------------------
bool BinTree::isEmpty() const {
   return (root == NULL);
} // eoisEmpty()

// ------------------------------------makeEmpty()---------------------------------------------------------------------
// Description: calls destroyTreeRecursively(Node*&) to delete the tree
// --------------------------------------------------------------------------------------------------------------------
void BinTree::makeEmpty() {
   destroyTreeRecursively(root); 
} // eomakeEmpty()

// ------------------------------------copyTreeRecursively(Node*, Node*&)----------------------------------------------
// Description: recursively copies one tree to another
// --------------------------------------------------------------------------------------------------------------------
void BinTree::copyTreeRecursively(Node *lhs, Node *& rhs) const {
   // tree is empty
   if (lhs != NULL){ 
      rhs = new Node; // create a new node
      NodeData *temp = new NodeData(*lhs->data); // create a temp node to hold data
      rhs->data = temp; 
      copyTreeRecursively(lhs->left, rhs->left); // go left
      copyTreeRecursively(lhs->right, rhs->right); // go right
   }
   else
   {
      rhs = NULL;  // copy empty tree
   }
} // eocopyTreeRecursively(Node*, Node*&)

// ------------------------------------destroyTreeRecursively(Node*&)--------------------------------------------------
// Description: recursively deletes a tree
// --------------------------------------------------------------------------------------------------------------------
void BinTree::destroyTreeRecursively(Node *& tree) {
   if (tree != NULL){  
      destroyTreeRecursively(tree->left); // destroy left
      destroyTreeRecursively(tree->right); // destroy right

	    delete tree->data; //delete NodeData
      tree->data = NULL;
	    delete tree; // delete Node
      tree = NULL;
   }
} // eodestroyTreeRecursively(Node*&)


// ------------------------------------operator=(BinTree&)-------------------------------------------------------------
// Description: uses copy tree to set one tree to be equal to the other
// --------------------------------------------------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree& rhs) {
   if (this != &rhs){ 
      destroyTreeRecursively(root);  // delete tree
      copyTreeRecursively(rhs.root, root);  // copy tree
   }
   return *this;
} // eooperator=(BinTree&)

// ------------------------------------operator==(BinTree&)-------------------------------------------------------------
// Description: calls checkEqualityRecursively to see if the trees are equal
// ---------------------------------------------------------------------------------------------------------------------
bool BinTree::operator==(const BinTree& rhs) const {
      return checkEqualityRecursively(root, rhs.root); 
} // eooperator==(BinTree&)

// ------------------------------------operator!=(BinTree&)-------------------------------------------------------------
// Description: ckecks to see if the two trees are not equal
// ---------------------------------------------------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree& rhs) const {
   return !(*this == rhs);
} // eooperator!=(BinTree&)

// ------------------------------------checkEqualityRecursively(Node*, Node*)-------------------------------------------
// Description: calls checkEqualityRecursively to see if the trees are equal
// ---------------------------------------------------------------------------------------------------------------------
bool BinTree::checkEqualityRecursively(Node* lhs, Node* rhs) const {

  if ((lhs != NULL && rhs != NULL) && (*lhs->data == *rhs->data)) // data isn't null and data is the same 
     return true;

  if ((lhs == NULL) || (rhs == NULL))  // reached the end 
     return false;

  // check to see if the data is the same and go left, and right
  return ((lhs->data == rhs->data) && checkEqualityRecursively(lhs->left,  rhs->left ) && checkEqualityRecursively (lhs->right, rhs->right));
} // eocheckEqualityRecursively(Node*, Node*)


// ------------------------------------insert(Node*)--------------------------------------------------------------------
// Description: inserts a node containing a value into the tree
// based on the insert function from note 3
// ---------------------------------------------------------------------------------------------------------------------
bool BinTree::insert(NodeData* value) {
    if (isEmpty()) {

        // build new Node
        Node* nodePtr = new Node;
        nodePtr->data = value;
        nodePtr->left = NULL;
        nodePtr->right = NULL;
        
        root = nodePtr;
    }
    else {
        Node* current = root;   
        bool success = false;   // is it inserted
        
        while (!success) {
            if (*value < *current->data) { // less than data
                if (current->left == NULL) {
                    
                    // build new Node
                    Node* nodePtr = new Node;
                    nodePtr->data = value;
                    nodePtr->left = NULL;
                    nodePtr->right = NULL;
                    
                    current->left = nodePtr; // found
                    success = true;
                }
                else {
                    current = current->left;   // go left
                }
            }
            else if (*value > *current->data) { // greater than data
                if (current->right == NULL) {
                    
                    // build new Node
                    Node* nodePtr = new Node;
                    nodePtr->data = value;
                    nodePtr->left = NULL;
                    nodePtr->right = NULL;
                    
                    current->right = nodePtr; // found
                    success = true;
                }
                else {
                    current = current->right;  // go right
                }
            }
            else {
                return false;
            }
        }
    }
    return true;
} // eoinsert(Node*)

// ------------------------------------retrieve(Node&, Node*&)----------------------------------------------------------
// Description: retrieves a node and makes result point to it
// ---------------------------------------------------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &search, NodeData *&result) const {
    result = NULL; // if never found
    
    if (!isEmpty()) {
        
        Node* current = root;   
        bool stop = false;      
        
        while (!stop) {
            if (*current->data != search) {
                if (search < *current->data) {
                    if (current->left == NULL) {     // reached end
                        stop = true;
                        return false;
                    }
                    else
                        current = current->left;     // go left
                }
                else {
                    if (current->right == NULL) {    // reached end
                        stop = true;
                        return false;
                    }
                    else
                        current = current->right;    // go right
                }
            }
            else {
                stop = true;
                result = current->data;
                return true;
            }
        }
    }
    return false;
} // eoretrieve(Node&, Node*&)

// ------------------------------------getHeight(Node&)-----------------------------------------------------------------
// Description: calss a recursive function to get the height of a node
// ---------------------------------------------------------------------------------------------------------------------
int BinTree::getHeight(const NodeData &value) const {
    return getHeightRecursively(root, value);
} // eogetHeight(Node&)

// ------------------------------------getHeightRecusively(Node*, Node&)------------------------------------------------
// Description: gets the node then calls a function that gets the height
// ---------------------------------------------------------------------------------------------------------------------
int BinTree::getHeightRecursively(Node* current, const NodeData &value) const {
    
    if (current == NULL) {
        return 0;
    }
    else if (value == *current->data) {
        return NodeHeight(current); // gets the height
    }
    else {
        int left = getHeightRecursively(current->left, value);     // go left
        int right = getHeightRecursively(current->right, value);   // go right
        
        return left + right;     
    }
} // eogetHeightRecusively(Node*, Node&)

// ------------------------------------nodeHeight(Node*)----------------------------------------------------------------
// Description: finds the height of the node
// ---------------------------------------------------------------------------------------------------------------------
int BinTree::NodeHeight(Node* current) const {

    if (current == NULL) {
        return 0;
    }
    else {
        int left = NodeHeight(current->left);    // go left
        int right = NodeHeight(current->right);  // go right
        
        return max(left, right) + 1;
    }
} // eonodeHeight(Node*)

// ------------------------------------bstreeToArray(NodeData* [])------------------------------------------------------
// Description: calls a recursive function that turns a BST into an array
// ---------------------------------------------------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* treeArray[]){
	int index = 0;

	bstreeToArrayRecursively(this->root, treeArray, index);
	destroyTreeRecursively(this->root); // remove tree
} // eobstreeToArray(NodeData* [])

// ------------------------------------bstreeToArrayRecursively(Node*, NodeData* [], int&)-----------------------------------
// Description: recursively turns a BST into an array
// ---------------------------------------------------------------------------------------------------------------------
void BinTree::bstreeToArrayRecursively(Node* current, NodeData* treeArray[], int& index) {
	if (current != NULL){ // not null
		  bstreeToArrayRecursively(current->left, treeArray, index); // go left
			treeArray[index] = current->data; // put current into the array
			current->data = NULL;	
			index++; // move the index
		bstreeToArrayRecursively(current->right, treeArray, index); // go right
	}
} // eobstreeToArrayRecursively(Node*, NodeData* [], int& )

// ------------------------------------arrayToBSTree(NodeData* [])------------------------------------------------------
// Description: calls a recursive function that turns a sorted array into a BST
// ---------------------------------------------------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* sortedArray[]){
	int low = 0;
	int high = 0;

	for (int i = 0; i < 100; i++){ // specified length in the instructions
		if (sortedArray[i] != NULL)
			high++;
	}
	
	if (isEmpty()){ // if the tress is empty
	arrayToBSTreeRecursively(this->root, sortedArray, low, high-1);
	}
	else { // the tree is not empty, so make it empty
		destroyTreeRecursively(this->root);
		arrayToBSTreeRecursively(this->root, sortedArray, low, high-1);
	}
} // eoarrayToBSTree(NodeData* [])

// ------------------------------------arrayToBSTreeRecursively(*&, NodeData * [], int , int)----------------------------
// Description: recursively turns a sorted array into a BST
// ---------------------------------------------------------------------------------------------------------------------
void BinTree::arrayToBSTreeRecursively(Node *& current, NodeData * sortedArray[], int low, int high){
	if (low > high) {
		current = NULL;
	} 
	else{
		int binIndex = (low + high) / 2; // find the correct index to put in the tree
	  NodeData* temp; // temp Node
	  temp = sortedArray[binIndex]; // temp equals the value in the array
	  sortedArray[binIndex] = NULL;
	  insert(temp); // insert the Node

	  arrayToBSTreeRecursively(current->left, sortedArray, low, binIndex - 1 ); // go left
	  arrayToBSTreeRecursively(current->right, sortedArray, binIndex + 1, high); // go right
	}
} // eoarrayToBSTreeRecursively(Node *&, NodeData * [], int , int)

// ------------------------------------displaySideways()----------------------------------------------------------------
// Description: calls a recursive function to display the tree, given function
// ---------------------------------------------------------------------------------------------------------------------
void BinTree::displaySideways() const{
   sideways(root, 0);
}

// ------------------------------------sideways(Node*, int)-------------------------------------------------------------
// Description: recursively displays the tree, given function
// ---------------------------------------------------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const{
   if (current != NULL) {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "    ";
      }

      cout << *current->data << endl;      // display data
      sideways(current->left, level);
   }
}

// ------------------------------------operator<<(ostream&, const BinTree&)---------------------------------------------
// Description: calls a recursive function to display the contents of the tree
// ---------------------------------------------------------------------------------------------------------------------
ostream& operator<<(ostream& output, const BinTree& bst){
   bst.inOrderDisplay(bst.root); //call inOrderDisplay
   output << endl;
   return output;
} // eooperator<<(ostream&, const BinTree&)

// ------------------------------------inOrderDisplay(Node*)------------------------------------------------------------
// Description: recursively displays the contents of the tree inorder
// ---------------------------------------------------------------------------------------------------------------------
void BinTree::inOrderDisplay(Node *current) const{
   if (current != NULL) 
   {  
      inOrderDisplay(current->left); // go left
      cout <<*current->data << " "; // print out the contents and a space
      inOrderDisplay(current->right); // go right
   }
} // eoinOrderDisplay(Node*)
