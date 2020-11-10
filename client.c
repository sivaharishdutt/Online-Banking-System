#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>

void Menu(int);
void displaySubMenu(int);
void adminFunctions(int);
void jointAccountLogin(int);
void jointDisplaySubMenu(int);


void deleteAccount(int sd)
{
	char uname[20],buffer[35];

	printf("\nEnter the username to be deleted: ");
	scanf(" %s", uname);

	write(sd, uname, sizeof(uname));
	read(sd, buffer, sizeof(buffer));
	
	printf("%s",buffer);
	adminFunctions(sd);
}

void deleteJointAccount(int sd)
{
	char uname1[20], uname2[20], buffer[35];

	printf("\nEnter Username 1 to delete: ");
	scanf(" %s",uname1);
	printf("\nEnter Username 2 to delete: ");
	scanf(" %s",uname2);

	write(sd, uname1, sizeof(uname1));
	write(sd, uname2, sizeof(uname2));

	read(sd, buffer, sizeof(buffer));

	printf("%s",buffer);
	adminFunctions(sd);
}

void newJointAccount(int sd, int flag)
{
	char uname1[20], pass1[20], uname2[20], pass2[20], buffer[30];
	printf("\nEnter first username: ");
	scanf(" %s", uname1);
	printf("\nEnter password: ");
	scanf(" %s", pass1);
	printf("\nEnter second username: ");
	scanf(" %s", uname2);
	printf("\nEnter password: ");
	scanf(" %s", pass2);

	write(sd, uname1, sizeof(uname1));
	write(sd, pass1, sizeof(pass1));
	write(sd, uname2, sizeof(uname2));
	write(sd, pass2, sizeof(pass2));

	read(sd, buffer, sizeof(buffer));
	printf("%s", buffer);
	if(flag==1)
		Menu(sd);
	else
		adminFunctions(sd);
}

void signUp(int sd, int flag)
{
	int account_id;
	char uname[20],pass[20], buffer[30];

	printf("\nEnter username: \n");
	scanf(" %s",uname);
	printf("\nEnter password: \n");
	scanf(" %s",pass);

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));

	read(sd, buffer, sizeof(buffer));
	printf("%s", buffer);
	if(flag==1)
		Menu(sd);
	else
		adminFunctions(sd);
}

void login(int sd)
{
	char buffer[30];
	char uname[20],pass[20];
	int flag;

	printf("\nEnter username: \n");
	scanf(" %s",uname);
	printf("\nEnter password: \n");
	scanf(" %s",pass);

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));

	read(sd, &flag, sizeof(flag));
	read(sd, &buffer, sizeof(buffer));
	printf("%s",buffer);

	if(flag==1)
		displaySubMenu(sd);
	else
		Menu(sd);


}

void jointAccountLogin(int sd)
{
	char buffer[30],buff[30];
	char uname1[20],pass[20],uname2[20];
	int flag;

	printf("\nEnter first username: \n");
	scanf(" %s",uname1);
	
	printf("\nEnter second username: \n");
	scanf(" %s",uname2);
	
	printf("\n Please Enter password  for user1: \n");
	scanf(" %s",pass);

	write(sd, uname1,sizeof(uname1));
	write(sd, uname2,sizeof(uname2));
	write(sd, pass, sizeof(pass));
	
	read(sd, &flag, sizeof(flag));
	read(sd, buffer, sizeof(buffer));
	printf("%s",buffer);

	if(flag==1)
	{
		jointDisplaySubMenu(sd);
	}
	else
		Menu(sd);

}
void balance(int sd)
{
float bal;
char haa[20];
read(sd,haa,sizeof(haa));
read(sd,&bal,sizeof(bal)); 
printf("\n %s,Your Balance is %.2f ",haa,bal);
displaySubMenu(sd);
}

void viewDetails(int sd)
{
	char uname[20];
	int acc_id;
	float  balance;

	read(sd,uname, sizeof(uname));
	read(sd,&acc_id, sizeof(acc_id));
	read(sd,&balance, sizeof(balance));

	printf("\nUsername: %s, Account ID: %d, Balance: %.2f\n",uname,acc_id,balance);
	displaySubMenu(sd);
}

void viewJointDetails(int sd)
{
	char uname1[20], uname2[20];
	int acc_id;
	float balance;

	read(sd,uname1, sizeof(uname1));
	read(sd,uname2, sizeof(uname2));
	read(sd,&acc_id, sizeof(acc_id));
	read(sd,&balance, sizeof(balance));

	printf("\nUsername1: %s,Username2: %s, Account ID: %d, Balance: %.2f\n",uname1,uname2,acc_id,balance);
	jointDisplaySubMenu(sd);
}

void deposit(int sd)
{
	float amount;
	printf("\nEnter amount to deposit: ");
	scanf("%f",&amount);
	
	write(sd, &amount, sizeof(amount));
	read(sd, &amount, sizeof(amount));
	printf("\nNew Balance: %.2f",amount);
	
	displaySubMenu(sd);
}

void jointDeposit(int sd)
{
	float amount;
	printf("\nEnter amount to deposit: ");
	scanf("%f",&amount);
	
	write(sd, &amount, sizeof(amount));
	read(sd, &amount, sizeof(amount));
	printf("\nNew Balance: %.2f",amount);
	
	jointDisplaySubMenu(sd);
}

