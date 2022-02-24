<h1 style="text-align: center;">Aufgabe 1: Müllabfuhr</h1>
<p style="text-align: center;">Teilnahme-ID: 00968</p>
<p style="text-align: center;">Bearbeiter: Finn Rudolph</p>
<p style="text-align: center;">20.02.2022</p>

## Problembeschreibung

Der Stadtplan kann als Graph gesehen werden, wobei Kreuzungen Knoten und Straßen Kanten entsprechen. Der Graph ist ungerichtet und mit den Distanzen zwischen den Kreuzungen gewichtet. Damit ist das Problem ein Kantenroutingproblem, auch Briefträgerproblem oder _Chinese Postman Problem_.

Genauer ist es das Min-Max $k$-Chinese Postman Problem, wie es 1978 von Frederickson, Hecht und Kim gestellt wurde. Das originale Paper ist leider nicht kostenfrei im Internet verfügbar, daher beziehe ich mich auf die Problembeschreibung von Ahr (2004). Das Min-Max $k$-Chinese Postman Problem verlangt es, eine gegebene Anzahl von $k$ Rundtouren $F_1, F_2, \dots, F_k$ durch einen gewichteten Graphen $G = (V, E, w)$ zu finden. Dabei gilt folgende Zielfunktion:

$$
\text{minimiere} \space \max _{i=1} ^k \sum _{e \in (F_i \cap E)} w(e)
$$

Eine Rundtour $F_i$ ist hier als Folge von Knoten und Kanten $v_0, e_1, v_1, ... e_n, v_n$ definiert. $F_i \cap E$ bezeichnet also die Kantenfolge von $F_i$. $w(e)$ sind die Kosten bzw. Länge der Kante $e$.

Folgenden Beschränkungen müssen erfüllt werden:

$$
\bigcup _{i=1} ^k (F_i \cap E) = E \\
$$

$$
F_i(v_0) = F_i(v_n) = s \space \forall F_i
$$

$F_i(v_j)$ bezeichnet hier den $j$´ten Knoten von $F$. $s$ ist der Startknoten oder das Stadtzentrum, oft auch Depot genannt. Die erste Einschränkung stellt sicher, dass alle Kanten des Graphen besucht werden. Die zweite besagt, dass jede Tour am Stadtzentrum beginnt und endet; diese nennt man den _Subtour Elimination Constraint_.

Es ist auch möglich, das Problem mit _Integer Linear Programming_ zu formulieren (Ahr, 2004, S. 125 - 134). Das heißt, man stellt eine lineare Kostenfunktion, Entscheidungsvariablen und meherere lineare Ungleichungen auf, die als Beschränkungen dienen. Hier wären das die Länge der längsten Tour, die Entscheidung, ob man eine Kante in einer bestimmten Tour durchläuft und wann, und Beschränkungen wie beispielsweise der Subtour Elimination Constraint. Diese Art der Problemstellung ist aber nur für exakte Methoden, vor allem _Branch and Cut_, relevant, daher werde ich sie nicht weiter ausführen.

## Lösungsidee

Das Min-Max $k$-CPP ist NP-schwer, daher existieren für exakte Lösungen nur Algorithmen mit exponentieller Laufzeit (Frederickson et al., 1978, zitiert nach Ahr, 2004, S. 32). Da das ist für große Probleminstanzen, wie z. B. `muellabfuhr8.txt` mit 1000 Knoten und 3543 Kanten nicht praktikabel ist, wurden bisher vor allem Heuristiken und Metaheuristiken entwickelt.

Obwohl bessere Metaheuristiken existieren, z. B. der Tabu-Suche Algorithmus von Willemse und Joubert (2012), habe ich mich für den FHK-Algorithmus von Frederickson et al. (1978), ein Approximationsalgorithmus, entschieden. Zum diesem Begriff: Der Unterschied eines Approximationsalgorithmus zu einer Heuristik ist, dass er eine Lösungsqualität innerhalb eines konstanten Faktors der optimalen Lösung garantiert. Grund dafür ist, dass ich selbst zwei Ideen habe, ihn zu verbessern. Auch kann der FHK-Algorithmus zur Erstellung der initialen Lösung für eine Metaheuristik gebraucht werden, das heißt ihn zu verbessern ist durchaus sinnvoll.

