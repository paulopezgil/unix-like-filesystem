#include "path.ih"

void appendName(Path *pt, Name name)
{
    /* if the path is full, double it's capacity */
    if (pt->size == pt->capacity)
    {
        pt->capacity *= 2;
        pt->name = realloc(pt->name, pt->capacity * sizeof(Name));
    }

    /* add the new name */
    strcpy(pt->name[pt->size], name);
    pt->size += 1;
}

Path createPath(int capacity)
{
    Path pt;
    pt.name = malloc(capacity * sizeof(Name));
    pt.size = 0;
    pt.capacity = capacity;
    return pt;
}

Path readPath()
{
    Name name;
    Path pt = createPath(1);
    char separator = getchar();

    /* if a space is read, read the path */
    /* otherwise, the path is empty */
    if (separator == ' ')
    {
        /* check if it's an absolute path */
        name[0] = getchar();
        if (name[0] == '/')
        {
            name[1] = '\0';
            appendName(&pt, name);
        }
        else
            ungetc(name[0], stdin);

        /* read each name until a space or a line break is found */
        do
        {
            scanf("%[^/ \n]", name);
            appendName(&pt, name);
            separator = getchar();
        }
        while (separator != ' ' && separator != '\n');

        ungetc(separator, stdin);
    }

    return pt;
}

void freePath(Path pt)
{
    free(pt.name);
}

void printPath(Path pt)
{
    for (int idx = 0; idx < pt.size - 1; ++idx)
        printf("%s/", pt.name[idx]);
    printf("%s\n", pt.name[pt.size - 1]);
}