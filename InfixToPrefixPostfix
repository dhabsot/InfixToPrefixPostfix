/************************************************************************/
/* Acquisizione da tastiera di un'espressione in notazione infissa e	  */
/* stampa a video le corrispondenti espressioni aritmetiche in notazione*/
/* prefissa	e postfissa, rispettivamente. Per semplicita', assumere che	*/
/* l'espressione di partenza contenga soltanto numeri (no variabili)	  */
/* ed occorrenze dei quattro operatori aritmetici binari (no		        */
/* operatori unari), piu' eventuali parentesi tonde.			              */
/************************************************************************/

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
#define DIMENSIONEMASSIMA 201

/**************************/
/* Dichiarazione funzioni */
/**************************/
void acquisizione_scelta(int *);
void infix_to_postfix(char *,
		                  char [],
		                  char []);
void reverse(char []);
void infix_to_prefix(char *,
		                 char [],
		                 char []);
int acquisisci_espressione(char []);
int operatore(char);
void push(char [],
	        char,
	        int *);
void pop(int *);
int pila_vuota(int);
int precedenza(char,
	             char);
int ottieni_precedenza(char);
void aggiungi_spazio(char [],
		                 int *);


/******************************/
/* Definizione delle funzioni */
/******************************/

/* Definizione della funzione main */
int main(void)
{
	/* Dichiarazione variabili locali alla funzione */
	int  scelta;
	char *espressione_infissa,
	     *espressione_output,
	     *pila;
	int espr_non_valida;
	
	/* Allocazione array */
	espressione_infissa = (char *)calloc(DIMENSIONEMASSIMA,
					                             sizeof(char));
	espressione_output = (char *)calloc(DIMENSIONEMASSIMA * 2,
					                            sizeof(char));
	pila = (char *)calloc(DIMENSIONEMASSIMA,
			                  sizeof(char));
	
	printf("\nIl programma consente di trasformare un'espressione aritmetica\n");
	printf("da notazione infissa a notazione prefissa o postfissa\n");
	printf("(sono ammessi al massimo 200 simboli)");
	
	do
	{
		printf("\n\nMenu':\n");
		printf("1) Da notazione infissa a prefissa\n");
		printf("2) Da notazione infissa a postfissa\n");
		printf("3) Esci\n");
		
		/* Acquisizione scelta */
		acquisizione_scelta(&scelta);
		
		switch(scelta)
		{
			espr_non_valida = 0;
			
			/* Scelta 1: da notazione infissa a prefissa */
			case 1:
				printf("\nInserisci l'espressione aritmetica, in notazione infissa,");
				printf(" da convertire in notazione prefissa:\nEspressione: ");
				
				espr_non_valida = acquisisci_espressione(espressione_infissa);
				
				if (espr_non_valida == 0)
				{
					infix_to_prefix(pila,
							            espressione_infissa,
							            espressione_output);
					printf("\nEspressione prefissa: %s",
					       espressione_output);
				}
				else
					printf("L'espressione inserita non e' valida\n");
				
				memset(espressione_infissa,
				       '\0',
				       DIMENSIONEMASSIMA);
				memset(espressione_output,
				       '\0',
				       DIMENSIONEMASSIMA * 2);
				memset(pila,
				       '\0',
				       DIMENSIONEMASSIMA);
				break;
				
			/* Scelta 2: da notazione infissa a postfissa */
			case 2:
				printf("\nInserisci l'espressione aritmetica, in notazione infissa,");
				printf(" da convertire in notazione postfissa:\nEspressione: ");
				
				espr_non_valida = acquisisci_espressione(espressione_infissa);
				
				if (espr_non_valida == 0)
				{
					infix_to_postfix(pila,
							             espressione_infissa,
							             espressione_output);
					printf("\nEspressione postfissa: %s",
					       espressione_output);
				}
				else
					printf("L'espressione inserita non e' valida");
				
				memset(espressione_infissa,
				       '\0',
				       DIMENSIONEMASSIMA);
				memset(espressione_output,
				       '\0',
				       DIMENSIONEMASSIMA);
				memset(pila,
				       '\0',
				       DIMENSIONEMASSIMA);				
				break;
				
			/* Scelta 3: uscita dal programma */
			case 3:
				printf("\nTerminazione.\n\n");
				break;
		}
	}
	while ((scelta == 1) || (scelta == 2));
	
	return(0);
}

/* Definizione della funzione acquisizione_scelta: */
/* permette l'acquisizione della scelta del menu' (1/2/3) */
void acquisizione_scelta(int *scelta)
{
	/* Dichiarazione variabili locali alla funzione */
	int esito_lettura;
	char carattere_non_letto;
	
	/* Validazione stretta input */
	do
	{
		printf("Scelta: ");
		esito_lettura = scanf("%d",
				                  scelta);
		do
			if (scanf("%c",
				  &carattere_non_letto) != 1);
		while (carattere_non_letto != '\n');
	}
	while ((esito_lettura != 1) || (*scelta < 1) || (*scelta > 3));
}


