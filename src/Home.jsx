import './CSS/home.css';
import { Link } from "react-router-dom";
import React, { useState, useEffect } from 'react';
import db from './firebase';
import { ref, onValue} from "firebase/database";


const Home = () => {
    const [todo, setTodo] = useState('');
    const [todos, setTodos] = useState([]);
    const [Temperatura, setTemperatura] = useState('');
    const [Humedad, setHumedad] = useState('');
    const [Presion, setPresion] = useState('');
    const [Distancia, setDistancia] = useState('');
    const [Altitud, setAltitud] = useState('');

    useEffect(() => {
        onValue(ref(db, "esp32/digitales/sensor"), (snapshot) => {
            setTodos([]);
            const data = snapshot.val();
            if (data !== null) {
                Object.values(data).map((todo) => {
                    setTemperatura((oldArray) => [...oldArray, todo.Temperatura]);
                    setHumedad((oldArray) => [...oldArray, todo.Humedad]);
                    setPresion((oldArray) => [...oldArray, todo.Presion]);
                    setDistancia((oldArray) => [...oldArray, todo.Distancia]);
                    setAltitud((oldArray) => [...oldArray, todo.Altitud]);
                });
            }
        });
    }, []);


    console.log("data", todos);


    return (
        <div className="parent">
            <div className="div1"></div>

            <div className="div2">
                <div className='title-home'>
                    <h1 >Welcome to Esp32</h1>
                </div>
            </div>

            <div className="div3">
                <div className='response'>
                    <h1 className='title'>SENSOR DHT11</h1>

                    <h1 className='text'>Humedad: {Humedad[Humedad.length - 1]}%rh</h1>
                    <h1 className='text'>Temperatura:  {Temperatura[Temperatura.length - 1]}°c</h1>
                    <Link to="History" type='button'>
                        <button type="button" >Historial</button>
                    </Link>
                </div>

            </div>
            <div className="div4">
                <div className='response'>
                    <h1 className='title'>SENSOR PRESIÓN</h1>
                    <h1 className='text'>Presion: {Presion[Presion.length - 1]}hPa</h1>
                    <h1 className='text'>Altitud: {Altitud[Altitud.length - 1]}m</h1>
                    <Link to="Presion">
                        <button type="button" >Historial</button>
                    </Link>
                </div>
                
            </div>
            <div className="div5">
                <div className='response'>
                    <h1 className='title'>SENSOR ULTRASONICO</h1>
                    <h1 className='text'>Distancia:  {Distancia[Distancia.length - 1]}m</h1>
                    <Link to="Distancia">
                        <button type="button" >Historial</button>
                    </Link>
                </div>
            </div>

        </div>
    )
}

export default Home;