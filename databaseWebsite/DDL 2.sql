-- All code handwritten by Project Group 35 (Greyson Sparling, Noah Letter), unless otherwise stated.

-- Creating Procedure to reset database
DROP PROCEDURE IF EXISTS spLoadRentalDB;
DELIMITER //
CREATE PROCEDURE spLoadRentalDB()
BEGIN

    -- disabling commits and foreign key checks to minimize import errors
    SET FOREIGN_KEY_CHECKS = 0;
    SET AUTOCOMMIT = 0;

    -- Dropping tables to prevent import errors
    DROP TABLE IF EXISTS RentalEmployees;
    DROP TABLE IF EXISTS Rentals;
    DROP TABLE IF EXISTS Employees;
    DROP TABLE IF EXISTS Boats;
    DROP TABLE IF EXISTS BoatTypes;
    DROP TABLE IF EXISTS Customers;

    -- Creating Customers table
    CREATE TABLE Customers (
        customerID INT AUTO_INCREMENT UNIQUE NOT NULL,
        customerName VARCHAR(255) NOT NULL,
        email VARCHAR(255) NOT NULL,
        PRIMARY KEY (customerID)
    );

    -- Creating BoatTypes table
    CREATE TABLE BoatTypes (
        boatTypeID INT AUTO_INCREMENT UNIQUE NOT NULL,
        boatTypeName VARCHAR(255) NOT NULL,
        hourlyCost DECIMAL(10,2) NOT NULL,
        PRIMARY KEY (boatTypeID)
    );

    -- Creating Boats table
    CREATE TABLE Boats (
        boatID INT AUTO_INCREMENT UNIQUE NOT NULL,
        boatTypeID INT NOT NULL,
        PRIMARY KEY (boatID),
        FOREIGN KEY (boatTypeID) REFERENCES BoatTypes(boatTypeID)
        ON DELETE RESTRICT
    );

    -- Creating Employees table
    CREATE TABLE Employees (
        employeeID INT AUTO_INCREMENT UNIQUE NOT NULL,
        employeeName VARCHAR(255) NOT NULL,
        PRIMARY KEY (employeeID)
    );

    -- Creating Rentals table
    CREATE TABLE Rentals (
        rentalID INT AUTO_INCREMENT UNIQUE NOT NULL,
        customerID INT,
        boatID INT,
        hoursRented INT NOT NULL,
        PRIMARY KEY (rentalID),
        FOREIGN KEY (customerID) REFERENCES Customers(customerID)
        ON DELETE SET NULL,
        FOREIGN KEY (boatID) REFERENCES Boats(boatID)
        ON DELETE SET NULL
    );

    -- Creating junction table for Rentals and Employees
    CREATE TABLE RentalEmployees (
        rentalEmployeeID INT AUTO_INCREMENT UNIQUE NOT NULL,
        rentalID INT NOT NULL,
        employeeID INT NOT NULL,
        FOREIGN KEY (rentalID) REFERENCES Rentals(rentalID)
        ON DELETE CASCADE,
        FOREIGN KEY (employeeID) REFERENCES Employees(employeeID)
        ON DELETE CASCADE,
        PRIMARY KEY (rentalEmployeeID)
    );

    -- adding data to tables
    INSERT INTO Customers (customerID, customerName, email)
    VALUES (1, 'Alice Smith', 'alice@email.com'),
    (2, 'Bob Johnson', 'bob@emaill.com'),
    (3, 'Carol Davis', 'carol@email.com');

    -- Only two types added based on outline
    INSERT INTO BoatTypes (boatTypeID, boatTypeName, hourlyCost)
    VALUES (1, 'Pontoon', 31.50),
    (2, 'Speedboat', 42),
    (3, 'Dinghy', 28);

    INSERT INTO Boats (boatID, boatTypeID)
    VALUES (1,1),
    (2,1),
    (3,2),
    (4,1);

    INSERT INTO Employees (employeeID, employeeName)
    VALUES (1, 'Steven Lash'),
    (2, 'Trevor Abrams'),
    (3, 'Billy Ken');

    INSERT INTO Rentals (rentalID, customerID, boatID, hoursRented)
    VALUES (1, 1, 1, 2),
    (2, 2, 3, 1),
    (3, 3, 4, 5),
    (4, 1, 1, 3);

    INSERT INTO RentalEmployees (rentalEmployeeID, rentalID, employeeID)
    VALUES (1, 1, 1),
    (2, 1, 2),
    (3, 2, 1),
    (4, 2, 3),
    (5, 3, 3),
    (6, 3, 2),
    (7, 4, 2),
    (8, 4, 1);

    -- turning back on commits and fk checks
    SET FOREIGN_KEY_CHECKS = 1;
    COMMIT;

END //
DELIMITER ;