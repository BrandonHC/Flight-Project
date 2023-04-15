#include <stdio.h>

#define n 10

typedef struct {
	//enum fl_t;
	int fl_index;
	int id;
} customer_t; 

typedef struct {
	int c_id;
	/* write rest of code here */
} staff_t;

void accountCreate (customer_t* client, int *registry) {
	printf("%d\n", *registry);
	client[*registry].id = *registry + 1; //Updates registry, then implements ID
	printf("\nA new account has been generated with ID: %d\n", client[*registry].id);
	++(*registry);

	return;
}

void accountAuthenticate(customer_t* client) {
	int userNum;
	printf("Enter your ID number: ");
	scanf("%d", &userNum);

	for(int i = 0; i < n; ++i) {
		if(userNum == client[i].id) {
			printf("Account found\n");
			return;
		}
	}

	printf("\nThis ID has not been registered in our database\n");
	return;
}

void customerInterface(customer_t* client, int *registry) {
	int uAccount;

	printf("\nAre you a new or returning customer?\n");
	printf("[1] New\t[2] Returning\nEnter one of the displayed keys above: ");

	do {
		scanf("%d", &uAccount);
		if (!(uAccount == 1 || uAccount == 2))
			printf("Error, please enter a valid key: ");
	} while (!(uAccount == 1 || uAccount == 2));

	if(uAccount == 1) {
		if(*registry == n) {
			printf("The maximum number of space has been reached within the database.\nAn account cannot be made at this moment.\n");
		} else
			accountCreate(client, registry);
	} else
		accountAuthenticate(client);
	
	return;
}

void companyInterface() {

}

int main() {
	int userOption = 0;
	customer_t client[n] = {0};
	//client[0].id = 0; 
	int registry = 0;

	while(userOption != 3) {
		printf("\nWelcome to Alaska International Airways\n");
		printf("[1] Customer\t[2] Staff\n[3] Exit Program\n");
		printf("Enter one of the displayed keys above: ");

		do {
			scanf("%d", &userOption);
			if (!(userOption == 1 || userOption == 2 || userOption == 3))
				printf("Error, please input a valid key: ");
		} while (!(userOption == 1 || userOption == 2 || userOption == 3));

		switch(userOption) {
			case 1:
				customerInterface(client, &registry);
				break;
			case 2:
				companyInterface();
				break;
		}

		/* for(int i = 0; i < n; ++i) {
			printf("ARRAY INDEX: %d, CLIENT ID: %d\n", i, client[i].id);
		} FOR DEBUGGING PURPOSES - LISTS DATA WITHIN CLIENT STRUCT ARRAY AND CORRESPONDING ID*/ 
	}

	return 0;
}
