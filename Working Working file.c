#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
    int AvailFlight;
	int flightnumber;
	float PriceofFlight;
	int distance;
	char InAirport[20];
	char OutPort[20];
	int InAirportCode;
	int OutAirportCode;
	int PlaneNumber;
} flight_t;

typedef struct Airport
{
  char Airport[20];
  int AirportCity;
  int AirportAvailability;
} Airport;

void PrintFlight (flight_t * point);

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
	printf("\n* A new account has been generated with ID: %d\n\n", client[*registry].id);
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
	int routeAvail = 0;
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

		for (int i=0; i < 10; i++) {
			if (flight[i].AvailFlight == 1) {
			printf ("\nRoute %d\n", i);
			PrintFlight (&flight[i]);
			++routeAvail;
			}
		}
		//printf("\nThere are 2 flights available at this moment.\n");
		printf("\nSelect one of the routes above: ");

		do {
			scanf("%d", &route);
			if(route < 0 || route >= routeAvail)
				printf("Error, please select a valid option and try again: ");
			else if (flight[route].capacity >= 40)	
				printf("This flight has reached the max capacitants, please select a different flight: ");
		} while ((route < 0 || route >= routeAvail) || flight[route].capacity >= 40);

		printflSeats(flight, route);
		reserveSeats(flight, client, userID, route);
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

