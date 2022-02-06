export type AdjMapWeighted = Array<Map<number, number>>;
export type AdjMatrix = Array<Array<number>>;
export type AdjMap = Array<Set<number>>;

export type Route = { vertices: Array<number>; length: number };

export type DijkstraVertex = {
	v: number;
	d: number;
	pre: number | undefined;
	vis: boolean;
};
