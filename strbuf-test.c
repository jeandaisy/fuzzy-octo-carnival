/* 
 * Testing the strbuf implementation. 
 * 
 * Note that this is just for testing! This code allows the user's
 * input to attempt removing things an empty buffer, adding things to
 * a full buffer, and moving left or right off the end of an array.
 * These should lead to a @requires violation.
 *
 * cc0 -d -w -x gapbuf.c0 gapbuf-test.c0
 * 
 * 15-122 Principles of Imperative Computation */
#include <stdio.h>
#include <stdlib.h>  //standard C library: free(),NULL
#include <stdbool.h>  //standard true, false, and bool type
#include <string.h>  //standard C version of lib/cstring.c0
#include "lib/contracts.h"  //our contracts library
#include "lib/xalloc.h"  //our allocation library
#include "strbuf.h"    //the string buffer library
#include <assert.h>


void test() 
{

  printf("beginning\n");
  struct strbuf* case_1 = xmalloc(sizeof(struct strbuf));
  case_1->limit = 3;
  case_1->len = 4;
  char *c = xmalloc(3*sizeof(char));
  case_1->buf = c;


  assert(is_strbuf(case_1)==false);
  free(c);
  free(case_1);
  printf("---CASE 1 DONE----\n");

  unsigned size = 13;
  struct strbuf* case_2 = strbuf_new(size);

  assert(is_strbuf(case_2));
  assert(case_2->len==0);
  assert(case_2->limit==size);
  assert(case_2->limit > 0);
  assert(case_2->buf != NULL);
  assert(case_2->buf[0]=='\0');


  printf("---CASE 2 DONE----\n");

  unsigned len1 = case_2->len;
  unsigned limit1 = case_2->limit;
  char *s0 = "over";

  strbuf_add(case_2, s0,4);

  assert(is_strbuf(case_2));
  printf("add = %c\n", case_2->buf[0]);
  assert(is_strbuf(case_2));
  assert(case_2->len - len1 == 4);
  assert(case_2->limit == limit1);

  char *c1 = strbuf_str(case_2);
  printf("add = %s\n", c1);
  assert(is_strbuf(case_2));
  assert(c1 != NULL);
  assert(c1[0]=='o');

  assert(case_2->len == 4);
  assert(case_2->limit ==size);
  assert(strcmp(case_2->buf,"over")==0);


  char *s1 = "loading";
  strbuf_addstr(case_2, s1);

  assert(is_strbuf(case_2));
  assert(case_2->len == 11);
  assert(case_2->limit ==size);
  assert(strcmp(case_2->buf,"overloading")==0);

  printf("add = %s\n", case_2->buf+case_2->len);

  char *s2 = "again";
  strbuf_addstr(case_2, s2);

  assert(case_2->len == 16);
  assert(case_2->limit > size);
  assert(strcmp(case_2->buf,
                        "overloadingagain")==0);

  unsigned limit2 = case_2->limit;
  char *s3 = "";
  strbuf_addstr(case_2, s3);

  assert(case_2->len == 16);
  assert(case_2->limit == limit2);
  assert(strcmp(case_2->buf,
                        "overloadingagain")==0);

  char *c2 = strbuf_str(case_2);
  printf("c2 = %s\n", c2);
  printf("com = %d\n",strcmp(c2,"overloadingagain") );
  assert(is_strbuf(case_2));
  assert(c2 != NULL);


  assert(strlen(c2) == 16);
  assert(strcmp(c2,"overloadingagain")==0);


  free(case_2->buf);  
  free(case_2);
  free(c1);
  free(c2);

  struct strbuf* case_3 = strbuf_new(size);
  *case_3->buf = 'h';
  *(case_3->buf+1) = 'i'; 
  *(case_3->buf+2) = ' '; 
  *(case_3->buf+3) = 'w'; 
  *(case_3->buf+4) = 'o'; 
  *(case_3->buf+5) = 'r'; 
  *(case_3->buf+6) = 'l'; 
  *(case_3->buf+7) = 'd'; 
  *(case_3->buf+8) = '\0'; 
  *(case_3->buf+9) = 'b'; 
  *(case_3->buf+10) = 'y'; 
  *(case_3->buf+11) = 'e';
  *(case_3->buf+12) = '\0'; 

  assert(!is_strbuf(case_3));
  case_3->len = 8;
  assert(is_strbuf(case_3));
  char *c3 = strbuf_str(case_3); 
  assert(strcmp(c3,"hi world")==0); 

  strbuf_add(case_3, "mm", 2);
  assert(strcmp(case_3->buf,"hi worldmm")==0);

  free(case_3->buf);  
  free(case_3);
  free(c3);
  
  printf("case_3 is done\n");

  struct strbuf* case_4 = strbuf_new(size);
  strbuf_add(case_4, "", 0);
  assert(is_strbuf(case_4));

  char *c4 = strbuf_str(case_4); 
  assert(strcmp(c4,"")==0);

  strbuf_addstr(case_4, " ");
  assert(is_strbuf(case_4));

  char *c5= strbuf_str(case_4); 
  assert(strcmp(c5," ")==0);

  free(case_4->buf);  
  free(case_4);
  free(c4);
  free(c5);

  printf("case_4 is done\n");

  unsigned size_5 = 1;
  struct strbuf* case_5 = strbuf_new(size_5);
  assert(is_strbuf(case_5));
  assert(case_5->len == 0);
  assert(*(case_5->buf) == '\0');

  strbuf_addstr(case_5, "hello world");
  assert(is_strbuf(case_5));
  assert(case_5->len == 11); 

  char *c6= strbuf_str(case_5); 
  assert(strcmp(c6,"hello world")==0); 

  printf("case_5 is done\n");

  free(case_5->buf);  
  free(case_5);
  free(c6);

  unsigned size_6 = 1;
  struct strbuf* case_6 = strbuf_new(size_6); 
  *(case_6->buf)='a';
  assert(!is_strbuf(case_6)); 

  printf("case_6 is done\n");

  free(case_6->buf);  
  free(case_6);
  
}

int main() {
  test();
  printf("Goodbye.");
  return 0;
}