void jointWithdraw(int sd)
{
	int flag;
	float amount; 
	printf("\nEnter amount to withdraw: ");
	scanf("%f",&amount);

	write(sd, &amount, sizeof(amount));
	read(sd, &flag, sizeof(flag));
	
	if(flag==0)
	{
		printf("\nInsufficient Balance\n");
		read(sd, &amount, sizeof(amount));
		printf("\nBalance: %.2f\n",amount);
	}
	else
	{
		read(sd, &amount, sizeof(amount));
		printf("\nNewBalance: %.2f\n",amount);

	}
	
	jointDisplaySubMenu(sd);
}





void withdraw(int sd)
{
	int  flag;
	float amount;
	printf("\nEnter amount to withdraw: ");
	scanf("%f",&amount);

	write(sd, &amount, sizeof(amount));
	read(sd, &flag, sizeof(flag));
	
	if(flag==0)
	{
		printf("\nInsufficient Balance\n");
		read(sd, &amount, sizeof(amount));
		printf("\nBalance: %.2f",amount);
	}
	else
	{
		read(sd, &amount, sizeof(amount));
		printf("\n NewBalance: %.2f",amount);

	}
	
	displaySubMenu(sd);
}

void jointPassChange(int sd)
{
	char pass[20];
	
	printf("\nEnter the new Password: ");
	scanf(" %s",pass);
    

	write(sd,pass,sizeof(pass));
	Menu(sd);
	
}



void passChange(int sd)
{
	char pass[20];
	
	printf("\nEnter the new Password: ");
	scanf(" %s",pass);

	write(sd,pass,sizeof(pass));
	Menu(sd);
	
}

void displaySubMenu(int sd)
{
	int choice;
	printf("\n1.Balance enquiry \n2.View Details\n3.Deposit\n4.Withdraw\n5.Password Change\n6.EXIT\n");
	printf("\nEnter your choice: ");
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: balance(sd);
				break;
		case 2: viewDetails(sd);
				break;
		case 3: deposit(sd);
				break;
		case 4: withdraw(sd);
				break;
		case 5: passChange(sd);
				break;
		case 6: Menu(sd);
				break;
		default: printf("\nEnter proper choice\n");
				break;


	}
}

void jointDisplaySubMenu(int sd)
{
	int choice;
	printf("\n1.View Details\n2.Deposit\n3.Withdraw\n4.Password Change\n5.EXIT\n");
	printf("\nEnter your choice: ");
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: viewJointDetails(sd);
				break;
		case 2: jointDeposit(sd);
				break;
		case 3: jointWithdraw(sd);
				break;
		case 4: jointPassChange(sd);
				break;
		case 5: Menu(sd);
				break;
	

	}

}

void adminFunctions(int sd)
{
	int choice;
	
	printf("\n1.Add Account\n2.Delete Account\n3.Search Account\n4.Add Joint Account\n5.Delete Joint Account\n6.Search Joint Account\n7.Exit\nEnter your choice: ");
	scanf("%d", &choice);
	
	char buffer[46], uname[20], pass[20], uname1[20], uname2[20];
	write(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
		case 1:signUp(sd,0);
			break;
		case 2:deleteAccount(sd);
			break;
		case 3:printf("\nEnter username to search: ");
			scanf(" %s", uname);
			write(sd, uname, sizeof(uname));
			read(sd, &buffer, sizeof(buffer));
			printf(" %s", buffer);
			adminFunctions(sd);
			break;
		case 4:newJointAccount(sd,0);
			break;
		case 5:deleteJointAccount(sd);
			break;
		case 6:printf("\nEnter username 1 to search: ");
			scanf(" %s", uname1);
			printf("\nEnter username 2 to search: ");
			scanf(" %s", uname2);
			write(sd, uname1, sizeof(uname1));
			write(sd, uname2, sizeof(uname2));
			read(sd, &buffer, sizeof(buffer));
			printf("%s", buffer);
			adminFunctions(sd);
			break;
		case 7:Menu(sd);
	}
}

void adminLogin(int sd)
{
	char uname[20], pass[20], buffer[20];
	int flag;
	
	printf("\nEnter the admin username: ");
	scanf(" %s",uname);
	printf("\nEnter admin password: ");
	scanf(" %s",pass);
	
	write(sd, uname, sizeof(uname));
	write(sd, pass, sizeof(pass));
	read(sd, &flag, sizeof(flag));
	read(sd, buffer, sizeof(buffer));
	
	printf("%s",buffer);
	if(flag == 1)
		adminFunctions(sd);
	else
		Menu(sd);
}

void Menu(int sd)
{
	int choice;
	printf("\n_____________________________________________Welcome to IIIT-Banglore Online Banking System________________________________________________\n");
	printf("\n\n");

	printf("\n1.Single User LOGIN\n2.Admin Login\n3.Joint Account Login\n4.Exit\n");
	printf("\n\nEnter your choice: ");
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: login(sd);
				break;
		case 2: adminLogin(sd);
				break;
		case 3: jointAccountLogin(sd);
				break;
		case 4: exit(0);
				break;

	}
}

int main()
{
	
	struct sockaddr_in server;
	int sd;
	char buffer[80];
	sd = socket(AF_INET, SOCK_STREAM,0);
	if(sd==-1)
	{
	perror("socket creation error");
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(7928);

	if(connect(sd, (struct sockaddr *)(&server), sizeof(server))<0)
	{
	perror("connection error");
	}
	
	Menu(sd);
	close(sd);
	return 0;
}

