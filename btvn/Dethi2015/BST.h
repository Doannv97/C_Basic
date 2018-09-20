#define MAX 30

typedef int keyType;

typedef struct _node{
	keyType key;
	char dochoi[MAX];
	struct _node* left,*right;
}node;

typedef node* BSTree;

node* makeNode(keyType key, char dochoi[]); //Tao 1 node moi 

int insertNode(BSTree* Root, keyType key, char dochoi[]); // Chen 1 node vao BST

node* search(BSTree Root, keyType key); // Tra ve dia chi key can tim

node* findMax(BSTree Root);
node* findMin(BSTree Root);

node* deleteNode(BSTree Root, keyType key);

void printInorder(BSTree Root);






