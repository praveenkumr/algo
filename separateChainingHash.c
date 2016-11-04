// Load factor = ( number of elements in hash table ) / ( size of the hash table )

#define LOAD_FACTOR		20

typedef struct LinkedNode {
	int key;
	int value;
	struct LinkedNode *next;
}LinkedNode;

typedef HashTableNode {
	int bCount;
	LinkedNode *next;
}HashTableNode;

typedef HastTable {
	int size;
	int count;
	HashTableNode **Table;
}HashTable;

// Create
HastTable *CreateHashTable (int size) {
	HastTable *h = NULL;
	int i ;

	h = ( HashTable * ) malloc ( sizeof(HashTable) );

	if ( !h )
		return NULL;

	h->size = size;
	h->count = 0;
	h->Table = ( HashTableNode ** ) malloc ( sizeof(HashTableNode) * h->size );

	if ( !h->Table ) {
		free(h);
		return NULL;
	}
	// memset the memory
	for ( i = 0 ; i < size ; i++ ) {
		h->Table[i]->next = NULL;
		h->Table[i]->bCount = 0;
	}
	return h;
}

// Search
int HashSearch ( HashTable *h, int val ) {

}
// Insert
int HashInsert ( HashTable *h, int val ) {

}
// Delete
int HashDelete ( HashTable *h, int val ) {

}
// Rehash
int ReHash ( HashTable *h ) {

}

