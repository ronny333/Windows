//Client
#include"header1.c"
main()
{
char a[20];
//struct st temp;
struct sockaddr_in v,v1;
//char a[20];
int sfd,nsfd,len;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
perror("socket");
return;
}

v.sin_family=AF_INET;
v.sin_port=htons(3000);//htons-host byte  to network byte
v.sin_addr.s_addr=inet_addr("127.0.0.1");// The inet_addr() function converts the Internet  host  address  cp  from
     					 // IPv4  numbers-and-dots notation into binary data in network byte order.



connect(sfd,(struct sockaddr *)&v,sizeof(v));
perror("connect");
printf("Enter data:\n");
scanf("%s",a);
//printf("%d %s\n",temp.a,temp.s);
write(sfd,a,strlen(a)+1);
}

