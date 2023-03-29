import './CSS/home.css';
import { Link } from "react-router-dom";


const Home = () => {





    return (
        <div className="parent">
            <div className="div1"></div>

            <div className="div2">
                <h1>Welcome to the Esp32</h1>
            </div>

            <div className="div3">
                <div className='response'>
                    <h1>SENSOR DHT11</h1>
                    <Link to="History">
                        <button type="button" >Historial</button>
                    </Link>
                </div>

            </div>
            <div className="div4">
                <div>
                    <h1>SENSOR PRESION</h1>
                    <Link to="History">
                        <button type="button" >Historial</button>
                    </Link>
                </div>

            </div>
            <div className="div5">
                <div>
                    <h1>SENSOR ULTRASONICO</h1>
                    <Link to="History">
                        <button type="button" >Historial</button>
                    </Link>
                </div>
            </div>
        </div>
    )
}

export default Home;