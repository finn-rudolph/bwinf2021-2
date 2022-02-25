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

Es ist auch möglich, das Problem mit Integer Linear Programming zu formulieren (Ahr, 2004, S. 125 - 134). Das heißt, man stellt eine lineare Kostenfunktion, Entscheidungsvariablen und meherere lineare Ungleichungen auf, die Beschränkungen formulieren. Bei diesem Problem wäre die Kostenfunktion die Länge der längsten Tour und die Entscheidungsvaribalen, ob man eine Kante in einer bestimmten Tour durchläuft und an welcher Position. Ein Beschränkung wäre der Subtour Elimination Constraint. Diese Art der Problemstellung ist aber nur für exakte Methoden, vor allem Branch and Cut, relevant, daher werde ich sie nicht weiter ausführen.

_Anmerkung:_ Der Weg, bis ich das Min-Max $k$-CPP gefunden hatte, war keineswegs linear. Angefangen bei Cluster Algorithmen und spektraler Graphentheorie, über das Traveling Salesman Problem und Vehicle Routing Problem, dann Google's PageRank Algorithmus bin ich erst nach vielen Wochen Recherche erstmals auf das Chinese Postman Problem gestoßen.

## Lösungsidee

Das Min-Max $k$-CPP ist NP-schwer, daher existieren für exakte Lösungen nur Algorithmen mit exponentieller Laufzeit (Frederickson et al., 1978, zitiert nach Ahr, 2004, S. 32). Da das ist für große Probleminstanzen, wie z. B. `muellabfuhr8.txt` mit 1000 Knoten und 3543 Kanten nicht praktikabel ist, wurden bisher vor allem Heuristiken und Metaheuristiken entwickelt.

Obwohl bessere Metaheuristiken existieren, z. B. der Tabu-Suche Algorithmus von Willemse und Joubert (2012), habe ich mich für den FHK-Algorithmus von Frederickson et al. (1978), ein Approximationsalgorithmus, entschieden. Zum diesem Begriff: Der Unterschied eines Approximationsalgorithmus zu einer Heuristik ist, dass er eine Lösungsqualität innerhalb eines konstanten Faktors der optimalen Lösung garantiert. Grund dafür ist, dass ich selbst zwei Ideen habe, ihn zu verbessern. Auch kann der FHK-Algorithmus zur Erstellung der initialen Lösung für eine Metaheuristik gebraucht werden, das heißt ihn zu verbessern ist durchaus sinnvoll.

### Der FHK-Algorithmus

Das Prinzip des FHK-Algorithmus ist es, eine Rundtour über alle Kanten Graphen in $k$ Pfade zu teilen, und den Anfangs- und Endknoten jedes Pfads mit dem Startknoten zu verbinden (Ahr, 2004, S. 44 - 46). Ein Pfad ist hier eine abwechselnde Abfolge von Knoten und Kanten, die von beidem Dopplungen enthalten kann. Diese Rundtour ist eine Lösung $C$ des Briefträgerproblems, oder Chinese Postman Problems auf dem Graphen. Die Kantenzahl in jedem Pfad ist nicht zwingend gleich lang, sondern ist neben der Länge der Postman-Tour auch vom _Shortest Path Tour Lower Bound_ $L$ abhängig. Weil er die Kosten zum Besuchen der vom Startknoten am weitest entfernten Kante angibt, ist er eine untere Grenze für die optimale Lösung des Min-Max $k$-CPP. Die maximale Distanz des $h$´ten Teilungsknoten von $v_0$ über $C$ wird durch $l_h$ angegeben. Der Teilungsknoten ist der letzte Knoten, mit dem die tatsächliche

Distanz $w(C(v_0, p_h))$ noch kleiner als $l_h$ ist. Dieser kann aber auch noch zum nächsten Knoten in $C$ nach $p_h$, bezeichnet als $C(p_h + 1)$ geändert werden. Informell formuliert: Das geschieht, wenn die Distanz von $p_h$ zu $C(p_h + 1)$ relativ klein ist und wenn dadurch die eigentlich vorgesehene Länge der Tour $l_h$ nicht stark überschritten wird. Exakt wird das in Z. 13 - 14 des Pseudocodes beschrieben. Die $h$´te Tour wird durch den kürzesten Pfad vom vorherigen Teilungsknoten $SP(p_{h-1}, v_0)$ und aktuellen Teilungsknoten $SP(p_h, v_0)$ zum Startknoten geschlossen.

Der Pseudocode des Algorithmus sieht folgendermaßen aus. `←` beduetet eine Zuweisung, `=` die Gleichheit zweier Variablen.

