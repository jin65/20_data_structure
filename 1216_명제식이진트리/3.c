#include <stdio.h>
#include <stdlib.h>
//#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)
#define MALLOC(p, s) \
	if( !( (p) = malloc( s ) ) ){	\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define MAX_STACK_SIZE 100

// tree node & header
typedef struct node *treePointer;
typedef struct node
{
	char data;		// operator or operand in char type
	int value;			// result of operation
	treePointer leftChild, rightChild;
}node;
treePointer root = NULL;

// stack
treePointer stack[MAX_STACK_SIZE];
int top = -1;
void push(treePointer item);
void stackFull();
treePointer pop();
treePointer stackEmpty();

// postfix expression 
char expr[81];
int vtable[8][3] = { 0 };
int tcnt;

// binary tree of an propositional expression
typedef enum { lparen, rparen, or , and, not, eos, operand } precedence;
precedence getToken(char *symbol, int *n);
treePointer createBinTree(void);

// binary tree traversals
void inorder(treePointer ptr);
void eval(treePointer ptr);
void maketable();

int main(void)
{
	FILE *fp;

	if (fopen_s(&fp, "postfix_2.txt", "r"))
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	maketable();
	fgets(expr, 80, fp);
	printf("%-23s : %s\n", "input string(postfix)", expr);

	//	printf("creating its binary tree\n");
	root = createBinTree();

	//	printf("%-23s : ", "inorder traversal");
	//	inorder(root); 	printf("\n\n");

	printf("find true condition \n");
	for (tcnt = 0; tcnt < 8; tcnt++) {
		eval(root);
		//		("result of evaluation : %s\n", ((root->value) ? "TRUE" : "FALSE"));
		if (root->value)
			printf("a=%d, b=%d, c=%d\n", vtable[tcnt][0], vtable[tcnt][1], vtable[tcnt][2]);
	}
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("%d %d %d\n", vtable[i][0],vtable[i][1],vtable[i][2]);
	}
	return 0;
}

void maketable()
{
	int cnt = 8;
	int row, col = 0;

	for (row = 0; row < 8; row++)
	{
		vtable[row][col] = (row >> 2) & 1;
		vtable[row][col + 1] = (row >> 1) & 1;
		vtable[row][col + 2] = (row) & 1;
		col = 0;
	}
}
// create a binary tree from a postfix arithmetic expression
treePointer createBinTree(void)
{
	treePointer pNode;
	precedence token;
	char symbol;
	int n = 0; /* counter for the expression string */
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos)
	{
		if (token == operand)
		{
			// operand node
			MALLOC(pNode, sizeof(*pNode));
			pNode->data = symbol;
			pNode->leftChild = NULL;
			pNode->rightChild = NULL;

			push(pNode); /* stack insert */
		}
		else {
			// operator node
			if (token == not )
			{ // unary operator
				MALLOC(pNode, sizeof(*pNode));
				pNode->data = symbol;			// operator
				pNode->rightChild = pop();	// link operand
				pNode->leftChild = NULL;	// link operand
			}
			else
			{ // binary operator
				MALLOC(pNode, sizeof(*pNode));
				pNode->data = symbol;			// operator
				pNode->rightChild = pop();	// link operand
				pNode->leftChild = pop();		// link operand
			}
			push(pNode);
		}
		token = getToken(&symbol, &n);
	}
	return pop(); /* return result, that is, root pointer */
}

// Program 3.14: Function to get a token from the input string
precedence getToken(char *symbol, int *n)
{ /* get the next token, symbol is the character representation,
	whichis returned, the tokenis represented by its enumerated value,
	which is returned inthe function name */
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
		//case '('		: return lparen;
		//case ')'		:  return rparen;
	case '&': return and;		// use '&' as the logical and(&&) 
	case '|': return or ;		// use '|' as the logical or(||)
	case '~': return not;		// use '~' as the logical not(!)
	case '\0': return eos;
	default: return operand; /* no error checking, default is operand */
	}
}

///////////////////// binary tree traversals //////////////////////////////

// Program 5.1 : Inorder traversal of a binary tree
void inorder(treePointer ptr)
{
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}


void eval(treePointer ptr)
{
	if (ptr)
	{
		eval(ptr->leftChild);
		eval(ptr->rightChild);
		switch (ptr->data)
		{
		case '&':
			ptr->value = ptr->leftChild->value && ptr->rightChild->value;
			break;
		case '|':
			ptr->value = ptr->leftChild->value || ptr->rightChild->value;
			break;
		case '~':
			ptr->value = !(ptr->rightChild->value);
			break;
		case 'a':
			ptr->value = vtable[tcnt][0];
			break;
		case 'b':
			ptr->value = vtable[tcnt][1];
			break;
		case 'c':
			ptr->value = vtable[tcnt][2];
			break;
		default:
			ptr->value = 1;
		}


	}
}

/////////////////////// stack operations ///////////////////////////////////
treePointer pop()
{/* delete and return the top int from the stack */
	if (top == -1)
		return stackEmpty();	/* returns an error key */
	return stack[top--];
}

treePointer stackEmpty()
{
	treePointer item;
	item = NULL;  // error key value - null pointer
	return item;
}

void push(treePointer item)
{/* add an item to the global stack */
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}

void stackFull()
{
	fprintf(stderr, "stack is full, cannot add item\n");
	exit(EXIT_FAILURE);
}
