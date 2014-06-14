#include "st.h"

#define UUID_NOT_FOUND -1

#define LEFT 0
#define RIGHT 1

#define LEFTLEFT 0
#define LEFTRIGHT 1
#define RIGHTLEFT 2
#define RIGHTRIGHT 3

int uuid_gen = 0;

SplayTree find_parent (SplayTree st, SplayTree target, int * direction);
SplayTree zigzig (SplayTree root, int mode);
SplayTree zigzag (SplayTree root, int mode);
int linage (SplayTree st, int uuid, SplayTree * balanceRoot);
SplayTree zig (SplayTree st, int uuid);

struct splaytree {
    struct splaytree * left;
    struct splaytree * right;
    int value;
    int uuid;
};

SplayTree splayTree_create (int value) {
    SplayTree st = malloc (sizeof (struct splaytree));
    st->left = NULL;
    st->right = NULL;
    st->value = value;
    st->uuid = uuid_gen++;
    return st;
}

SplayTree splayTree_insert (SplayTree st, int value) {
    // insert as normal
    int uuid_new = 0;
    int found = 0;

    // Make the new node
    SplayTree new = splayTree_create (value);
    uuid_new = new->uuid;

    // Go down the tree till we find the right spot for it
    SplayTree targetNode = st;
    while (found == 0) {
        if (value <= targetNode->value) {
            if (targetNode->left == NULL) {
                targetNode->left = new;
                found = 1;
            } else {
                targetNode = targetNode->left;
            }
        } else {
            if (targetNode->right == NULL) {
                targetNode->right = new;
                found = 1;
            } else {
                targetNode = targetNode->right;
            }
        }
    }

    // perform splays

    // Zig only?
    if ((st->left != NULL && st->left->uuid == uuid_new) ||
        (st->right != NULL && st->right->uuid == uuid_new)) {
        return zig (st, uuid_new);
    } else {
        SplayTree balanceRoot;
        int linageResult = linage (st, uuid_new, &balanceRoot);
        assert (balanceRoot != NULL);
        assert (linageResult != UUID_NOT_FOUND);
        int direction = 0;
        printf ("ROOT VAL %D, BALANCEROOT VAL %D\n", st->value, balanceRoot->value);
        SplayTree parent = find_parent (st, balanceRoot, &direction);
        


        if (parent != NULL) {
            if (linageResult == LEFTLEFT || linageResult == RIGHTRIGHT) {
                SplayTree newBalanced = zigzig (balanceRoot, linageResult);
                
                if (direction == LEFT) {
                    parent->left = newBalanced;
                } else {
                    parent->right = newBalanced;
                }
                if (balanceRoot->uuid == st->uuid) {
                    st = newBalanced;
                }
            } else {
                SplayTree newBalanced = zigzag (balanceRoot, linageResult);

                if (direction == LEFT) {
                    parent->left = newBalanced;
                } else {
                    parent->right = newBalanced;
                }
                if (balanceRoot->uuid == st->uuid) {
                    st = newBalanced;
                }
            }


        }
        

        return st;
    }
}

SplayTree splayTree_delete (SplayTree st, int value) {
    return NULL;
}

void splayTree_print (SplayTree st) {
    return;
}

int splayTree_lookup (SplayTree st, int value) {
    if (st != NULL) {
        if (st->value == value) {
            return VALUE_FOUND;
        } else {
            if (value <= st->value) {
                return splayTree_lookup (st->left, value);
            } else {
                return splayTree_lookup (st->right, value);
            }
        }
    }

    return VALUE_NOT_FOUND;
}

SplayTree zig (SplayTree st, int uuid) {
    // left or right?
    if (st->left != NULL && st->left->uuid == uuid) {
        // keep track of our target
        SplayTree temp = st->left;
        // change root's left to target's right
        st->left = temp->right;
        // change target's right to root
        temp->right = st;
        // make target the new root
        return temp;
    } else {
        // keep track of our target
        SplayTree temp = st->right;
        // change root's right to target's left
        st->right = temp->left;
        // change target's left to root;
        temp->left = st;
        // make target the new root
        return temp;
    }

    return NULL;
}

