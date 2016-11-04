#include <stdio.h>
#include <errno.h>

struct pkBtreeKey {
	long key;			// This is the key which create difference
};

struct pkBtreeEntry {
	pkBtreeKey entry;
	int value ;
};

struct pkBtree {
	struct pkBtree *parent;
//	struct pkBtree *root;
	int n;	 // No of nodes
	struct pkBtreeEntry *keyList;	// need to calloc the memory to size of n. Wrapping key with information
	bool leaf;
	struct pkBtree *children;	// n + 1 children
	uint8_t depth;	// Just to keey an information at which depth the node is.
	uint8_t t;	// minimum number of children - degree
};

struct pkBtreeLoc {
	struct pkBtree *loc;
	int index;
};

struct pkBtreeLoc* searchBTree( struct pkBtree *root, struct pkBtreeKey *k ) {
	struct pkBtreeLoc *loc = NULL;
	int i = 0;

	if ( root && pkBtreeKey )
	{
		while (( i <= root->n ) && (k->key > root->keyList[i].entry.key )) {
			i++;
		}
		if ((i < root->n) && (k->key == root->keyList[i].entry.key )) {
			loc->loc = root;
			loc->index = i;
			return loc;
		} else if ( root->leaf ) {
			return NULL;
		} else {
			// Disk read operation in actuals but we are not going to do for this program
			return searchBTree (root->child[i], k);
		}
	}
	return loc;
}

static long keyGenerator = 0;

static inline long getGeneratedKey () {
	return keyGenerator++;
}

struct pkBtree* allocAndInitNode(struct pkBtree *parent, int degree) {

	struct pkBtree *temp = NULL;
	temp = (struct pkBtree *) malloc (sizeof(struct pkBtree));
	if ( temp ) {
		temp->parent = parent;
		temp->keyList = (struct pkBtreeEntry *) calloc ( degree-1, sizeof ( pkBtreeEntry ) );
		temp->leaf = true;
		temp->children = (struct pkBtree *) calloc ( 2 * degree, sizeof( struct pkBtree *) );	// Note we have pointers not the whole node
		temp->depth = 0;
		temp->t = degree;
	}
	return temp;
}

void deleteNode (struct pkBtree *node) {

}

uint8_t splitBtreeNode (struct pkBtreeLoc *loc) {

	struct pkBtree *toSplit = loc->loc->children [loc->index];
	struct pkBtree *temp = NULL;
	int j;
	int t;

	if ( !toSplit )
		return -1;

	temp = allocAndInitNode (toSplit->parent, toSplit->t );
	int j = 0;
	temp->leaf = toSplit->leaf;

	temp->n = toSplit->t - 1;		// Since wei 2*t -1 keys, and we are dividing into nodes with t-1, 1, t-1 keys

	// Copying the t+1 till end to new splitted node
	memcpy (temp->keyList, toSplit->keyList[toSplit->t + 1], toSplit->t - 1);
	bzero (toSplit->keyList[toSplit->t + 1], toSplit->t - 1);
	if ( !toSplit->leaf ) {
		t = toSplit->t;
		for ( j = 1; j <= t ; j++) {
			temp->children[j] = toSplit->children[t+j];
			toSplit->children[t+j] = NULL;
		}
	}

	// Correcting the number of keys in toSplit
	toSplit->n = toSplit->t - 1;

	// Update the parent entry to accomodate the median key.
	{
		// Move the children by 1 to right from loc->index+1
		for ( j = loc->loc->n ; j > loc->index; j-- ) {
			loc->loc->children[j+1] = loc->loc->children[j];
		}
		loc->loc->children[index + 1] = temp;
		// Shifting the element towards right
		memmove( loc->loc->keyList[loc->index+1], loc->loc->keyList[loc->index], loc->loc->n - loc->index + 1);
		// copying the data from toSplit to parent
		memcpy ( loc->loc->keyList[loc->index], toSplit->keyList[toSplit->t], sizeof (struct pkBtree) );
		loc->loc->n++;
	}

	return 0;
}

uint8_t insertValueNonFull ( struct pkBtree *node, struct pkBtreeKey *k ) {

	int n;
	if ( !node )
		return -1;

	n = node->n;

	while ( n > 0 && k->entry->key < node->keyList[n]->entry->key )
		n--;

	n = n + 1;
	if ( node->leaf ) {
		// memmove the entry
		memmove (node->keyList[n+1], node->keyList[n], node->t - n - 1);
		memcpy (node->keyList[n], k, sizeof ( struct pkBtreeKey));
		node->n++;
		return 0;
	} else {
		if (node->children[n]->n == (2 * node->t - 1) ) {
			struct pkBtreeLoc loc = { node, n };

			splitBtreeNode (&loc);
			if (k->entry->key > node->keyList[n]->entry->key)
				n = n + 1;
		}
	}
	return insertValueNonFull ( node->children[n], k );
}


uint8_t insertValue ( struct pkBtree *root, int value) {

	struct pkBtreeKey *key = NULL;

	if ( !root )
		return -1;

	key = (struct pkBtreeKey *)malloc (sizeof (struct pkBtreeKey));

	key->entry.key = getGeneratedKey();
	key->value = value;

	if ( root->n == (2 * root->t - 1) ) {
		struct pkBtreeLoc loc;
		struct pkTree *temp = allocAndInitNode ( root->parent, root->t );

		if ( !temp )
			return -1;

		temp->leaf = false;
		temp->n = 0;
		temp->children[0] = root;

		loc.loc = temp;
		loc.index = 0;

		splitBtreeNode (&loc);

		// Keeping the root address to start
		rootBtree = temp;

		insertValueNonFull ( temp, &key);
	} else {
		insertValueNonFull ( root, &key);
	}
	return 0;
}

/* Just a crude way to start */
static struct pkBtree *rootBtree = NULL;

	/*{
		NULL,
//		&rootBtree,
		0,
		NULL,
		true,
		NULL,
		0,
		2
	};*/


