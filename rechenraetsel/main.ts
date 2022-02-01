import { generateEquation, mystify } from "./generate.ts";

const operators = ["+", "-", "*", "/"];

const n = Number(prompt("Anzahl an Operatoren: "));

const equation = generateEquation(n, operators);
const riddle = mystify(equation);

console.log(riddle);
console.log("Lösung: ", equation);
