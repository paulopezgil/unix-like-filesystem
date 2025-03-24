#ifndef COMMANDS_H
#define COMMANDS_H
#include "tree.h"
#include "path.h"

void cd(Tree *tr, Path pt);
void ls(Tree tr, Path pt);
void cat(Tree tr, Path pt);
void find(Tree tr, Path *pt);
void touch(Tree tr, Path pt);
void echo(char *str, int size, Tree tr, Path pt, int override);
void mkdir(Tree tr, Path pt);
void mv(Tree tr, Path pt1, Path pt2);
void cp(Tree tr, Path pt1, Path pt2);
void rm(Tree tr, Path pt);
void ln(Tree tr, Path pt1, Path pt2);

#endif