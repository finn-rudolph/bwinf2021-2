import { generateEquation } from "./generate.ts";

const operators = ["+", "-", "*", "/"];
const size = 4;
const cases = 1;

const report: { solutions: Set<string> } = {
	solutions: new Set()
};

const testUniqueness = (
	splitted: Array<string>,
	operators: Array<string>,
	result: number,
	i0 = 1
) => {
	const doTest = i0 === splitted.length - 2;
	for (let i = i0; i < splitted.length; i += 2) {
		for (let j = 0; j < operators.length; j++) {
			const splCopy = splitted.slice();
			splCopy[i] = operators[j];
			const newRiddle = splCopy.join(" ");

			if (doTest) {
				if (eval(newRiddle) === result) report.solutions.add(newRiddle);
			} else {
				testUniqueness(splCopy, operators, result, i + 2);
			}
		}
	}
};

for (let i = 0; i < cases; i++) {
	const splitted = generateEquation(size, operators).split(" ");
	const result = Number(splitted[splitted.length - 1]);
	splitted.splice(splitted.length - 2, 2);

	testUniqueness(splitted, operators, result);

	console.log(splitted.join(" "), "=", result);

	report.solutions.forEach((e) => console.log(e));
	report.solutions.clear();

	if (!eval(splitted.join(" ").replace("=", "===")))
		throw new Error("invalid riddle");
}
