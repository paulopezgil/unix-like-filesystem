#include "console.ih"

/**************************************************\
*   The following functions decide which command   *
*   to call based on the input recieved at main    *
\**************************************************/

int (*execute[12])(Tree *) = {
    callExit,
    callCd,
    callLs,
    callCat,
    callFind,
    callTouch,
    callEcho,
    callMkdir,
    callMv,
    callCp,
    callRm,
    callLn
};

int executeCommand(char *name, Tree *dir)
{
    return execute[getCommandId(name)](dir);
}

int getCommandId(char *command)
{
    if (strcmp(command, "exit") == 0)
        return EXIT;
    if (strcmp(command, "cd") == 0)
        return CD;
    if (strcmp(command, "ls") == 0)
        return LS;
    if (strcmp(command, "cat") == 0)
        return CAT;
    if (strcmp(command, "find") == 0)
        return FIND;
    if (strcmp(command, "touch") == 0)
        return TOUCH;
    if (strcmp(command, "echo") == 0)
        return ECHO;
    if (strcmp(command, "mkdir") == 0)
        return MKDIR;
    if (strcmp(command, "mv") == 0)
        return MV;
    if (strcmp(command, "cp") == 0)
        return CP;
    if (strcmp(command, "rm") == 0)
        return RM;
    if (strcmp(command, "ln") == 0)
        return LN;
    return -1;
}

/**************************************************************\
*   The following functions parse the input from stdin, and    *
*   call the appropiate methods with the scanned arguments     *
\**************************************************************/

/* read a string of arbitrary length until the delimiter is found */
int readString(char **str, char delimiter)
{
    int capacity = 1, size = 0, foundDelimiter = 0;
    *str = malloc(sizeof(char));

    while (!foundDelimiter)
    {
        (*str)[size] = getchar();

        /* stop if the delimiter is found */
        if ((*str)[size] == delimiter)
            break;

        /* otherwise, continue and double the capacity if necessary */
        ++size;
        if (size == capacity)
        {
            capacity *= 2;
            *str = realloc(*str, (capacity + 1) * sizeof(char));
        }
    }

    /* turn the delimiter into a null terminator and return */
    (*str)[size] = '\0';
    return size + 1;
    return 0;
}

/* skip the specified number of characters if they match the pattern */
void skipString(char *pattern, int size)
{
    char read[size];

    /* check if the expected pattern is found in stdin */
    for(int idx = 0; idx != size; ++idx)
    {    
        read[idx] = getchar();

        /* if the char is not the expected one, return the chars to stdin */
        if (read[idx] != pattern[idx])
        {
            for(int pos = idx; pos != -1; --pos)
                ungetc(read[pos], stdin);
            break;
        }
    }
}

int callExit(Tree *dir)
{
    freeTree(findRoot(*dir));
    return 1;
}

int callCd(Tree *dir)
{
    Path pt = readPath();
    cd(dir, pt);

    /* free the path and return */
    freePath(pt);
    return 0;
}

int callLs(Tree *dir)
{
    Path pt = readPath();
    ls(*dir, pt);

    /* free the path and return */
    freePath(pt);
    return 0;
}

int callCat(Tree *dir)
{
    Path pt = readPath();
    cat(*dir, pt);

    /* free the path and return */
    freePath(pt);
    return 0;
}

int callFind(Tree *dir)
{
    /* create the initial path */
    Path pt = createPath(1);
    Name dot = ".";
    appendName(&pt, dot);

    find(*dir, &pt);

    /* free the path and return */
    freePath(pt);
    return 0;
}

int callTouch(Tree *dir)
{
    /* read the paths until '\n' is read */
    Path pt = readPath();
    while (pt.size != 0)
    {
        touch(*dir, pt);
        freePath(pt);
        pt = readPath();
    }

    /* free the path and return */
    freePath(pt);
    
    return 0;
}

int callEcho(Tree *dir)
{
    /* skip ' "'*/
    skipString(" \"", 2);

    /* read the content of the stringing */
    char *content = NULL;
    int size = readString(&content, '"');

    /* skip ' >' */
    skipString(" >", 2);

    /* deduce the mode of execution */
    int override = 1;
    if (getchar() == '>')
        override = 0;
    else
        ungetc(' ', stdin);

    /* read the path */
    Path pt = readPath();

    /* call the appropiate version of echo */
    echo(content, size, *dir, pt, override);

    /* free the data and return */
    free(content);
    freePath(pt);
    return 0;
}

/* we assume that the -p flag is always given*/
int callMkdir(Tree *dir)
{   
    /* skip " -p" */
    skipString(" -p", 3);

    /* read the paths until '\n' is read */
    Path pt = readPath();
    while (pt.size != 0)
    {
        mkdir(*dir, pt);
        freePath(pt);
        pt = readPath();
    }

    /* free the path and return */
    freePath(pt);
    return 0;
}

int callMv(Tree *dir)
{
    Path pt1 = readPath();
    Path pt2 = readPath();
    mv(*dir, pt1, pt2);

    /* free the paths and return */
    freePath(pt1);
    freePath(pt2);
    return 0;
}

int callCp(Tree *dir)
{
    /* skip ' -r' */
    skipString(" -r", 3);

    Path pt1 = readPath();
    Path pt2 = readPath();
    cp(*dir, pt1, pt2);

    /* free the paths and return */
    freePath(pt1);
    freePath(pt2);
    return 0;
}

int callRm(Tree *dir)
{
    /* skip ' -r' */
    skipString(" -r", 3);

    /* read the paths until '\n' is read */
    Path pt = readPath();
    while (pt.size != 0)
    {
        rm(*dir, pt);
        freePath(pt);
        pt = readPath();
    }

    /* free the path and return */
    freePath(pt);
    return 0;
}

int callLn(Tree *dir)
{
    Path pt1 = readPath();
    Path pt2 = readPath();
    ln(*dir, pt1, pt2);

    /* free the paths and return */
    freePath(pt1);
    freePath(pt2);
    return 0;
}