void infix_to_postfix(char pila[],
		                  char infissa[],
		                  char postfissa[])
{
	/* Dichiarazione variabili locali alla funzione */
	int i,
	    top,
	    j;
	char elem_temp;
	
	/* Inizializzazione variabili */
	j = 0;
	top = 0;
	
	/* Conversione da notazione infissa a postfissa */
	for (i = 0; infissa[i] != '\0'; i++)
	{
		elem_temp = infissa[i];
		
		if (isdigit(elem_temp))
		{
			postfissa[j] = elem_temp;
			j++;
			if((operatore(infissa[i + 1]) == 1) ||
			  ((infissa[i + 1] == ')') && (operatore(infissa[i + 2]) == 1)))
				aggiungi_spazio(postfissa,
						&j);
		}
		else if (elem_temp == '(')
		{
			push(pila,
			     elem_temp,
			     &top);
		}
		else if (elem_temp == ')')
		{
			while ((pila_vuota(top) == 0) && 
			       (pila[top] != '('))
			{
				aggiungi_spazio(postfissa,
						            &j);
				postfissa[j] = pila[top];
				j++;
				pop(&top);
				aggiungi_spazio(postfissa,
						            &j);
			}
			pop(&top);
		}
		else
		{
			while ((pila_vuota(top) == 0) && 
			       (precedenza(pila[top],elem_temp) == 1))
			{
				postfissa[j] = pila[top];
				j++;
				pop(&top);
				aggiungi_spazio(postfissa,
						            &j);
			}
			push(pila,
			     elem_temp,
			     &top);
		}
	}
	while (pila_vuota(top) == 0)
	{
		aggiungi_spazio(postfissa,
				            &j);
		postfissa[j] = pila[top];
		j++;
		pop(&top);
	}
	if(postfissa[strlen(postfissa) - 1] == ' ')
		postfissa[strlen(postfissa) - 1] = '\0';
	else
		postfissa[j] = '\0';
}

/* Definizione funzione reverse: dato in input un array di char lo restituisce inverso */
void reverse(char espressione[])
{
	/* Dichiarazione variabili locali alla funzione */
	int i,
	    j;
	char tmp;
	
	/* Inizializzazione variabili */
	i = (strlen(espressione) - 1);
	j = 0;

	/* Elaborazione array */
	while(i > j)
	{
		tmp = espressione[i];
		espressione[i] = espressione[j];
		espressione[j] = tmp;
		i--;
		j++;
	}
}

void aggiungi_spazio(char espressione[],
		                 int *j)
{
	if(espressione[*j - 1] != ' ')
	{
		espressione[*j] = ' ';
		*j += 1;
	}
}

void infix_to_prefix(char pila[],
		                 char infissa[],
		                 char prefissa[])
{
	/* Dichiarazione variabili locali alla funzione */
	int i,
	    top,
	    j;
	char elem_temp;
	
	/* Inizializzazione variabili */
	j = 0;
	top = 0;
	
	/* Reverse dell'array */
	reverse(infissa);
	
	/* Conversione da notazione infissa a prefissa */
	for (i = 0; infissa[i] != '\0'; i++)
	{
		elem_temp = infissa[i];
		if (isdigit(elem_temp))
		{
			prefissa[j] = elem_temp;
			j++;
			if(operatore(infissa[i + 1]) == 1)
				aggiungi_spazio(prefissa,
						            &j);
		}
		else if (elem_temp == ')')
			push(pila,
			     elem_temp,
			     &top);
		else if (elem_temp == '(')
		{
			while ((pila_vuota(top) == 0) && 
			       (pila[top] != ')'))
			{
				aggiungi_spazio(prefissa,
						&j);
				prefissa[j] = pila[top];
				j++;
				pop(&top);
			}
			aggiungi_spazio(prefissa,
					            &j);
			pop(&top);
		}
		else
		{
			if ((pila_vuota(top) == 0) && 
			    (ottieni_precedenza(pila[top]) <= ottieni_precedenza(elem_temp)))
			{
				push(pila,
				     elem_temp,
				     &top);
			}
			else
			{
				while ((pila_vuota(top) == 0) && 
				       (ottieni_precedenza(pila[top]) >= ottieni_precedenza(elem_temp)))
				{
					prefissa[j] = pila[top];
					j++;
					pop(&top);
					aggiungi_spazio(prefissa,
							&j);				
				}
				push(pila,
				     elem_temp,
				     &top);
			}
		}
	}
	while (pila_vuota(top) == 0)
	{
		aggiungi_spazio(prefissa,
				            &j);
		prefissa[j] = pila[top];
		j++;
		pop(&top);
	}
	
	if(prefissa[strlen(prefissa) - 1] == ' ')
		prefissa[strlen(prefissa) - 1] = '\0';
	
	/* Reverse array */
	reverse(prefissa);
	
	prefissa[j] = '\0';
}

