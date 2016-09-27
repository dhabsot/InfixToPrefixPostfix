/********************************************************************************/
/* Acquisizione da tastiera di un'espressione in notazione infix e		*/
/* stampa a video le corrispondenti espressioni aritmetiche in notazione	*/
/* prefissa	e postfix, rispettivamente. Per semplicita', assumere che	*/
/* l'espressione di partenza contenga soltanto numeri (no variabili)	  	*/
/* ed occorrenze dei quattro operatori aritmetici binari (no		        */
/* operatori unari), piu' eventuali parenthesis tonde.	     			*/
/********************************************************************************/

/*****************************/
/* Inclusione delle librerie */
/*****************************/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/***********************************/
/* Definizione costanti simboliche */
/***********************************/
#define MAXDIMENSION 201

/**************************/
/* Dichiarazione funzioni */
/**************************/
void choice_acquisition(int *);
void infix_to_postfix(char *,
		      char [],
		      char []);
void reverse(char []);
void infix_to_prefix(char *,
		     char [],
		     char []);
int acquire_expression(char []);
int operator(char);
void push(char [],
	  char,
	  int *);
void pop(int *);
int empty_stack(int);
int precedence(char,
	       char);
int acquire_precedence(char);
void add_space(char [],
	             int *);

/******************************/
/* Definizione delle funzioni */
/******************************/

/* Definizione della funzione main */
int main(void)
{
	/* Dichiarazione variabili locali alla funzione */
	int  choice;
	char *infix_expression,
	     *output_expression,
	     *stack;
	int not_valid_expression;
	
	/* Allocazione array */
	infix_expression = (char *)calloc(MAXDIMENSION,
		                             sizeof(char));
	output_expression = (char *)calloc(MAXDIMENSION * 2,
		                            sizeof(char));
	stack = (char *)calloc(MAXDIMENSION,
	                      sizeof(char));
	
	printf("The program can transform an arithmetic expression in \n");
	printf("infix notation into prefix or postfix notation\n");
	printf("(allowed only 200 symbols)");
	
	do
	{
		printf("\n\nMenu':\n");
		printf("1) Infix notation to prefix notation\n");
		printf("2) Infix notation to postfix notation\n");
		printf("3) Exit\n");
		
		/* Acquisizione choice */
		choice_acquisition(&choice);
		
		switch(choice)
		{
			not_valid_expression = 0;
			
			/* Choice 1: from infix to prefix notation */
			case 1:
				printf("Insert the arithmetic expression, in infix notation,");
				printf(" to convert it in prefix notation.\nExpression: ");
				
				not_valid_expression = acquire_expression(infix_expression);
				
				if (not_valid_expression == 0)
				{
					infix_to_prefix(stack,
						        infix_expression,
						        output_expression);
					printf("\nPrefix notation: %s",
					       output_expression);
				}
				else
					printf("The inserted expression is not valid.\n");
				
				memset(infix_expression,
				       '\0',
				       MAXDIMENSION);
				memset(output_expression,
				       '\0',
				       MAXDIMENSION * 2);
				memset(stack,
				       '\0',
				       MAXDIMENSION);
				break;
				
			/* Choice 1: from infix to postfix notation */
			case 2:
				printf("Insert the arithmetic expression, in infix notation,");
				printf(" to convert it in postfix notation.\nExpression: ");
				
				not_valid_expression = acquire_expression(infix_expression);
				
				if (not_valid_expression == 0)
				{
					infix_to_postfix(stack,
						         infix_expression,
						         output_expression);
					printf("\nPostfix notation: %s",
					       output_expression);
				}
				else
					printf("The inserted expression is not valid.");
				
				memset(infix_expression,
				       '\0',
				       MAXDIMENSION);
				memset(output_expression,
				       '\0',
				       MAXDIMENSION);
				memset(stack,
				       '\0',
				       MAXDIMENSION);				
				break;
				
			case 3:
				printf("\Exiting.\n\n");
				break;
		}
	}
	while ((choice == 1) || (choice == 2));
	
	return(0);
}

