#ifndef PATH_H
#define PATH_H
#define MAX_SIZE 61

#ifndef NAME
#define NAME
typedef char Name[MAX_SIZE];
#endif

typedef struct Path {
    Name *name;
    int size;
    int capacity;
} Path;

/* add a name to the path */
void appendName(Path *pt, Name name);

/* create a new path with given capacity */
Path createPath(int capacity);

/* read a path from stdin */
Path readPath();

/* free a path */
void freePath(Path pt);

/* print a path */
void printPath(Path pt);

#endif