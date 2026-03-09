/* 
Citation for the following section of code
Date: 2/11/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from bsg_sample_data_manipulation_queries as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/assignments/10323336?module_item_id=26243423
*/
-- Using ? to denote variables that will have data from backend progamming language

-- Getting all contents to display the customers table
SELECT * FROM Customers;

-- Getting all contents to display Employees
SELECT * FROM Employees;

-- Getting all contents to display Rentals
SELECT Rentals.rentalID, Rentals.customerID, Customers.customerName, Rentals.boatID, Rentals.hoursRented FROM Rentals
JOIN Customers ON Rentals.customerID = Customers.customerID;

-- Getting all contents to display BoatTypes
SELECT * FROM BoatTypes;

-- Boats table with boatTypeName and hourlyCost included
SELECT Boats.boatID, Boats.boatTypeID, BoatTypes.boatTypeName, BoatTypes.hourlyCost FROM Boats
JOIN BoatTypes ON Boats.boatTypeID = BoatTypes.boatTypeID;

-- Cleaning table for what employees are cleaning what rental
SELECT RentalEmployees.rentalEmployeeID, RentalEmployees.rentalID, RentalEmployees.employeeID, Employees.employeeName FROM RentalEmployees
JOIN Employees ON RentalEmployees.employeeID = Employees.employeeID
ORDER BY RentalEmployees.rentalEmployeeID ASC;

-- Get data for UPDATE page absed on form submission
SELECT rentalEmployeeID, rentalID, employeeID FROM RentalEmployees WHERE rentalEmployeeID = ?rentalEmployeeIDFromCleaningPage;

-- get employees to populate a dropdown
SELECT employeeID as eid, employeeName FROM Employees;

-- insert into Customers
INSERT INTO Customers (CustomerName, email)
VALUES (?customerNameInput, ?emailInput);

-- update cleaning table
UPDATE RentalEmployees SET employeeID = ?eidFromDropdown
WHERE rentalEmployeeID = ?rentalEmployeeIDFromCleaningPage;

-- delete from employees to show cascade in cleaning table
DELETE FROM Employees
WHERE employeeID = ?eidFromDropdown;


