#include "commands.ih"

void cd(Tree *tr, Path pt)
{
    /* if an empty path is given, go to the root */
    if (pt.size == 0)
        *tr = findRoot(*tr);

    /* navigate through the path */
    for (int idx = 0; idx != pt.size; ++idx)
        *tr = findNode(*tr, pt.name[idx]);
}

void ls(Tree tr, Path pt)
{
    /* go to the specified path */
    if (pt.size != 0)
        cd(&tr, pt);

    /* Obtain tr's child list */
    int size = 0;
    Tree *children = childList(tr->in->content.folder, &size);

    /* print the name of it's childs */
    for (int idx = 0; idx != size; ++idx)
        printf("%s\n", children[idx]->name);

    /* free allocated memory */
    free(children);
}

void cat(Tree tr, Path pt)
{
    /* go to the specified file */
    cd(&tr, pt);

    /* print the content of the file */
    if (tr->in->size != 1)
        printf("%s\n", tr->in->content.file);
}

void find(Tree tr, Path *pt)
{
    /* print the current node */
    printPath(*pt);

    /* if tr is a folder, print the path of it's files */
    if (tr->in->type == Folder)
    {
        /* obtain the array of children */
        int size = 0;
        Tree *children = childList(tr->in->content.folder, &size);
        
        /* for each file, execute find again */
        for (int idx = 0; idx != size; ++idx)
        {
            /* add the name of the child to the path */
            appendName(pt, children[idx]->name);

            /* call find with the new path */
            find(children[idx], pt);

            /* remove the name of the child from the path */
            --(pt->size);
        }

        free(children);
    }
}

void touch(Tree tr, Path pt)
{
    /* go to the specified directory */
    cd(&tr, pt);

    /* create the file using helper function */
    createTree(tr, pt.name[pt.size - 1], File);
}

/* overwrite the contents of the file with str */
void echo(char *str, int size, Tree tr, Path pt, int override)
{
    /* go to the specified file */
    cd(&tr, pt);

    /* if the file does not exist, create it */
    if (tr->in->type != File)
        tr = createTree(tr, pt.name[pt.size - 1], File);

    /* perform the requested operation */
    if (override)
    {
        /* overwrite the file */
        free(tr->in->content.file);
        tr->in->content.file = malloc(size * sizeof(char));
        strcpy(tr->in->content.file, str);

        /* update the size of the file */
        tr->in->size = size;
    }
    else
    {
        /* append the content of str to the file */
        tr->in->content.file = realloc(tr->in->content.file,
                                       (tr->in->size + size) * sizeof(char));
        strcat(tr->in->content.file, str);
        tr->in->size += size;
    }
}

void mkdir(Tree tr, Path pt)
{
    /* loop through all elements of the path */
    Tree auxTr;
    for (int idx = 0; idx != pt.size; ++idx)
    {
        auxTr = findNode(tr, pt.name[idx]);

        /* case where the folder doesn't exist*/
        if (auxTr == tr)
            auxTr = createTree(tr, pt.name[idx], Folder);

        tr = auxTr;
    }
}

void mv(Tree tr, Path pt1, Path pt2)
{
    /* go to the specified addresses */
    Tree dir1 = tr, dir2 = tr;
    cd(&dir1, pt1);
    cd(&dir2, pt2);
    
    /* if the file at pt2 doesn't exist, create it */
    if (strcmp(dir1->name, dir2->name) != 0 || dir1->in->type != dir2->in->type)
        dir2 = createTree(dir2, pt2.name[pt2.size - 1], dir1->in->type);
    /* swap the content of the files at dir1 and dir2 */
    swapContent(dir1, dir2);

    /* delete dir1 */
    removeFile(dir1->parent, dir1->name);
}

void cp(Tree tr, Path pt1, Path pt2)
{
    /* go to the specified addresses */
    Tree dir1 = tr, dir2 = tr;
    cd(&dir1, pt1);
    cd(&dir2, pt2);

    /* create the dir2 if it wasn't found */
    if (dir2->in->type == Folder)
        dir2 = createTree(dir2, pt2.name[pt2.size - 1], dir1->in->type);

    /* copy dir1 to dir2 */
    copyTree(dir1, dir2);
}

void rm(Tree tr, Path pt)
{
    /* go to the specified location */
    cd(&tr, pt);

    /* remove tr from it's parent folder */
    removeFile(tr->parent, tr->name);
}

void ln(Tree tr, Path pt1, Path pt2)
{
    /* go to the specified addresses */
    Tree dir1 = tr, dir2 = tr;
    cd(&dir1, pt1);
    cd(&dir2, pt2);

    /* create the hard linked file without inode at pt2 */
    dir2 = createTree(dir2, pt2.name[pt2.size - 1], File);
    freeNode(dir2->in);

    /* assign the inode of dir1 to dir2 and increase the reference count */
    dir2->in = dir1->in;
    ++(dir1->in->refCount);
}