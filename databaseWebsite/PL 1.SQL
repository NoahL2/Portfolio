-- Citation for the following section of code
-- Date: 2/26/26
-- Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas Explorations as reference
-- Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-implementing-cud-operations-in-your-app?module_item_id=26243436

-- Delete for RentalEmployees
DROP PROCEDURE IF EXISTS spDeleteEmployee;

DELIMITER //
CREATE PROCEDURE spDeleteEmployee(IN eidFromDropdown INT)
BEGIN
    DECLARE errorMessage VARCHAR(255);

    -- error handling
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
        RESIGNAL;
    END;

    START TRANSACTION;
        -- delete row based on name that comes from a dropdown
        DELETE FROM Employees WHERE employeeID = eidFromDropdown;

        -- in case no matching name is found raise an error
        IF ROW_COUNT() = 0 THEN
            SET errorMessage = CONCAT('No matching record found in Employees for employeeID: ', eidFromDropdown);
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = errorMessage;
        END IF;

    COMMIT;

END //
DELIMITER ;


-- Insert for Customers
DROP PROCEDURE IF EXISTS spInsertCustomer;

DELIMITER //
CREATE PROCEDURE spInsertCustomer(IN customerNameInput VARCHAR(255), IN emailInput VARCHAR(255))
BEGIN
    INSERT INTO Customers (CustomerName, email)
    VALUES (customerNameInput, emailInput);
END //
DELIMITER ;


-- Update RentalEmployees to change Employee ID associated
DROP PROCEDURE IF EXISTS spUpdateRentalEmployees;

DELIMITER //
CREATE PROCEDURE spUpdateRentalEmployees(IN eidFromDropdown INT, IN rentalEmployeeIDFromCleaningPage INT)
BEGIN
    UPDATE RentalEmployees SET employeeID = eidFromDropdown
    WHERE rentalEmployeeID = rentalEmployeeIDFromCleaningPage;
END //
DELIMITER ;