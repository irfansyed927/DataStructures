/*
 * Homework 3 by Irfan Syed 
 * File: Htmlchecker.c 
 * --------------------
 * This program is to check if the HTML tags in a give file are nested correctly or not. You will deal with HTML tags and read them from a file. So you need to use stack ADT as we discussed in class. 
 */

#include <stdio.h>
#include "stack.h"
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"

char *readTag(FILE *fp);  //prototype functions
char *getword(FILE *fp);  // prototype functions


int main(int argc, char *argv[])
{
  FILE *fp;       // opening file sample1.txt and declaring variables
  string tag, temp;
  char *tbag;
  int len; 
  stackADT stack; // defining a new stack ADT pointer 
  
  if (argc < 2)
 {
  printf("Usage:driver infile>html\n");   
  exit(-1);
 }

 if((fp = fopen(argv[1], "r")) == NULL)
 {
	printf("input file cannot be opened\n");
  exit(-1);
 }

 stack = NewStack(); // Created a new Stack 
 while ((tag = readTag(fp)) != NULL)
 { 
   while ((tag = readTag(fp)) != NULL) {
        len = strlen(tag);
        printf("Tag is: %s\n", tag);
        if (StackIsEmpty(stack)) {
            Push(stack, tag);
        }
         else if (*(tag + 1) == '/') {
                temp = (char*)malloc(sizeof(char)*len); // allocating new memory 
                temp = Pop(stack);
                if (tagMatch(tag, temp) == 0) {
             
                    free(tag);
                    free(temp);
                }
            }
         else {
             Push(stack, tag);
         }
         free(tag);
   }



 if (StackIsEmpty(stack))
 { 
   printf("all the tags are nested correctly\n");
 } 
   FreeStack(stack);
   return 1;
 }
}

char *getword(FILE *fp)
{
  char *w, aword[100], ch, *temp;
int i = 0, len;
    while ((ch = fgetc(fp)) != EOF) {
        if (!isspace(ch))break;
    }
    if (ch == EOF) return NULL;
    aword[i++] = ch;

    if (ch == '<') {
        while ((ch = getc(fp)) != EOF) {
            if (ch == '!') {
                aword[i++] = ch;
                temp= ReadLine(fp);
               // printf("%s\n", temp);
                strcat(aword, temp);
                free(temp);
                break;
            }
            else if (ch == '>') {
                aword[i++] = ch;
                break;
            }
            aword[i++] = ch;
        }
        aword[i] = '\0';

        w = (char*)malloc(i + 1);
        if (w == NULL) return NULL;
        strcpy(w, aword);
        return w;
    }
    else {
        while ((ch = getc(fp)) != EOF) {
            if (isspace(ch)) break;
            aword[i++] = ch;
        }
        aword[i] = '\0';
        w = (char*)malloc(i + 1);
        if (w == NULL) return NULL;
        strcpy(w, aword);
        return w;
    }

}

char *readTag(FILE *fp)
{
  char *word, *tag, *temp;
  int len;
  int i = 0;
  int j;

 while //((ch == getc(fp))!= NULL)
 {
   if (Comment(word) == 0) 
 {
	free(word);
 }
else if (singleSided(word) == 0)
 {
 	free(word);
  }
else if(*word == '<')
{
	len = strlen(word);	
	tag = (char*)malloc(sizeof(char) *len);
	strcpy(tag, word);
	return tag;
    }
   else 
 {
	free(word);
     }
  }
   free(tag);
     free(word);
 }
   

int tagMatch(char *b, char *c)
{
 if (!b || !c)
 { 
	return 0; 
  }
 
 if (*b == '<' && *c == '<' && *(c+1) == '/' && strcmp (b+1, c+2 == 0))
 {
 	return 1; 
 } 
  else 
 { 
 	return 0; 
 } 
}

int Comment(string tag) 
{
	int len = strlen(tag);
	if ((*tag == '<') && (*(tag + 1) == '!'))
	return 0;
	return 1; 
 }

string ReadLine(FILE *infile)
{
    string line, nline;
    int n, ch, size;

    n = 0;
    size = 120;
    line = (string)malloc(size + 1);
    if (line == NULL) return NULL;
    while ((ch = getc(infile)) != '\n' && ch != EOF) {
        if (n == size) {
            size *= 2;
            nline = (string)malloc(size + 1);
            if (nline == NULL) { free(line); return NULL; }
            strncpy(nline, line, n);
            free(line);
            line = nline;
        }
        line[n++] = ch;
    }
    if (n == 0 && ch == EOF) {
        free(line);
        return (NULL);
    }
    line[n] = '\0';
    nline = (string)malloc(n + 1);
    if (nline == NULL) { free(line); return NULL; }
    strcpy(nline, line);
    free(line);
    return (nline);
}

string GetLine(void)
{
    return (ReadLine(stdin));
}

int singleSided(char *tag)
{
	int len = strlen(tag);
	if (*(tag + (len - 2)) == '/') 
	return 0; 
	return 1; 
 }

