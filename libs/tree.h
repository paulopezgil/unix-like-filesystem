#ifndef FILE_H
#define FILE_H
#define MAX_SIZE 61
#define MAX_CHAR 128

#ifndef NAME
#define NAME
typedef char Name[MAX_SIZE];
#endif

typedef struct TreeNode *Tree;
typedef struct TrieNode *Trie;

typedef struct TrieNode {
    Tree file;
    Trie next[MAX_CHAR];
} TrieNode;

typedef enum InodeType {
    Folder,
    File
} InodeType;

typedef union InodeContent {
    Trie folder;    /* a trie of child nodes  */
    char *file;     /* an array of characters */
} InodeContent;

typedef struct Inode {
    InodeType type;
    InodeContent content;
    int size;
    int refCount;
} Inode;

typedef struct TreeNode {
    Tree parent;
    Name name;
    Inode *in;    
} TreeNode;

/* create a copy of a Tree in a destination folder */
void copyTree(Tree file, Tree folder);

/* obtain a list with the childs of tr and the number of them */
Tree *childList(Trie tr, int *size);

/* create the root node */
Tree createRoot();

/* create a tree on a given folder */
Tree createTree(Tree parent, Name name, InodeType type);

/* go to node nodeName from folder tr */
Tree findNode(Tree tr, Name nodeName);

/* free an inode */
void freeNode(Inode *in);

/* find the root of a tree */
Tree findRoot(Tree tr);

/* free a tree */
void freeTree(Tree root);

/* delete a file from a folder*/
void removeFile(Tree folder, Name name);

/* swap the inodes of two trees */
void swapContent(Tree tr1, Tree tr2);

#endif