/* This method allows the acquisition of the menu' choice (1/2/3) */
void choice_acquisition(int *choice)
{
	int scanning;
	char not_read_char;
	
	/* This do-while allows only 1-2-3 numbers */
	do
	{
		printf("Choice: ");
		scanning = scanf("%d",
				      choice);
		do
			if (scanf("%c",
				  &not_read_char) != 1);
		while (not_read_char != '\n');
	}
	while ((scanning != 1) || (*choice < 1) || (*choice > 3));
}


void infix_to_postfix(char stack[],
		      char infix[],
		      char postfix[])
{
	int i,
	    top,
	    j;
	char elem_temp;
	
	j = 0;
	top = 0;
	
	/* Infix to postfix conversion */
	for (i = 0; infix[i] != '\0'; i++)
	{
		elem_temp = infix[i];
		
		if (isdigit(elem_temp))
		{
			postfix[j] = elem_temp;
			j++;
			if((operator(infix[i + 1]) == 1) ||
			  ((infix[i + 1] == ')') && (operator(infix[i + 2]) == 1)))
				add_space(postfix,
						&j);
		}
		else if (elem_temp == '(')
		{
			push(stack,
			     elem_temp,
			     &top);
		}
		else if (elem_temp == ')')
		{
			while ((empty_stack(top) == 0) && 
			       (stack[top] != '('))
			{
				add_space(postfix,
				                &j);
				postfix[j] = stack[top];
				j++;
				pop(&top);
				add_space(postfix,
				                &j);
			}
			pop(&top);
		}
		else
		{
			while ((empty_stack(top) == 0) && 
			       (precedence(stack[top],elem_temp) == 1))
			{
				postfix[j] = stack[top];
				j++;
				pop(&top);
				add_space(postfix,
				                &j);
			}
			push(stack,
			     elem_temp,
			     &top);
		}
	}
	while (empty_stack(top) == 0)
	{
		add_space(postfix,
			        &j);
		postfix[j] = stack[top];
		j++;
		pop(&top);
	}
	if(postfix[strlen(postfix) - 1] == ' ')
		postfix[strlen(postfix) - 1] = '\0';
	else
		postfix[j] = '\0';
}

/* Reverse array */
void reverse(char espressione[])
{
	int i,
	    j;
	char tmp;
	
	i = (strlen(espressione) - 1);
	j = 0;

	while(i > j)
	{
		tmp = espressione[i];
		espressione[i] = espressione[j];
		espressione[j] = tmp;
		i--;
		j++;
	}
}

void add_space(char espressione[],
	             int *j)
{
	if(espressione[*j - 1] != ' ')
	{
		espressione[*j] = ' ';
		*j += 1;
	}
}

void infix_to_prefix(char stack[],
		     char infix[],
		     char prefissa[])
{
	int i,
	    top,
	    j;
	char elem_temp;
	
	j = 0;
	top = 0;
	
	reverse(infix);
	
	/* Infix to prefix conversion */
	for (i = 0; infix[i] != '\0'; i++)
	{
		elem_temp = infix[i];
		if (isdigit(elem_temp))
		{
			prefissa[j] = elem_temp;
			j++;
			if(operator(infix[i + 1]) == 1)
				add_space(prefissa,
						&j);
		}
		else if (elem_temp == ')')
			push(stack,
			     elem_temp,
			     &top);
		else if (elem_temp == '(')
		{
			while ((empty_stack(top) == 0) && 
			       (stack[top] != ')'))
			{
				add_space(prefissa,
						&j);
				prefissa[j] = stack[top];
				j++;
				pop(&top);
			}
			add_space(prefissa,
					&j);
			pop(&top);
		}
		else
		{
			if ((empty_stack(top) == 0) && 
			    (acquire_precedence(stack[top]) <= acquire_precedence(elem_temp)))
			{
				push(stack,
				     elem_temp,
				     &top);
			}
			else
			{
				while ((empty_stack(top) == 0) && 
				       (acquire_precedence(stack[top]) >= acquire_precedence(elem_temp)))
				{
					prefissa[j] = stack[top];
					j++;
					pop(&top);
					add_space(prefissa,
							&j);				
				}
				push(stack,
				     elem_temp,
				     &top);
			}
		}
	}
	while (empty_stack(top) == 0)
	{
		add_space(prefissa,
				&j);
		prefissa[j] = stack[top];
		j++;
		pop(&top);
	}
	
	if(prefissa[strlen(prefissa) - 1] == ' ')
		prefissa[strlen(prefissa) - 1] = '\0';
	
	reverse(prefissa);
	
	prefissa[j] = '\0';
}

