import { AdjMapWeighted, Route, DijkstraVertex } from "./types.ts";
import { BinaryHeap } from "./data-structures.ts";

export const savings = (adjMap: AdjMapWeighted, m: number): Set<Route> => {
	const routes: Array<Route> = [];
	const belonging: Array<Map<number, Route>> = new Array(m)
		.fill(undefined)
		.map(() => new Map());
	const dis = new Array(adjMap.length);
	const pre = new Array(adjMap.length);

	for (let i = 0; i < adjMap.length; i++) {
		const [distances, predecessors] = dijkstra(adjMap, i);
		dis[i] = distances;
		pre[i] = predecessors;
	}

	for (let i = 0; i < adjMap.length; i++) {
		for (const [j, w] of adjMap[i]) {
			const route: Route = {
				vertices: [0, i, j, 0],
				cost: dis[0][i] + w + dis[0][j]
			};

			routes.push(route);
			belonging[i].set(j, route);
			belonging[j].set(i, route);
		}
	}

	const savings = new BinaryHeap<{
		vertices: [number, number, number, number];
		reduction: number;
	}>((a, b) => a.reduction >= b.reduction);

	for (let i = 0; i < routes.length; i++) {
		for (let j = i + 1; j < routes.length; j++) {
			for (let p = 0; p < 4; p++) {
				const [a1, b1, a2, b2] = [
					routes[i].vertices[(p % 2) + 1],
					routes[i].vertices[(p % 2) + 2],
					routes[j].vertices[Math.floor(p / 2) + 1],
					routes[j].vertices[Math.floor(p / 2) + 2]
				];
				savings.insert({
					vertices: [a1, b1, a2, b2],
					reduction: dis[0][b1] + dis[0][a2] - dis[b1][a2]
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
	const tracedRoutes = traceBackRoutes(routes, pre);
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
