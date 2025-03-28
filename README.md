# Unix like filesystem
A small C program that emulates a Unix shell.

## Executing the program
1 - build the program using make

2 - Execute a.out

## Code organization

The code is divided into source files, public header files, and internal header files. Source files are found in the `src` directory, while header files are located in the `hds` directory.
- **Public headers**: These files contain declarations, data structures and preprocessor directives required by their users, which are the source files that include them.
- **Internal headers**: These files contain declarations, data structures and preprocessor directives needed by the source files that implement the functions declared in the public headers.
- **Source files**: These files contain the implementation of the functions declared in the public headers. They handle the core functionality of the program and are compiled into object files, which are then linked together to create the final executable.

The following scheme illustrates the program structure:

```
main.c
│
└── console.c
    │
    └── commands.c
        │
        ├── tree.c
        │   │
        │   └── trie.c
        │
        └── path.c
```


## List of Commands
1. **exit**
    - This command terminates the shell, freeing all allocated memory and closing the program. Each session ends with this command.
    - Arguments: None.

2. **cd [DIRECTORY]**
    - Changes the current working directory to the specified DIRECTORY. If no DIRECTORY is provided, it defaults to the root directory.
    - Arguments: DIRECTORY (optional) must be a valid path that points to an existing directory.

3. **ls [DIRECTORY]**
    - Lists the names of all files in the specified DIRECTORY in ASCII order. If no DIRECTORY is provided, it lists the files in the current working directory. DIRECTORY 
    - Arguments: DIRECTORY (optional) must be a valid path that points to an existing directory.

4. **cat FILENAME**
    - Displays the contents of the specified FILENAME. If the file is empty, it outputs nothing.
    - Arguments: FILENAME (required) must be a valid path that points to an existing non-directory file.

5. **find**
    - Recursively lists all files in the current working directory and its subdirectories in ASCII order, starting with the working directory itself, denoted as “.”.
    - Arguments: None.

6. **touch FILENAME [FILENAME [FILENAME ...]]**
    - Creates empty files at the specified locations. These files must not already exist, but their parent directory must exist.
    - Arguments: STRING (required), FILENAME (required).

8. **echo "STRING" >> FILENAME**
    - Appends STRING to the contents of FILENAME. If FILENAME does not exist, it creates the file.
    - Arguments: STRING (required), FILENAME (required).

9. **mkdir -p DIRECTORY [DIRECTORY [DIRECTORY ...]]**
    - Creates the specified directories and any necessary parent directories. If a directory already exists, it does nothing.
    - Arguments: DIRECTORY (at least one required).

10. **mv PATH_1 PATH_2**
     - Moves PATH_1 to PATH_2. If PATH_1 is a file and PATH_2 exists, it overwrites PATH_2. If PATH_1 is a directory, PATH_2 must not exist, and the directory is moved to PATH_2.
     - Arguments: PATH_1 (required), PATH_2 (required).

11. **cp [-r] PATH_1 PATH_2**
     - Copies PATH_1 to PATH_2. If PATH_1 is a file and PATH_2 exists, it overwrites PATH_2. If PATH_1 is a directory, PATH_2 must not exist, and the directory is copied recursively to PATH_2.
     - Arguments: PATH_1 (required), PATH_2 (required).

12. **rm [-r] PATH [PATH [PATH ...]]**
     - Removes each specified PATH. If PATH is a directory, it removes all its contents recursively before removing the directory itself.
     - Arguments: PATH (at least one required).

13. **ln FILENAME_1 FILENAME_2**
     - Creates a hard link from FILENAME_1 to FILENAME_2. FILENAME_1 must exist, and FILENAME_2 must not exist.
     - Arguments: FILENAME_1 (required), FILENAME_2 (required).

### Example

Input:
```
ls
echo "CS is fun." >> cs-hymn.txt
ls
cat cs-hymn.txt
rm cs-hymn.txt
ls
exit
```

Output:
```
cs-hymn.txt
CS is fun.
```

