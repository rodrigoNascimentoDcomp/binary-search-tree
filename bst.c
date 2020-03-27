#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left, *right;
} node;

void print_in_order(node *n) {
    if (n == NULL)
        return;
    print_in_order(n->left);
    printf("%d\n", n->value);
    print_in_order(n->right);
}

void print_pre_order(node *n) {
    if (n == NULL)
        return;
    printf("%d\n", n->value);
    print_pre_order(n->left);
    print_pre_order(n->right);
}

void print_post_order(node *n) {
    if (n == NULL)
        return;
    print_post_order(n->left);
    print_post_order(n->right);
    printf("%d\n", n->value);
}

int count(node *n) {
    if (n == NULL)
        return 0;

    return count(n->left) + count(n->right) + 1;
}

int is_empty(node *n) {
    return !n;
}

int is_ordered(node *n) {
    if (n == NULL)
        return 1;

    if (n->left && n->left->value > n->value)
        return 0;
    if (n->right && n->right->value <= n->value)
        return 0;

    return is_ordered(n->left) && is_ordered(n->right);
}

int get_height(node *n) {
    if (n == NULL)
        return 0;
    
    int l = get_height(n->left);
    int r = get_height(n->right);

    return (l > r ? l : r) + 1;
}

node* create(int v) {
    node *n = (node*) malloc(sizeof(node));
    n->value = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

node* push(node *r, node *n) {
    if (r == NULL)
        r = n;
    else if (r->value > n->value)
        r->left = push(r->left, n);
    else if (r->value <= n->value)
        r->right = push(r->right, n);
    return r;
}

// Returns the node of the tree
// with the greatest value.
node* biggest(node *r) {
    if (r == NULL)
        return r;
    else if (r->right != NULL)
        return biggest(r->right);
    else
        return r;
}

// Returns the node of the tree
// with the smallest value.
node* smallest(node *r) {
    if (r == NULL)
        return r;
    else if (r->left != NULL)
        return smallest(r->left);
    else
        return r;
}

node* delete(node *r, int v) {
    if (r == NULL)
        return r;
    else if (r->value > v)
        r->left = delete(r->left, v);
    else if (r->value < v)
        r->right = delete(r->right, v);
    else {
        node *temp;
        if (r->left == NULL) {
            temp = r->right;
        } else if (r->right == NULL) {
            temp = r->left;
        } else {
            r->value = smallest(r->right)->value;
            r->right = delete(r->right, r->value);
            return r;
        }
        free(r);
        return temp;
    }
    return r;
}

int main()
{
    node *n;
    n = create(10);
    n = push(n, create(5));
    n = push(n, create(20));
    n = push(n, create(10));
    
    n = delete(n, 10);
    print_in_order(n);

    return 0;
}
