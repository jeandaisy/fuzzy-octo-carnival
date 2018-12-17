
#include <stdlib.h>  //standard C library: free(),NULL
#include <stdbool.h>  //standard true, false, and bool type
#include <string.h>  //standard C version of lib/cstring.c0
#include "lib/contracts.h"  //our contracts library
#include "lib/xalloc.h"  //our allocation library
#include "strbuf.h"    //the string buffer library



/*** Implementation ***/

bool is_strbuf(struct strbuf *sb)
{
  if (sb==NULL) return false;
  if (sb->len >= sb->limit) return false;
  if (sb->limit <1) return false;

  if (sb->buf == NULL) return false;

  if (strlen(sb->buf) != sb->len) return false;
  for(size_t i=0; i<sb->len; i++){
    if(sb->buf[i] == '\0') return false;
  }  
  if(sb->buf[sb->len] != '\0') return false;
  return true;
}

struct strbuf* strbuf_new(size_t init_limit)
//@requires init_limit > 0;
//@ensures is_strbuf(\result);
{
  REQUIRES(init_limit > 0);
  struct strbuf *r = xmalloc(sizeof(struct strbuf));
  r->limit = init_limit;
  r->len = 0;
  r->buf = xcalloc(init_limit,sizeof(char));
  r->buf[0]='\0';

  ENSURES(is_strbuf(r));
  ENSURES(r->limit == init_limit);
  ENSURES(r->len == 0);
  ENSURES(strcmp(r->buf,"")==0);
  return r;
}

char* strbuf_str(struct strbuf* sb)
//@requires is_strbuf(sb);
//@ensures \length(\result)==sb->len+1;
//@ensures \length(\result) < sb->limit;
/*@ensures string_compare(string_from_chararray(sb->buf),
                          string_from_chararray(\result))==0;@*/
{

  REQUIRES(is_strbuf(sb));

  char *c = xcalloc(sb->len+1,sizeof(char));
  c = strcpy(c, sb->buf);

  ENSURES(c != NULL);
  ENSURES(strlen(sb->buf)==sb->len);
  ENSURES(strcmp(c,sb->buf)==0);
  return c;
}

void strbuf_add(struct strbuf *sb, char *str, size_t str_len)
//@requires str_len >=1;
//@requires \length(str)==str_len+1;
//@requires is_strbuf(sb);
//@ensures is_strbuf(sb);
{
  REQUIRES(is_strbuf(sb));
  REQUIRES(str != NULL);
  REQUIRES(strlen(str) == str_len);

  size_t ini_len = sb->len;
  if(ini_len + str_len < sb->limit){
    for(size_t i =0; i < str_len;i++){
      sb->buf[i+ini_len] = str[i];
      sb->len++;
    }
    sb->buf[sb->len]='\0';
  }
  else{

    sb->limit = 2*(ini_len + str_len);
    char *c = xcalloc(sb->limit,sizeof(char));
    for(size_t i =0; i < ini_len;i++){
      c[i] = sb->buf[i];
    }

    for(size_t j=0; j < str_len; j++){
      c[j+ini_len]=str[j];
      sb->len++; 
    }
    free(sb->buf);
    c[sb->len]='\0';
    sb->buf = c;
  }
  ENSURES(is_strbuf(sb));
  ENSURES(strlen(sb->buf) == ini_len + str_len);
  ENSURES(strcmp(str,sb->buf+ini_len)==0);
}

void strbuf_addstr(struct strbuf *sb, char *str)
//@requires is_strbuf(sb);
//@requires \length(str) > 1;
//@ensures is_strbuf(sb);
{
  REQUIRES(is_strbuf(sb));
  REQUIRES(str != NULL);
  strbuf_add(sb, str, strlen(str));
  ENSURES(is_strbuf(sb));
}

char *strbuf_dealloc(struct strbuf *sb)
{
  REQUIRES(is_strbuf(sb));
  char *result =sb->buf;
  free(sb);
  ENSURES(result != NULL);
  return result;
}
