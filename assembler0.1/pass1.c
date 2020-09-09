#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>

void pass1()
{
    FILE *input,*optab,*symtab,*input1;
    int location,systemass,line,optable,operation,length,flag=0;
    char m1[20],la[20],op[20],otp[20],locationstr[5];
    input=fopen("input.txt","r");
    symtab=fopen("symtab.txt","w");
    input1=fopen("acode.txt","w");
    fscanf(input,"%s %s %d",la,m1,&optable);
    if(strcmp(m1,"START")==0)
    {
        systemass=optable;
        location=systemass;
        printf("\t%s\t%s\t%d\n",la,m1,optable);
        fprintf(input1,"%d\t%s\t%s\t%d\n",optable,la,m1,optable);
    }
    else
        location=0;
    fscanf(input,"%s %s",la,m1);
    while(!feof(input))
    {
        fscanf(input,"%s",op);
        printf("\n%d\t%s\t%s\t%s\n",location,la,m1,op);
        fprintf(input1,"%d\t%s\t%s\t%s\n",location,la,m1,op);
        if(strcmp(la,"^")!=0)
        {

            itoa(location,locationstr,16);
            fprintf(symtab,"%d\t%s\n",location,la);
        }
        optab=fopen("optab.txt","r");
        fscanf(optab,"%s %d",otp,&operation);
        while(!feof(optab))
        {
            if(strcmp(m1,otp)==0)
            {
                location=location+3;
                flag=1;
                break;
            }
            fscanf(optab,"%s %d",otp,&operation);
        }
        if(flag!=1)
        {
            printf("error\n");
            exit(-1);
        }
        fclose(optab);
        if(strcmp(m1,"WORD")==0)

        {
            location=location+3;
        }
        else if(strcmp(m1,"RESW")==0)
        {
            optable=atoi(op);
            location=location+(3*optable);

        }
        else if(strcmp(m1,"BYTE")==0)
        {
            if(op[0]=='X')
                location=location+1;
            else
            {
                length=strlen(op)-3;
                location=location+length;
            }
        }
        else if(strcmp(m1,"RESB")==0)
        {
            optable=atoi(op);
            location=location+optable;
        }
        fscanf(input,"%s%s",la,m1);
    }
    if(strcmp(m1,"END")==0)
    {
        FILE *length;
        length=fopen("length.txt","w");
        printf("Program length =\n%d",location-systemass);
        fprintf(length,"%d",location-systemass);
        fclose(length);
    }
    fclose(input);
    fclose(symtab);
    fclose(input1);
    getch();
}




int main()
{
    pass1();
     return 0;
}
