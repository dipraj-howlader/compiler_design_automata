#include<stdio.h>
#include<conio.h>
void main()
{
    char s[5];
    printf("Enter any operator: ");
    gets(s);
    switch(s[0])
    {
    case'>':
        if(s[1]=='=')
            printf("\nGreater than or equal");
        else
            printf("\nGreater than");
        break;
    case'<':
        if(s[1]=='=')
            printf("\nLess than or equal");
        else
            printf("\nLess than");
        break;
    case'=':
        if(s[1]=='=')
            printf("\nEqual to");
        else
            printf("\nAssignment");
        break;
    case'!':
        if(s[1]=='=')
            printf("\nNot Equal");
        else
            printf("\nBit Not");
        break;
    case'&':
        if(s[1]=='&')
            printf("\nLogical AND");
        else
            printf("\nBitwise AND");
        break;
    case'|':
        if(s[1]=='|')
            printf("\nLogical OR");
        else
            printf("\nBitwise OR");
        break;
    case'+':
        printf("\nAddition");
        break;
    case'-':
        printf("\nSubstraction");
        break;
    case'*':
        printf("\nMultiplication");
        break;
    case'/':
        printf("\nDivision");
        break;
    case'%':
        printf("Modulus");
        break;
    default:
        printf("\nNot a operator");
    }
    getch();
}
