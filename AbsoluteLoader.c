#include<stdio.h>
#include<string.h>
#include<math.h>

int free,startfree;

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

void loaded()
{
	FILE *fp,*fp1;
	int flag=0,flag1=0,start,fn,sfn,fi=0,sfi=0,start1,start3,starttemp,i,j=0,k,l=0,m,lngth,lngthf,lf=0,finfinal=0;
	char temp[100],str[200],str1[100],str2[100],str3[100],f[10],sf[10];
	fp=fopen("objpgm.txt","r");
	fp1=fopen("loaded.txt","w");
	startfree=hexa(startfree);
	fscanf(fp,"%s",str);
	for(i=2;str[i]!='^';i++){}
	i++;
	while(str[i]!='^')
		sf[sfi++]=str[i++];
	sf[sfi]='\0';
	sfn=atoi(sf);
	finfinal=finfinal+sfn;
	//printf("\n%d\n",sfn);
	sfn=hexa(sfn);
	i++;
	while(i<strlen(str))
		f[fi++]=str[i++];
	f[fi]='\0';
	fn=atoi(f);
	finfinal=finfinal+fn;
	//printf("\n%d\n",fn);
	fn=hexa(fn);
	if((sfn+fn)>(startfree+free))
	{
		printf("\nCannot be loaded\n");
		exit(0);
	}
	//finfinal=sfn+fn;
	printf("Finfinal is %d\n",finfinal);
	//finfinal=hexa(finfinal);
	printf("%s\n",str);
	fscanf(fp,"%s",str);
	printf("%s\n",str);
	for(i=2;str[i]!='^';i++)
		temp[j++]=str[i];
	temp[j]='\0';
	//stadf=atoi(temp);
	//i++;
	i=i+4;
	/*while(str[i]!='^')
		length[lf++]=str[i++];
	length[lf]='\0';
	lngthf=atoi(length);
	lngthf=hexa(lngthf);*/
	start=atoi(temp);
	fprintf(fp1,"%d\t",start);
	start1=start;
	while(!feof(fp))
	{
		j=0;
		while(i<strlen(str))
		{
			while(l<8)
			{
				k=0;
				while(k<8)
				{
					if(i>=(strlen(str)))
					{
						goto a1;
					}
					if(str[i]!='^')
					{
						flag=0;
						temp[j++]=str[i++];
						k++;
					}
					else
						i++;
				}
				temp[j]='\0';
				flag=1;
				l=l+2;
				start1=start1+2;
				fprintf(fp1,"%s\t",temp);
				j=0;
			}
			printf("\n....Starts...\n");
			fprintf(fp1,"\n");
			start1=start1+2;
			start3=start1;
			start1=start1-(start1%10);
			fprintf(fp1,"%d\t",start1);
			l=0;
			if(i>=(strlen(str)-1))
				break;
		}
		a1:
		if(l<7)
		{
			printf("\n...Enters....\n");
			fprintf(fp1,"\t");
			if(flag!=1)
			{
				temp[j]='\0';
				m=strlen(temp);
				fprintf(fp1,"%s",temp);
			}
			else
			{
				k=8;
				while(l<8)
				{
					fprintf(fp1,"XXXXXXXX\t");
					l=l+2;
				}
			}
		}
		if(k<7)
		{
			printf("\n....Enters1....\n");
			while(k<=8)
			{
				fprintf(fp1,"X");
				k++;
			}
			l=l+2;
			flag=1;
			goto a1;
		}
		fprintf(fp1,"\n");
		fscanf(fp,"%s",str);
		if(str[0]=='E')
		{
			//fprintf(fp1,"\n");
			printf("E%dE\n",start3);
			start3=start3+10;
			//start3=hexa(start3);
			start3=start3-(start3%10);
			while(start3!=(finfinal+10))
			{
				fprintf(fp1,"%d\t",start3);
				for(i=0;i<4;i++)
				{
					fprintf(fp1,"XXXXXXXX\t");
				}
				fprintf(fp1,"\n");
				start3=start3+10;
				//start3=hexa(start3);
				start3=start3-(start3%10);
			}
			break;
		}
		i=2;j=0;l=0;k=0;
		start3=start3+10;
		start3=start3-(start3%10);
		printf("%d\n",start3);
		while(str[i]!='^')
			temp[j++]=str[i++];
		temp[j]='\0';
		i=i+4;
		fprintf(fp1,"%d\t",start3);
		start1=atoi(temp);
		if(start3<start1)
		{
			starttemp=start3;
			while(starttemp+2<start1)
			{
				fprintf(fp1,"XXXXXXXX\t");
				starttemp=starttemp+2;
				l=l+2;
			}
		}
	}
	fclose(fp);
	fclose(fp1);
}
		

main()
{
	printf("\nEnter the address:");
	scanf("%d",&startfree);
	printf("\nEnter the number of free bytes:");
	scanf("%d",&free);
	loaded();
}
