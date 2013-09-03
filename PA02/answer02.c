
#include "pa02.h"

/**
 * Count the number of characters in a null-terminated string 's' 
 * (not counting the null character).
 *
 * Example: my_strlen("foo") should yield 3.
 */
int my_strlen(const char * s)
{
  int length = 0;
  while (s[length]!='\0') /* Counts until it reaches null at the end of the string */
      length++;
  return length;
}

/**
 * Count the number of occurrences of a particular character 'c' in a
 * null-terminated string 's'.
 *
 * Example: my_countchar("foo", 'o') should yield 2.
 */
int my_countchar(const char * s, char c)
{
  int x = 0;            /* variable for going through the char array */
  int count  = 0;       /* variable for counting the occurences */
  while(s[x]!='\0')
    {
      if(s[x]==c)
	count++;
      x++;
    }
    return count;
}

/**
 * Convert an entire null-terminated string 's' to uppercase.  Only
 * alphabetical characters should be converted; numbers and symbols
 * should not be affected.  Hint: toupper(c) is a macro that yields
 * the uppercase version of a character c.
 *
 * Example: char foobar[10] = "foobar";
 * my_strupper(foobar) yields "FOOBAR".
 */
void my_strupper(char * s)
{
  int x = 0;
  while(s[x]!='\0')
    {
      if(s[x]<123 && s[x]>96)  /* checking if the given char is a lower case alphabet*/
	s[x]=toupper(s[x]);
      x++;
    }
}

/**
 * Convert an entire null-terminated string 's' to lowercase.  Only
 * alphabetical characters should be converted; numbers and symbols
 * should not be affected.  Hint: tolower(c) is a macro that yields
 * the lowercase version of a character 'c'.
 *
 * Example: char foobar[10] = "FOOBAR";
 * my_strupper(foobar) yields "foobar".
 */
void my_strlower(char * s)
{
  int x = 0;
  while(s[x]!='\0')
  {
    if(s[x]<91 && s[x]>64)  /* checking if the given char is an upper case alphabet*/
      s[x]=tolower(s[x]);
    x++;
  }
}

/**
 * Copy the contents of a null-terminated string 's2' into the memory
 * pointed to by 's1'.  Any existing data in 's1' will be overwritten by
 * the contents of 's2'.  Note: you can assume that there is sufficient
 * memory available in 's1'.  Hint: Don't forget to terminate the new
 * string with '\0'!
 * 
 * Example: char foo[10];
 * my_strcpy(foo, "foo") yields "foo".
 */
void my_strcpy(char * s1, const char * s2)
{
  int x = 0;
  while(s2[x]!='\0')
    {
      s1[x]=s2[x];
      x++;
    }
  s1[x]='\0';  /* ends s1 wherever s2 ends*/
}

/**
 * Copy the first 'n' characters of a null-terminated string 's2' into the
 * memory pointed to by 's1'. Any existing data in 's1' will be
 * overwritten by the contents of 's2'.  Note: you can assume that there
 * is sufficient memory available in 's1'.  Hint: Don't forget to
 * terminate the new string with '\0'!
 * 
 * Example: char foo[10];
 * my_strncpy(foo, "foo", 1) yields "f".
 */
void my_strncpy(char * s1, const char * s2, int num)
{
  int x = 0;

  while(x!=num)
    {
      s1[x]=s2[x];
      x++;
    }

  s1[x]='\0'; /* ends s1 at num after copying s2 in it*/
}


/** 
 * Concatenate (append) the contents of a null-terminated string 's2'
 * onto the end of the null-terminated string 's1'.  Note: you can
 * assume that there is sufficient memory available in 's1'.  Hint:
 * Don't forget to terminate the new string with '\0'!
 * 
 * Example: char foo[10] = "foo";
 * my_strcat(foo, "bar") yields "foobar".
 */
void my_strcat(char * s1, const char * s2) 
{
  int length = 0;
  int x = 0;

  while(s1[length]!='\0')
      length++;

  while(s2[x]!='\0')
    {
      s1[length]=s2[x];
      length++;
      x++;
    }

  s1[length]='\0'; /* ends s1 after adding s2*/
}

/** 
 * Concatenate (append) the first n characters of a null-terminated
 * string 's2' onto the end of the null-terminated string 's1'.  Note: you
 * can assume that there is sufficient memory available in 's1'.  Hint:
 * Don't forget to terminate the new string with '\0'!
 * 
 * Example: char foo[10] = "foo";
 * my_strcat(foo, "bar", 1) yields "foob".
 */
void my_strncat(char * s1, const char * s2, int num)
{
  int length = 0;
  int x = 0;

  while(s1[length]!='\0')
    length++;

  while(x!=num)
    {
      s1[length]=s2[x];
      length++;      
      x++;
    }
  s1[length]='\0'; /* ends s1 after adding num number of chars from s2*/
}

/**
 * Return a pointer to the first occurrence of a null-terminated
 * substring 's2' in a null-terminated string 's1'.  If 's2' does not appear
 * in 's1', the empty (NULL) pointer is returned.
 * 
 * Example: my_strstr("hello world!", "test") will yield 0 (NULL).
 * Example(2): my_strstr("foobar", "bar") will yield a pointer to the
 * "bar" portion of the "foobar" argument.
 */