int linage (SplayTree st, int uuid, SplayTree * balanceRoot) {
    if (st == NULL) return UUID_NOT_FOUND;
    SplayTree parentLeft = st->left;
    SplayTree parentRight = st->right;
    SplayTree childLeftLeft = NULL;
    SplayTree childLeftRight = NULL;
    SplayTree childRightLeft = NULL;
    SplayTree childRightRight = NULL;

    if (parentLeft != NULL) {
        childLeftLeft = parentLeft->left;
        childLeftRight = parentLeft->right;
    }
    if (parentRight != NULL) {
        childRightLeft = parentRight->left;
        childRightRight = parentRight->right;
    }

    if (childLeftLeft != NULL && childLeftLeft->uuid == uuid) {
        *balanceRoot = st;
        return LEFTLEFT;
    } else if (childLeftRight != NULL && childLeftRight->uuid == uuid) {
        *balanceRoot = st;
        return LEFTRIGHT;
    } else if (childRightLeft != NULL && childRightLeft->uuid == uuid) {
        *balanceRoot = st;
        return RIGHTLEFT;
    } else if (childRightRight != NULL && childRightRight->uuid == uuid) {
        *balanceRoot = st;
        return RIGHTRIGHT;
    } else {
        // recurse
        int leftResult = linage (parentLeft, uuid, balanceRoot);
        int rightResult = linage (parentRight, uuid, balanceRoot);

        if (leftResult != UUID_NOT_FOUND) {
            return leftResult;
        } else {
            return rightResult;
        }
    }
    return UUID_NOT_FOUND;
}

SplayTree zigzag (SplayTree root, int mode) {
    if (mode == LEFTRIGHT) {
        // Step 1. Rotate LEFT between target and parent.
        SplayTree parent = root->left;
        SplayTree target = parent->right;

        // parent right is now target's left.
        parent->right = target->left;

        // target's left is now parent
        target->left = parent;

        // root's left is now target not parent
        root->left = target;

        // Step 2. Rotate RIGHT between target and root.
        parent = root;
        // target should still point at target

        // parent's left should be target's right
        parent->left = target->right;

        // target's right should be parent.
        target->right = parent;

        // root is now target not parent.
        root = target;

        return root;
    } else if (mode == RIGHTLEFT) {
        // Step 1. Rotate RIGHT between target and parent
        SplayTree parent = root->right;
        SplayTree target = parent->left;

        // parent left is now target's right
        parent->left = target->right;

        // target's right is now parent
        target->right = parent;

        // root's right is now target not parent
        root->right = target;

        // Step 2. Rotate LEFT between target and root
        parent = root;
        // target should still point to target

        // parent's right should be target's left
        parent->right = target->left;

        // target's right should be parent
        target->left = parent;

        // root is now target not parent
        root = target;

        return root;
    } else {
        assert (0);
    }

    return NULL;
}

SplayTree zigzig (SplayTree root, int mode) {
    if (mode == LEFTLEFT) {
        // Step1. Rotate RIGHT between root and parent
        SplayTree parent = root->left;

        // make root's left now be parent's right;
        root->left = parent->right;

        // make parent's right be root
        parent->right = root;

        // make root now be parent.
        root = parent;

        // Step2. Rotate RIGHT between the new root and root's left. (i.e. target)
        SplayTree target = root->left;

        // set root's left to target's right
        root->left = target->right;

        // set target's right to be root
        target->right = root;

        // now target is root.
        root = target;

        return root;
    } else if (mode == RIGHTRIGHT) {
        // Step1. Rotate LEFT between root and parent
        SplayTree parent = root->right;

        // make root's right now be parent's left;
        root->right = parent->left;

        // make parent's left be root
        parent->left = root;

        // make root now be parent.
        root = parent;

        // Step2. Rotate LEFT between the new root and root's right. (i.e. target)
        SplayTree target = root->right;

        // set root's right to target's left
        root->right = target->left;

        // set target's left to be root
        target->left = root;

        // now target is root.
        root = target;

        return root;
    } else {
        assert (0);
    }
    
    return NULL;
}

SplayTree find_parent (SplayTree st, SplayTree target, int * direction) {
    if (st->uuid == target->uuid) {
        return NULL;
    }
    if (st->value >= target->value) {
        if (st->left == NULL) return NULL;
        if (st->left->uuid == target->uuid) {
            *direction = LEFT;
            return st;
        } else {
            return find_parent (st->left, target, direction);
        }
    } else if (st->value < target->value) {
        if (st->right == NULL) {
            return NULL;
        }
        if (st->right->uuid == target->uuid) {
            *direction = RIGHT;
            return st;
        } else {
            return find_parent (st->right, target, direction);
        }
    } else {
        assert (0);
    }
    return NULL;
}






