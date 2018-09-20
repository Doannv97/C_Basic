#define MAX 20 

typedef char keyType;

typedef struct _node{
	keyType key[MAX];
	char vn[MAX];
	struct _node* left,*right;
}node;

typedef node* BSTree;

int stringcmp(char a[], char b[]);

node* makeNode(keyType key[], char vn[]); //Tao 1 node moi 

int insertNode(BSTree* Root, keyType key[],char vn[]); // Chen 1 node vao BST

node* search(BSTree Root, keyType key[]); // Tra ve dia chi key can tim

node* findMax(BSTree Root);
node* findMin(BSTree Root);

node* deleteNode(BSTree Root, keyType key[]);

int highTree(BSTree Root);

void printInorder(BSTree Root);
void printPreorder(BSTree Root);
void printPosorder(BSTree Root);
