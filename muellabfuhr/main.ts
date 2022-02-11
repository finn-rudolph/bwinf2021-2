import {
	toAdjacencyMap,
	invertGraph,
	revertWalks,
	formatOutput
} from "./io-conversion.ts";
import { savings } from "./savings-algorithm.ts";

const testCase = prompt("Nummer der Eingabedatei: ");

const file = await Deno.readTextFile(
	`muellabfuhr/beispiele/muellabfuhr${testCase}.txt`
);

const [_n, m, adjMap] = toAdjacencyMap(file);
const [inverted, edgeWeights, belongingEdges] = invertGraph(adjMap, m);
const routes = savings(inverted, edgeWeights);

console.log(formatOutput(revertWalks(routes, belongingEdges, adjMap)));
