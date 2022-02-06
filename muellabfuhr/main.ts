import { toAdjacencyMap, invertGraph } from "./io-conversion.ts";
import { savings } from "./savings-algorithm.ts";

const testCases = 1;

for (let i = 0; i < testCases; i++) {
	const file = await Deno.readTextFile(
		`muellabfuhr/beispiele/muellabfuhr${i}.txt`
	);
	const [n, m, adjMap] = toAdjacencyMap(file);
	const inverted = invertGraph(adjMap, m);
	console.log(adjMap);
	savings(adjMap);
}
