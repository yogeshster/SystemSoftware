#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *fp1,*fp2,*fp3,*fp4,*fp5;
char stad[10],iop[30][30];
int fi,op=0,sym=0,flag,flag1=0,io=0,flag2=0,flagad=0,flags=0,flage=0,resbno,pgmlngth,starting;

struct opt
{
	char c[20];
}temp[30];

struct symtab
{
	char symbol[30];
	int address;
	int flagt;
}symt[30];



int power(int a,int n)
{
	int i,b=1;
	if(n==0)
	{
		return 1;
	}
	else
	{
		for(i=1;i<=a;i++)
		{
			b=b*n;
		}
		return b;
	}
}

int hexa(int a)
{
	int b=0,n=0;
	while(a!=0)
	{
		b=b+((a%10)*(power(n,16)));
		a=a/10;
		n++;
	}
	return b;
}



void optab()
{
	int i;
	char str[20],str1[20];
	fp1=fopen("SIC.txt","r");
	fscanf(fp1,"%s",str);
	if(strcmp(str,"START")==0)
	{
		fscanf(fp1,"%s",stad);
		flagad=1;
	}
	fclose(fp1);
	fp1=fopen("SIC.txt","r");
	fp2=fopen("optab.txt","w+");
	while(!feof(fp1))
	{
		flag=0;
		fscanf(fp1,"%s",str);
		fp3=fopen("validop.txt","r");
		while(!feof(fp3))
		{	
			flag=0;
			fscanf(fp3,"%s",str1);
			if(strcmp(str,str1)==0)
			{
				for(i=0;i<=op;i++)
				{
					if(strcmp(str1,temp[i].c)==0)
					{
						flag=1;
					}
				}
				if(flag!=1)
				{
					strcpy(temp[op++].c,str1);
					fprintf(fp2,"%s\t",str);
					fscanf(fp3,"%s",str1);
					fprintf(fp2,"%s\n",str1);
				}
			}
		}
		fclose(fp3);
	}
	fclose(fp1);
	fclose(fp2);
}

