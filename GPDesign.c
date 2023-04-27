#include <stdio.h>

#define MAXCLIENTS 20
#define MAXROUTES 10
#define FLIGHTROWSIZE 6

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
	char seat = 'A'; //starting seat
	int i;

	for(i = 1; i <= sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]); ++i) {
		if(i < 10)
			printf(" %d  ", i); //formatting - not perfect
		else
			printf(" %d ", i);
	}

	printf("\n");
	for(i = 0; i < FLIGHTROWSIZE; ++i) {
			for(int j = 0; j < sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]); ++j)
				printf("[%c] ", seat);
		printf("\n");

		if(i == 2)
			printf("\n");
		++seat;
	}
}

void reserveSeats(flight_t* flight, customer_t* client) {
	int cSeat; //Row Number
	char rSeat; //Column Char -> Number

	printf("Select the seat number (Column Number): %d", &cSeat);
	printf("Select the seat letter (Row Letter): ", &rSeat);
	return;
}

void accountCreate (customer_t* client, int *registry) {
	client[*registry].id = *registry + 1; //Implements ID
	printf("\n* A new account has been generated with ID: %d\n", client[*registry].id);
	++(*registry);

	return;
}

int accountAuthenticate(customer_t* client) {
	int userNum;
	printf("Enter your ID number: ");
	scanf("%d", &userNum);

	for(int i = 0; i < MAXCLIENTS; ++i) {
		if(userNum == client[i].id && userNum != 0) {
			printf("Account found\n");
			return -1; //works for now - fix later
		}
	}

	printf("\nThis ID has not been registered in our database.\n");
	return 0;
}

void customerInterface(customer_t* client, flight_t* flight, int *registry) {
	int uAccount = 0;
	int route;

	while(uAccount != 3 && uAccount != -1) {
		printf("\nAre you a new or returning customer?\n");
		printf("[1] New\t[2] Returning\n[3] Exit\nSelect one of the displayed options above: ");

		do {
			scanf("%d", &uAccount);
			if (!(uAccount == 1 || uAccount == 2 || uAccount == 3))
				printf("Error, please enter a valid key: ");
		} while (!(uAccount == 1 || uAccount == 2 || uAccount == 3));

		if (uAccount == 1) {
			if(*registry == MAXCLIENTS)
				printf("\nThe maximum number of space has been reached within the database.\nAn account cannot be made at this moment.\n");
			else
				accountCreate(client, registry);
				uAccount = -1;
		} else if (uAccount == 2)
			uAccount = accountAuthenticate(client);
	}

	if(uAccount == -1) { //Flight Reservation & seat
		printf("\nThere are 2 flights available at this moment.\n");
		printf("[1] Chicago\t[2] Austin\nSelect one of the options above: \n");

		do {
			scanf("%d", &route);
			if(!(route == 1 || route == 2))
				printf("Error, please select a valid option and try again: ");
		} while (!(route == 1 || route == 2));

		printflSeats(flight, route);
	}
	
	return;
}

void companyInterface() {
    
}

void initializeFlights(flight_t* flight, int flightNum) {
    for(int i = 0; i < FLIGHTROWSIZE; ++i) {
            for(int j = 0; j < sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]); ++j)
                flight[flightNum].seats[i][j] = 0;
    }

	return;
}

int main() {
	int userOption = 0;
	customer_t client[MAXCLIENTS] = {0};
	staff_t staff[MAXCLIENTS] = {0};
	flight_t flight[MAXROUTES];
	int registry = 0;
	int staffReg = 0;

    for(int i = 0; i < MAXROUTES; ++i)
        initializeFlights(flight, i); //sets plane seat contents to zero for every plane
    
	while(userOption != 3) {
		//printf("ROW SIZE: %d", sizeof(flight[0].seats)/sizeof(flight[0].seats[0]));
		//printf("COLUMN SIZE: %d", sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]));

		printf("Welcome to Wisp Airlines\n");
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

		/* for(int i = 0; i < MAXCLIENTS; ++i) {
			printf("ARRAY INDEX: %d, CLIENT ID: %d\MAXCLIENTS", i, client[i].id);
		} //FOR DEBUGGING PURPOSES - LISTS DATA WITHIN CLIENT STRUCT ARRAY AND CORRESPONDING ID  */
	}

	return 0;
}