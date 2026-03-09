/* 
Citation for the following section of code
Date: 3/02/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-web-application-technology-2?module_item_id=26243419
*/

import React, {useEffect, useState} from "react";
import {Link} from "react-router-dom";
import TableRow from "./tableRow";

function Rentals({backendURL}){
    const [rentals, setRentals] = useState([]);

    const getData = async function () {
        try {
            const response = await fetch (`${backendURL}/api/rent`);
            const {rentals} = await response.json();
            setRentals(rentals);
        } catch (error){
            console.log("ERROR: ", error);
        }
    };

    useEffect(() => {
        getData();
    }, []);


    return (
        <div>
            <h1>Rentals</h1>
            <Link to="/">Home</Link>

            <h2>Available For Rent</h2>
            <table className="rentTable">
                <thead>
                    <tr>
                        {rentals.length > 0 && Object.keys(rentals[0]).map((header, index) => (
                            <th key={index}>{header}</th>
                        ))}
                    </tr>
                </thead>
                <tbody>
                    {rentals.map((rental, index) => (
                        <TableRow key={index} rowObject={rental}/>
                    ))}
                </tbody>
            </table>

        </div>
    );
}

export default Rentals;