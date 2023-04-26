#include <stdio.h>

#define n 50
#define MAXROUTES 10

typedef struct {
	int seats[6][40];
} flight_t;

typedef struct {
	//enum fl_t;
	int id;
} customer_t;

typedef struct {
	/* write rest of code here */
	int id;
} staff_t;

 void printflSeats(flight_t* flight, int route) {
	for(int i = 0; i < 6; ++i) {
		printf("[ ] ");
			for(int j = 0; j < 40; ++j)
				printf("[ ] ");
		printf("\n");

		if(i == 2)
			printf("\n");
	}
}

void accountCreate (customer_t* client, int *registry) {
	client[*registry].id = *registry + 1; //Implements ID
	printf("\n* A new account has been generated with ID: %d\n", client[*registry].id);
	++(*registry); //Updates registry count by 1

	return;
}

void accountAuthenticate(customer_t* client) {
	int userNum;
	printf("Enter your ID number: ");
	scanf("%d", &userNum);

	for(int i = 0; i < n; ++i) {
		if(userNum == client[i].id && userNum != 0) {
			printf("Account found\n");
			return; //fix later - works for now
		}
	}

	printf("\nThis ID has not been registered in our database.\n");
	return;
}

void customerInterface(customer_t* client, flight_t* flight, int *registry) {
	int uAccount = 0;
	int route;

	while(uAccount != 3) {
		printf("\nAre you a new or returning customer?\n");
		printf("[1] New\t[2] Returning\n[3] Exit\nSelect one of the displayed options above: ");

		do {
			scanf("%d", &uAccount);
			if (!(uAccount == 1 || uAccount == 2 || uAccount == 3))
				printf("Error, please enter a valid key: ");
		} while (!(uAccount == 1 || uAccount == 2 || uAccount == 3));

		if (uAccount == 1) {
			if(*registry == n)
				printf("\nThe maximum number of space has been reached within the database.\nAn account cannot be made at this moment.\n");
			else
				accountCreate(client, registry);
		} else if (uAccount == 2)
			accountAuthenticate(client);

		printf("\nThere are 2 flights available at this moment.\n");
		printf("[1] Chicago\t[2] Austin\nSelect one of the options above: \n");

		do {
			scanf("%d", route);
			if(!(route == 1 || route == 2))
				printf("Error, please select a valid option and try again: ");
		} while (!(route == 1 || route == 2));

		printflSeats(flight, route);
	}
	
	return;
}

void companyInterface() {
    
}

void initializeFlights(flight_t* flights, int flightNum) {
    for(int i = 0; i < 6; ++i) {
            for(int j = 0; j < 40; ++j)
                flights[flightNum].seats[i][j] = 0;
    }
}

int main() {
	int userOption = 0;
	customer_t client[n] = {0};
	staff_t staff[n] = {0};
	flight_t flight[MAXROUTES];
	int registry = 0;
	int staffReg = 0;

    for(int i = 0; i < MAXROUTES; ++i)
        initializeFlights(flight, i);
    
	while(userOption != 3) {
		printf("Welcome to Milk Airlines\n");
		printf("[1] Customer\t[2] Staff\n[3] Exit Program\n");
		printf("Select one of the displayed options above: ");

		do {
			scanf("%d", &userOption);
			if (!(userOption == 1 || userOption == 2 || userOption == 3))
				printf("Error, please input a valid key: ");
		} while (!(userOption == 1 || userOption == 2 || userOption == 3));

		switch(userOption) {
			case 1:
				customerInterface(client, flight, &registry);
				break;
			case 2:
				companyInterface();
				break;
		}

		/* for(int i = 0; i < n; ++i) {
			printf("ARRAY INDEX: %d, CLIENT ID: %d\n", i, client[i].id);
		} //FOR DEBUGGING PURPOSES - LISTS DATA WITHIN CLIENT STRUCT ARRAY AND CORRESPONDING ID  */
	}

	return 0;
}
