export const generateEquation = (
	n: number,
	operators: Array<string>
): string => {
	let result = randomInt(10);
	let leftTerm = result.toString();

	for (let i = 1; i <= n; i++) {
		const operator = operators[randomInt(operators.length)];
		let digit = randomInt(10);

		switch (operator) {
			case "+":
				result += digit;
				break;
			case "-":
				result -= digit;
				break;
			case "*":
				result *= digit;
				break;
			case "/":
				while (result % digit != 0) digit = randomInt(10);
				result /= digit;
				break;
		}
		leftTerm += ` ${operator} ${digit}`;
	}
	return `${leftTerm} = ${result}`;
};

export const mystify = (equation: string) =>
	equation.replace(/(\+|-|\*|\/)/g, "o");

// The limit is exclusive.
const randomInt = (limit: number) => Math.floor(Math.random() * limit);
