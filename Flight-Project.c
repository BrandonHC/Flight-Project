#include <stdio.h>
#include <stdbool.h>

#define MAXCLIENTS 20
#define MAXROUTES 10
#define FLIGHTROWSIZE 6

struct employee {
    int empID;
    int flight;
};

typedef struct {
	int seats[6][40];
	int capacity;
	int num;
    struct employee employees[4];
} flight_t;

typedef struct {
	bool hasSlot;
	int routeNum;
	int id;
} customer_t;

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
			for(int j = 0; j < sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]); ++j) {
				if(flight[route].seats[i][j] == 0)
					printf("[%c] ", seat);
				else
					printf("[-] ");
			}
		printf("\n");

		if(i == 2)
			printf("\n");
		++seat;
	}
}

void reserveSeats(flight_t* flight, customer_t* client, int userID, int route) {
	int cSeat; //Row Number
	char rSeat; //Coloumn Char -> Number
	bool availSeat = true;

	while(availSeat == true) {
		do {
			printf("Select the Seat Number (Number Column): ");
			scanf("%d", &cSeat);
			if(!(cSeat <= sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]) && cSeat >= 1))
				printf("Invalid input, please try again.\n");
		} while (!(cSeat <= sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]) && cSeat >= 1));

		do {
			printf("Select a Seat Letter (Row Letter): ");
			scanf(" %c", &rSeat);
			if(!(rSeat >= 'A' && rSeat <= 'F'))
				printf("Invalid input, please try again.\n");
		} while (!(rSeat >= 'A' && rSeat <= 'F'));

		if(flight[route].seats[(int)rSeat - 65][cSeat - 1] != 0)
			printf("This seat has been taken, please select a different seat.\n");
		else
			availSeat = false;
	}

	client[userID - 1].routeNum = route;
	client[userID - 1].hasSlot = true;

	flight[route].seats[(int)rSeat - 65][cSeat - 1] = client[userID - 1].id;
	++(flight[route].capacity);

	printf("Thank you for using our service, your seat is located at %d%c\n", cSeat, rSeat);
}

bool checkMaxFlights(flight_t* flight) {
	int maxFlights = 0;

	for(int i = 0; i < 2; ++i) {
		if(flight[i].capacity == 40)
			++maxFlights;
	}

	if(maxFlights == 2)
		return true;
	else
		return false;
}

void deleteUserSlot(flight_t* flight, customer_t* client, int userID) {
	client[userID - 1].hasSlot = false;
	--(flight[client[userID - 1].routeNum].capacity);

	for(int i = 0; i < FLIGHTROWSIZE; ++i)
		for(int j = 0; j < sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]); ++j) {
			if(flight[client[userID - 1].routeNum].seats[i][j] == client[userID - 1].id)
				flight[client[userID - 1].routeNum].seats[i][j] = 0;
		} 
}

int accountCreate (customer_t* client, int *registry) {
	client[*registry].id = *registry + 1; //Implements ID
	printf("\n* A new account has been generated with ID: %d\n", client[*registry].id);
	client[*registry].hasSlot = false;
	++(*registry);

	return client[*registry - 1].id;
}

int accountAuthenticate(customer_t* client) {
	int userNum;
	printf("Enter your ID number: ");
	scanf("%d", &userNum);

	for(int i = 0; i < MAXCLIENTS; ++i) {
		if(userNum == client[i].id && userNum != 0) {
			printf("Account found\n");
			return client[i].id;
		}
	}

	printf("\nThis ID has not been registered in our database.\n");
	return -1;
}

