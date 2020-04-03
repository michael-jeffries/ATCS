#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//char arr[0000] = {0};

// char* ptr = arr;


static char *stack[256] = { (char *)0, };
static int stack_ptr = 0;

#define push(p) (stack[stack_ptr++] = p)
#define pop()	(stack[--stack_ptr])
#define empty() (stack_ptr == 0)
#define full()	(stack_ptr == 256)

bool isvalid(char* input)
{
  int count = 0;
  while(*input != '\0')
  {
    switch(*input)
    {
      case '<': break;
      case '>': break;
      case '+': break;
      case '-': break;
      case '(': count++; break;
      case ')': count--; break;
      case '*': break;
      default: break;
    }
    if(count < 0)
    {
      return false;
    }
    input++;
  }
  if(count > 0)
  {
    return false;
  }
  return true;
}



char* interpret(char* input, char* ptr)
{

  char* save = input;
  while(*input != '\0')
  {
    if(*input == '>')
    {
      //printf("%c", '>');
      ++ptr;
      input++;
    }
    else if(*input == '<')
    {
      //printf("%c", '<');
      --ptr;
      input++;
    }
    else if(*input == '+')
    {
      //printf("%c", '+');
      ++*ptr;
      input++;
    }
    else if(*input == '-')
    {
      //printf("%c", '-');
      --*ptr;
      input++;
    }
    else if(*input == '(')
    {
      if (*ptr == 0)
      {
        int parenCount = 1;
        while (parenCount > 0)
        {
          input++;
          switch (*input)
          {
            case '(': parenCount++; break;
            case ')': parenCount--; break;
            default: break;
          }
        }
      }
      input++;
    //  printf("%c", '(');
      // if (full()){ printf("%s\n", "full"); exit(1); }
			// if (*ptr == 0)
      // {
      //   push(input);
			// 	while(!empty())
			// 	{
      //     ++input;
			// 		if(*input == '(')
      //     {
      //       push(input);
      //     }
			// 		if(*input == ')')
      //     {
      //       pop();
      //     }
			// 	}
      //   input++;
			// }
			// else
      // {
			// 	push(input);
      //   input = interpret(input + 1, ptr);
      //   input++;
			// }
    }
    else if(*input == ')')
    {
      if (*ptr != 0)
      {
        int parenCount = 1;
        while (parenCount > 0)
        {
          input--;
          switch(*input)
          {
            case ')': parenCount++; break;
            case '(': parenCount--; break;
            default: break;
          }
        }
      }
      input++;

      //printf("%c", ')');
      // if(*ptr == 0)
			// {
			// 	pop();
			// 	return input;
			// }
			// else
			// {
			// 	input = save;
			// }
    }
    else if(*input == '*')
    {
    //  printf("%c", '*');
      printf("%c", *ptr);
      input++;
    }
    else
    {
      input++;
    }
  }
  return '\0';
}








int main(int argc, char** argv)
{
  char* ptr = (char*) calloc(100000, 1);
  char* filename = argv[1];
  FILE* fp = fopen(filename, "r");
  if(fp == NULL)
  {
    printf("Uhoh, couldn’t open file!");
    exit(1);
  }

  char * contents;
  fseek (fp, 0, SEEK_END);
  int length = ftell (fp);
  fseek (fp, 0, SEEK_SET);
  contents = malloc(length + 1);
  fread(contents, 1, length, fp);
  fclose(fp);



  clock_t begin = clock();

  printf("%s\n", contents);
  if(isvalid(contents))
  {
    interpret(contents, ptr);
  }
  else
  {
    printf("%s\n", "BAD");
  }


  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent: %f\n", time_spent);
  fclose(fp);
  return 0;

}






// When the Divine Pointress executes a ‘>’ rune, she moves one step to the right, pointing to a new member of the tribe.
// When she executes a ‘<’ rune, she moves one step to the left. See notes on wrapping behavior for what should happen at the boundaries of the data region.
//
// When the Divine Pointress executes a ‘+’ rune, she instructs the person she is currently pointing at to add a pebble to their bag. When she executes a ‘-’ rune,
// she instructs them to remove one. See later notes on wrapping behavior around empty/full bags.
//
// When the Divine Pointress sees a ‘(‘ rune, she asks the person she is currently pointing at how many pebbles are in their bag.
// Depending on the result, she does one of two things:
// If the bag of the current person contains zero pebbles, she skips forward to the next ‘)’ rune on her stone tablet.
// If the bag of the current person has one or more pebbles, she proceeds to execute the next rune on the tablet.
//
// When the Divine Pointress sees a ‘)’ rune, she does one of two things:
// If the bag of the current person contains zero pebbles, she proceeds to execute the next rune on her tablet.
// If the bag of the current person contains one or more pebbles, she jumps back to the prior matching ‘(‘ rune on her stone tablet.










// void convert(char* input)
// {
//   for(i = 0; input[i] != 0; i++)
//   {
//     switch(input[i])
//     {
//       case ">": fputs("ptr++;\n", fp);
//       case "<": fputs("ptr--;\n", fp);
//       case "+": fputs("*ptr++;\n", fp);
//       case "-": fputs("*ptr--;\n", fp);
//       case "(": fputs("while(*ptr){\n", fp);
//       case ")": fputs("}\n", fp);
//       case "*": fputs("printf(\"%s\n\", *ptr);\n", fp);
//       default : continue;
//     }
//   }
//   fputs("}", fp);
//
// }
//
// int main()
// {
//   FILE* fp = fopen("/atcs/test.c", "w");
//   if (fp == NULL)
//   {
//     printf("Uhoh, couldn’t open file!"");
//     exit(1);
//   }
//   fputs("#include <stdio.h>\nchar arr[50000] = {0};\nchar* ptr = arr;\nint main(void) {", fp)
//   convert("++++++++(>++++(>++>+++>+++>+<<<<-)>+>->+>>+(<)<-)>>*>>---*+++++++**+++*>*<<-*>*+++*------*--------*>+*>++*", fp)
//
// }
