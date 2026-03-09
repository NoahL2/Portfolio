/* 
Citation for the following section of code
Date: 3/02/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-web-application-technology-2?module_item_id=26243419
*/

import React, {useEffect, useState} from "react";
import {Link, useNavigate} from "react-router-dom";
import TableRow from "./tableRow";

function Cleanings({backendURL}){
    const [cleanings, setCleaning] = useState([]);

    const getData = async function () {
        try{
            const response = await fetch (`${backendURL}/api/cleanings`);
            const {cleanings} = await response.json();
            setCleaning(cleanings);
        }catch(error){
            console.log("ERROR: ", error);
        }
    }

    useEffect(() => {
        getData();
    }, []);

    const navigate = useNavigate();
    const movePages = (rentalEmployeeID, employeeID) => {
        navigate(`/edit/${rentalEmployeeID}`, {state: {employeeID}});
    }

    return (
        <div>
            <h1>Cleaning</h1>
            <Link to="/">Home</Link>

            <h2>Cleaning Jobs</h2>
            <table className="cleaningTable">
                <thead>
                    <tr>
                        {cleanings.length > 0 && Object.keys(cleanings[0]).map((header, index) => (
                            <th key={index}>{header}</th>
                        ))}
                        <th>actions</th>
                    </tr>
                </thead>
                <tbody>
                    {cleanings.map(c => (
                        <TableRow 
                            key={`${c.rentalID}-${c.employeeID}`}
                            rowObject={c}
                            actions={<button onClick={() => movePages( c.rentalEmployeeID, c.employeeID)}>Edit</button>}
                        />
                    ))}
                </tbody>
            </table>

        </div>
    );
}

export default Cleanings;