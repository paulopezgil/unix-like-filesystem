#include "main.ih"

/*****************************************************************************\
*                                                                             *
*  ORGANIZATION:                                                              *
*                                                                             *
*  The code is divided into source files, public header files, and internal   *
*  header files. Public headers contain only the declarations, data           *
*  structures and preprocessor directives needed by their users (i.e., the    *
*  source files that include them), while internal headers contain the        *
*  declarations and preprocessor directives needed by the source files        *
*  implementing the public header functions.                                  *
*                                                                             *
*                                                                             *
*  HIERARCHY:                                                                 *
*                                                                             *
*  The following scheme illustrates the program structure:                    *
*                                                                             *
*                                              tree.c  ····  trie.c           *
*                                                ·                            *
*                                                ·                            *
*  main.c  ····  console.c  ····  commands.c ·····                            *
*                                                ·                            *
*                                                ·                            *
*                                              path.c                         *
*                                                                             *
\*****************************************************************************/

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