void companyInterface(flight_t* flight, struct employee *employee, Airport* NumberofAirports) {
	int value;
  int RevAdd, NewLocation;

	printf("Do you want to manage routes, manage employees, or exit the program?\n"); 
	printf("[1] Manage Routes \n[2] Manage Planes \n[3] Manage Airports \n[4] Manage Employees \n[hit any other numerical key] Exit Program \n");
	scanf("%d", &value);
		switch(value) {
			case 1: printf("you have selected to manage routes\n");
	
    printf ("Enter [1] to Add a Route, [2] to remove.\n");
  
    do
      {
	scanf ("%d", &RevAdd);
	if (RevAdd > 2 || RevAdd < 1)
	  printf ("please enter [1] or [2]");
      }
    while (RevAdd > 2 || RevAdd < 1);
//for the first thing
    if (RevAdd == 1)
      {
	printf
	  ("Select a destination to add by entering the number displayed next to the route\n");
	printf ("Route Corpus to Austin [1]\n");
	printf ("Route Austin to Houston [2]\n");
	printf ("Route SanAntonio to Cospus [3]\n");

	do
	  {
	    scanf ("%d", &NewLocation);
	    if (NewLocation > 3 || NewLocation < 1)
	      printf ("Please enter [1], [2] or [3]\n");
	  }
	while (NewLocation > 3 || NewLocation < 1);
	if (NewLocation == 1)
	  {
	    if (flight[3].AvailFlight != 1)
	      {
		PrintFlight (&flight[3]);
		flight[3].AvailFlight= 1;
		printf("Route Corpus to Austin [1] has been added.");
	      }else{printf("This flight is already available.");}
	  }
	if (NewLocation == 2)
	  {
	    if (flight[4].AvailFlight != 1)
	      {
		PrintFlight (&flight[4]);
				flight[4].AvailFlight= 1;
		printf("Route Austin to Houston [2] has been added.");

	      }else{printf("This flight is already available.");}
	  }
	if (NewLocation == 3)
	  {
	    if (flight[5].AvailFlight != 1)
	      {
		PrintFlight (&flight[5]);
				flight[5].AvailFlight= 1;
	printf("Route SanAntonio to Cospus [3] has been added.");
	      }else{printf("This flight is already available.");}
	  }
      }

    if (RevAdd == 2)
      {
	printf ("Below are the available flights that can be removed.\n");
	for (int i=0; i < 10; i++)
	  {
	    if (flight[i].AvailFlight == 1)
	      {
		printf ("\nRoute %d\n", i);
		PrintFlight (&flight[i]);

	      }

	  }
	printf
	  ("Enter the number of which route you would like to remove.\n");
	do
	  {
	    scanf ("%d", &RevAdd);
	    if (RevAdd > 5 || RevAdd < 0)
	      printf ("Please Enter a route number to remove.\n");
	  }
	while (RevAdd > 5 || RevAdd < 0);
	flight[RevAdd].AvailFlight = 0;
	printf("Route %d has been removed",flight[RevAdd].flightnumber);
  	//paste code here
			}
			break;
			case 2:   printf ("Enter [1] to Remove a plane, [2] to Add one.\n ");
  do
    {
      scanf ("%d", &RevAdd);
      if (RevAdd > 2 || RevAdd < 1)
	printf ("please enter [1] or [2]\n");
    }
  while (RevAdd > 2 || RevAdd < 1);
  if (RevAdd == 1)
    {
      for (int i=0; i < 6; i++)
	{
	  if (flight[i].AvailFlight == 1)
	    {
	      printf ("ID %d, Plane %d\n\n", i,
		      flight[i].PlaneNumber);
	    }
	}
      printf
	("Enter the ID number of the place(Not the Plane Number) to Remove a plane.\n");
      do
	{
	  scanf ("%d", &RevAdd);
	  if (RevAdd > 6 || RevAdd < 0)
	    printf
	      ("Please enter the ID number of the Plane you wish to remove.\n");
	}
      while (RevAdd > 6 || RevAdd < 0);
      flight[RevAdd].AvailFlight = 0;
      flight[RevAdd].PlaneNumber =
	  flight[RevAdd].PlaneNumber + 1000;
	  printf("Plane %d has been removed",RevAdd);
    }
  if (RevAdd == 2)
    {
      for (int i=0; i < 6; i++)
	{
	  if (flight[i].AvailFlight == 0
	      && flight[i].PlaneNumber >= 6000)
	    {
	      printf ("ID %d, Plane %d\n\n", i,
		      flight[i].PlaneNumber);
	    }
	}
      printf ("Enter the ID number of the place(Not the Plane Number) to Add a plane.\n");
      do
	{
	  scanf ("%d", &RevAdd);
	  if (RevAdd > 6 || RevAdd < 0)
	    printf
	      ("Please enter the ID number of the Plane you wish to Add.\n");
	}
      while (RevAdd > 6 || RevAdd < 0);
      if (NumberofAirports[RevAdd].AirportCity ==
	  flight[RevAdd].InAirportCode
	  || NumberofAirports[RevAdd].AirportCity ==
	  flight[RevAdd].OutAirportCode)
	{
	  if (NumberofAirports[RevAdd].AirportAvailability == 1)
	    {
	      flight[RevAdd].AvailFlight = 1;
	    }
	}
      flight[RevAdd].PlaneNumber =
	flight[RevAdd].PlaneNumber - 1000;
	printf("Plane %d has been added\n",flight[RevAdd].PlaneNumber);
    }
        break;
			case 3:  printf ("Enter [1] to add an airport,[2] to remove one.\n");
  do
    {
      scanf ("%d", &RevAdd);
      if (RevAdd > 2 || RevAdd < 1)
	printf ("please enter [1] or [2]\n");
    }
  while (RevAdd > 2 || RevAdd < 1);
  if (RevAdd == 2)
    {
      for (int i=0; i < 6; i++)
	{
	  if (NumberofAirports[i].AirportAvailability == 1)
	    {

	      printf ("Enter %d to remove %s Airport\n", i,
		      NumberofAirports[i].Airport);

	    }
	}
      do
	{
	  scanf ("%d", &RevAdd);
	  if (RevAdd > 5 || RevAdd < 0)
	    printf
	      ("Please enter the number of the Airport you would like to remove\n");
	}
      while (RevAdd > 5 || RevAdd < 0);
      NumberofAirports[RevAdd].AirportAvailability = 0;
      for (int i=0; i < 6; i++)
	{
	  if (NumberofAirports[RevAdd].AirportCity ==
	      flight[i].InAirportCode
	      || NumberofAirports[RevAdd].AirportCity ==
	      flight[i].OutAirportCode)
	    {
	      flight[i].AvailFlight = 0;
	    }
	}
printf ("Airport %s has been removed.\n Any flights with this airport with no longer be available\n",
		      NumberofAirports[RevAdd].Airport);
    }
  if (RevAdd == 1)
    {
      for (int i= 0; i < 6; i++)
	{
	  if (NumberofAirports[i].AirportAvailability == 0)
	    {
	      printf ("Enter %d to Add %s Airport\n", i,
		      NumberofAirports[i].Airport);
	    }
	}
      do
	{
	  scanf ("%d", &RevAdd);
	  if (RevAdd > 6 || RevAdd < 0)
	    printf ("Please enter \n");
	}
      while (RevAdd > 6 || RevAdd < 0);
      NumberofAirports[RevAdd].AirportAvailability = 1;
      printf ("Airport %s has been added.\n",NumberofAirports[RevAdd].Airport);
    }
    break;
			case 4:printf("you have selected to manage employees\n");
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
 	int NewLocation;
  	int RevAdd;
	Airport NumberofAirports[6];

	strcpy (NumberofAirports[0].Airport, "Austin");
	NumberofAirports[0].AirportCity = 0;
	NumberofAirports[0].AirportAvailability = 1;

	strcpy (NumberofAirports[1].Airport, "SanAntonio");
	NumberofAirports[1].AirportCity = 1;
	NumberofAirports[1].AirportAvailability = 1;

	strcpy (NumberofAirports[2].Airport, "Houston");
	NumberofAirports[2].AirportCity = 2;
	NumberofAirports[2].AirportAvailability = 1;


	strcpy (NumberofAirports[3].Airport, "Corpus");
	NumberofAirports[3].AirportCity = 3;
	NumberofAirports[3].AirportAvailability = 1;


	strcpy (NumberofAirports[4].Airport, "Dallas");
	NumberofAirports[4].AirportCity = 4;
	NumberofAirports[4].AirportAvailability = 0;


	strcpy (NumberofAirports[5].Airport, "Armadillo");
	NumberofAirports[5].AirportCity = 5;
	NumberofAirports[5].AirportAvailability = 0;

	//Identify Flight routes
	flight[0].flightnumber = 0;
	flight[0].PlaneNumber = 5000;
	flight[0].PriceofFlight = 450.90;
	strcpy (flight[0].InAirport, "Austin");
	flight[0].InAirportCode = 0;
	strcpy (flight[0].OutPort, "SanAntonio");
	flight[0].OutAirportCode = 1;
	flight[0].distance = 80;
	flight[0].AvailFlight = 1;

	flight[1].flightnumber = 1;
	flight[1].PlaneNumber = 5001;
	flight[1].PriceofFlight = 390.25;
	strcpy (flight[1].InAirport, "SanAntonio");
	flight[1].InAirportCode = 1;
	strcpy (flight[1].OutPort, "Houston");
	flight[1].OutAirportCode = 2;
	flight[1].distance = 200;
	flight[1].AvailFlight = 1;

	flight[2].flightnumber = 2;
	flight[2].PlaneNumber = 5002;
	flight[2].PriceofFlight = 330.25;
	strcpy (flight[2].InAirport, "Houston");
	flight[2].InAirportCode = 2;
	strcpy (flight[2].OutPort, "Cospus");
	flight[2].OutAirportCode = 3;
	flight[2].distance = 210;
	flight[2].AvailFlight = 1;

	flight[3].flightnumber = 3;
	flight[3].PlaneNumber = 5003;
	flight[3].PriceofFlight = 270.25;
	strcpy (flight[3].InAirport, "Corpus");
	flight[3].InAirportCode = 3;
	strcpy (flight[3].OutPort, "Austin");
	flight[3].OutAirportCode = 0;
	flight[3].distance = 217;
	flight[3].AvailFlight = 0;

	flight[4].flightnumber = 4;
	flight[4].PlaneNumber = 6004;
	flight[4].PriceofFlight = 190.25;
	strcpy (flight[4].InAirport, "Austin");
	flight[4].InAirportCode = 0;
	strcpy (flight[4].OutPort, "Houston");
	flight[4].OutAirportCode = 2;
	flight[4].distance = 160;
	flight[4].AvailFlight = 0;

	flight[5].flightnumber = 5;
	flight[5].PlaneNumber = 6005;
	flight[5].PriceofFlight = 150.25;
	strcpy (flight[5].InAirport, "SanAntonio");
	flight[5].InAirportCode = 1;
	strcpy (flight[5].OutPort, "Corpus");
	flight[5].OutAirportCode = 3;
	flight[5].distance = 150;
	flight[5].AvailFlight = 0;


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
				companyInterface(flight, employees, NumberofAirports);
				break;
		}
	}
	return 0;
}

void PrintFlight (flight_t * point)
{
  printf ("Flight Number %d\n", (*point).flightnumber);
  printf ("Plane Number %d\n", (*point).PlaneNumber);
  printf ("Flight Price %.2f\n", (*point).PriceofFlight);
  printf ("Incoming Airport %s\n", (*point).InAirport);
  printf ("Incoming Airport Code %d\n", (*point).InAirportCode);
  printf ("Outgoing Airport %s\n", (*point).OutPort);
  printf ("Outgoing Airport Code%d\n", (*point).OutAirportCode);
  printf ("%d Mile Flight\n\n", (*point).distance);

}


