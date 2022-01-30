// Edge weight is not implemented yet for the Adjacency Map.
const toAdjacencyMap = (
	file: string
): [number, number, Map<number, Set<number>>] => {
	const [size, ...edges] = file.split(/\r\n|\n/);
	const [n, m] = size.split(" ").map((x) => Number(x));

	const adjMap: Map<number, Set<number>> = new Map();

	for (let i = 0; i < edges.length; i++) {
		const [vertex1, vertex2, _weight] = edges[i]
			.split(" ")
			.map((x) => Number(x));

		if (!adjMap.has(vertex1)) adjMap.set(vertex1, new Set());
		adjMap.get(vertex1)?.add(vertex2);

		if (!adjMap.has(vertex2)) adjMap.set(vertex2, new Set());
		adjMap.get(vertex2)?.add(vertex1);
	}
	return [n, m, adjMap];
};

const toAdjacencyMatrix = (
	file: string
): [number, number, Array<Array<number>>] => {
	const [size, ...edges] = file.split(/\r\n|\n/);
	const [n, m] = size.split(" ").map((x) => Number(x));

	const adjMatrix: Array<Array<number>> = [...Array(n)].map(() =>
		new Array(n).fill(0)
	);

	for (let i = 0; i < edges.length; i++) {
		const [vertex1, vertex2, weight] = edges[i]
			.split(" ")
			.map((x) => Number(x));
		adjMatrix[vertex1][vertex2] = weight;
		adjMatrix[vertex2][vertex1] = weight;
	}
	return [n, m, adjMatrix];
};
