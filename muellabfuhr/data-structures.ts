export class BinaryHeap<T> {
	private arr: Array<T>;
	private greater: (a: T, b: T) => boolean;

	constructor(comparisonFn: (a: T, b: T) => boolean, values: Array<T> = []) {
		this.arr = [];
		this.greater = comparisonFn;

		for (let i = 0; i < values.length; i++) {
			this.insert(values[i]);
		}
	}

	insert(v: T): void {
		this.arr.push(v);
		let i = this.arr.length - 1;

		while (i > 0 && this.greater(v, this.arr[this.parent(i)])) {
			const tmp = this.arr[i];
			this.arr[i] = this.arr[this.parent(i)];
			this.arr[this.parent(i)] = tmp;
			i = this.parent(i);
		}
	}

	top(): T {
		return this.arr[0];
	}
	pop(): void {
		this.arr[0] = this.arr[this.arr.length - 1];
		this.arr.pop();

		let i = 0;
		let j = this.greaterChild(i);

		while (i < this.arr.length && !this.greater(this.arr[i], this.arr[j])) {
			const tmp = this.arr[i];
			this.arr[i] = this.arr[j];
			this.arr[j] = tmp;

			i = j;
			j = this.greaterChild(i);
		}
	}

	private greaterChild(i: number): number {
		return i * 2 + 2 < this.arr.length
			? this.greater(this.arr[i * 2 + 2], this.arr[i * 2 + 1])
				? i * 2 + 2
				: i * 2 + 1
			: i * 2 + 1 < this.arr.length
			? i * 2 + 1
			: i;
	}
	private parent(i: number): number {
		return Math.floor((i - 1) / 2);
	}

	length(): number {
		return this.arr.length;
	}
}
