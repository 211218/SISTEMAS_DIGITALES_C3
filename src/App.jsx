import { BrowserRouter, Routes, Route } from "react-router-dom";
import Home from './Home';
import History from './Components/History';
import Distancia from './Components/Distancia';
import Presion from "./Components/Presion";


function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route index element={<Home />} />
        <Route path="/" element={<Home />} />
        <Route path="History" element={<History />} />
        <Route path="Distancia" element={<Distancia/>} />
        <Route path="Presion" element={<Presion/>} />
      </Routes>
    </BrowserRouter>
  )
}

export default App;
