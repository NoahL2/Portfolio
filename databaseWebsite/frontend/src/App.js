import {BrowserRouter as Router, Routes, Route, Link } from "react-router-dom";

import Index from "./pages/index";
import Customers from "./pages/customers";
import Cleanings from "./pages/cleanings";
import Rent from "./pages/rent";
import Staff from "./pages/staff";
import Boats from "./pages/boats";
import Types from "./pages/boatTypes";
import Edit from "./pages/edit";

const backendPort = 58414;

function App(){
  const backendURL = `http://classwork.engr.oregonstate.edu:${backendPort}`;

  return (
    <Router>
        <Routes>
          <Route path="/" element={<Index backendURL={backendURL}/>} />
          <Route path="/customers" element={<Customers backendURL={backendURL}/>} />
          <Route path="/cleanings" element={<Cleanings backendURL={backendURL}/>} />
          <Route path="/rent" element={<Rent backendURL={backendURL}/>} />
          <Route path="/staff" element={<Staff backendURL={backendURL}/>} />
          <Route path="/types" element={<Types backendURL={backendURL} />} />
          <Route path="/edit/:rentalEmployeeID" element={<Edit backendURL={backendURL}/>} />
          <Route path="/boats" element={<Boats backendURL={backendURL}/>} />
        </Routes>
    </Router>
  );
}

export default App;