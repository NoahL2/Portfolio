/* 
Citation for the following section of code
Date: 3/02/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-web-application-technology-2?module_item_id=26243419
*/

import React, {useEffect, useState} from "react";
import {Link, useParams, useNavigate, useLocation} from "react-router-dom";

function Edit({backendURL}) {
    const {rentalEmployeeID} = useParams();
    const [employees, setEmployees] = useState([]);
    const [dropdown, setDropdown] = useState(true);
    const [nameSelection, setNameSelection] = useState("");
    const location = useLocation();
    const employeeID = location.state?.employeeID;

    useEffect(() => {
        const getEmployees = async () => {
            try {
                const response = await fetch (`${backendURL}/api/edit/${rentalEmployeeID}`);
                const data = await response.json();
                
                setEmployees(data.employees);
            } catch (error) {
                console.error("Error loading employees: ", error);
            }
        };

        getEmployees();
    }, [backendURL, rentalEmployeeID]);

    const navigate = useNavigate();
    const movePages = () => {
            navigate(`/cleanings`);
        }
    const editing = async () => {
        
        if (!nameSelection) return;

        try {
            const response = await fetch(`${backendURL}/api/edit/${rentalEmployeeID}`,
                {
                    method:"POST",
                    headers: {"Content-Type": "application/json"},
                    body: JSON.stringify({eidFromDropdown: nameSelection, rentalEmployeeIDFromCleaningPage: rentalEmployeeID})
                }
            );            
            
            if (!response.ok){
                throw new Error("Failed to Update");
            }

            movePages();
        } catch (error) {
            console.error("ERROR: ", error);
        }
    };

    return (
        <div>
            <h1>Edit Cleaning Job</h1>
            <div style={{ display: "flex", gap: "20px" }}>
                <Link to="/">Home</Link>
                <Link to="/cleanings">Back to Cleanings</Link>
            </div>

            <h2>Edit</h2>
            <div>
                <label htmlFor="rentalEmployeeID">Rental Employee ID:</label>
                <input className="field" type="text" value={rentalEmployeeID} style={{marginLeft: "8px", width: "10px"}} readOnly/>
            </div>
            <div>
                <label htmlFor="employeeID">Current Employee ID:</label>
                <input className="field" type="text" value={employeeID} style={{marginLeft: "8px", width: "10px"}} readOnly/>
            </div>

            {dropdown && (
                <div style={{marginTop: "10px"}}>
                    <select value={nameSelection} onChange={(e) => setNameSelection(e.target.value)}>
                        <option value="">Select Employee</option>
                        {employees.map(emp => (
                            <option key={emp.eid} value={emp.eid}>{emp.eid} - {emp.employeeName}</option>
                        ))}
                    </select>

                    <button onClick={editing} style={{marginLeft: "10px"}}>Update</button>
                </div>
            )}
        </div>

    );
}

export default Edit;