void symboltable()
{
	int i,j,add,addprev;
	char str[30],str1[30],str2[30],temp[30];
	fp1=fopen("SIC.txt","r");
	if(flagad!=1)
	{
		starting=0;
		add=-3;
	}
	else
	{
		add=atoi(stad);
		add=hexa(add);
		starting=add;
		add=add-3;
	}
	while(!feof(fp1))
	{
		flags=flag1=0;
		b1:
		fscanf(fp1,"%s",str);
		if(strcmp(str,"END")==0)
		{
			goto a1;
		}
		if(strcmp(str,"START")==0)
		{
			fscanf(fp1,"%s",str);
			goto b1;
		}
		fp2=fopen("validop.txt","r");
		while(!feof(fp2))
		{
			fscanf(fp2,"%s",str1);
			if(strcmp(str,str1)==0)
			{
				flags=1;
			}
		}
		fclose(fp2);
		if(flags!=1)
		{
			flag2=flage=flag=flag1=0;
			strcpy(temp,str);
			/*fscanf(fp3,"%s",str2);
			while(strcmp(str,str2)!=0)
			{
				fscanf(fp3,"%s",str2);
				fscanf(fp3,"%s",str2);
			}
			fscanf(fp3,"%s",str2);
			printf("%s\t%s\n",str,str2);
			if(strcmp(str2,"BYTE")==0)
			{
				flag1=1;
			}*/
			fscanf(fp1,"%s",str);
			if((strcmp(str,"BYTE")==0))
			{
				flag1=1;
			}
			else if(strcmp(str,"RESB")==0)
			{
				flag1=2;
			}
			else if(strcmp(str,"RESW")==0)
			{
				flag1=3;
			}
			fp2=fopen("validop.txt","r");
			while(!feof(fp2))
			{
				fscanf(fp2,"%s",str1);
				{
					if(strcmp(str,str1)==0)
					{
						flag=1;
					}
				}
			}
			fclose(fp2);
			if((flag!=1)&&((strcmp(str,"BYTE")!=0)&&(strcmp(str,"WORD")!=0)&&(strcmp(str,"RESB")!=0)&&(strcmp(str,"RESW")!=0)))
			{
				flage=1;
				goto b1;
			}
			if(flag!=1)
			{
				for(i=0;i<=sym;i++)
				{
					if(strcmp(symt[i].symbol,temp)==0)
					{
						symt[i].flagt=1;
						flag2=1;
					}
				}
				if(flag2!=1)
				{
					strcpy(symt[sym].symbol,temp);
					if(flag1==1)
					{
						add++;
						symt[sym++].address=(add-1)+3;
						symt[sym].address=add;
					}
					else if(flag1==0)
					{
						add=add+3;
						symt[sym++].address=add;
					}

				}
			}
			else
			{
				add=add+3;
			}
		}
		else
		{
			add=add+3;
		}
		fscanf(fp1,"%s",str);
		if(flag1==2)
                {
                        resbno=atoi(str);
                        add=add+resbno;
                        symt[sym++].address=((add-resbno)+3);
			symt[sym].address=add;
                }
		else if(flag1==3)
		{
			resbno=atoi(str);
			add=add+(3*resbno);
			symt[sym++].address=((add-(3*resbno)+3));
			symt[sym].address=add;
		}
		/*if(flag1==1)
		{
			add++;
			symt[sym++].address=(add-1)+3;
			symt[sym].address=add;
		}
		else
		{
			add=add+3;
			symt[sym++].address=add;
		}
		symt[sym++].address=add;*/
	}
	a1:
	fclose(fp1);
	fp1=fopen("symtab.txt","w+");
	fprintf(fp1,"Symbol\t");
	fprintf(fp1,"Address\t");
	fprintf(fp1,"Flag\n");
	for(i=0;i<sym;i++)
	{
		fprintf(fp1,"%s\t",symt[i].symbol);
		fprintf(fp1,"%4x\t",symt[i].address);
		fprintf(fp1,"%d\n",symt[i].flagt);
	}
	fprintf(fp1,"\nDuplicate Symbol(s):\n");
	for(i=0;i<sym;i++)
	{
		if(symt[i].flagt!=0)
		{
			fprintf(fp1,"%s\n",symt[i].symbol);
		}
	}
	fclose(fp1);
}


