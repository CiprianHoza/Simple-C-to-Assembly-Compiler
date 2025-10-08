#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registri
{
char a[5], b[5], c[5], d[5];
} registri;

int isitmov(char tokeni[][10], int k)
{
if (strstr("abcd", tokeni[0]) && k - 1 == 3)
	return 1;
return 0;
}

int isitarithmetic(char tokeni[][10], int k)
{
if (strstr("abcd", tokeni[0]) && k - 1 == 5)
	return 1;
return 0;
}

char *whichreg(registri *r, char reg)
{
if (reg == 'a')
	return r->a;
else if (reg == 'b')
	return r->b;
else if (reg == 'c')
	return r->c;
return r->d;
}

	void printmov(char tokeni[][10], registri r)
	{
	printf("MOV ");
	char *reg;
	reg = whichreg(&r, tokeni[0][0]);
	printf("%s, ", reg);
	if (strstr("abcd", tokeni[2])) {
		reg = whichreg(&r, tokeni[2][0]);
		printf("%s\n", reg);
	} else {
		printf("%s\n", tokeni[2]);
	}
	}

	void printlassh(char tokeni[][10], registri r)
	{
	if (tokeni[3][0] == '&')
		printf("AND ");
	else if (tokeni[3][0] == '|')
		printf("OR ");
	else if (tokeni[3][0] == '^')
		printf("XOR ");
	else if (tokeni[3][0] == '+')
		printf("ADD ");
	else if (tokeni[3][0] == '-')
		printf("SUB ");
	else if (strcmp(tokeni[3], "<<") == 0)
		printf("SHL ");
	else if (strcmp(tokeni[3], ">>") == 0)
		printf("SHR ");
	char *reg = whichreg(&r, tokeni[0][0]);
	printf("%s, ", reg);
	if (strstr("abcd", tokeni[4])) {
		reg = whichreg(&r, tokeni[4][0]);
		printf("%s\n", reg);
	} else {
		printf("%s\n", tokeni[4]);
	}
	}

	void printmd(char tokeni[][10], registri r)
	{
	char *reg;
	if (tokeni[0][0] == 'a') {
		if (tokeni[3][0] == '*')
			printf("MUL ");
	else if (tokeni[4][0] != '0')
		printf("DIV ");
	else
	{
		printf("Error\n");
		return;
	}
	if (strstr("abcd", tokeni[4])) {
		reg = whichreg(&r, tokeni[4][0]);
		printf("%s\n", reg);
	} else {
		printf("%s\n", tokeni[4]);
	}
	} else {
		char aux_tok[4][10];
		memset(aux_tok, 0, sizeof(aux_tok));
		aux_tok[0][0] = 'a';
		aux_tok[1][0] = '=';
		aux_tok[2][0] = tokeni[0][0];
		if ((tokeni[3][0] == '/' && tokeni[4][0] != '0') || tokeni[3][0] == '*')
			printmov(aux_tok, r);
		if (tokeni[3][0] == '*')
			printf("MUL ");
		else if (tokeni[4][0] != '0')
			printf("DIV ");
		else
		{
			printf("Error\n");
			return;
		}
		if (strstr("abcd", tokeni[4])) {
			reg = whichreg(&r, tokeni[4][0]);
			printf("%s\n", reg);
		} else {
			printf("%s\n", tokeni[4]);
		}
		aux_tok[0][0] = tokeni[0][0];
		aux_tok[1][0] = '=';
		aux_tok[2][0] = 'a';
		printmov(aux_tok, r);
	}
	}

char *whatcond(char token[])
{
static char cond[4];
memset(cond, 0, sizeof(cond));
if (strcmp("==", token) == 0)
	strcpy(cond, "JNE");
else if (strcmp("!=", token) == 0)
	strcpy(cond, "JE");
else if (strcmp(">", token) == 0)
	strcpy(cond, "JLE");
else if (strcmp(">=", token) == 0)
	strcpy(cond, "JL");
else if (strcmp("<", token) == 0)
	strcpy(cond, "JGE");
else
	strcpy(cond, "JG");
return cond;
}

void printif(char tokeni[][10], registri r)
{
printf("CMP ");
char *reg = whichreg(&r, tokeni[1][0]);
printf("%s, %s\n", reg, tokeni[3]);
printf("%s end_label\n", whatcond(tokeni[2]));
}

void printwhile(char tokeni[][10], registri r)
{
printf("start_loop:\n");
printf("CMP ");
char *reg = whichreg(&r, tokeni[1][0]);
printf("%s, %s\n", reg, tokeni[3]);
printf("%s end_label\n", whatcond(tokeni[2]));
}

void printfor(char tokeni[][10], registri r)
{
char *reg = whichreg(&r, tokeni[1][0]);
printf("MOV %s, %s\n", reg, tokeni[3]);
printf("start_loop:\n");
printf("CMP %s, %s\n", reg, tokeni[6]);
printf("%s end_label\n", whatcond(tokeni[5]));
}

void remove_whitespaces(char token[][10])
{
char t = token[0][strlen(token[0]) - 1];
strcpy(token[0], &t);
}

	int main(void)
	{
	registri r;
	int k, ifactive = 0, whileactive = 0, foractive = 0;
	char *reg;
	strcpy(r.a, "eax");
	strcpy(r.b, "ebx");
	strcpy(r.c, "ecx");
	strcpy(r.d, "edx");
	char tokeni[20][10], sep[20] = " ;(){";
	char token[30];
	while (fgets(token, 30, stdin))
	{
		k = 0;
		char *p = strtok(token, sep);
		while (p)
		{
			strcpy(tokeni[k++], p);
			p = strtok(NULL, sep);
		}
		if ((ifactive == 1 || whileactive == 1 || foractive == 1))
			if (tokeni[0][0] != '}')
				remove_whitespaces(&tokeni[0]);
		if (isitmov(tokeni, k))
			printmov(tokeni, r);
		else if (isitarithmetic(tokeni, k))
		{
			if (strchr("*/", tokeni[3][0]))
				printmd(tokeni, r);
			else
				printlassh(tokeni, r);
		} else if (strcmp("if", tokeni[0]) == 0)
		{
			ifactive = 1;
			printif(tokeni, r);
		} else if (strcmp("while", tokeni[0]) == 0)
		{
			whileactive = 1;
			printwhile(tokeni, r);
		} else if (strcmp("for", tokeni[0]) == 0)
		{
			foractive = 1;
			reg = whichreg(&r, tokeni[1][0]);
			printfor(tokeni, r);
		} else if (tokeni[0][0] == '}')
		{
			if (ifactive == 1)
			{
				printf("end_label:\n");
				ifactive = 0;
			} else if (whileactive == 1)
			{
				printf("JMP start_loop\n");
				printf("end_label:\n");
				whileactive = 0;
			} else {
				printf("ADD %s, 1\n", reg);
				printf("JMP start_loop\n");
				printf("end_loop:\n");
				foractive = 0;
			}
		}
	}
	return 0;
	}
