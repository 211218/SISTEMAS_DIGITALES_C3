import { BrowserRouter, Routes, Route } from "react-router-dom";
import Home from './Home';
import History from './Components/History';


function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route index element={<Home />} />
        <Route path="/" element={<Home />} />
        <Route path="History" element={<History />} />
      </Routes>
    </BrowserRouter>
  )
}

export default App;
