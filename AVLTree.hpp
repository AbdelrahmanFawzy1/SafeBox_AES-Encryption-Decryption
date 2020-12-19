#include "AVLNode.hpp"
/****************************************************************************************/
/*                                 AVLTree Prototype                                    */
/****************************************************************************************/
template <typename ITEM>
class AVLTree : public BinarySearchTree<AVLNode<ITEM>, ITEM>
{
private:
	AVLNode <ITEM> * updateHeightAndEvaluateBalance(AVLNode <ITEM> * n);
	void rotateWithLeftChild(AVLNode <ITEM> * p);
	void rotateWithRightChild(AVLNode <ITEM> * p);
	void doubleRotateWithLeftChild(AVLNode <ITEM> * p);
	void doubleRotateWithRightChild(AVLNode <ITEM> * p);
	int min;
	int max;
public:
	AVLTree();
	AVLNode <ITEM> * insert(const ITEM & item);
	bool remove(const ITEM & item);
	void traverse(AVLNode <ITEM> * n = NULL, int depth = 0);
	void printStats();
	~AVLTree();
};

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                               AVLTree Implementation                                 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

template <typename ITEM>  AVLNode <ITEM> * AVLTree<ITEM>::updateHeightAndEvaluateBalance(AVLNode <ITEM> * n)
{
	if (n == NULL) return NULL;
	n->setHeight(MAX(HEIGHT(n->getLeft()), HEIGHT(n->getRight())) + 1);
	if (!(HEIGHT(n->getLeft()) - HEIGHT(n->getRight()) > 1 || HEIGHT(n->getRight()) - HEIGHT(n->getLeft()) > 1))
		return updateHeightAndEvaluateBalance(n->getParent());
	else return n;
}
template <typename ITEM> void AVLTree<ITEM>::rotateWithLeftChild(AVLNode <ITEM> * p)
{
	if (p->getParent()==NULL){
	cout << "p is the parent \n";
	
	this->root = p->getLeft();
	p->setParent(p->getLeft());
p->getLeft()->setParent(NULL);
	this->root->setRight(p);	


	this->root->getLeft()->setLeft(NULL);
	this->root->getLeft()->setRight(NULL);
	p->setRight(NULL);
	p->setLeft(NULL);

	cout << "all is done in case 1\n";

	
}
	else 
		{

std::cout << " FINE " << std::endl; 
			if (p->getLeft()->getRight()==p)
			{
				p->getParent()->setRight(p->getLeft());
				p->getLeft()->setParent(p->getParent());
				p->setParent(p->getLeft());
				p->getLeft()->setRight(p);
				//p->setRight(NULL);
				p->setLeft(NULL);
	
			}
			else
			{
				p->getParent()->setLeft(p->getLeft());
				p->getLeft()->setParent(p->getParent());
				p->setParent(p->getLeft());
				p->getLeft()->setRight(p);
				//p->setRight(NULL);
				p->setLeft(NULL);
				
			}
			//p->setLeft(NULL);
		}	
        p->setHeight(MAX(HEIGHT(p->getLeft()),HEIGHT(p->getRight()))+1);
        p->getParent()->setHeight(MAX(HEIGHT(p->getParent()->getLeft()),HEIGHT(p->getParent()->getRight()))+1);

	
}

template <typename ITEM> void AVLTree<ITEM>::rotateWithRightChild(AVLNode <ITEM> * p)
{
if(p->getParent()==NULL){
	cout << "p is the parent \n";
	this->root = p->getRight();
	p->setParent(p->getRight());
p->getRight()->setParent(NULL);
        p->getRight()->setLeft(p);
	cout << "all done in case 4 \n";
	
	this->root->getRight()->setLeft(NULL);
cout << " Aww" << endl; 
        this->root->getRight()->setRight(NULL);
cout << " Aww" << endl; 
        p->setRight(NULL);
        p->setLeft(NULL);

}
	else 
		{
        std::cout<<"g";
			if (p->getLeft()->getRight()==p)
			{
				p->getParent()->setRight(p->getRight());
				p->getRight()->setParent(p->getParent());
				p->setParent(p->getRight());
				p->getRight()->setLeft(p);
				p->setRight(NULL);
				//p->setLeft(NULL);
	
			}
			else 
			{
				p->getParent()->setLeft(p->getRight());
				p->getRight()->setParent(p->getParent());
				p->setParent(p->getRight());
				p->getRight()->setLeft(p);
				p->setRight(NULL);
				//p->setLeft(NULL);
				
			}
			//p->setRight(NULL);

		}	
		p->setHeight(MAX(HEIGHT(p->getLeft()),HEIGHT(p->getRight()))+1);
        p->getParent()->setHeight(MAX(HEIGHT(p->getParent()->getLeft()),HEIGHT(p->getParent()->getRight()))+1);
	
}

template <typename ITEM> void AVLTree<ITEM>::doubleRotateWithLeftChild(AVLNode <ITEM> * p)
{
   rotateWithRightChild(p->getLeft());
   rotateWithLeftChild(p);

}
template <typename ITEM> void AVLTree<ITEM>::doubleRotateWithRightChild(AVLNode <ITEM> * p)
{  

 
   	rotateWithLeftChild(p->getRight());
	rotateWithRightChild(p);


}

template <typename ITEM> AVLTree<ITEM>::AVLTree():BinarySearchTree<AVLNode<ITEM>, ITEM>()
{ min = 1000000; max = 0; }
template <typename ITEM> AVLNode <ITEM> * AVLTree<ITEM>::insert(const ITEM & item) {
	AVLNode <ITEM> * avlNode = BinarySearchTree<AVLNode<ITEM>, ITEM>::insert(item);

	while (avlNode != NULL)
	{
		AVLNode <ITEM> * balance_node = updateHeightAndEvaluateBalance(avlNode);
		if (balance_node != NULL)
		{
			if (balance_node->getLeft() != NULL)
			{
				if (HEIGHT(balance_node->getLeft()->getLeft()) >= HEIGHT(balance_node->getLeft()->getRight()))
					rotateWithLeftChild(balance_node); // Insertion into the left sub tree of the left child
				else doubleRotateWithLeftChild(balance_node);
			}
			if (balance_node->getRight() != NULL)
			{
				if (HEIGHT(balance_node->getRight()->getRight()) >= HEIGHT(balance_node->getRight()->getLeft()))
					rotateWithRightChild(balance_node);  // Insertion into the right sub tree of the right child
				else doubleRotateWithRightChild(balance_node);
			}
		}
		avlNode = balance_node;
	}
	return avlNode;
}
template <typename ITEM> void AVLTree<ITEM>::traverse(AVLNode <ITEM> * n, int depth)
{
	if (n == NULL) n = this->root;
	depth++;
	if (ISLEAF(n))
	{
		if (max < depth) max = depth;
		if (min > depth) min = depth;
		return;
	}
	if (n->getLeft() != NULL) traverse(n->getLeft(), depth);
	if (n->getRight() != NULL) traverse(n->getRight(), depth);
}
template <typename ITEM> void AVLTree<ITEM>::printStats()
{
	cout << "Min:" << min << endl;
	cout << "Max:" << max << endl;
}
template <typename ITEM> bool AVLTree<ITEM>::remove(const ITEM & item) {
	return BinarySearchTree<AVLNode<ITEM>, ITEM>::remove(item);
}
template <typename ITEM> AVLTree<ITEM>::~AVLTree(){}

