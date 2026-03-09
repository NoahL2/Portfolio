/* 
Citation for the following section of code
Date: 3/02/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-web-application-technology-2?module_item_id=26243419
https://canvas.oregonstate.edu/courses/2031764/pages/exploration-implementing-cud-operations-in-your-app?module_item_id=26243436
*/

import React, {useEffect, useState} from "react";
import {Link} from "react-router-dom";
import TableRow from "./tableRow";

function Employees({backendURL}){
    const [employees, setEmployees] = useState([]);
    const [idSelection, setIdSelection] = useState("");

    const headerMap = {
        eid: "Employee ID",
        employeeName: "Name"
    };

    const getData = async function () {
        try {
            const response = await fetch (`${backendURL}/api/staff`);
            const {employees} = await response.json();
            setEmployees(employees);
        } catch (error){
            console.log("ERROR: ", error);
        }
    };

    useEffect(() => {
        getData();
    }, []);

    const deletion = async () => {
        if (!idSelection) return;

        const deletedEmployee = employees.find(
            emp => emp.eid === Number(idSelection)
        );

        const deletedName = deletedEmployee?.employeeName;
        console.log("Deleting employee: ", deletedName);

        try{
            const response = await fetch(
                `${backendURL}/api/staff`,
                {method: "POST", 
                    headers: {"Content-Type": "application/json"},
                    body: JSON.stringify({eidFromDropdown: idSelection, deletedEmployeeName: deletedName})
                }
            );

            if (!response.ok){
                throw new Error("Couldn't remove employee");
            }

            await getData();
            setIdSelection("");

        } catch(error){
            console.log("ERROR: ", error);
        }
    };

    return (
        <div>
            <h1>Staff</h1>
            <Link to="/">Home</Link>
            

            <h2>Our Staff</h2>
            <table className="staffTable">
                <thead>
                    <tr>
                        {employees.length > 0 && Object.keys(employees[0]).map((header, index) => (
                            <th key={index}>{headerMap[header] || header}</th>
                        ))}
                    </tr>
                </thead>
                <tbody>
                    {employees.map((employee, index) => (
                        <TableRow key={index} rowObject={employee}/>
                    ))}
                </tbody>
            </table>

            <h2>Remove Employee</h2>
            
        
                <div style={{marginTop: "10px"}}>
                    <select value={idSelection} onChange={(e) => setIdSelection(e.target.value)}>
                        <option value="">Select Employee</option>
                        {employees.map(emp => (
                            <option key={emp.eid} value={emp.eid}>{emp.employeeName}</option>
                        ))}
                    </select>

                    <button onClick={deletion} style={{marginLeft: "10px"}}>
                        Confirm
                    </button>
                </div>
        </div>
    );
}

export default Employees;
