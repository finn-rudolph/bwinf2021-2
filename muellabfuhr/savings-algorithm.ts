import { AdjMapWeighted, Route, DijkstraVertex } from "./types.ts";
import { BinaryHeap } from "./data-structures.ts";

export const savings = (adjMap: AdjMapWeighted): Array<Route> => {
	const routes: Array<Route> = [];
	const dMatrix = new Array(adjMap.length);
	const preMatrix = new Array(adjMap.length);

	for (let i = 0; i < adjMap.length; i++) {
		const [distances, predecessors] = dijkstra(adjMap, i);
		dMatrix[i] = distances;
		preMatrix[i] = predecessors;
	}

	console.log(dMatrix);

	return [];
};

export const dijkstra = (
	adjMap: AdjMapWeighted,
	start: number
): [Array<number | undefined>, Array<number | undefined>] => {
	const vertices: Array<DijkstraVertex> = new Array(adjMap.length)
		.fill(0)
		.map((_v, i) => {
			return {
				v: i,
				d: Infinity,
				pre: undefined,
				vis: false
			};
		});
	vertices[start].d = 0;

	const toBeProcessed = new BinaryHeap<DijkstraVertex>(
		(a, b) => a.d <= b.d,
		[vertices[start]]
	);

	while (toBeProcessed.length() !== 0) {
		const { v: curr, d: currD } = toBeProcessed.top();
		toBeProcessed.pop();
		vertices[curr].vis = true;

		for (const [neighbor, w] of adjMap[curr]) {
			if (!vertices[neighbor].vis && vertices[neighbor].d > currD + w) {
				vertices[neighbor].d = currD + w;
				vertices[neighbor].pre = curr;
				toBeProcessed.insert(vertices[neighbor]);
			}
		}
	}
	const distances: Array<number> = [];
	const predecessors: Array<number | undefined> = [];

	for (let i = 0; i < vertices.length; i++) {
		distances.push(vertices[i].d);
		predecessors.push(vertices[i].pre);
	}
	return [distances, predecessors];
};
