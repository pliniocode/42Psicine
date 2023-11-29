#ifndef FT_BTREE_H
#define FT_BTREE_H

#define VECTOR_SIZE(n)  sizeof(n)/sizeof(n[0])

typedef struct      s_btree
{
    struct s_btree  *left;
    struct s_btree  *right;
    void            *item;
}                   t_btree;

t_btree             *btree_create_node(void *item);
t_btree             *btree_insert_node(t_btree *btree, void *item);
t_btree             *btree_make(t_btree *btree, int itens[], int len);
void                btree_print_nodes(t_btree *node);



#endif