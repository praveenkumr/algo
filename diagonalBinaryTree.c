/* A binary tree node
struct Node
{
    int data;
    struct Node* left, * right;
}; */


void diagonalPrint(Node *root)
{
    Queue *Q = NULL;
    if (!root) {
        return;
    }

    Q = CreateEmptyQueue ();

    Q.EnQueue (root);

    while ( !Q.isEmpty() ) {
        Node *ptr = Q.deQueue();
        do {
            if ( ptr->left ) {
                Q.EnQueue(ptr->left);
            }
            printf ( "%d ", ptr->data);
            ptr= ptr->right;
        }while ( ptr && ptr->right );
    }

}
