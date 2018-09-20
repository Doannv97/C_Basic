#define MAX 20 

typedef char keyType;

typedef struct _node{
	keyType key[MAX];
	char password[MAX];
	struct _node* left,*right;
}node;

typedef node* BSTree;

int stringcmp(char a[], char b[]);

node* makeNode(keyType key[], char vn[]); 

int insertNode(BSTree* Root, keyType key[],char password[]); 

node* search(BSTree Root, keyType key[]);

node* findMax(BSTree Root);
node* findMin(BSTree Root);

node* deleteNode(BSTree Root, keyType key[]);

int highTree(BSTree Root);

void printInorder(BSTree Root);
void printPreorder(BSTree Root);
void printPosorder(BSTree Root);
