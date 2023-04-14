#include <stdio.h>

#define n 100

typedef struct {
	//enum fl_t;
	int fl_index;
	int id;
} customer_t; 

typedef struct {
	int c_id;
	/* write rest of code here */
} staff_t;

void accountCreate (customer_t* client, int *numCount) {
	printf("%d\n", *numCount);
	client[*numCount].id = *numCount + 1; //grab id from previous user, add one
	printf("Here's your new ID:%d\n", client[*numCount].id);

	*numCount += 1; //updates count for next registry
}

void accountAuthenticate(customer_t* client) {
	int userNum;
	printf("Enter your ID number: ");
	scanf("%d", &userNum);

	for(int i = 0; i < n; ++i) {
		if(userNum == client[i].id) {
			printf("Account found\n");
		}
	}
}

void customerInterface(customer_t* client, int *numCount) {
	int uAccount;

	printf("\nAre you a new or returning customer?\n");
	printf("[1] New\t[2] Returning\nEnter one of the displayed keys above: ");

	do {
		scanf("%d", &uAccount);
		if (!(uAccount == 1 || uAccount == 2))
			printf("Error, please enter a valid key: ");
	} while (!(uAccount == 1 || uAccount == 2));

	if(uAccount == 1)
		accountCreate(client, numCount);
	else
		accountAuthenticate(client);
	
	return;
}

void companyInterface() {

}

int main() {
	int userOption = 0;
	customer_t client[n];
	client[0].id = 0; 
	int numCount = 0;

	while(userOption != 3) {
	printf("\nWelcome to Alaska International Airways\n");
	printf("[1] Customer\t[2] Staff\n[3] Exit Program\n");
	printf("Enter one of the displayed keys above: ");

	do {
		scanf("%d", &userOption);
		if (!(userOption == 1 || userOption == 2 || userOption == 3))
		       printf("Error, please input a valid key: ");
 	} while (!(userOption == 1 || userOption == 2 || userOption == 3));

	switch(userOption){
		case 1:
			customerInterface(client, &numCount);
			break;
		case 2:
			companyInterface();
			break;
	}	
	}

	return 0;
}
