typedef struct Node {
	int data;
	struct Node *left, *right;
}Node;

typedef struct Stack {
	Node *item;
	struct Stack *next;
}Stack;

typedef struct map {
	Node *key, value;
	struct map *next;
}Map;

void printTopToLeaf(Node *ptr, Map *m) {
	/* TODO
	 * create a stack and walk through parents using Map m and ptr as start.
	 * Print the stack
	 */
}

void PrintRootToLeftIterative (Node *root) {

	Node *ptr = root;

	Stack S = CreateEmptyStack();
	Map *m = CreateEmptyMap();

	S.push(ptr);

	while ( !S.isEmpty() ) {
		ptr = S.pop();
		if ( ptr ) {
			if ( !ptr->left && !ptr->right ) {
				/* How to keep track of each list
				 * a) Create a key pair mapping for each node with parent
				 */
				printTopToLeaf(ptr, m);
				ptrintf ("\n");
			}
			else if ( ptr->left ) {
				m.insert(ptr->left, parent);
				S.push(ptr->left);
			}
			else if ( ptr-> right ) {
				m.insert(ptr->right, parent);
				S.push(ptr->right);
			}
		}
	}

}
