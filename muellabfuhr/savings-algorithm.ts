import { AdjMapWeighted, Route, DijkstraVertex } from "./types.ts";
import { BinaryHeap } from "./data-structures.ts";

export const savings = (adjMap: AdjMapWeighted): Set<Route> => {
	const routes: Set<Route> = new Set();
	const belonging: Map<number, Route> = new Map();
	const disMatrix = new Array(adjMap.length);
	const preMatrix = new Array(adjMap.length);

	for (let i = 0; i < adjMap.length; i++) {
		const [distances, predecessors] = dijkstra(adjMap, i);
		disMatrix[i] = distances;
		preMatrix[i] = predecessors;
	}

	for (let i = 1; i < adjMap.length; i++) {
		const route: Route = { vertices: [0, i, 0], cost: 2 * disMatrix[0][i] };
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
					reduction:
						disMatrix[0][i] + disMatrix[0][j] - disMatrix[i][j]
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
				newRoute.vertices.push(
					...route2.vertices.slice(0, -1),
					...route1.vertices.slice(1)
				);
			} else {
				newRoute.vertices.push(
					...route1.vertices.slice(0, -1),
					...route2.vertices.slice(1)
				);
			}

			routes.delete(route1);
			routes.delete(route2);
			routes.add(newRoute);
			for (const v of newRoute.vertices) belonging.set(v, newRoute);
		}
	}
	const tracedRoutes = traceBackRoutes(routes, preMatrix);
	return tracedRoutes;
};

const traceBackRoutes = (
	routes: Set<Route>,
	preMatrix: Array<Array<number | undefined>>
): Set<Route> => {
	const traced: Set<Route> = new Set();
	for (const route of routes) {
		const realRoute: Route = {
			cost: route.cost,
			vertices: []
		};
		realRoute.vertices.push(route.vertices[0]);

		for (let i = 0; i < route.vertices.length - 1; i++) {
			let curr = preMatrix[route.vertices[i + 1]][route.vertices[i]];

			while (curr !== undefined) {
				realRoute.vertices.push(curr);
				curr = preMatrix[route.vertices[i + 1]][curr];
			}
		}
		traced.add(realRoute);
	}
	return traced;
};

export const dijkstra = (
	adjMap: AdjMapWeighted,
	start: number
): [Array<number | undefined>, Array<number | undefined>] => {
	const vertices: Array<DijkstraVertex> = new Array(adjMap.length)
		.fill(0)
		.map((_v, i) => {
			return {
				vertex: i,
				dis: Infinity,
				pre: undefined,
				visited: false
			};
		});
	vertices[start].dis = 0;

	const queue = new BinaryHeap<DijkstraVertex>(
		(a, b) => a.dis <= b.dis,
		[vertices[start]]
	);

	while (queue.length() !== 0) {
		const { vertex: curr, dis: currDis } = queue.top();
		queue.pop();
		vertices[curr].visited = true;

		for (const [neighbor, cost] of adjMap[curr]) {
			if (
				!vertices[neighbor].visited &&
				vertices[neighbor].dis > currDis + cost
			) {
				vertices[neighbor].dis = currDis + cost;
				vertices[neighbor].pre = curr;
				queue.insert(vertices[neighbor]);
			}
		}
	}
	const distances: Array<number> = [];
	const predecessors: Array<number | undefined> = [];

	for (let i = 0; i < vertices.length; i++) {
		distances.push(vertices[i].dis);
		predecessors.push(vertices[i].pre);
	}
	return [distances, predecessors];
};
