#include"header.c"
main()
{
FILE *fp;
char a[20],b[12];
struct st temp;
struct sockaddr_in v,v1;
//char a[20];
int sfd,nsfd,len,i=0;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
perror("socket");
return;
}

v.sin_family=AF_INET;
v.sin_port=htons(3000);//htons-host byte  to network byte
v.sin_addr.s_addr=inet_addr("0.0.0.0");// The inet_addr() function converts the Internet  host  address  cp  from
     					 // IPv4  numbers-and-dots notation into binary data in network byte order.

bind(sfd,(struct sockaddr *)&v,sizeof(v));
perror("bind");

listen(sfd,5);
perror("listen");

len=sizeof(v1);
printf("Before....\n");
nsfd=accept(sfd,(struct sockaddr *)&v1,&len);
printf("After...\n");
//if(fork())
//{
read(nsfd,a,20);
printf("%s\n",a);
//}
//else
//{
	fp=fopen(a,"r+");
	if(fp==NULL)
	{
	printf("file not present..\n");
	return;
	}

	while(fgets(b,10,fp)!=NULL)
	{
	temp.a=++i;
	strcpy(temp.s,b);
	printf("%d %s\n",temp.a,temp.s);
	write(nsfd,&temp,sizeof(temp)+1);
	}
//}
}
