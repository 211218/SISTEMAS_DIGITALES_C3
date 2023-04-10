import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";

const firebaseConfig = {
  apiKey: "AIzaSyBMAHvh9hTpe9-bPRUIyw_v4K7NBrneNLA",
  authDomain: "integrative-project.firebaseapp.com",
  databaseURL: "https://integrative-project-default-rtdb.firebaseio.com",
  projectId: "integrative-project",
  storageBucket: "integrative-project.appspot.com",
  messagingSenderId: "319391819666",
  appId: "1:319391819666:web:84c2c606138785670a834b",
  measurementId: "G-1XDW3TJHY1"
};

const app = initializeApp(firebaseConfig);
const db = getDatabase(app);
export default db;