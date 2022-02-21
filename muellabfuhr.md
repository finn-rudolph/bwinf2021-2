<h1 style="text-align: center;">Aufgabe 1: Müllabfuhr</h1>
<p style="text-align: center;">Teilnahme-ID: 00968</p>
<p style="text-align: center;">Bearbeiter: Finn Rudolph</p>
<p style="text-align: center;">20.02.2022</p>

## Problembeschreibung

Der Stadtplan kann als Graph gesehen werden, wobei Kreuzungen Knoten und Straßen Kanten entsprechen. Der Graph ist ungerichtet und mit den Distanzen zwischen den Kreuzungen gewichtet. Andere Einschränkungen, wie Planarität gibt es nicht, weil z. B. `muellabfuhr8.txt` mit $|E| = 3453$ und $|V| = 1000$ das Kriterium $|E| > 3|V| - 6$ verletzt, das aus dem eulerschen Polyedersatz hervorgeht. Auch sind nicht alle gegebenen Beispiele metrisch, denn z. B. erfüllen die Gewichte zwischen den Knoten $0, 3, 5$ in `muellabfuhr5.txt` die Dreiecksungleichung nicht. Der Graph ist folglich sehr verschieden zu einem realen Straßennetz.

Das vorliegende Problem ist ein Kantenroutingproblem, genauer das Min-Max $k$-Chinese Postman Problem, wie es 1978 von Frederickson, Hecht und Kim gestellt wurde. Die originale Beschreibung ist leider nicht kostenfrei im Internet verfügbar, daher beziehe ich mich auf die von Ahr (2004). Das Min-Max $k$-Chinese Postman Problem verlangt es, eine gegebene Anzahl von $k$ Rundtouren $F_1, F_2, ... F_k$ durch einen gewichteten Graphen $G = (V, E, w)$ zu finden. Dabei gilt folgende Zielfunktion:

$$
\text{minimiere} \space \max _{i=1} ^k \sum _{e \in (F_i \cap E)} w(e)
$$

Eine Rundtour $F_i$ ist hier als Folge von Knoten und Kanten $v_0, e_1, v_1, ... e_n, v_n$ definiert. $F_i \cap E$ bezeichnet also die Kantenmenge von $F_i$. $w(e)$ sind die Kosten bzw. Länge der Kante $e$.

Folgenden Beschränkungen müssen erfüllt werden:

$$
\bigcup _{i=1} ^k (F_i \cap E) = E \\
$$

$$
v_0 = v_k = s \space \forall F_i
$$

$s$ ist der Startknoten oder das Stadtzentrum, oft auch Depot genannt.

## Lösungsidee

Das Min-Max $k$-CPP ist NP-schwer, daher existiert für eine exakte Lösung nur ein Algorithmus mit exponentieller Laufzeit (Frederickson et al, 1978, zitiert nach Ahr, 2004, S. 32). Da das ist für große Probleminstanzen, wie z. B. `muellabfuhr8.txt` mit 1000 Knoten und 3543 Kanten nicht praktikabel ist, sind Heuristiken oder Metaheuristiken zur Lösung geeignet. In einem Vergleich der wenigen existierenden Algorithmen für das Min-Max $k$-CPP von Ahr (2004) schnitt der Approximationsalgorithmus von Frederickson, Hecht und Kim sehr gut ab. Zum Begriff Approximationsalgorithmus: Der Unterschied eines Approximationsalgorithmus zu einer Heuristik ist, dass er eine Lösungsqualität innerhalb eines konstanten Faktors der optimalen Lösung garantiert.

Obwohl bessere Heuristiken, unter Einsatz von mehreren nachträglichen Verbesserungsalgorithmen, als der FHK-Algorithmus existieren (Ahr, 2004, S. 46), habe ich mich für eine Implementierung von diesem entschieden. Denn ohne Verbesserungsverfahren war der FHK-Algorithmus in 81% aller Testinstanzen überlegen, erst durch die zusätzliche Anwendung der Metaheuristik Tabu-Suche (S. 63 - 67) konnte er von den anderen vorgestellten Algorithmen _Augment-Merge_ (S. 46 - 47) und _Cluster_ (S. 47 - 51) übertroffen werden. Auch habe ich selbst eine Idee, um seine Laufzeit zu verbessern.

### Der FHK-Algorithmus

### Das Chinese Postman Problem / Briefträgerproblem

### Minimale Perfekte Matchings

## Implementierung

## Beispiele

## Literaturverzeichnis

1. Ahr, D. (2004). _Contributions to Multiple Postmen Problems_ (Dissertation, Ruprecht-Karls-Universität Heidelberg). http://archiv.ub.uni-heidelberg.de/volltextserver/4963/1/thesis.pdf
2. Cook, W. & Rohe, A. (1999). _Computing Minimum Weighted Perfect Matchings_. http://www.math.uwaterloo.ca/~bico/papers/match_ijoc.pdf
3. Edmonds, J. & Johnson, E. (1973). _Matching, Euler Tours and the Chinese Postman_. http://web.eecs.umich.edu/~pettie/matching/Edmonds-Johnson-chinese-postman.pdf
4. Laporte, G. (1991). _The Vehicle Routing Problem: An Overview of exact and approximate Algorithms_. https://staff.fmi.uvt.ro/~daniela.zaharie/ma2017/projects/applications/VehicleRouting/VRP_Laporte_review.pdf
5. Sannemo, J. (2018). _Principles of Algorithmic Problem Solving_. KTH Royal Institute of Technology. https://www.csc.kth.se/~jsannemo/slask/main.pdf

## Quellcode
