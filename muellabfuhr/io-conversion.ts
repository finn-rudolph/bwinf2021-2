import { AdjMatrix, AdjMapWeighted, AdjMap } from "./types.ts";

// Edge weight is not implemented yet for the Adjacency Map.
export const toAdjacencyMap = (
	file: string
): [number, number, AdjMapWeighted] => {
	const [size, ...edges] = file.split(/\r\n|\n/);
	const [n, m] = size.split(" ").map((x) => Number(x));

	const adjMap: AdjMapWeighted = new Array(n)
		.fill(undefined)
		.map(() => new Map());

	for (let i = 0; i < edges.length && edges[i] !== ""; i++) {
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

	for (let i = 0; i < edges.length && edges[i] !== ""; i++) {
		const [v1, v2, w] = edges[i].split(" ").map((x) => Number(x));
		adjMatrix[v1][v2] = w;
		adjMatrix[v2][v1] = w;
	}
	return [n, m, adjMatrix];
};

export const invertGraph = (adjMap: AdjMapWeighted, m: number) => {
	const edgeAdjMap: AdjMap = new Array(m)
		.fill(undefined)
		.map(() => new Set());

	const belongingIndices: Array<Map<number, number>> = new Array(
		adjMap.length
	)
		.fill(undefined)
		.map(() => new Map());

	const belongingEdges: Array<{ a: number; b: number }> = new Array(m);

	// Correspond to vertex weights in the inverse graph
	const edgeWeights: Array<number> = new Array(m);

	let i = 0;
	for (const v1 in adjMap) {
		for (const [v2, w] of adjMap[v1]) {
			if (v2 > Number(v1)) {
				belongingIndices[v1].set(v2, i);
				belongingIndices[v2].set(Number(v1), i);
				belongingEdges[i] = { a: Number(v1), b: v2 };
				edgeWeights[i] = w;
				i += 1;
			}
		}
	}

	for (const v1 in adjMap) {
		for (const [v2, _w] of adjMap[v1]) {
			for (const [u, _w] of adjMap[v1]) {
				edgeAdjMap[belongingIndices[v1].get(v2)!].add(
					belongingIndices[v1].get(u)!
				);
			}
		}
	}
	return [edgeAdjMap, edgeWeights, belongingIndices, belongingEdges];
};
