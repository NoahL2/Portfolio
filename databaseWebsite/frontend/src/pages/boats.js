/* 
Citation for the following section of code
Date: 3/02/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-web-application-technology-2?module_item_id=26243419
*/


import React, {useEffect, useState} from "react";
import {Link} from "react-router-dom";
import TableRow from "./tableRow";

function Boats({backendURL}) {
    const [boats, setBoats] = useState([]);

    const getData = async function () {
        try {
            const response = await fetch (`${backendURL}/api/boats`);
            const {boats} = await response.json();
            setBoats(boats);
        } catch (error){
            console.log("ERROR: ", error);
        }
    };

    useEffect(() => {
        getData();
    }, []);

    return (
        <div>
            <h1>Boats</h1>
            <Link to="/">Home</Link>
            <h2>Our Boats</h2>
            <table className="boatTable">
                <thead>
                    <tr>
                        {boats.length > 0 && Object.keys(boats[0]).map((header, index) => (
                            <th key={index}>{header}</th>
                        ))}
                    </tr>
                </thead>
                <tbody>
                    {boats.map((boat, index) => (
                        <TableRow key={index} rowObject={boat}/>
                    ))}
                </tbody>
            </table>
        </div>
    );
}

export default Boats;