void intermediate()
{
	int i,j,add;
	char str[30],str1[30],str2[30],temp[30],temp1[30];
	flage=0;
	fp1=fopen("SIC.txt","r");
	fp3=fopen("intermediate.txt","w+");
	if(flagad!=1)
	{
		add=0;
	}
	else
	{
		add=atoi(stad);
		add=hexa(add);
	}
	while(!feof(fp1))
	{
		flags=flag1=0;
		b1:
		fscanf(fp1,"%s",str);
		if(strcmp(str,"START")==0)
		{
			fprintf(fp3,"\t%s\t",str);
			fscanf(fp1,"%s",str);
			fprintf(fp3,"%s\n",str);
			goto b1;
		}
		fprintf(fp3,"%4x\t",add);
		if(strcmp(str,"END")==0)
		{
			goto a1;
		}
		c1:
		fp2=fopen("validop.txt","r");
		while(!feof(fp2))
		{
			fscanf(fp2,"%s",str1);
			if(strcmp(str,str1)==0)
			{
				flags=1;
			}
		}
		fclose(fp2);
		if((flags!=1))
		{
			flag2=flag=flag1=0;
			strcpy(temp,str);
			/*fscanf(fp3,"%s",str2);
			while(strcmp(str,str2)!=0)
			{
				fscanf(fp3,"%s",str2);
				fscanf(fp3,"%s",str2);
			}
			fscanf(fp3,"%s",str2);
			printf("%s\t%s\n",str,str2);
			if(strcmp(str2,"BYTE")==0)
			{
				flag1=1;
			}*/
			fscanf(fp1,"%s",str);
			fp2=fopen("validop.txt","r");
			while(!feof(fp2))
			{
				fscanf(fp2,"%s",str1);
				{
					if(strcmp(str,str1)==0)
					{
						flag=1;
					}
				}
			}
			fclose(fp2);
			if((flag!=1)&&((strcmp(str,"BYTE")!=0)&&(strcmp(str,"RESB")!=0)&&(strcmp(str,"WORD")!=0)&&(strcmp(str,"BYTE")!=0)))
			{
				flag1=1;
			}
			if(flag1==1)
			{
				printf("%s\n",temp);
				strcpy(iop[io++],temp);
				fscanf(fp1,"%s",str);
				goto c1;
			}
			else if((flag!=1)&&(flag1!=1))
			{
				fprintf(fp3,"%s\t",temp);
				fprintf(fp3,"%s\t",str);
				/*fprintf(fp3,"%4x\t",symt[0].address);
				fprintf(fp3,"%s\t",symt[0].symbol);
				fprintf(fp3,"%s\t",str);*/
				fscanf(fp1,"%s",str);
				fprintf(fp3,"%s\n",str);
				for(i=1;i<sym;i++)
				{
					if(i==sym-1)
					{
						fscanf(fp1,"%s",str);
						fprintf(fp3,"%4X\t",symt[i].address);
						fprintf(fp3,"%s\t",symt[i].symbol);
						fscanf(fp1,"%s",str);
						fprintf(fp3,"%s\t",str);
						/*if(strcmp(str,"RESB")==0)
						{*/
							fscanf(fp1,"%s",str);
							fprintf(fp3,"%s\n",str);
							/*resbno=atoi(str);
						}
						else if(strcmp(str,"BYTE")==0)
						{
							resbno=1;
						}
						else if(strcmp(str,"RESW")==0)
						{
							fscanf(fp1,"%s",str);
							fprintf(fp3,"%s\n",str);
							resbno=atoi(str);
						}
						else
						{
							resbno=3;
							fscanf(fp1,"%s",str);
							fprintf(fp3,"%s\n",str);
						}*/
					}
					else
					{
						fscanf(fp1,"%s",str);
						fprintf(fp3,"%4x\t",symt[i].address);
						fprintf(fp3,"%s\t",symt[i].symbol);
						fscanf(fp1,"%s",str);
						fprintf(fp3,"%s\t",str);
						fscanf(fp1,"%s",str);
						fprintf(fp3,"%s\n",str);
					}
				}
				goto a1;
			}
			else
			{
				fprintf(fp3,"%s\t",temp);
				fprintf(fp3,"%s\t",str);
				fscanf(fp1,"%s",str);
				fprintf(fp3,"%s\n",str);
			}
		}
		else
		{
			fprintf(fp3,"%s\t",str);
			fscanf(fp1,"%s",str);
			fprintf(fp3,"%s\n",str);
		}
		/*if(flag1==1)
		{
			add++;
		}
		else*/
			add=add+3;
	}
	a1:
	while(!feof(fp1))
	{
		if(strcmp(str,"END")!=0)
		{
			fscanf(fp1,"%s",str);
		}
		else
		{
			flage=1;
		}
		if(flage!=0)
		{
			while(!feof(fp1))
			{
				fprintf(fp3,"\t");
				fprintf(fp3,"%s\t",str);
				fscanf(fp1,"%s",str);
			}
		}
	}
	if(flagad!=1)
	{
		pgmlngth=(symt[sym-1].address)+resbno;
	}
	else
	{
		pgmlngth=(((symt[sym-1].address)+resbno)-(2*starting));
	}
	fprintf(fp3,"\n\n\nProgram Length:");
	fprintf(fp3,"%4X\n",pgmlngth);
	fclose(fp1);
	fclose(fp3);
	fp4=fopen("Length.txt","w+");
	fprintf(fp4,"%4X",pgmlngth);
	fclose(fp4);
}
			
				
main()
{
	int i;
	optab();
	symboltable();
	intermediate();
	fp5=fopen("invalidop.txt","w+");
	for(i=0;i<io;i++)
	{
		fprintf(fp5,"%s\n",iop[i]);
	}
}
