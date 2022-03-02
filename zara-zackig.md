<h1 style="text-align: center;">Bonusaufgabe: Zara Zackigs Zurückkehr</h1>
<p style="text-align: center;">Teilnahme-ID: 00968</p>
<p style="text-align: center;">Bearbeiter: Finn Rudolph</p>
<p style="text-align: center;">02.03.2022</p>

## Problembeschreibung

Zunächst einige wichtige Eigenschaften des $\text{xor}$ Operators. Das exklusive Oder zweier gleicher Zahlen ist immer $0$. weil sich bei diesen Zahlen kein Bit unterscheidet. Auch ist er kommutativ sowie assoziativ, d. h. die Anwendungsreihenfolge auf mehrere Operanden und Anordnung der Operanden sind irrelevant für das Ergebnis. Die Problemstellung verlangt es, aus einer Menge von Karten oder Binärzahlen $S$, $k$ Zahlen zu finden, deren $\text{xor}$ gleich irgendeiner anderen Zahl $\in S$ ist. Mit den oben genannten Eigenschaften kann das Problem umformuliert werden: Finde $k + 1$ Zahlen aus $S$, deren $\text{xor}$ gleich $0$ ist. 

Das Problem ist Variation des Teilsummenproblems, das ein Spezialfall des Rucksackproblems ist. Das Teilsummenproblem verlangt es, von einer Menge an ganzen Zahlen $S$ eine Teilmenge $T$ zu bestimmen, deren Summe gleich einer gegebenen Zahl (hier $0$) ist. In diesem Fall wird statt des $+$ Operators der $\text{xor}$ Operator verwendet. Diese Eigenschaft allein würde das Problem, im Gegensatz zum Teilsummenproblem, in polynomialer Zeit lösbar machen (Jafargholi & Viola, 2018, S. 2). Aber da die Größe von $T$ ebenfalls vorgegeben ist, ist es NP-schwer, kann also nur in exponentieller Zeit optimal gelöst werden.

Formal ausgedrückt, soll eine Menge $T$ bestimmt werden, die folgende Eigenschaften erfüllt. $t_i$ bezeichnet die $i$´te Zahl in $T$.
$$
t_1 \text{ xor } t_2 \text{ xor } \dots \text{ xor } t_{k + 1} = 0 \\
|T| = k + 1 \\
T \subseteq S
$$


## Lösungsidee

## Zeitkomplexität

## Implementierung

## Quellcode

## Literaturverzeichnis

1. Jafargholi, Z. & Viola, E. (2018). _3SUM, 3XOR, Triangles_. https://arxiv.org/pdf/1305.3827.pdf
1. Lewin, M. (2012). _All about XOR_. https://accu.org/journals/overload/20/109/lewin_1915/
2. Sannemo, J. (2018). _Principles of Algorithmic Problem Solving_. KTH Royal Institute of Technology. https://www.csc.kth.se/~jsannemo/slask/main.pdf
3. Wagner, D. (2002). _A Generalized Birthday Problem (Long version)_. University of California at Berkeley. https://people.eecs.berkeley.edu/~daw/papers/genbday.html
