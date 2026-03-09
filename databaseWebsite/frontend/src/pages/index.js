import {Link} from "react-router-dom";

function Index({backendURL}){
    const resetDatabase = async () => {
        const confirmReset = window.confirm(
            "Do you want to reset?"
        );
        if (!confirmReset) return;

        try{
            const response = await fetch (`${backendURL}/api/reset`,{
                method: "POST"
            });

            console.log("STATUS: ", response.status);

            if (!response.ok){
                throw new Error("Reset failed");
            }
            
            alert("Database successfull reset");

        } catch(error){
            console.log("FULL ERROR: ", error);
            alert("Reset failed.");
        }
    };

    return (
        <div>
            <h1>Pacific Boat Rental</h1>
            <div style={{ display: "flex", gap: "20px" }}>
                <Link to="/cleanings">Need Cleaning</Link>
                <Link to="/customers">Customers</Link>
                <Link to="/staff">Our Staff</Link>
                <Link to="/rent">Rentals</Link>
                <Link to="/boats">Boats</Link>
                <Link to="/types">Boat Types</Link>
            </div>
            <div style = {{marginTop: "30px"}}>
                <button onClick={resetDatabase}>
                    Reset Database
                </button>
            </div>
        </div>
    );
}

export default Index;