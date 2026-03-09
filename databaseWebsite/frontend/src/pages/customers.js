/* 
Citation for the following section of code
Date: 3/02/26
Code wrote by Project Group 35 (Greyson Sparling, Noah Letter) using code from canvas explorations as reference
Source URL: https://canvas.oregonstate.edu/courses/2031764/pages/exploration-web-application-technology-2?module_item_id=26243419
*/

import React, {useEffect, useState} from "react";
import {Link} from "react-router-dom";
import TableRow from "./tableRow";

function Customers({backendURL}){
    const [customers, setCustomers] = useState([]);
    const [customerNameInput, setCustomerNameInput] = useState("");
    const [emailInput, setEmailInput] = useState("");

    const getData = async function () {
        try {
            const response = await fetch (`${backendURL}/api/customers`);
            const {customers} = await response.json();
            setCustomers(customers);
        } catch (error){
            console.log("ERROR: ", error);
        }
    };

    useEffect(() => {
        getData();
    }, []);

    const addition = async (e) => {
        e.preventDefault();

        try{
            const response = await fetch(`${backendURL}/api/customers`,
                {
                    method: "POST",
                    headers: {"Content-Type": "application/json"},
                    body: JSON.stringify({customerNameInput: customerNameInput, emailInput: emailInput})
                }
            );

            if(!response.ok){
                throw new Error("Couldn't add customer");
            }

            getData();
            setCustomerNameInput("");
            setEmailInput("");
        } catch (error){
            console.log("ERROR: ", error);
        }
    };

    return (
        <div>
            <h1>Customers</h1>
            <Link to="/">Home</Link>

            <h2>Our Customers</h2>
            <table className="customerTable">
                <thead>
                    <tr>
                        {customers.length > 0 && Object.keys(customers[0]).map((header, index) => (
                                <th key={index}>{header}</th>
                        ))}
                    </tr>
                </thead>
                <tbody>
                    {customers.map((customer, index) => (
                        <TableRow key={customer.customerID} rowObject={customer}/>
                    ))}
                </tbody>
            </table>

            <h2>Add Customer</h2>
            <form onSubmit={addition}>
                <input type="text" placeholder="Name" value={customerNameInput} onChange={(e) => setCustomerNameInput(e.target.value)}/>
                <input type="text" placeholder="Email" value={emailInput} onChange={(e) => setEmailInput(e.target.value)}/>
                <button type="submit">Add</button>
            </form>
        </div>
    );
}

export default Customers;