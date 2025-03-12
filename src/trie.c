#include "tree.ih"

Tree *childList(Trie tr, int *size)
{
    if (tr == NULL)
    {
        *size = 0;
        return NULL;
    }
    
    /* initialize capacity and size */
    int capacity = 2;
    *size = 0;
    Tree *list = calloc(capacity, sizeof(Tree));
    
    /* add the file of the current trie node if it exists */
    if (tr->file != NULL)
    {
        list[0] = tr->file;
        ++(*size);
    }
    
    /* process each child in the trie */
    for (int idx = 0; idx < MAX_CHAR; idx++)
    {
        if (tr->next[idx] != NULL)
        {
            /* recursively obtain the childList of each child */
            int size2 = 0;
            Tree *list2 = childList(tr->next[idx], &size2);
            
            if (size2 != 0)
            {
                /* expand the capacity if needed */
                if (*size + size2 > capacity)
                {
                    capacity = (*size + size2) * 2;
                    list = realloc(list, capacity * sizeof(Tree));
                }
                
                /* Add all child trees to the list */
                for (int pos = 0; pos != size2; ++pos)
                {
                    list[*size] = list2[pos];
                    ++(*size);
                }
                
                free(list2);
            }
        }
    }
    
    /* If no children was found, return NULL */
    if (*size == 0)
    {
        free(list);
        return NULL;
    }
    
    /* return the found list */
    return list;
}

Trie createTrie()
{
    /* allocate memory */
    Trie tr = malloc(sizeof(TrieNode));

    /* set default values */
    tr->file = NULL;
    for (int pos = 0; pos != MAX_CHAR; ++pos)
        tr->next[pos] = NULL;

    /* return the trie */
    return tr;
}

void insertTrie(Trie tr, Tree file)
{
    for (int pos = 0; pos != MAX_SIZE; ++pos)
    {
        /* if null-terminator was read, we arrived to the correct node */
        if (file->name[pos] == '\0')
        {
            tr->file = file;
            return;
        }

        /* create the child if it doesn't exist */
        if (tr->next[(int)file->name[pos]] == NULL)
            tr->next[(int)file->name[pos]] = createTrie();

        /* go to the next letter */
        tr = tr->next[(int)file->name[pos]];
    }
}

Tree searchTrie(Trie tr, Name name)
{
    /* search the name in the trie */
    for (int pos = 0; pos != MAX_SIZE; ++pos)
    {
        /* if tr is NULL, there is no child called name */
        if (tr == NULL)
            return NULL;

        /* if null-terminator is read, the name could be in the trie */
        if (name[pos] == '\0')
            return tr->file;    /* NULL if the name is not actually there  */

        /* go to the next letter */
        tr = tr->next[(int)name[pos]];
    }

    /* at this point, the name wasn't found */
    return NULL;
}

void freeTrie(Trie tr)
{
    /* base case: NULL pointer */
    if (tr == NULL)
        return;

    /* free the file */
    freeTree(tr->file);

    /* recursively free the next nodes */
    for (int ch = 0; ch != MAX_CHAR; ++ch)
        freeTrie(tr->next[(int)ch]);

    /* free the node */
    free(tr);
}