const char *my_strstr(const char * s1, const char * s2)
{
  int x = 0;            /* match counter*/
  int length = 0;       /* variable for going through s1 and its length*/
  int start = 0;
  char *ptr = '\0';

  while(s1[length]!='\0')
    {
      if(s1[length]==s2[x])  /* if a char of s1 and s2 match*/
	{
	  if(x==0)           /* if this is the first time a char from s1 and s2 match */
	    start = length;  /* mark this index as the potential start of s2 */
	  x++;  
	}
      else
	{
	  x=0;               /* if the chars from s1 and s2 don't match, reset the match counter*/
	}
      length++;              /* while s1's index counter keeps going*/

      if(s2[x]=='\0')        /* if the match counter reaches the end of s2 without resetting */
	{
	  int i = 0;
	  for(i = start; i < length; i++)
	    ptr+=s1[i];      /* copy that substring of s1 to a new string */
	}
    }

    return ptr;
}



/**
 * Insert a null-terminated string s2 in the null-terminated string s1
 * at position pos.  All characters following position pos in s1 will
 * be moved to follow directly after the inserted characters from s2;
 * no characters will be overwritten.  Note: you can assume that there
 * is sufficient memory available in s1.
 * 
 * Hint: there is no need to create any temporary memory; simply copy
 * the contents of the string after position pos to its new location
 * starting from the back of the string and going forwards.
 * 
 * Insertions should happen BEFORE the character position referenced
 * by pos.  In other words, inserting s2 at position 0 (the first
 * character of a string) in s1 is equivalent to the string s2
 * followed by string s1.
 * 
 * If the character position pos is higher (or equivalent to) the
 * length of string s1, s2 will simply be appended to the end of s1
 * (i.e. it is equivalent to my_strcat(s1, s2);
 * 
 * Example: char foo[10] = "foo";
 * my_strinsert(foo, "bar", 0) yields "barfoo".
 * 
 * Example(2): char foo[10] = "foo";
 * my_strinsert(foo, "bar", 100) yields "foobar".
 */
void my_strinsert(char *s1, const char *s2, int pos)
{
  int length1 = 0;       /* length of s1 */
  int length2 = 0;       /* length of s2 */

  while(s1[length1]!='\0')
    length1++;

  while(s2[length2]!='\0')
    length2++;

  if(pos > length1)      /* if the char position is higher or equal to the  */
    my_strcat(s1,s2);    /* length of s1, do my_strcat(s1,s2) */

  else
    {
      int x = length1-1;
      int i = 0;
      for(i = length1+length2-1; i > pos+length2-1; i--) /* this loop copies */
	{                       /* contents of s1 after pos to their new loc */
	  s1[i]=s1[x];          /* from the back of string going forward     */
	  x--;
	}
      x=0;
      for(i = pos ; i < pos+length2; i++) /* this loop puts s2 in pos location in s1*/
	{
	  s1[i]=s2[x];
	  x++;
	}
      s1[length1+length2]='\0'; /* ending s1 after adding s2 at pos */
    }
}

/**
 * Delete a portion of the null-terminated string s that starts at
 * character position pos and is length characters long.  All
 * characters following position pos + length in s will be moved up to
 * follow directly after the characters before position pos. 
 * 
 * Hint: there is no need to create any temporary memory; simply copy
 * the contents of the string after position pos + length to their new
 * location.
 * 
 * Deletions should happen BEFORE the character position referenced by
 * pos.  In other words, deleting position 0 (the first character of a
 * string) in s means will start deleting from the first character.
 *
 * If the character position pos is higher (or equivalent to) the
 * length of string s, the function will do nothing.
 * 
 * If the length of the deleted portion from its starting position pos
 * extends past the end of the string, the remainder of the string
 * will be deleted.
 * 
 * Example: char foo[10] = "foobar";
 * my_strdelete(foo, 3, 3) yields "foo".
 *
 * Example(2): char foo[10] = "foobar";
 * my_strdelete(foo, 0, 3) yields "bar".
 * 
 * Example(3): char foo[10] = "foobar";
 * my_strdelete(foo, 0, 34) yields "".
 */
void my_strdelete(char *s, int pos, int length)
{
  int slen = 0;
  while(s[slen]!='\0')
    slen++;

  if(pos >= slen) /* case 1 where pos is higher or equal to length of s*/
    return;
  else
    {
      if(pos+length >= slen) /* case 2 where the entire array after pos */
	s[pos]='\0';         /* is to be deleted */
      else 
	{  /* case 3 where a portion from the middle of s is to be deleted  */
	  int i = 0;
	  int x = 0;
	  for(i = pos; i < slen-length; i++) /* goes from pos to pos+(locations left after deleting) */
	    {
	      if(s[pos+length+x]!='\0')      /* checks if we haven't reached the end of s */
		{
		  s[i]=s[pos+length+x];
		  x++;
		}
	    }
	  s[pos+slen-length]='\0';        /* terminates s after deleting a middle portion */
	}
    }
}

