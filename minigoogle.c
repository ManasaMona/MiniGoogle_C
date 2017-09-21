#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int couwrds;
int coulinks;

struct alllinks
{
	char elink[150][30];
}el;

struct dictionary
 {
 	char wrds[1000];
 	char url[100][80];
 	int wrdFreqncy[100];
 }dict[10000]; 

char add_to_index(char *word,char *link)
{
	static int i=0;
	int ui=0,wi=0,k=0,freq=0,urltemp=0,uii=0;
	int index=0;
	int swrd=0;
	char stop[100];

	FILE *stp=fopen("StopWords.txt","r");

	while((fscanf(stp,"%s",stop))!= EOF)
	{
		if(strcmp(word,stop)==0)
		{
			swrd=1;
		}
	}
	if(swrd==0)
	{
		if(i==0)
		{
				strcpy(dict[i].wrds,word);
				strcpy(dict[i].url[ui],link);
				dict[i].wrdFreqncy[wi]=1;
				i++;
				couwrds++;

		}
		else
		{
			for(k=0;k<couwrds;k++)
			{
				urltemp=0;
				if(strcmp(word,dict[k].wrds)==0)
				{
						freq=1;
	
					for(uii=0;uii<5;uii++)
					{

					 	if(strcmp(dict[k].url[uii],link)==0)
						{
				
							 urltemp=1;
							dict[k].wrdFreqncy[uii]++;

						}
					}
					if(urltemp==0){
						ui++;
						wi++;
						strcpy(dict[k].url[ui],link);
						dict[k].wrdFreqncy[wi]=1;
						
					}
				}
			}
			if(freq==0)
			{
					strcpy(dict[i].wrds,word);
					strcpy(dict[i].url[ui],link);
					dict[i].wrdFreqncy[wi]=1;
					i++;
					couwrds++;
			}
		}
	}
	 return NULL;
	//printf("%s-%s-%d\n",dict[i-1].wrds,dict[i-1].url[ui-1],dict[i-1].wrdFreqncy);
}


char *get_page(char *urllinks)//get all the contents of page
{
	//printf("%s**getpage",url);
	char ch;
	char contnt[20000];
	int i=0;
	char *cntnt;

	FILE *pfp=fopen(urllinks,"r");
	if(pfp==NULL)
	{
		//printf(" Error in opening the file");
	}
	else
	{
		while((ch=fgetc(pfp))!=EOF)
		{
			contnt[i]=ch;
			i++;	
		}
		contnt[i]='\0';
	}
	//printf("%s",contnt);
	fclose(pfp);
	cntnt=contnt;
	return cntnt;
}

char *add_page_to_index(char *url)
{
	char ch;
	int i=0,len=0;
	char *content;
	content=get_page(url);

	FILE *wfp;
	wfp=fopen("words.txt","w");
	 len=strlen(content);
		 for(int i=0;i<len;i++)
		 {
		 	if(content[i]=='<')
		 	{
		 		i++;
		 		while(content[i]!='>')
		 		{
		 			i++;
		 		}
		 	}
		 	else
		 	{
				fputc(content[i],wfp);
		 	}
		 }
 	fclose(wfp);
 
 char str1[100];
 FILE *rfp;
 rfp=fopen("words.txt","r");
	 while((fscanf(rfp,"%s",str1))!= EOF)
	 {
	 	add_to_index(str1,url);
	 }
	fclose(rfp);
}


char *get_next_target(char *stripedString)
{
	//printf("*%s\n",stripedString);
	int len,i=0,m=0;
	char *lptr;
	len=strlen(stripedString);
	char link[1000];
	static int jj=0;
	for(jj;jj<len;jj++)
	{
		if(stripedString[jj]=='a' || stripedString[jj]=='A')
		{
			jj++;
			jj++;
			if(stripedString[jj]=='h' || stripedString[jj]=='H' )
			{
				jj++;
				if(stripedString[jj]=='r' || stripedString[jj]=='R')
				{
					jj++;
					if(stripedString[jj]=='e' || stripedString[jj]=='E')
					{
						jj++;
						if(stripedString[jj]=='f' || stripedString[jj]=='F')
						{
							jj++;
							if(stripedString[jj]=='=')
							{
								jj++;
								if(stripedString[jj]=='"')
								{
									jj++;
									//i=0;
									while(stripedString[jj]!='"')
									{
										link[i]=stripedString[jj];
										i++;
										jj++;
									}
										link[i]='\0';
										//printf("link0000%s\n",link);
										lptr=link;
										return  lptr;		
								}
							}
						}
					}	
				}
			}
		}	
	}
	return NULL;
}

char *get_all_links (char *htmlstring)
{
	int m=0;
	static int li=0;
	int count=0;
 	int rep=1;
	do
	{
		char *elin;
		elin=get_next_target(htmlstring);

		if(elin!=NULL)
		{
			if(li==0)
			{
				strcpy(el.elink[li],elin);
				li++;
				coulinks++;	
			}
			else
			{
				for(int m=0;m<li;m++)
				{
					if(strcmp(elin,el.elink[m])==0)
					{
						count++;
					}
				}
				if(count==0)
				{
					strcpy(el.elink[li],elin);
					li++;
					coulinks++;
				}
			}
		}
		else
		{
			break;
		}
	}
	while(rep==1);
	//jj=0;
	
}

void rank_of_word(char *find)
{
	int ocur=0;
	for(int p=0;p<couwrds;p++)
	{
		if(strcmp(find,dict[p].wrds)==0)
		{
			ocur=1;
			if(dict[p].wrdFreqncy[0]>dict[p].wrdFreqncy[1])
			{
				printf("%s\n",dict[p].url[0]);
				printf("%s\n",dict[p].url[1]);
				//exit(0);
			}
			else
			{
				printf("%s\n",dict[p].url[1]);
				printf("%s\n",dict[p].url[0]);
				//exit(0);
			}

		}
	}
	if(ocur==0)
	{
		printf(" Word not found! ");
	}

}
char *web_crawl(char *seedpage)
{
	char *pgcntnt,*stlink;
	pgcntnt=get_page(seedpage);
	get_all_links(pgcntnt);

	for(int j=0;j<coulinks;j++)
	{

		get_all_links(get_page(el.elink[j]));
	}


	for(int j=0;j<coulinks;j++){
	//printf("%s-arr\n",el.elink[j]);
	add_page_to_index(el.elink[j]);	
	}
	
	 for(int j=0;j<couwrds;j++)
	 {
	 	printf("\n%s : ",dict[j].wrds);
	 	for(int w=0;w<2;w++)
	 	{
			printf(" %s---%d // ",dict[j].url[w],dict[j].wrdFreqncy[w]);	
		}
	}

	char input[25];
	printf(" ^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n ");
	printf("\n Enter the word : "); 
	scanf("%s",input);
	rank_of_word(input);
}


void main()
{
	//printf(" Enter the URL : ");
	//scanf("%s",inputurl);
	web_crawl("first.txt");
	// char input[25];
	// printf(" Enter the word : ")
	// scanf("%s",input);
	 //printf("%s",pgcntnt);
	//get_next_target (pgcntnt);
	
	

}