int acquire_expression(char infix_expression [])
{
	int i,
	    j,
	    parenthesis,
	    not_valid_expression;
	char *temp_expression,
	     not_read_char;
	size_t lenght_s;
	
	/* Temp array */
	temp_expression = (char *)calloc(MAXDIMENSION,
					  sizeof(char));
	
	/* Acquire string from the input */
	if (fgets(temp_expression,
		  MAXDIMENSION,
		  stdin));
	
	lenght_s = strlen(temp_expression);

	/* Buffer cleaning, if it's necessary */
	if (temp_expression[lenght_s - 1] == '\n')
		temp_expression[lenght_s - 1] = 0;	
	else
	{
		printf("The inserted expression is too long, ");
		printf("only the first 200 symbols will be acquired.\n");
		while ((not_read_char != '\n') && (not_read_char != EOF))
			not_read_char = getchar();
	}
	
	parenthesis = 0;
	i = 0;
	j = 0;
	not_valid_expression = 0;	
	
	do
	{
		if (((isdigit(temp_expression[i])) ||
		    (temp_expression[i] == '(') ||
		    (temp_expression[i] == ')') ||
		    (operator(temp_expression[i]) == 1)))
		{
			if ((i > 0) &&
			    (operator(temp_expression[i]) == 1) &&
			    (operator(temp_expression[i - 1]) == 1))
				not_valid_expression = 1;
			else if((operator(temp_expression[i]) == 1) &&
				(temp_expression[i + 1] == ')'))
				not_valid_expression = 1;
			else if((temp_expression[i] == '(') &&
			 	(operator(temp_expression[i + 1]) == 1))
				not_valid_expression = 1;
			else
			{
				infix_expression[j] = temp_expression[i];
				j++;
			}
		}
		
		if (temp_expression[i] == '(')
		{
			parenthesis++;
			if ((i != 0) && (temp_expression[i - 1] == ')'))
				not_valid_expression = 1;				
		}
		else if (temp_expression[i] == ')')
		{
			parenthesis--;
			if ((i != 0) && (temp_expression[i - 1] == '('))
				not_valid_expression = 1;
		}
		if (parenthesis < 0)
			not_valid_expression = 1;
		
		i++;
	}while ((temp_expression[i] != '\0') && (not_valid_expression != 1));

	if(parenthesis != 0)
		not_valid_expression = 1;
	if ((operator(infix_expression[0]) == 1))
		not_valid_expression = 1;
	if (operator(infix_expression[strlen(infix_expression) - 1]) == 1)
		not_valid_expression = 1;
	if (infix_expression[0] == '\0')
		not_valid_expression = 1;
	
	free(temp_expression);
	
	return not_valid_expression;
}

int operator(char el)
{
	int val = 0;
	
	if ((el == '+') ||
	    (el == '-') ||
	    (el == '*') ||
	    (el == '/'))
		val = 1;
	return val;
}

void push(char stack [],
	  char elem,
	  int *top) 
{
	if (*top == (MAXDIMENSION - 1))
		printf("Errore\n");
	else
		stack[*top += 1] = elem;		
}

void pop(int *top) 
{
	if (*top == -1)
		printf("Errore: nessun elemento di cui fare il pop\n");
	else
		*top -= 1;
}

int empty_stack(int top)
{
	int val = 0;

	if (top == -1) 
		val = 1;

    return val;
}
		
int precedence(char top, char elem)
{
	return acquire_precedence(elem) <= acquire_precedence(top) ? 1:0;
}

int acquire_precedence(char el)
{
	int prec = -1;
	
	switch(el)
	{
		case ')':
			prec = 0;
			break;
		case '+':
			prec = 1;
			break;
		case '-':
			prec = 1;
			break;
		case '*':
			prec = 2;
			break;
		case '/':
			prec = 2;
			break;
	}
	return prec;
}
