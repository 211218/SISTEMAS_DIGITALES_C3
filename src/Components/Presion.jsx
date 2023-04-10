import '../CSS/History.css';
import db from '../firebase';
import { useState, useEffect } from 'react';
import { ref, onValue} from "firebase/database";

const Presion = () => {

    const [todos, setTodos] = useState([]);

    useEffect(() => {
        onValue(ref(db, "esp32/digitales/sensor"), (snapshot) => {
            setTodos([]);
            const data = snapshot.val();
            if (data !== null) {
                Object.values(data).map((todo) => {
                    setTodos((oldArray) => [...oldArray, todo]);
                });
            }
        });
    }, []);

    console.log("data", todos);

    return (
        <div className="parent1">
            <div className="div11">
            </div>
            <div className="div2">
                <div className='title-home'>
                    <h1 >Hist.. Atmosferica</h1>
                </div>
            </div>
            <div className="div31">

                <table summary="Los grupos de música punk más famosos del Reino Unido">
                    <thead>
                        <tr>
                            <th scope="col">ID</th>
                            <th scope="col">Presion</th>
                            <th scope="col">Altitud</th>
                            <th scope="col">FECHA</th>

                        </tr>
                    </thead>

                    <tbody>
                                {todos.map((todo) => (
                                    <tr>
                                        <th scope="row">{todo.Id}</th>
                                        <td>{todo.Presion}</td>
                                        <td>{todo.Altitud}</td>
                                        <td>{todo.Hora}</td>

                                    </tr>
                                ))}
                            </tbody>
                </table>

            </div>
        </div>
    )
}

export default Presion;