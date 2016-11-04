typedef struct Node {
	int data;
	struct Node *left, *right;
};

void BToDLL ( Node *root, Node **head ) {
	if ( !root ) {
		return;
	}

	BToDLL ( root->right, head );

	root->right = *head;

	if ( *head ) {
		(*head)->left = root;
	}

	*head = root;

	BToDLL ( root->left, head );
}
