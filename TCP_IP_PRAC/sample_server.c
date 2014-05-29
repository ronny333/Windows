#include"header.c"
main()
{
char ch,ch1;
FILE *fp;
char a[20],b[20];
struct st temp;
struct sockaddr_in v,v1;
int sfd,nsfd,len,i=0;

sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
perror("Socket");
return;
}

v.sin_family=AF_INET;
v.sin_port=htons(3002);
v.sin_addr.s_addr=inet_addr("0.0.0.0");

bind(sfd,(struct sockaddr *)&v,sizeof(v));
perror("bind");

listen(sfd,5);
perror("listen");

len=sizeof(v1);
printf("Before...\n");
nsfd=accept(sfd,(struct sockaddr *)&v1,&len);
printf("After...\n");
while(1)
{
 read(nsfd,a,20);
                printf("received data:%s\n",a);

printf("Enter data:");
write(sfd,b,strlen(b)+1);

}

/* 	if(fork())
	{
		while(1)
		{
		read(nsfd,a,20);
		printf("%s\n",a);
		}
	}
	else
	{
		while(1)
		{
		printf("Enter client data:");
		scanf("%s",b);
		write(nsfd,b,strlen(b)+1);
		}
	}
*/
/*if(fp==NULL)
{
printf("File not present...\n");
return;
}*/
//	while(fgets(b,10,fp)!=NULL)
//	{
//	temp.a=++i;
//	strcpy(temp.s,b);
//	printf("%d %s\n",temp.a,temp.s);

//	}

}