void customerInterface(customer_t* client, flight_t* flight, int *registry) {
	int uAccount = 0;
	int userID = 1; //works for now
	int route, userChoice;

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
			else {
				userID = accountCreate(client, registry);
				uAccount = -1;
			}
		} else if (uAccount == 2) {
			userID = accountAuthenticate(client);

			if(userID != -1) {
				if(client[userID - 1].hasSlot) {
					printf("There is a flight registered with this account, would you like to delete your current reservation?\n[1] Delete\t[2] Exit\n");
					do {
						scanf("%d", &userChoice);
						if (!(userChoice == 1 || userChoice == 2))
							printf("Invalid input, please try again: ");
					} while (!(userChoice == 1 || userChoice == 2));

				if (userChoice == 1)
					deleteUserSlot(flight, client, userID);
				else
					return;
				}
			else
				uAccount = -1;
			}
		}
	}

	if(uAccount == -1) {
		if(checkMaxFlights(flight) == true) {
			printf("All flights are at maximum capacity, no reservations can be made at this moment.\n");
			return;
		}

		printf("\nThere are 2 flights available at this moment.\n");
		printf("[1] Chicago\t[2] Austin\nSelect one of the options above: ");

		do {
			scanf("%d", &route);
			if(!(route == 1 || route == 2))
				printf("Error, please select a valid option and try again: ");
			else if (flight[route - 1].capacity >= 40)	
				printf("This flight has reached the max capacitants, please select a different flight: ");
		} while (!(route == 1 || route == 2) || flight[route - 1].capacity >= 40);

		printflSeats(flight, route - 1);
		reserveSeats(flight, client, userID, route - 1);
	}
}

void createEmployee(struct employee *point, int id, int fnum) {
    point->empID = id;
    point->flight = fnum;
}

void addEmployee(flight_t* flight, struct employee *employee, int fnum, int crewnum) {
    flight[fnum - 1].employees[crewnum].empID = employee->empID;
    flight[fnum - 1].employees[crewnum].flight = employee->flight;
}

void removeEmployee(flight_t* flight, struct employee *employee, int fnum, int crewnum) {
    flight[fnum - 1].employees[crewnum].empID = 0;
    flight[fnum - 1].employees[crewnum].flight = 0;
}

void companyInterface(flight_t* flight, struct employee *employee) {
	int value;

	printf("Do you want to manage routes, manage employees, or exit the program?\n"); 
	printf("[1] Manage Routes \n[2] Manage Employees \n[hit any other numerical key] Exit Program \n");
	scanf("%d", &value);
		switch(value) {
			case 1: printf("you have selected to manage routes");
		{ 
				//paste code here
			}
			break;
			case 2: printf("you have selected to manage employees\n");
				int empID, flightNum, crewNum, action;
				printf("Enter 1 to add employee, 2 to remove employee: ");
				scanf("%d", &action);

				if (action == 1) {
					printf("Enter employee ID: ");
					scanf("%d", &empID);

					printf("Enter flight number: ");
					scanf("%d", &flightNum);

					printf("Enter crew number: ");
					scanf("%d", &crewNum);

					struct employee newEmployee;
					createEmployee(&newEmployee, empID, flightNum);
					addEmployee(flight, &newEmployee, flightNum, crewNum - 1);
					printf("Employee added successfully to flight %d\n", flightNum);
				} else if (action == 2) {
					printf("Enter flight number: ");
					scanf("%d", &flightNum);
			
					printf("Enter crew number: ");
					scanf("%d", &crewNum);
			
					struct employee employeeToRemove = flight->employees[crewNum - 1];
					removeEmployee(flight, &employeeToRemove, flightNum, crewNum - 1);
					printf("Employee removed successfully from flight %d\n", flightNum);
				} else {
					printf("Invalid action. Please enter 1 or 2.\n");
				}
			break;
			default: printf("You have selected to return to the menu\n");
		}
}

void initializeFlights(flight_t* flight, int flightNum) {
    for(int i = 0; i < FLIGHTROWSIZE; ++i) {
            for(int j = 0; j < sizeof(flight[0].seats[0])/sizeof(flight[0].seats[0][0]); ++j) {
                flight[flightNum].seats[i][j] = 0;
				flight[flightNum].capacity = 0;
			}
    }
}

int main() {
	customer_t client[MAXCLIENTS] = {0};
	flight_t flight[MAXROUTES];
	struct employee employees[40];
	int registry = 0;
	int userOption = 0;

    for(int i = 0; i < MAXROUTES; ++i)
        initializeFlights(flight, i); //sets plane seat contents to zero for every plane
    
	while(userOption != 3) {
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
				companyInterface(flight, employees);
				break;
		}
	}
	return 0;
}