### Der FHK-Algorithmus

Das Prinzip des FHK-Algorithmus ist es, eine Rundtour über alle Kanten Graphen in $k$ Pfade zu teilen, und den Anfangs- und Endknoten jedes Pfads mit dem Startknoten zu verbinden (Ahr, 2004, S. 44 - 46). Ein Pfad ist hier eine abwechselnde Abfolge von Knoten und Kanten, die von beidem Dopplungen enthalten kann. Diese Rundtour ist eine Lösung des Briefträgerproblems, oder Chinese Postman Problems, auf dem Graphen. Der Pseudocode des Algorithmus sieht wie folgt aus:

```pseudocode
procedure FHK(Graph G = (V, E, w))

    C = ChinesePostman(G);

    Lₘ = max {w(SP(v₀, a,)) + w(e) + w(SP(a, v₀))}, e = (a, b) ∊ E;

    T = ∅;

    for h ∊ [1, k] ∊ ℕ

        lₕ = (h / k) ⋅ (Lₘ - w(C)) + 0.5 ⋅ Lₘ;

        pₕ = C(v₀);
        while w(C(v₀, pₕ)) < lₕ
            pₕ = C(pₕ + 1);
        end while

        if w(SP(pₕ, v₀) ≤ w(pₕ, C(pₕ + 1)) + w(SP(C(pₕ + 1), v₀)) - 2(lₕ - w(C(v₀, pₕ)))
            pₕ = C(pₕ + 1);
        end if

        T = T ∪ (SP(v₀, pₕ₋₁) + C(pₕ₋₁, pₕ) + SP(v₀, pₕ));

    end for

return T;
```

### Das Chinese Postman Problem / Briefträgerproblem

### Minimale Perfekte Matchings

## Implementierung

## Beispiele

## Literaturverzeichnis

1. Ahr, D. (2004). _Contributions to Multiple Postmen Problems_ (Dissertation, Ruprecht-Karls-Universität Heidelberg). http://archiv.ub.uni-heidelberg.de/volltextserver/4963/1/thesis.pdf
2. Broek, R. (2018). _Lecture Notes on Linear Programming_. Universiteit Utrecht. http://www.cs.uu.nl/docs/vakken/mads/LectureNotesILP.pdf
3. Cook, W. & Rohe, A. (1999). _Computing Minimum Weighted Perfect Matchings_. http://www.math.uwaterloo.ca/~bico/papers/match_ijoc.pdf
4. Edmonds, J. & Johnson, E. (1973). _Matching, Euler Tours and the Chinese Postman_. http://web.eecs.umich.edu/~pettie/matching/Edmonds-Johnson-chinese-postman.pdf
5. Laporte, G. (1991). _The Vehicle Routing Problem: An Overview of exact and approximate Algorithms_. https://staff.fmi.uvt.ro/~daniela.zaharie/ma2017/projects/applications/VehicleRouting/VRP_Laporte_review.pdf
6. Limon, Y. & Azizoglu, M. (2018). _New Heuristics for the balanced k-Chinese Postman Problem_. http://www.inderscience.com/storage/f581191312274106.pdf
7. Liu, S. & Louis, S. & Harris, N. & La, H. (2019). _A Genetic Algorithm for the MinMax k-Chinese Postman Problem with Applications to Bride Inspection_. Missouri University of Science and Technology. https://scholarsmine.mst.edu/cgi/viewcontent.cgi?article=1050&context=inspire-meetings
8. Sannemo, J. (2018). _Principles of Algorithmic Problem Solving_. KTH Royal Institute of Technology. https://www.csc.kth.se/~jsannemo/slask/main.pdf
9. Willemse, E. & Joubert, J. (2012). _Applying min-max k postman problems to the routing of security guards_. https://repository.up.ac.za/bitstream/2263/18380/1/Willemse_Applying%282012%29.pdf

**Testinstanzen:** https://www.uv.es/~belengue/carp/eglese.zip

## Quellcode
