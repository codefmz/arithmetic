#include "radixtree.h"
#include "base.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

#define LEVEL_32 16

typedef struct radixtreenode {
    struct radixtreenode* child[4];
    struct radixtreenode* parent;
    uintptr_t value;
} RadixTreeNode;

typedef struct {
    RadixTreeNode* root;
} RadixTree;

void* RadixTreeCreate32(int preallocate)
{
    (void)preallocate;
    RadixTree* tree;
    RadixTreeNode* root;

    root = (RadixTreeNode*)malloc(sizeof(RadixTreeNode));
    memset(root, 0, sizeof(RadixTreeNode));
    tree = (RadixTree*)malloc(sizeof(RadixTree));
    root->value = INVALID_VALUE;
    tree->root = root;
}

void RadixTreeFreeNode(RadixTreeNode* node)
{
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < 4; ++i) {
        RadixTreeFreeNode(node->child[i]);
    }

    free(node);
}

uint32_t RadixTreeDestory32(void* rTree)
{
    RadixTree* tree = (RadixTree*)rTree;

    RadixTreeFreeNode(tree->root);
    free(rTree);

    return OK;
}

uint32_t RadixTreeInsert32(void* rTree, uint32_t key, uintptr_t value)
{
    RadixTree* tree = (RadixTree*)rTree;
    uint32_t bit;
    RadixTreeNode* node;
    uint32_t index = 0;
    uint32_t i = 0;

    node = tree->root;
    bit = 0x03;
    while (i < LEVEL_32) {
        index = key & bit;
        if (node->child[index] == NULL) {
            node->child[index] = (RadixTreeNode*)malloc(sizeof(RadixTreeNode));
            memset(node->child[index], 0, sizeof(RadixTreeNode));
            node->child[index]->parent = node;
            node->child[index]->value = INVALID_VALUE;
        }
        node = node->child[index];
        key >>= 2;
        ++i;
    }

    node->value = value;
    return OK;
}

uint32_t RadixTreeDelete32(void* rTree, uint32_t key)
{
    RadixTree* tree = (RadixTree*)rTree;
    uint32_t bit;
    uintptr_t value;
    RadixTreeNode* node;
    uint32_t index = 0;
    uint32_t i = 0;

    bit = 0x3;
    value = INVALID_VALUE;
    node = tree->root;
    while (i < LEVEL_32) {
        index = key & bit;

        if (node->child[index] == NULL) {
            LOG_ERROR("key(%u) is not exist", key);
            return ERROR;
        }

        node = node->child[index];
        key >>= 2;
        i++;
    }

    node->value = INVALID_VALUE;
    return OK;
}

uintptr_t RadixTreeFind32(void* rTree, uint32_t key)
{
    RadixTree* tree = (RadixTree*)rTree;
    uint32_t bit;
    uintptr_t value;
    RadixTreeNode* node;
    uint32_t index = 0;
    uint32_t i = 0;

    bit = 0x3;
    value = INVALID_VALUE;
    node = tree->root;
    while (i < LEVEL_32) {
        index = key & bit;

        if (node->child[index] == NULL) {
            return INVALID_VALUE;
        }

        node = node->child[index];
        key >>= 2;
        ++i;
    }

    return node->value;
}
