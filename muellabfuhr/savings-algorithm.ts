import { AdjMapWeighted, Route, DijkstraVertex } from "./types.ts";
import { BinaryHeap } from "./data-structures.ts";

export const savings = (adjMap: AdjMapWeighted): Set<Route> => {
	const routes: Set<Route> = new Set();
	const belonging: Map<number, Route> = new Map();
	const dMatrix = new Array(adjMap.length);
	const preMatrix = new Array(adjMap.length);

	for (let i = 0; i < adjMap.length; i++) {
		const [distances, predecessors] = dijkstra(adjMap, i);
		dMatrix[i] = distances;
		preMatrix[i] = predecessors;
	}

	for (let i = 1; i < adjMap.length; i++) {
		const route: Route = { vertices: [0, i, 0], cost: 2 * dMatrix[0][i] };
		routes.add(route);
		belonging.set(i, route);
	}

	const savings = new BinaryHeap<{
		vertex1: number;
		vertex2: number;
		reduction: number;
	}>((a, b) => a.reduction >= b.reduction);

	for (let i = 1; i < adjMap.length; i++) {
		for (let j = i + 1; j < adjMap.length; j++) {
			if (i !== j) {
				savings.insert({
					vertex1: i,
					vertex2: j,
					reduction: dMatrix[0][i] + dMatrix[0][j] - dMatrix[i][j]
				});
			}
		}
	}

	while (routes.size > 5) {
		const sav = savings.top();
		savings.pop();
		const route1 = belonging.get(sav.vertex1)!;
		const route2 = belonging.get(sav.vertex2)!;

		if (
			route1 !== route2 &&
			(sav.vertex1 === route1.vertices[1] ||
				sav.vertex1 === route1.vertices[route1.vertices.length - 2]) &&
			(sav.vertex2 === route2.vertices[1] ||
				sav.vertex2 === route2.vertices[route2.vertices.length - 2])
		) {
			const newRoute: Route = {
				cost: route1.cost + route2.cost - sav.reduction,
				vertices: []
			};

			if (sav.vertex1 === route1.vertices[1]) {
				newRoute.vertices.push(...route2.vertices.slice(0, -1));
				newRoute.vertices.push(...route1.vertices.slice(1));
			} else {
				newRoute.vertices.push(...route1.vertices.slice(0, -1));
				newRoute.vertices.push(...route2.vertices.slice(1));
			}

			routes.delete(route1);
			routes.delete(route2);
			routes.add(newRoute);
			for (const v of newRoute.vertices) belonging.set(v, newRoute);
		}
	}

	console.log("Routes:\n", routes);
	return routes;
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