```pseudocode
procedure FHK(Graph G)
    C ← ChinesePostman(G);
    L ← max { w(SP(v₀, a)) + w(e) + w(SP(b, v₀)) }, e = (a, b) ∊ E;
    T ← ∅;

    for h ∊ [1, k]
        lₕ ← (h / k) ⋅ (L - w(C)) + 0.5 ⋅ L;

        pₕ ← C(v₀);
        while w(C(v₀, pₕ)) ≤ lₕ
            pₕ ← C(pₕ + 1);

        rₕ ← lₕ - w(C(v₀, pₕ));
        if w(SP(pₕ, v₀) > w(pₕ, C(pₕ + 1)) + w(SP(C(pₕ + 1), v₀)) - 2rₕ
            pₕ ← C(pₕ + 1);

        T ← T ∪ (SP(v₀, pₕ₋₁) + C(pₕ₋₁, pₕ) + SP(v₀, pₕ));

    return T;
```

### Das Chinese Postman Problem / Briefträgerproblem

Eine optimale Lösung des Briefträgerproblems kann in polynomialer Zeit gefunden werden, es gehört also der Komplexitätsklasse P an (Edmonds & Johnson, 1973). Zuerst werden alle Knoten von ungeradem Grad identifiziert, aus denen ein vollständiger Graph $G_o$ ($o$ für _odd_) erstellt wird, der mit mit den kürzesten Pfaden zwischen den Knoten im Originalgraphen gewichtet ist. Nachdem ein [Minimales Perfektes Matching](#minimale-perfekte-matchings) $M$ für diesen gefunden wurde, wird der Originalgraph mit den Kanten des perfekten Matchings zu einem Multigraphen augmentiert. Darin existiert nun ein Eulerkreis, weil jeder ungerade Knoten durch seinen Matching-Partner zu einem geraden Knoten gemacht wurde. $d(v)$ bezeichnet den Grad eines Knoten.

Das Matching geht immer genau auf, weil ein Graph immer eine gerade Anzahl an Knoten mit ungeradem Grad hat, was einfach zu sehen ist: Angenommen, ein Graph hat nur einen Knoten, d. h. $0$ ungerade Knoten, also eine gerade Anzahl. Das Hinzufügen eines neuen Knoten verändert diese Zahl nicht, weil der neue isolierte Knoten Grad $0$ hat. Das Hinzufügen einer Kante erhöht den Grad von zwei Knoten um eins, verändert also nichts an der Parität der Zahl ungerader Knoten. Das kann man beliebig fortführen, um jeden Graphen zu konstruieren.

Um einen Eulerkreis zu finden, wird der Algorithmus von Hierholzer verwendet. Edmonds und Johnson (1973) verwenden diesen in zwei abgewandelten Formen. Der Eulerkreis ist die optimale Lösung des CPPs, wobei parallele Kanten als eine Kante im ursprünglichen Graphen behandelt werden müssen.

```pseudocode
procedure ChinesePostman(Graph G)
    Gₒ = (Vₒ ← ∅, Eₒ ← ∅, wₒ ← ∅);

    for v ∊ V
        if d(v) ≡ 1 (mod 2)
            Vₒ ← Vₒ ∪ v;

    for a ∊ Vₒ
        for b ∊ Vₒ
            Eₒ ← Eₒ ∪ (a, b);
            wₒ(a, b) ← w(SP(a, b));

    M ← PerfectMatching(Gₒ);

    for (a, b) ∊ M
        E ← E ∪ { e | e ∊ SP(a, b) };

    return EulerTour(G);
```

Der Algorithmus von Hierholzer konstruiert einen Eulerkreis, indem zunächst zufällig ein Kreis $K$ durch den Graphen ausgewählt wird. Das geschieht durch Depth-First-Search, der stoppt, sobald er auf einen Knoten mit Grad $0$ trifft. Direkt nach dem Benutzen einer Kante wird diese aus dem Graphen entfernt. Daher muss ein Knoten $v \space | \space d(v) = 0$ notwendigerweise der Anfangsknoten der Suche sein. Danach wird die Suche von einem Knoten $v \in K$ ausgeführt, der noch anliegende Kanten besitzt. Der resultierende Kreis wird in $K$ an der Position von $v$ eingefügt. Dieser Prozess wird solange wiederholt, bis alle Kanten in $K$ enthalten sind.

```pseudocode
procedure EulerTour(Graph G)
    K ← DFS(G, v₀);

    while E ≠ ∅
        s | s ∊ K ∧ d(w) ≠ 0;
        T ← DFS(G, s);
        K ← K(v₀, s) + T + K(s, v₀);

    return K;
```

Depth-First-Search oder Tiefensuche erkundet einen Graphen, indem rekursiv ein benachbarter Knoten des aktuellen Knoten vor den anderen benachbarten Knoten _vollständig_ erkundet wird. In diesem Fall wird eine Liste benutzter Kanten zurückgegeben.

```pseudocode
procedure DepthFirstSearch(Graph G, Node s, Tour T)
    if d(s ≠ 0)
        E ← E \ (s, v | (s, v) ∊ E);
        T ← DepthFirstSearch(G, v, T);

    return T ∪ s;
```

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
