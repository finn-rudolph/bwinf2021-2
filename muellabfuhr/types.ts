export type AdjMapWeighted = Array<Map<number, number>>;
export type AdjMatrix = Array<Array<number>>;

export type Route = { vertices: Array<number>; cost: number };

export type DijkstraVertex = {
	vertex: number;
	dis: number;
	pre: number | undefined;
	visited: boolean;
};
