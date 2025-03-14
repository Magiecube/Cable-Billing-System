//Name: <Olayemi Odjetunde>
//Class: <Fall - COSC 1436.81802>
//Final Project.
//Revision: <1.0>
//Date: <12/04/2023>
//Description: <This program computes the billing statement for a local cable company based on the customer type.>

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const double RES_CONSTANTS[] = { 4.50, 20.50, 7.50 };
const double BUS_CONSTANTS[] = { 15.00, 75.00, 5.00, 50.00 };
struct Customer {
    char type;
    int accountNumber;
    int numOfBasicServConn;
    int numOfPremChannels;
    double amountDue;
};

int main() {
    const int MAX_CUSTOMERS = 15;
    Customer customers[MAX_CUSTOMERS];
    int numResidentialCustomers = 0;
    int numBusinessCustomers = 0;
    double totalResidentialSpending = 0.0;
    double totalBusinessSpending = 0.0;

    ifstream inFile;
    ofstream outFile;

    inFile.open("input.txt");
    outFile.open("output.txt");

    outFile << fixed << showpoint << setprecision(2);

    if (!inFile) {
        cout << "Error opening input file." << endl;
        return 0;
    }

    // Read customer data from the input file
    for (int i = 0; i < MAX_CUSTOMERS && inFile >> customers[i].type >> customers[i].accountNumber; ++i) {
        if (customers[i].type == 'R' || customers[i].type == 'r') {
            inFile >> customers[i].numOfPremChannels;
            customers[i].amountDue = RES_CONSTANTS[0] + RES_CONSTANTS[1] + customers[i].numOfPremChannels * RES_CONSTANTS[2];
            totalResidentialSpending += customers[i].amountDue;
            numResidentialCustomers++;
        }
        else if (customers[i].type == 'B' || customers[i].type == 'b') {
            inFile >> customers[i].numOfBasicServConn >> customers[i].numOfPremChannels;
            if (customers[i].numOfBasicServConn <= 10) {
                customers[i].amountDue = BUS_CONSTANTS[0] + BUS_CONSTANTS[1] + customers[i].numOfPremChannels * BUS_CONSTANTS[3];
            }
            else {
                customers[i].amountDue = BUS_CONSTANTS[0] + BUS_CONSTANTS[1] + (customers[i].numOfBasicServConn - 10) * BUS_CONSTANTS[2] + customers[i].numOfPremChannels * BUS_CONSTANTS[3];
            }
            totalBusinessSpending += customers[i].amountDue;
            numBusinessCustomers++;
        }
        else {
            cout << "Invalid customer type in input file." << endl;
            return 0;
        }
    }

    // Write customer bills to the output file
    for (int i = 0; i < MAX_CUSTOMERS && i < numResidentialCustomers + numBusinessCustomers; ++i) {
        outFile << "Account number: " << customers[i].accountNumber << endl;
        outFile << "Amount due: $" << customers[i].amountDue << endl;
        outFile << "\0" << endl;
    }

    // Write average summaries to the output file
    outFile << "Summary:" << endl;
    outFile << "Residential Customers: Average spending = $" << totalResidentialSpending / numResidentialCustomers << endl;
    outFile << "Business Customers: Average spending = $" << totalBusinessSpending / numBusinessCustomers << endl;

    inFile.close();
    outFile.close();

    return 0;
}
