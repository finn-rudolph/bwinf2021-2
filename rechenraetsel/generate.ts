export const generateEquation = (
	n: number,
	operators: Array<string>
): string => {
	const lastOperators: Array<string | undefined> = new Array(2);
	const lastDigits: Array<number | undefined> = new Array(2);

	const rankRes: Array<number> = new Array(2);
	const rankOp: Array<string> = new Array(2);

	rankRes[1] = randomInt(10);
	let leftTerm = rankRes[1].toString();

	for (let i = 1; i <= n; i++) {
		let digit: number | undefined, operator: string;

		do {
			operator = randomOp(operators, lastOperators);
			digit = randomDg(lastDigits, operator, rankRes);
		} while (digit === undefined);

		switch (operator) {
			case "+":
				rankRes[0] = applyOp(rankRes[0], rankRes[1], rankOp[0]);
				rankOp[0] = "+";
				rankRes[1] = digit;
				break;
			case "-":
				rankRes[0] = applyOp(rankRes[0], rankRes[1], rankOp[0]);
				rankOp[0] = "-";
				rankRes[1] = digit;
				break;
			case "*":
				rankRes[1] = applyOp(rankRes[1], digit, operator);
				rankOp[1] = "*";
				break;
			case "/":
				rankRes[1] = applyOp(rankRes[1], digit, operator);
				rankOp[1] = "/";
				break;
		}
		leftTerm += ` ${operator} ${digit}`;
	}
	return `${leftTerm} = ${applyOp(rankRes[0], rankRes[1], rankOp[0])}`;
};

export const mystify = (equation: string) =>
	equation.replace(/(\+|-|\*|\/)/g, "o");

const randomOp = (
	operators: Array<string>,
	forbidden: Array<string | undefined>
): string => {
	let operator: string;

	do {
		operator = operators[randomInt(operators.length)];
	} while (forbidden.includes(operator));

	forbidden.unshift(operator);
	forbidden.pop();

	return operator;
};

const randomDg = (
	forbidden: Array<number | undefined>,
	operator: string,
	rankRes: Array<number>
): number | undefined => {
	let digit: number;
	const digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

	do {
		[digit] = digits.splice(randomInt(digits.length), 1);
		if (digits.length === 0) return undefined;
	} while (
		// Ensure integral result
		(operator === "/" && (digit === 0 || rankRes[1] % digit !== 0)) ||
		// Ensure explicit result
		forbidden.includes(digit) ||
		((operator === "+" || operator === "-") && digit === 0) ||
		((operator === "*" || operator === "/") && digit === 1) ||
		((operator === "+" || operator === "*") &&
			digit === 2 &&
			rankRes[1] === 2)
	);

	forbidden.unshift(digit);
	forbidden.pop();

	return digit;
};

const applyOp = (a: number | undefined, b: number, op: string): number => {
	if (a === undefined) return b;
	switch (op) {
		case "+":
			return a + b;
		case "-":
			return a - b;
		case "*":
			return a * b;
		case "/":
			return a / b;
	}
	throw new Error("Invalid operator.");
};

// The limit is exclusive.
const randomInt = (limit: number) => Math.floor(Math.random() * limit);
