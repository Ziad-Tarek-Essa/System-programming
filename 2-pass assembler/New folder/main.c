#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>

int sti(char a[])
{
    int c,sign,offset,n;
    if(a[0]=='-')sign=-1;
    if(sign==-1)offset=1;
    else offset=0;
    n=0;
    for(c=offset; a[c]!='\0'; c++)
        n=n*10+a[c]-'0';
    if(sign==-1)n=-n;
    return n;
}


void pass2(int c)
{
    FILE *input1,*length,*optab,*symbol1;
    int op1[10],txtlen,txtlen1,i,j=0,len,startX,operandX,counter=0,symaddX,addX;
    char add[5],op[5],start[10],temp[30],line[20],label[20],mne[10],operand[10],symtab[10],opmne[10],symadd[10];
    input1=fopen("input1.txt","r");
    length=fopen("length.txt","r");
    //symbol1=fopen("symtab.txt","r");
    //optab=fopen("optab.txt","r");
    fscanf(input1,"%s%s%s%s",add,label,mne,operand);

    if(strcmp(mne,"START")==0)
    {
        strcpy(start,operand);
        fscanf(length,"%d",&len);
    }
    startX=sti(start);
    printf("H^%s^%06X^%06X",label,startX,len,startX);
    for(i=0;i<c;i++)
    {
    fscanf(input1,"%s%s%s%s",add,label,mne,operand);

    while(strcmp(mne,"END")!=0)
    {
        if(counter%10==0)
        {
            addX=sti(add);
            printf("\nT^%06X^",addX);

        }
        optab=fopen("optab.txt","r");
        fscanf(optab,"%s%s",opmne,op);
        while(!feof(optab))
        {
            if(!strcmp(mne,opmne))
            {
                symbol1=fopen("symtab.txt","r");
                fscanf(symbol1,"%s%s",symadd,symtab);
                while(!feof(symbol1))
                {
                    if(strcmp(operand,symtab)==0)
                    {
                        symaddX=sti(symadd);

                        printf("%s%04X^",op,symaddX);
                        counter++;
                        fclose(symbol1);
                        fclose(optab);
                        break;
                    }
                    else
                        fscanf(symbol1,"%s%s",symadd,symtab);
                }
                break;
            }
            else
            {
                fscanf(optab,"%s%s",opmne,op);
            }
        }
        if(strcmp(mne,"WORD")==0)
        {
            operandX=sti(operand);
            printf("%06X^",operandX);
            counter++;
        }
        if(strcmp(mne,"BYTE")==0)
        {
            if(operand[0]=='C')
            {
                len=strlen(operand);
                for(i=2; i<strlen(operand)-1; i++)
                {
                    printf("%X",operand[i]);
                }
                counter++;
            }
            if(operand[0]=='X')
            {
                len=strlen(operand);
                for(i=2; i<strlen(operand)-1; i++)
                {
                    printf("%c",operand[i]);
                }
                counter++;
            }
            if(operand[i]!='\'')
            {
                printf("\n%c\n",operand[i]);
                printf("\nerror\n");
                exit(-1);
            }
            printf("^");
        }
        fscanf(input1,"%s%s%s%s",add,label,mne,operand);
        optab=fopen("optab.txt","r");
        fseek(optab,SEEK_SET,0);
        //counter++;
        //printf("\ncount=%d\n",counter);
    }
    }
    printf("\nE^%06X",startX);
    fclose(input1);
    fclose(optab);
    fclose(symbol1);
    fclose(length);
    getch();

}
int counters()
{
    FILE *f=fopen("input1.txt","r");
    float c=0,le;
    char a[15],l[15],o[15],r[15];
    fscanf(f,"%s%s%s%s",a,l,o,r);

    while(!feof(f))
    {
        if(!(strcmp(o,"START")==0||strcmp(o,"RESB")==0||strcmp(o,"RESW")==0||strcmp(o,"END")==0))
        {
            if(strcmp(o,"BYTE")==0){
                    if(r[0]=='C')
                    {
                        le=strlen(r)-3;
                        c=c+le;
                    }
                    else if(r[0]=='X')
                    {
                        c++;
                    }
            }
            else
                {
                    c=c+3;
                }
    }
    fscanf(f,"%s%s%s%s",a,l,o,r);

    }
    fclose(f);
    c=c/30;
    c=ceil(c);
    return (int)c;

}

int main()
{

    printf("\n");
    int c=counters();
    pass2(c);

    return 0;
}
