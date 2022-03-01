<h1 style="text-align: center;">Aufgabe 1: Müllabfuhr</h1>
<p style="text-align: center;">Teilnahme-ID: 00968</p>
<p style="text-align: center;">Bearbeiter: Finn Rudolph</p>
<p style="text-align: center;">20.02.2022</p>

## Problembeschreibung

Der Stadtplan kann als Graph gesehen werden, wobei Kreuzungen Knoten und Straßen Kanten entsprechen. Der Graph ist ungerichtet und mit den Distanzen zwischen den Kreuzungen gewichtet. Damit ist das Problem ein Kantenroutingproblem, oder Variation des Briefträgerproblems / _Chinese Postman Problem_. Dieses gehört zu den kombinatorischen Optimierungsproblemen, in denen durch mehrere Entscheidungen eine Kostenfunktion maximiert bzw. minimiert werden soll, während Rahmenbedingungen beachtet werden.

Genauer ist es das Min-Max $k$-Chinese Postman Problem, wie es 1978 von Frederickson, Hecht und Kim gestellt wurde. Das originale Paper ist leider nicht kostenfrei im Internet verfügbar, daher beziehe ich mich auf die Problembeschreibung von Ahr (2004). Das Min-Max $k$-Chinese Postman Problem verlangt es, eine gegebene Anzahl von $k$ Rundtouren $F_1, F_2, \dots, F_k$ durch einen gewichteten Graphen $G = (V, E, w)$ zu finden. Dabei gilt folgendes Ziel:

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

