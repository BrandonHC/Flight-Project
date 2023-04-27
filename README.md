# Flight-Project
Group project for CS 2073
#include <stdio.h>
#include <stdlib.h>

typedef struct Flight
{
    int AvailFlight;
 int flightnumber;
 float PriceofFlight;
 int seats[6][40];
 int distance;
 char InAirport[20];
 char OutPort[20];
 int InAirportCode;
 int OutAirportCode;
 int PlaneNumber;

}FlightRoutes;

typedef struct Airport
{
    char Airport[20];
    char Airport3Code[3];
    int AirportCity;
    int IncomingPlanes[10];
    
}Airport;

void PrintFlight(FlightRoutes *point);

int main (){
    int NewLocation;
    int RevAdd;
    int logicAirports;
    FlightRoutes NumberofFlights[10];
    Airport NumberofAirports[6];
    
   
    
{//
 printf("Enter [1] to Add a Route, [2] to remove.\n");
 do{
     scanf("%d",&RevAdd);
     if(RevAdd>2 || RevAdd<1)
         printf("please enter [1] or [2]");
     }while(RevAdd>2 || RevAdd<1);
//for the first thing
if(RevAdd==1){
    printf("Select a destination to add\n");
    printf("Route A[1]\n");
    printf("Route B[2]\n");
    printf("Route C[3]\n");
do{
 scanf("%d",&NewLocation);   
 if(NewLocation>3 || NewLocation<1)
         printf("Please enter [1], [2] or [3]");
     }while(NewLocation>3 || NewLocation<1);
       // PrintFlight(&NumberofFlights[4]);
    if(NewLocation==1)
    {
    NumberofFlights[3].flightnumber=5;
    NumberofFlights[3].PlaneNumber=50001;
    NumberofFlights[3].PriceofFlight=500;
   // NumberofFlights[3].InAirport[20]=
   NumberofFlights[3].InAirportCode=12345667;
 //  NumberofFlights[3].OutPort[20]=
   NumberofFlights[3].OutAirportCode=1234556;
   NumberofFlights[3].distance=3000;
    NumberofFlights[3].AvailFlight=1;
    PrintFlight(&NumberofFlights[3]);
    }
    if(NewLocation==2)
    {
     NumberofFlights[4].flightnumber=5;
    NumberofFlights[4].PlaneNumber=50001;
    NumberofFlights[4].PriceofFlight=500;
   // NumberofFlights[4].InAirport[20]=
   NumberofFlights[4].InAirportCode=12345667;
 //  NumberofFlights[4].OutPort[20]=
   NumberofFlights[4].OutAirportCode=1234556;
   NumberofFlights[4].distance=3000;
    NumberofFlights[4].AvailFlight=1;
    PrintFlight(&NumberofFlights[4]);
    }
    if(NewLocation==3)
    {
    NumberofFlights[4].flightnumber=5;
    NumberofFlights[4].PlaneNumber=50001;
    NumberofFlights[4].PriceofFlight=500;
   // NumberofFlights[4].InAirport[20]=
   NumberofFlights[4].InAirportCode=12345667;
 //  NumberofFlights[4].OutPort[20]=
   NumberofFlights[4].OutAirportCode=1234556;
   NumberofFlights[4].distance=3000;
    NumberofFlights[4].AvailFlight=1;
    PrintFlight(&NumberofFlights[4]);
    }
    }

}//
if(RevAdd==2)
{
    printf("Below are the available flights that can be removed.");
    for(int i;i<10;i++)
    {
        if(NumberofFlights[i].AvailFlight==1){
        printf("Route %d\n",i);
        PrintFlight(&NumberofFlights[i]);
        
        }
        
    }
        printf("Enter the number of which route you would like to remove or enter 10 to exit.");
do{
     scanf("%d",&RevAdd);
     if(RevAdd==10){
         exit;
     }
     if(RevAdd>10 || RevAdd<1)
         printf("Please Enter a the number of a route or enter 10 to exit");
     }while(RevAdd>10 || RevAdd<1);
NumberofFlights[RevAdd].AvailFlight=0;
}
 return 0;
}
void PrintFlight(FlightRoutes *point){
    printf("Flight Number %d\n",(*point).flightnumber);
    printf("Plane Number %d",(*point).PlaneNumber);
    printf("Flight Price %.2f\n",(*point).PriceofFlight);
    printf("Incoming Airport %s\n",(*point).InAirport);
    printf("Incoming Airport Code %d\n",(*point).InAirportCode);
    printf("Outgoing Airport %s\n",(*point).OutPort);
    printf("Outgoing Airport Code%d\n",(*point).OutAirportCode);
    printf("%d Hour Flight\n",(*point).distance);

}