int acquisisci_espressione(char espressione_infissa [])
{
	/* Dichiarazione variabili locali alla funzione */
	int i,
	    j,
	    parentesi,
	    espr_non_valida;
	char *espressione_temp,
	     carattere_non_letto;
	size_t lunghezza_s;
	
	/* Allocazione array temporaneo */
	espressione_temp = (char *)calloc(DIMENSIONEMASSIMA,
					                          sizeof(char));
	
	/* Acquisizione stringa */
	if (fgets(espressione_temp,
		        DIMENSIONEMASSIMA,
		        stdin));
	
	lunghezza_s = strlen(espressione_temp);

	/* Pulizia buffer, se necessario */
	if (espressione_temp[lunghezza_s - 1] == '\n')
		espressione_temp[lunghezza_s - 1] = 0;	
	else
	{
		printf("L'espressione inserita e' troppo lunga, ");
		printf("verranno acquisiti i primi 200 simboli.\n");
		while ((carattere_non_letto != '\n') && (carattere_non_letto != EOF))
			carattere_non_letto = getchar();
	}
	
	/* Inizializzazione variabili locali */
	parentesi = 0;
	i = 0;
	j = 0;
	espr_non_valida = 0;	
	
	/* Valutazione ed elaborazione stringa acquisita */
	do
	{
		/* Verifica se il carattere in esame e' un numero, un operatore o parentesi */
		if (((isdigit(espressione_temp[i])) ||
		    (espressione_temp[i] == '(') ||
		    (espressione_temp[i] == ')') ||
		    (operatore(espressione_temp[i]) == 1)))
		{
			/* Verifica se nell'espressione ci sono due operatori consecutivi */
			if ((i > 0) &&
			    (operatore(espressione_temp[i]) == 1) &&
			    (operatore(espressione_temp[i - 1]) == 1))
				espr_non_valida = 1;
			/* Verifica se nell'espressione c'e' un operatore seguito da ')' */
			else if((operatore(espressione_temp[i]) == 1) &&
				      (espressione_temp[i + 1] == ')'))
				espr_non_valida = 1;
			/* Verifica se nell'espressione c'e' '(' seguito da un operatore */
			else if((espressione_temp[i] == '(') &&
				      (operatore(espressione_temp[i + 1]) == 1))
				espr_non_valida = 1;
			else
			{
				espressione_infissa[j] = espressione_temp[i];
				j++;
			}
		}
		
		/* Contatore e check di parentesi */
		if (espressione_temp[i] == '(')
		{
			parentesi++;
			if ((i != 0) && (espressione_temp[i - 1] == ')'))
				espr_non_valida = 1;				
		}
		else if (espressione_temp[i] == ')')
		{
			parentesi--;
			if ((i != 0) && (espressione_temp[i - 1] == '('))
				espr_non_valida = 1;
		}
		if (parentesi < 0)
			espr_non_valida = 1;
		
		i++;
	}while ((espressione_temp[i] != '\0') && (espr_non_valida != 1));

	/* Verifica se il numero di parentesi finale e' valido */
	if(parentesi != 0)
		espr_non_valida = 1;
	/* Verifica se il primo carattere e' un operatore */
	if ((operatore(espressione_infissa[0]) == 1))
		espr_non_valida = 1;
	/* Verifica se l'ultimo carattere e' un operatore */
	if (operatore(espressione_infissa[strlen(espressione_infissa) - 1]) == 1)
		espr_non_valida = 1;
	/* Verifica se la stringa acquisita e' vuota */
	if (espressione_infissa[0] == '\0')
		espr_non_valida = 1;
	
	/* Disallocazione array temporaneo */
	free(espressione_temp);
	
	return espr_non_valida;
}


/* Definizione della funzione operatore: restituisce 1 se 	*/
/* l'elemento in input e' un operatore,	0 altrimenti		*/
int operatore(char el)
{
	int val = 0;
	
	if ((el == '+') ||
	    (el == '-') ||
	    (el == '*') ||
	    (el == '/'))
		val = 1;
	return val;
}

/* Definizione della funzione push: inserisce un elemento nel top della pila */
void push(char pila [],
	  char elem,
	  int *top) 
{
	if (*top == (DIMENSIONEMASSIMA - 1))
		printf("Errore\n");
	else
		pila[*top += 1] = elem;		
}

/* Definizione della funzione pop: estrae un elemento dal top della pila */
void pop(int *top) 
{
	if (*top == -1)
		printf("Errore: nessun elemento di cui fare il pop\n");
	else
		*top -= 1;
}

/* Definizione funzione pila_vuota: restituisce 1 se la pila e' vuota, 0 altrimenti */
int pila_vuota(int top)
{
	/* Dichiarazione variabile locale alla funzione */
	int val = 0;

	/* Check del valore al top della pila */
	if (top == -1) 
		val = 1;

    return val;
}

/* Definizione della funzione precedenza: restituisce 1 se il primo elemento	*/
/* dato in input ha precedenza minore o uguale del secondo, 0 altrimenti		*/			
int precedenza(char top, char elem)
{
	return ottieni_precedenza(elem) <= ottieni_precedenza(top) ? 1:0;
}

/* Definizione funzione ottieni_precedenza: restituisce un valore di precedenza tra gli operatori */
int ottieni_precedenza(char el)
{
	/* Dichiarazione variabile locale alla funzione */
	int prec = -1;
	
	/* Assegnazione valore di precedenza a seconda dell'operatore dato in input */
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
