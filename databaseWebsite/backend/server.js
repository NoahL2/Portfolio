/* 
Citation for the following section of code
Date: 2/26/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-web-application-technology-2?module_item_id=26243419
*/

// Database connection
const db = require('./db-connector')

// Express
const express = require('express');  
const app = express();

// Path module for React
const path = require('path');


// Middleware
const cors = require('cors')
app.use(cors({ credentials: true, origin: "*" }));
app.use(express.json());

const PORT = 58414; 
// ROUTE HANDLERS

// READ ROUTES

// route to get customers from database
app.get('/api/customers', async (req, res) => {
    try {
        const query1 = `SELECT * FROM Customers;`;
        const [customers] = await db.query(query1);

        res.status(200).json({ customers });
    } catch (error) {
        console.error("Error executing queries:", error);
        res.status(500).send("An error occurred while executing the database queries.");
    }

});

// route to get cleaning data from database table RentalEmployees
app.get('/api/cleanings', async (req, res) => {
    try {
        const query1 = `SELECT RentalEmployees.rentalEmployeeID, RentalEmployees.rentalID, Boats.boatID, BoatTypes.boatTypeName, RentalEmployees.employeeID, Employees.employeeName FROM RentalEmployees \
            JOIN Employees ON RentalEmployees.employeeID = Employees.employeeID \
            JOIN Rentals ON RentalEmployees.rentalID = Rentals.rentalID \
            JOIN Boats ON Rentals.boatID = Boats.boatID \
            JOIN BoatTypes ON Boats.boatTypeID = BoatTypes.boatTypeID \
            ORDER BY RentalEmployees.rentalEmployeeID ASC;`;
        const [cleanings] = await db.query(query1);

        res.status(200).json({ cleanings });
    } catch (error) {
        console.error("Error executing queries:", error);
        res.status(500).send("An error occurred while executing the database queries.");
    }

});

// route to get rental data from database 
app.get('/api/rent', async (req, res) => {
    try {
        const query1 = `SELECT Rentals.rentalID, Rentals.customerID, Customers.customerName, Rentals.boatID, BoatTypes.boatTypeName, Rentals.hoursRented FROM Rentals \
            JOIN Customers ON Rentals.customerID = Customers.customerID \
            JOIN Boats ON Rentals.boatID = Boats.boatID \
            JOIN BoatTypes ON Boats.boatTypeID = BoatTypes.boatTypeID \
            ORDER BY Rentals.rentalID ASC;`;
        const [rentals] = await db.query(query1);

        res.status(200).json({ rentals });
    } catch (error) {
        console.error("Error executing queries:", error);
        res.status(500).send("An error occurred while executing the database queries.");
    }

});

// route to get staff data from database 
app.get('/api/staff', async (req, res) => {
    try {
        const query1 = `SELECT * FROM Employees;`;
        // query2 is for dropdown selection
        const query2 = `SELECT employeeID as eid, employeeName FROM Employees;`
        const [staff] = await db.query(query1);
        const [employees] = await db.query(query2);

        res.status(200).json({ staff, employees });
    } catch (error) {
        console.error("Error executing queries:", error);
        res.status(500).send("An error occurred while executing the database queries.");
    }

});

// route to get boat data from database 
app.get('/api/boats', async (req, res) => {
    try {
        const query1 = `SELECT Boats.boatID, Boats.boatTypeID, BoatTypes.boatTypeName, BoatTypes.hourlyCost FROM Boats \
            JOIN BoatTypes ON Boats.boatTypeID = BoatTypes.boatTypeID;`;
        const [boats] = await db.query(query1);

        res.status(200).json({ boats });
    } catch (error) {
        console.error("Error executing queries:", error);
        res.status(500).send("An error occurred while executing the database queries.");
    }

});

// route to get boattype data from database 
app.get('/api/types', async (req, res) => {
    try {
        const query1 = `SELECT * FROM BoatTypes;`;
        const [types] = await db.query(query1);

        res.status(200).json({ types });
    } catch (error) {
        console.error("Error executing queries:", error);
        res.status(500).send("An error occurred while executing the database queries.");
    }

});

// route to edit staff data
app.get('/api/edit/:rentalEmployeeID', async (req, res) => {
    try {
        // getting rentalEmployeeID for SELECT statement to populate page
        const rentalEmployeeIDFromCleaningPage = req.params.rentalEmployeeID

        const query1 = `SELECT rentalEmployeeID, rentalID, employeeID FROM RentalEmployees WHERE rentalEmployeeID = ?;`;
        // query2 is for dropdown selection
        const query2 = `SELECT employeeID as eid, employeeName FROM Employees;`
        const [cleanings] = await db.query(query1, [rentalEmployeeIDFromCleaningPage]);
        const [employees] = await db.query(query2);

        res.status(200).json({ cleanings, employees });
    } catch (error) {
        console.error("Error executing queries:", error);
        res.status(500).send("An error occurred while executing the database queries.");
    }

});


// RESET ROUTE
app.post('/api/reset', async function (req, res) {
    try {
        const query1 = `CALL spLoadRentalDB();`
        await db.query(query1);

        res.status(200).json({ message: 'Reset successful'});
    } catch (error) {
        console.error('Error executing queries:', error);
        res.status(500).send('An error occurred while executing the database queries.');
    }
});


/* 
Citation for the following section of code
Date: 2/26/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-implementing-cud-operations-in-your-app?module_item_id=26243436
*/

// route to delete staff from database
app.post('/api/staff', async function (req, res) {
    try {
        let data = req.body;

        const query1 = `CALL spDeleteEmployee(?);`
        await db.query(query1, [data.eidFromDropdown]);

        console.log(`DELETE employee. ID: ${data.eidFromDropdown} ` + `Name: ${data.deletedEmployeeName}`);

        res.status(200).json({ message: 'Deletion successful'});
    } catch (error) {
        console.error('Error executing queries:', error);
        res.status(500).send('An error occurred while executing the database queries.');
    }
});

// route to insert into customers
app.post('/api/customers', async function (req, res) {
    try {
        let data = req.body;

        const query1 = `CALL spInsertCustomer(?, ?);`;

        await db.query(query1, [data.customerNameInput, data.emailInput]);
        res.status(200).json({message: 'Customer created successfully'})
    } catch (error) {
        console.error('Error executing queries:' , error);
        res.status(500).send('An error occurred while executing the database queries');
    }
});

// route to update cleaning table
app.post('/api/edit/:rentalEmployeeID', async function (req, res) {
    try {
        const data = req.body;

        const query1 = `CALL spUpdateRentalEmployees(?, ?)`
        await db.query(query1, [data.eidFromDropdown, data.rentalEmployeeIDFromCleaningPage]);
        console.log(`UPDATE RentalEmployees. RentalEmployeeID: ${data.rentalEmployeeIDFromCleaningPage} ` + `EmployeeID: ${data.eidFromDropdown}`);
        res.status(200).json({message: 'Cleaning Job updated successfully'});
    } catch (error) {
        console.error('Erro executing queries:', error);
        res.status(500).send('An error occurred while executing the database queries.');
    }
});

app.use(express.static(path.join(__dirname, '../frontend/build')));

// READ ROUTES
app.get(/.*/, (req, res) => {
    res.sendFile(path.join(__dirname, '../frontend/build/index.html'));
});


app.listen(PORT, "0.0.0.0",() => {    
    console.log('Server running on port 58414')
});