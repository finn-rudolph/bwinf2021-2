export const generateEquation = (
	n: number,
	operators: Array<string>
): string => {
	let result = randomInt(10);
	let leftTerm = result.toString();

	const lastOperators: Array<string | undefined> = [undefined, undefined];
	const lastDigits: Array<number | undefined> = [undefined, undefined];

	for (let i = 1; i <= n; i++) {
		const operator = nextOperator(operators, lastOperators);
		const digit = nextDigit(lastDigits, operator, result);

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
				result /= digit;
				break;
		}

		leftTerm += ` ${operator} ${digit}`;
	}
	return `${leftTerm} = ${result}`;
};

export const mystify = (equation: string) =>
	equation.replace(/(\+|-|\*|\/)/g, "o");

const nextOperator = (
	operators: Array<string>,
	forbidden: Array<string | undefined>
): string => {
	let operator = operators[randomInt(operators.length)];
	while (forbidden.includes(operator))
		operator = operators[randomInt(operators.length)];

	forbidden.unshift(operator);
	forbidden.pop();

	return operator;
};

const nextDigit = (
	forbidden: Array<number | undefined>,
	operator: string,
	result: number
): number => {
	let digit = randomInt(10);
	while (
		forbidden.includes(digit) ||
		(operator == "/" && result % digit != 0) ||
		((operator == "+" || operator == "-") && digit == 0) ||
		((operator == "*" || operator == "/") && digit == 1)
	)
		digit = randomInt(10);

	forbidden.unshift(digit);
	forbidden.pop();

	return digit;
};

// The limit is exclusive.
const randomInt = (limit: number) => Math.floor(Math.random() * limit);
