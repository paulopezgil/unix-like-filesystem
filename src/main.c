#include "main.ih"

int main()
{
    /* initialize the root directory */
    Tree currentDir = createRoot();

    /* read all the commands until exit is read */
    char name[6];
    int stop = 0;
    while (!stop)
    {
        /* read and execute each command */
        scanf("%s", name);
        stop = executeCommand(name, &currentDir);
    } 
}