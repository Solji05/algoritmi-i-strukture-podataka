#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

struct _Node;
typedef struct _Node * Position;

struct _Node
{
	int Koeficijent;
	int Exponent;
	Position Next;
};

void ReadPolynom(Position);
void PrintPolynom(Position);
void SumPolynom(Position, Position, Position);
void MulPolynom(Position, Position, Position);


void main(void)
{
	struct _Node P, Q, S, M;	
	P.Next = NULL;
	Q.Next = NULL;
	S.Next = NULL;
	M.Next = NULL;

	ReadPolynom(&P);
	ReadPolynom(&Q);
	printf("\r\n");

	printf("\r\nP(x) = ");
	PrintPolynom(P.Next);
	printf("\r\nQ(x) = ");
	PrintPolynom(Q.Next);

	printf("\r\n");
	SumPolynom(P.Next, Q.Next, &S);
	printf("\r\nS(x) = P(x) + Q(x) = ");
	PrintPolynom(S.Next);

	printf("\r\n");
	MulPolynom(P.Next, Q.Next, &M);
	printf("\r\nM(x) = P(x) * Q(x) = ");
	PrintPolynom(M.Next);
	printf("\r\n");
	printf("\r\n");
}

void ReadPolynom(Position P)
{
	char ime_dat[1024];
	FILE *stream;
	Position q, i;

	printf("\r\nUnesite ime datoteke za citanje polinoma : ");
	scanf_s(" %s", ime_dat, 1024);

	fopen_s(&stream, ime_dat, "r");
	if(stream == NULL)
		printf("\r\nGreska!Datoteka %s nije otvorena.", ime_dat);
	else
	{
		while(!feof(stream))
		{
			q = (Position)malloc(sizeof(struct _Node));
			fscanf_s(stream, " %d %d", &q->Koeficijent, &q->Exponent);

			if(q->Koeficijent == 0)
				free(q);
			else
			{
				i = P;
				
				while(i->Next != NULL && i->Next->Exponent > q->Exponent)
					i = i->Next;
				if(i->Next != NULL && i->Next->Exponent == q->Exponent)
				{
					i->Next->Koeficijent += q->Koeficijent;
					free(q);
					if(i->Next->Koeficijent == 0)
					{
						q = i->Next;
						i->Next = q->Next;
						free(q);
					}
				}
				else
				{
					q->Next = i->Next;
					i->Next = q;
				}
			}
		}
		fclose(stream);
	}
}

void PrintPolynom(Position P)
{
	bool first = true;

	while(P != NULL)
	{
		if(first == true)
		{
			if(P->Koeficijent == 1 && P->Exponent == 0)
				printf("1");
			if(P->Koeficijent == -1 && P->Exponent == 0)
				printf("- 1");
			if(P->Koeficijent == 1 && P->Exponent > 0)
				printf("x^%d", P->Exponent);
			if(P->Koeficijent == 1 && P->Exponent < 0)
				printf("x^(%d)", P->Exponent);
			if(P->Koeficijent > 0 && P->Koeficijent != 1 && P->Exponent > 0)
				printf("%dx^%d", P->Koeficijent, P->Exponent);
			if(P->Koeficijent < 0 && P->Koeficijent != -1  && P->Exponent > 0)
				printf("-%dx^%d", (-1) * P->Koeficijent, P->Exponent);
			if(P->Koeficijent > 0 && P->Koeficijent != 1  && P->Exponent < 0)
				printf("%dx^(%d)", P->Koeficijent, P->Exponent);
			if(P->Koeficijent < 0 && P->Koeficijent != -1  && P->Exponent < 0)
				printf("-%dx^(%d)", (-1) * P->Koeficijent, P->Exponent);

			first = false;
		}
		else
		{
			if(P->Koeficijent == 1 && P->Exponent == 0)
				printf(" + 1");
			if(P->Koeficijent == -1 && P->Exponent == 0)
				printf(" - 1");
			if(P->Koeficijent == 1 && P->Exponent > 0)
				printf(" + x^%d", P->Exponent);
			if(P->Koeficijent == 1 && P->Exponent < 0)
				printf(" + x^(%d)", P->Exponent);
			if(P->Koeficijent > 0 && P->Exponent > 0)
				printf(" + %dx^%d", P->Koeficijent, P->Exponent);
			if(P->Koeficijent < 0 && P->Exponent > 0)
				printf(" - %dx^%d", (-1) * P->Koeficijent, P->Exponent);
			if(P->Koeficijent > 0 && P->Exponent < 0)
				printf(" + %dx^(%d)", P->Koeficijent, P->Exponent);
			if(P->Koeficijent < 0 && P->Exponent < 0)
				printf(" - %dx^(%d)", (-1) * P->Koeficijent, P->Exponent);
		}

		P = P->Next;
	}
	printf("\r\n");
}

void SumPolynom(Position P, Position Q, Position S)
{
	Position q, i;
	while(P != NULL && Q != NULL)
	{
		q = (Position)malloc(sizeof(struct _Node));

		if(P->Exponent > Q->Exponent)
		{
			q->Exponent = P->Exponent;
			q->Koeficijent = P->Koeficijent;

			P = P->Next;
		}
		else if(P->Exponent < Q->Exponent)
		{
			q->Exponent = Q->Exponent;
			q->Koeficijent = Q->Koeficijent;

			Q = Q->Next;
		}
		else
		{
			q->Exponent = P->Exponent;
			q->Koeficijent = P->Koeficijent + Q->Koeficijent;

			P = P->Next;
			Q = Q->Next;
		}

		q->Next = S->Next;
		S->Next = q;
		S = S->Next;
	}

	if(P == NULL)
		i = Q;
	else
		i = P;

	while(i != NULL)
	{
		q = (Position)malloc(sizeof(struct _Node));
			
		q->Exponent = i->Exponent;
		q->Koeficijent = i->Koeficijent;

		i = i->Next;

		q->Next = S->Next;
		S->Next = q;
		S = S->Next;
	}
}

void MulPolynom(Position P, Position Q, Position M)
{
	Position q, i, j, tmp;

	i = P;
	while(i != NULL)
	{
		j = Q;
		while(j != NULL)
		{
			q = (Position)malloc(sizeof(struct _Node));

			q->Exponent = i->Exponent + j->Exponent;
			q->Koeficijent = i->Koeficijent * j->Koeficijent;

			tmp = M;

			while(tmp->Next != NULL && tmp->Next->Exponent > q->Exponent)
				tmp = tmp->Next;

			if(tmp->Next != NULL && tmp->Next->Exponent == q->Exponent)
			{
				tmp->Next->Koeficijent += q->Koeficijent;
				free(q);
			}
			else
			{
				q->Next = tmp->Next;
				tmp->Next = q;
			}
			j = j->Next;
		}
		i = i->Next;
	}
}