Das Prinzip des FHK-Algorithmus ist es, eine Rundtour durch alle Kanten des Graphen in $k$ Pfade zu teilen, und den Anfangs- und Endknoten jedes Pfads mit dem Startknoten zu verbinden (Ahr, 2004, S. 44 - 46). Ein Pfad ist hier eine abwechselnde Abfolge von Knoten und Kanten, die von beidem Dopplungen enthalten kann. Diese Rundtour $C$ ist eine Lösung des Briefträgerproblems, oder Chinese Postman Problems (CPP) auf dem Graphen. Die Kantenzahl in jedem Pfad ist nicht zwingend gleich lang, sondern ist neben der Länge der Postman-Tour, bezeichnet als $w(C)$, auch vom _Shortest Path Tour Lower Bound_ $L$ (Pseudeocode Z. 3) abhängig. Er gibt die Kosten zum Besuchen der vom Startknoten am weitest entfernten Kante an, daher ist er eine untere Grenze für die optimale Lösung des Min-Max $k$-CPP. Die genaue Festlegung der (vorläufig) maximalen Länge $l_i$ der $i$´ten Tour geschieht in Zeile 7 des Pseudocodes. Der Knoten $p_i$, an dem der $i$´te Pfad endet, ist der letzte Knoten in $C$, mit dem die tatsächliche Distanz $w(C(v_0, p_i))$ noch kleiner als $l_i$ ist. Dieser kann aber auch noch zum nächsten Knoten in $C$ nach $p_i$, bezeichnet als $C(p_i + 1)$ geändert werden. Informell formuliert: Das geschieht, wenn die Distanz von $p_i$ zu $C(p_i + 1)$, und die von $C(p_i + 1)$ zum Startknoten, relativ klein ist und wenn dadurch die eigentlich vorgesehene Länge der Tour $l_i$ nicht stark überschritten wird. Exakt wird das in Z. 13 - 14 des Pseudocodes beschrieben. $r_i$ bezeichnet die übrige Länge der $i$`ten Tour zur vorgesehenen Maximallänge. Die $i$´te Tour wird durch den kürzesten Pfad vom vorherigen Teilungsknoten zum Startknoten $SP(p_{i - 1}, v_0)$ und analog zum aktuellen Teilungsknoten $SP(p_i, v_0)$ geschlossen.

Der Pseudocode des Algorithmus sieht folgendermaßen aus. `←` bedeutet eine Zuweisung, `=` die Gleichheit zweier Variablen.

```pseudocode
procedure FHK(Graph G)
    C ← ChinesePostman(G);
    L ← max { w(SP(v₀, a)) + w(e) + w(SP(b, v₀)) } wobei e = (a, b) ∊ E;
    T ← ∅;

    for i ∊ [1, k]
        lᵢ ← (h / k) ⋅ (L - w(C)) + 0.5 ⋅ L;

        pᵢ ← arg max w(C(v₀, v)) wobei w(C(v₀, v)) ≤ lᵢ;

        while w(C(v₀, pᵢ)) ≤ lᵢ
            pₕ ← C(pᵢ + 1);

        rᵢ ← lᵢ - w(C(v₀, pₕ));
        if w(SP(pᵢ, v₀) > w(pᵢ, C(pᵢ + 1)) + w(SP(C(pᵢ + 1), v₀)) - 2rᵢ
            pᵢ ← C(pᵢ + 1);

        T ← T ∪ (SP(v₀, pᵢ₋₁) + C(pᵢ₋₁, pₕ) + SP(v₀, pᵢ));

    return T;
```

### Das Chinese Postman Problem / Briefträgerproblem

Wie oben beschrieben, ist eine Lösung dieses Problems eine Voraussetzung für den FHK-Algorithmus. Eine optimale Lösung des Briefträgerproblems kann in polynomialer Zeit gefunden werden. Es gehört also, wie für Routingprobleme eher unüblich, der Komplexitätsklasse P an (Edmonds & Johnson, 1973). Ich werde den dort vorgestellten Algorithmus mit einigen Abänderungen verwenden. Vor allem bei dem dafür erforderlichen Algorithmus für minimale perfekte Matchings gab es seit dem große Weiterentwicklungen.

Zuerst werden alle Knoten von ungeradem Grad identifiziert, aus denen ein vollständiger Graph $G_o$ ($o$ für _odd_) erstellt wird, der mit mit den kürzesten Pfaden zwischen den Knoten im Originalgraphen gewichtet ist. Nachdem ein [Minimales Perfektes Matching](#minimale-perfekte-matchings) $M$ in $G_o$ gefunden wurde, wird der Originalgraph mit den Kanten des perfekten Matchings zu einem Multigraphen $G_a$ augmentiert. Darin existiert nun ein Eulerkreis, weil jeder ungerade Knoten durch seinen Matching-Partner zu einem geraden Knoten gemacht wurde. $d(v)$ bezeichnet den Grad eines Knoten.

Das Matching geht immer genau auf, weil ein Graph immer eine gerade Anzahl $b$ an Knoten mit ungeradem Grad hat. Angenommen, ein Graph hat nur einen Knoten, d. h. $b \larr 0 \implies b \equiv 0 \space (\bmod 2)$ Das Hinzufügen eines neuen Knoten verändert $b$ nicht. Das Hinzufügen einer Kante erhöht den Grad von zwei Knoten um $1$. Allgemein formuliert:

$$
b \equiv 0 \space (\bmod 2); \space b \larr b + 2 \implies b \equiv 0 \space (\bmod 2)
$$

Da man beliebig Knoten und Kanten hinzufügen kann, um jeden Graphen zu konstruieren, gilt es für jeden Graphen.

Um einen Eulerkreis zu finden, wird der Algorithmus von Hierholzer verwendet. Edmonds und Johnson (1973) verwenden diesen in zwei abgewandelten Formen, ich werde ihn in seiner ursprünglichen Form verwenden. Der Eulerkreis in dem Multigraphen ist die optimale Lösung des CPPs, wobei parallele Kanten als eine Kante im ursprünglichen Graphen behandelt werden müssen.

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

    Gₐ = (V, Eₐ ← E, w);

    for (a, b) ∊ M
        Eₐ ← Eₐ ∪ { e | e ∊ SP(a, b) };

    return EulerCircuit(Gₐ);
```

Der Algorithmus von Hierholzer konstruiert einen Eulerkreis, indem zunächst ein zufälliger Kreis $K$ in $G_a$ durchlaufen wird. Das geschieht durch Depth-First-Search (DFS), der stoppt, sobald er auf einen Knoten mit Grad $0$ trifft. Weil direkt nach dem Benutzen einer Kante diese aus dem Graphen entfernt wird, muss ein Knoten $v \space | \space d(v) = 0$ notwendigerweise der Anfangsknoten $s$ der Suche sein. Denn nach dem ersten Suchschritt hat in $G_a$ hat jeder Knoten einen geraden Grad, weil beim Durchlaufen eines Knotens immer genau zwei Kanten entfernt werden. Der Knoten, bei dem DFS aktuell steht, hat einen ungeraden Grad, weil die Kante zum Verlassen noch nicht entfernt wurde. Nur bei $s$ sind diese Regeln der Parität umgekehrt, weil dort im ersten Schritt nur eine Kante entfernt wurde. Daher kann nur sein Grad $0$ sein, während DFS bei ihm steht. Danach wird die Suche von einem Knoten $v \in K$ ausgeführt, der noch anliegende Kanten besitzt. Der resultierende Kreis wird in $K$ an der Position von $v$ eingefügt. Dieser Prozess wird solange wiederholt, bis alle Kanten in $K$ enthalten sind.

```pseudocode
procedure EulerCircuit(Graph G)
    K ← DFS(G, v₀);

    while E ≠ ∅
        s ← v | v ∊ K ∧ d(v) ≠ 0;
        T ← DFS(G, s);
        K ← K(v₀, s) + T + K(s, v₀);

    return K;
```

Depth-First-Search, oder Tiefensuche, erkundet einen Graphen, indem rekursiv ein benachbarter Knoten des aktuellen Knoten vor den anderen benachbarten Knoten _vollständig_ erkundet wird. Die Abbruchbedingung ist hier, wenn der aktuelle Knoten Grad $0$ hat, wie oben beschrieben. In diesem Fall wird die Liste aller benutzter Kanten zurückgegeben.

```pseudocode
procedure DepthFirstSearch(Graph G, Node s, Tour T)
    if d(s ≠ 0)
        E ← E \ (s, v | (s, v) ∊ E);
        T ← DepthFirstSearch(G, v, T);

    return T ∪ s;
```

### Minimale Perfekte Matchings

## Implementierung

Ich schreibe das Programm in C++ für den Compiler g++ aus der GNU Compiler Collection. Es kann auf einem x86-64 Linux PC ausgeführt werden. Der Code ist grundsätzlich in Funktionen gegliedert, die aus `main.cpp`, oder untereinander aufgerufen werden. In `main.cpp` geschieht Ein- und Ausgabe, die übrigen Funktionen sind nach Unterprobleme in Module zusammengefasst. Ich schreibe den Code auf Englisch, weil die Schlüsselwörter von C++ ebenfalls englisch sind, damit er einfacher lesbar ist.

### Der FHK-Algorithmus

&rarr; zugehörige Funktion: `vector<vector<int>> fhk(adj_map &graph)`

Meine [Implementierung des FHK-Algorithmus](#der-fhk-algorithmus-2) beginnt mit Aufrufen von Dijkstra's _Single Source Shortest Path_ Algorithmus für jeden Knoten im Graphen, um eine Distanzmatrix `dis` und Vorgängermatrix `pre` für alle kürzesten Pfade zu erstellen (Z. 2 - 7). Ich habe ihn in meiner Lösungsidee nicht erwähnt, weil er ein Standardalgorithmus bei sehr vielen Problemen ist und ich voraussetze, dass er bekannt ist. Ich habe ihn dem _All Pairs Shortest Path_ Algorithmus von Floyd und Warshall vorgezogen, weil die Problemgraphen durchschnittlich sehr dünn sind, d. h. $|E| \ll |V|^2$. Bei solchen Graphen arbeitet Dijkstra's Algorithmus unter Verwendung einer Prioritätsschlange (C++ `priority_queue`) ähnlich schnell bzw. schneller.

Nachdem die Lösung des [Chinese Postman Problems](#der-chinese-postman-algorithmus) und der [Shortest Path Tour Lower Bound](#shortest-path-tour-lower-bound) errechnet wurden (später beschrieben), beginnt die eigentliche Logik des FHK-Algorithmus. `pre_split` speichert den vorherigen Teilungsknoten, `tours` die am Ende zurückgegebenen Rundtouren (Z. 14 - 15). Im Gegensatz zum Pseudocode wird hier ein Pfad / eine Rundtour nur als Knotenfolge definiert. `cost` speichert die Kosten zum Erreichen des vorherigen Teilungsknotens (Z. 16), was für die Bestimmung des nächsten Teilungsknotens relevant ist. Die Bestimmung einer Rundtour geschieht `num_tours - 1`-mal (`num_tours` $=k$ des Pseudocodes). Zunächst wird ihre maximale Länge `max_cost` (Z. 19 - 20) durch die bereits beschriebene Formel errechnet. Indem die Chinese Postman Tour durchlaufen wird, bis `cost > max_cost`, während `cost` ständig mit dem Gewicht der gerade gebrauchten Kante erhöht wird, wird der nächste Teilungsknoten `split` vorläufig festgelegt (Z. 23 - 27). Weil bei Abbruch der `while`-Schleife `split` bereits ein Knoten zu weit gesetzt wurde, implementiere ich das mögliche Verschieben des Teilungsknotens um $1$ etwas anders. Die etwas unpräzise aber intuitive Erklärung dafür war, dass es geschieht, wenn damit die vorgesehene maximale Länge nicht stark überschritten wird. Hier in der Implementierung wird die umgekehrte Bedingung überprüft, und gegebenenfalls der vorherige Knoten als Teilungsknoten gewählt.

Alle Touren, bis auf die letzte, werden auf diese Weise bestimmt, durch [`construct_tour()`]() explizit konstruiert und der `tours`-Liste hinzugefügt. Die letzte Tour besitzt keinen zweiten Teilungsknoten und kann daher sofort festgelegt werden (Z. 45).

#### Shortest Path Tour Lower Bound

&rarr; zugehörige Funktion: `int farthest_edge_cost(adj_map &graph, matrix_2d &dis)`

Ich habe die Funktion aus Platzgründen anders benannt als Ahr (2004, S. 89). Sie iteriert über alle Kanten des Graphen und gibt die größten Kosten zurück, die ein kürzester Pfad zum ersten Knoten der Kante, über die Kante und vom zweiten Knoten zurück zum Startknoten hat.

#### Konstruktion einer Tour

&rarr; zugehörige Funktion: `vector<int> construct_tour(vector<int> &cpp_tour, matrix_2d &pre, int start, int end)`

Diese Funktion dient dazu, die eigentliche Logik zum Verbinden einer Tour zum Startknoten, implementiert in `close_tour()`, für beide Seiten des Pfads anzuwenden. Damit wird vermieden, das zweimal explizit als Code zu schreiben.

&rarr; zugehörige Funktion `void close_tour(vector<int> &tour, matrix_2d &pre, bool append_front)`

Der Parameter `append_front` ist `true`, wenn der Anfangsknoten des Pfads zum Startknoten verbunden werden soll und `false`, wenn das mit dem Endknoten des Pfads geschehen soll. Die Knoten, die auf dem kürzesten Pfad des zu verbindenden Knoten zum Startknoten liegen, sind in der Vorgängermatrix im Vektor bei Index `0` enthalten. `curr`, der aktuelle Knoten auf dem kürzesten Pfad, wird solange mit seinem Vorgänger, der bei `pre[0][curr]` liegt, ersetzt, bis dieser `-1` ist, was bedeutet, dass der Startknoten erreicht wurde (Z. 4 - 8). Dass `-1` bedeutet, dass der Zielknoten erreicht ist, habe ich in Dijkstra's Algorithmus so festgelegt. Alle auf diesem Weg besuchten Knoten werden vorne bzw. hinten an die Tour angehängt. Die Funktion verändert direkt die Tour, die ihr als Referenz mitgegeben wurde.

### Der Chinese Postman Algorithmus

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

**Testinstanzen:** https://www.sintef.no/nearp/

## Quellcode

### Typdefinitionen

```c++
typedef vector<map<int, int>> adj_map;

typedef map<int, map<int, int>> map_2d;

typedef vector<vector<int>> matrix_2d;
```

_Anmerkung:_ In der Dokumentation beziehen sich alle Typen auf das Namespace `std`, wie es auch in den Quellcodedateien (`.cpp`) getan wird. Die Headerdateien (`.hpp`) legen jedoch kein Namespace fest.

_Anmerkung:_ `matrix_2d` wird nur für `vector<vector<int>>` eingesetzt, wenn die Datenstruktur wirklich als Matrix gedacht ist.

### Der FHK-Algorithmus

Die folgenden Funktionen befinden sich in `fhk_algorithm.cpp`.

```c++
vector<vector<int>> fhk(adj_map &graph) {
    matrix_2d dis, pre;
    for (int v = 0; v < graph.size(); v++) {
        auto [distances, predecessors] = dijkstra(graph, v);
        dis.push_back(distances);
        pre.push_back(predecessors);
    }

    auto [cpp_tour, cpp_cost] = postman(graph, dis, pre);

    int lower_bound = farthest_edge_cost(graph, dis);
    int pre_split = 0;
    int cost = 0;
    vector<vector<int>> tours;

    for (int i = 1; i <= num_tours - 1; i++) {
        int max_cost = ((float) i / (float) num_tours) *
            (float) (cpp_cost - lower_bound) + 0.5 * (float) lower_bound;

        int split = pre_split; // index in cpp_tour, not actual vertex
        while (cost <= max_cost) {
            cost += graph[cpp_tour[split]][cpp_tour[split + 1]];
            split += 1;
        }

        int residual = max_cost - cost - graph[cpp_tour[split]][cpp_tour[split + 1]];

        if (
            dis[cpp_tour[split]][0] <=
                graph[cpp_tour[split]][cpp_tour[split + 1]]
                + dis[cpp_tour[split + 1]][0]
                - 2 * residual
        ) {
            split -= 1;
            cost -= graph[cpp_tour[split]][cpp_tour[split + 1]];
        }

        tours.push_back(construct_tour(cpp_tour, pre, pre_split, split));
        pre_split = split;
    }
    tours.push_back(construct_tour(cpp_tour, pre, pre_split, cpp_tour.size() - 1));
    return tours;
}
```

_Anmerkung:_ `num_tours` ist eine globale Konstante mit dem Wert `5`.

```c++
vector<int> construct_tour(vector<int> &cpp_tour, matrix_2d &pre, int start, int end) {
    vector<int> tour(cpp_tour.begin() + start, cpp_tour.begin() + end + 1);
    close_tour(tour, pre, true);
    close_tour(tour, pre, false);

    return tour;
}
```

```c++
void close_tour(vector<int> &tour, matrix_2d &pre, bool append_front) {
    int curr = pre[0][append_front ? *tour.begin() : *(--tour.end())];

    while (curr != -1) {
        if (append_front) tour.insert(tour.begin(), curr);
        else tour.push_back(curr);
        curr = pre[0][curr];
    }
}
```

```c++
int farthest_edge_cost(adj_map &graph, matrix_2d &dis) {
    int farthest = 0;
    for (int a = 0; a < graph.size(); a++) {
        for (const auto &[b, w]: graph[a]) {
            farthest = max(dis[0][a] + w + dis[b][0], farthest);
        }
    }

    return farthest;
}
```

#### Dijkstra's Algorithmus

```c++
pair<vector<int>, vector<int>> dijkstra(adj_map &graph, int start) {
    vector<int> dis(graph.size(), INT_MAX), pre(graph.size(), -1);
    vector<bool> visited(graph.size(), false);

    auto is_closer = [&dis](int a, int b) -> bool {
        return dis[a] > dis[b];
    };

    priority_queue<int, vector<int>, decltype(is_closer)> queue(is_closer);
    queue.push(start);
    dis[start] = 0;

    while (!queue.empty()) {
        int curr = queue.top();
        queue.pop();
        visited[curr] = true;

        for (const auto &[next, w]: graph[curr]) {
            if (!visited[next] && dis[next] > dis[curr] + w) {
                dis[next] = dis[curr] + w;
                pre[next] = curr;
                queue.push(next);
            }
        }
    }

    return { dis, pre };
}
```

### Der Chinese Postman Algorithmus
