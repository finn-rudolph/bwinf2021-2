import { AdjMatrix, AdjMapWeighted } from "./types.ts";

// Edge weight is not implemented yet for the Adjacency Map.
export const toAdjacencyMap = (
	file: string
): [number, number, AdjMapWeighted] => {
	const [size, ...edges] = file.split(/\r\n|\n/);
	const [n, m] = size.split(" ").map((x) => Number(x));

	const adjMap: AdjMapWeighted = new Array(n)
		.fill(undefined)
		.map(() => new Map());

	for (let i = 0; i < edges.length; i++) {
		const [v1, v2, w] = edges[i].split(" ").map((x) => Number(x));
		adjMap[v1].set(v2, w);
		adjMap[v2].set(v1, w);
	}
	return [n, m, adjMap];
};

export const toAdjacencyMatrix = (
	file: string
): [number, number, AdjMatrix] => {
	const [size, ...edges] = file.split(/\r\n|\n/);
	const [n, m] = size.split(" ").map((x) => Number(x));

	const adjMatrix: AdjMatrix = [...Array(n)].map(() => new Array(n).fill(0));

	for (let i = 0; i < edges.length; i++) {
		const [v1, v2, w] = edges[i].split(" ").map((x) => Number(x));
		adjMatrix[v1][v2] = w;
		adjMatrix[v2][v1] = w;
	}
	return [n, m, adjMatrix];
};
