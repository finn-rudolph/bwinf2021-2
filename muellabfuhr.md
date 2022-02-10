<h1 style="text-align: center;">Aufgabe 1: Müllabfuhr</h1>
<p style="text-align: center;">Teilnahme-ID: 00968</p>
<p style="text-align: center;">Bearbeiter: Finn Rudolph</p>
<p style="text-align: center;">30.01.2022</p>

## Problembeschreibung

Der Stadtplan kann als Graph gesehen werden, wobei Kreuzungen Knoten und Straßen Kanten entsprechen. Dieser Graph besitzt folgende Eigenschaften: Seine Kanten sind mit der Länge der zugehörigen Straßen gewichtet, außerdem sind sie ungerichtet. Der Graph kann Zyklen enthalten. Auch erfüllen einige Beispiele das Kriterium für Planarität eines Graphen nicht, das aus dem Eulerschen Polyedersatz hervorgeht:
$$
|E| \leq 3|V| - 6
$$
Z. B. besitzt `muellabfuhr8.txt` $3453$ Kanten, was größer als $3|V| - 6$, wobei $|V| = 1000$. Des weiteren ist der Graph nicht immer metrisch, denn z. B. erfüllen die Kanten zwischen den Knoten $0, 3, 5$ in `muellabfuhr5.txt` die Dreiecksungleichung nicht.

Das Ziel ist es, fünf geschlossene Kantenzüge $Z_1, Z_2, ... Z_ 5$ zu finden. Der Begriff *Kantenzug* wird mehrdeutig verwendet, daher die folgende Definition.

**Definition Kantenzug**: Ein Kantenzug ist eine Folge von Kanten $e_1, e_2, \dots e_n$, wobei $e_i = (a_i, b_i)$ und $b_i = a_{i+1}$. Bei einem geschlossenen Kantenzug gilt $a_1 = b_n$.

Bei jedem der Kantenzüge muss $a_1 = v_0$, der Zentrumsknoten, sein. Gemeinsam müssen alle Kanten des Graphen abgedeckt werden, wobei der längste Zyklus möglichst günstig sein soll:
$$
\text{minimiere} \space \max _{i=1} ^5 \sum _{e \in Z_i} w(e)
$$

$e$ steht für eine Kante, deren Kosten durch die Kostenfunktion $w$ angegeben werden. Die Bedingung gilt, dass jede Kante durchlaufen wird:
$$
\bigcup _{i=1} ^5 Z_i = E
$$

## Literaturverzeichnis

1. Sannemo, J. (2018). _Principles of Algorithmic Problem Solving_. KTH Royal Institute of Technology. https://www.csc.kth.se/~jsannemo/slask/main.pdf
2. Wyss-Gallifent, J. (2021). _Graph Theory_. University of Maryland. https://www.math.umd.edu/~immortal/MATH401/book/ch_graph_theory.pdf
3. Zhang, C. & Wei, F. & Liu, Q. & Gavin Tang, Z. & Li, Z. (2017). _Graph Edge Partitioning via the Neighborhood Heuristic_. Chinesische Universität Hongkong. https://lqhl.me/publication/kdd2017.pdf
4. Yin, H. & Benson, A. & Lescovec, J. & Gleich, D. (2017). _Local Higher-Order Graph Clustering_. Stanford University. https://cs.stanford.edu/people/jure/pubs/mappr-kdd17.pdf
5. Cai, L. (2019). _Everything about spectral graph theory_. University of Cambridge. https://www.cl.cam.ac.uk/~lc647/drafts/Spectral_Graph_Theory.pdf
6. Ye, A. (2020, 16. Juni). _The Jewel of the Matrix: A deep dive into eigenvalues & eigenvectors_. towardsdatascience. https://towardsdatascience.com/the-jewel-of-the-matrix-a-deep-dive-into-eigenvalues-eigenvectors-22f1c8da11fd Aufrufdatum: 22.01.2022
7. Weru, L. (o. D.). _11 Animated Algorithms for the Traveling Salesman Problem_. Stem Lounge. https://stemlounge.com/animated-algorithms-for-the-traveling-salesman-problem/ Aufrufdatum: 23.01.2022
8. Nilsson, C. (o. D.) _Heuristics for the Traveling Salesman Problem_. http://160592857366.free.fr/joe/ebooks/ShareData/Heuristics%20for%20the%20Traveling%20Salesman%20Problem%20By%20Christian%20Nillson.pdf
9. Wilhelm, B. & Ritter, M. (o. D.) _Der Nearest-Insert-Algorithmus für TSP_. Technische Universität München. https://www-m9.ma.tum.de/downloads/felix-klein/19B/nearest-insert.pdf
10. Wikipedia (2022, 26. Januar). _Vehicle Routing Problem_. https://en.wikipedia.org/wiki/Vehicle_routing_problem Aufrufdatum: 25.01.2022
11. Benson, A. & Gleich, D. & Lescovec, J. (2016) _Higher-order organization of complex networks_.  Stanford University. https://cs.stanford.edu/people/jure/pubs/higher-order-science.pdf
12. University of Pennsylvania (2016). _Graph Isomorphism_. https://www2.math.upenn.edu/~mlazar/math170/notes05-2.pdf
13. Moler, C. (2011) _Google Page Rank_. Mathworks. https://www.mathworks.com/content/dam/mathworks/mathworks-dot-com/moler/exm/chapters/pagerank.pdf
14. Berkeley University of California (o. D.). _Savings Algorithm_. University of California, Berkeley. http://courses.ieor.berkeley.edu/ieor151/lecture_notes/ieor151_lec18.pdf
15. Laporte, G. (1991). _The Vehicle Routing Problem: An Overview of exact and approximate Algorithms_. https://staff.fmi.uvt.ro/~daniela.zaharie/ma2017/projects/applications/VehicleRouting/VRP_Laporte_review.pdf
16. Saunders, S. (1999). *A Comparison of Data Structures for Dijkstra's Single Source Shortest Path Algorithm*. University of Canterbury. https://www.cosc.canterbury.ac.nz/research/reports/HonsReps/1999/hons_9907.pdf
17. Mayer, T. (2019). *Automatisierte Auswahl von Algorithmen für das dynamische Fahrzeugwegeplanungsproblem* (Dissertation, Informatik). https://athene-forschung.unibw.de/download/130767/130767.pdf
