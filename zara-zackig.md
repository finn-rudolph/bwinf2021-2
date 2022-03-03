<h1 style="text-align: center;">Bonusaufgabe: Zara Zackigs Zurückkehr</h1>
<p style="text-align: center;">Teilnahme-ID: 00968</p>
<p style="text-align: center;">Bearbeiter: Finn Rudolph</p>
<p style="text-align: center;">02.03.2022</p>

## Problembeschreibung

Zunächst einige wichtige Eigenschaften des $\text{xor}$ Operators. Das exklusive Oder zweier gleicher Zahlen ist immer 0, weil sich bei diesen Zahlen kein Bit unterscheidet. Auch ist $\text{xor}$ kommutativ sowie assoziativ, d. h. die Anwendungsreihenfolge auf mehrere Operanden und Anordnung der Operanden sind irrelevant für das Ergebnis. Die Aufgabenstellung verlangt es, aus einer Menge $S$ von Karten oder Binärzahlen, $k$ Zahlen zu finden, deren $\text{xor}$ gleich irgendeiner anderen Zahl $\in S$ ist. Mit den oben genannten Eigenschaften kann das Problem umformuliert werden: Finde $k + 1$ Zahlen aus $S$, deren $\text{xor}$ gleich $0$ ist. Für weitere Beschreibungen werde ich $k$ für die Anzahl an Zahlen, der $\text{xor}$ gleich 0 sein soll verwenden, und nicht $k + 1$, weil das der Standard in allen Quellen ist.

Das Problem ist Variation des Teilsummenproblems, das ein Spezialfall des Rucksackproblems ist. Das Teilsummenproblem verlangt es, von einer Menge an ganzen Zahlen $S$ eine Teilmenge $T$ zu bestimmen, deren Summe gleich 0 ist. In diesem Fall wird statt des $+$ Operators der $\text{xor}$ Operator verwendet. Diese Eigenschaft allein würde das Problem, im Gegensatz zum Teilsummenproblem, in polynomialer Zeit lösbar machen (Jafargholi & Viola, 2018, S. 2). Aber da die Größe von $T$ ebenfalls vorgegeben ist, ist es NP-schwer, kann also nur in exponentieller Zeit optimal gelöst werden.

Formal ausgedrückt, soll eine Menge $T$ bestimmt werden, die folgende Eigenschaften erfüllt. $t_i$ bezeichnet die $i$´te Zahl in $T$.

$$
t_1 \text{ xor } t_2 \text{ xor } \dots \text{ xor } t_k = 0 \\
|T| = k \\
T \subseteq S
$$

## Lösungsidee

Im Gegensatz zum Müllabfuhr-Problem ist eine Heuristik hier unangebracht, denn fast richtige Schlüsselkarten helfen Zara nicht weiter. Das Ziel ist es also, die exponentielle Laufzeit, die ein optimaler Algorithmus haben wird, mit einigen Tricks im Rahmen zu halten.

### Das 3-XOR Problem

Für den Fall $k = 3$ (3-XOR Problem) existiert bereits ein einfacher Algorithmus mit quadratischer Laufzeit (Bouillaguet & Delaplace, 2021, S. 5). Mit einem naiven Ausprobieren aller Kombinationen würde er $O(n^3)$ benötigen, da man $\binom{n}{3} = \frac 16 n^3 - \frac 12 n^2 + \frac 13 n$ Möglichkeiten hat, die Zahlen zu kombinieren. $n = |S|$, wie in der Aufgabenstellung. Durch Speichern aller Zahlen $\in S$ in einer Hashmap, um nicht für jedes $\text{xor}$-verknüpfte Paar von Zahlen die ganze Liste durchgehen zu müssen, kann der Grad des Polynoms um $1$ reduziert werden.

_Anmerkung:_ Der Algorithmus für das 3-XOR Problem läuft in polynomialer Zeit, weil das Problem für variable $k$ eine Zeitkomplexität mit $k$ im Exponenten hat.

### Verallgemeinerung des 3-XOR Problems

Ich möchte diese Idee für größere $k$ generalisieren. Um das Problem für $k = 4$ zu lösen, wird die Hashmap $H$ um eine Dimension vergrößert:

$$
H = \{s_1 \text{ xor } s_2 \space
\forall \space (s_1, s_2 \in S \space | \space s_1 \neq s_2)
$$

$H$ enthält also alle möglichen $\text{xor}$-Verknüpfungen von zwei ungleichen Zahlen $\in S$. Damit ist das Problem für $k = 4$ ebenfalls in $O(n^2)$ lösbar, weil die Erstellung von $H$ sowie das Überprüfen der Existenz jedes $\text{xor}$-verknüpften Paares in $H$ in $O(n^2)$ ausgeführt werden kann. Diese Strategie, einen Teil, meist die Hälfte, aller möglichen Lösungen im Voraus zu berechnen, heißt _Meet in the Middle_ (Sannemo, 2018, S. 138). Warum gerade die Hälfte sinnvoll ist, erkläre ich später.

Sei $d$ die Dimension von $H$, das heißt $H$ hat $n^d$ Einträge, die durch eine Verallgemeinerung obiger Formel erzeugt werden. In dem gerade beschriebenen Fall war $d=2$.

$$
H = \{s_1 \text{ xor } s_2 \text{ xor } \dots \text{ xor } s_d \space
\forall \space (s_i \in S \space | \space
s_i \neq s_j \space \forall \space i < j \leq d)
$$

Für größere $k$ muss beachtet werden, dass der Speicherbedarf sowie die Zeit zur Erstellung von $H$ mit $O(n^d)$ zunimmt, weshlb es nicht immer sinnvoll ist $d = k - 2$ zu wählen. Man stößt hier auf ein _Space-Time-Tradeoff_, das durch ein gut ausgewähltes $d$ optimiert werden kann.

Betrachten wir zunächst nur die Zeitkomplexität. Wenn $d \neq k - 2$, kann das spätere Durchsuchen der Hashmap auch nicht mehr in $O(n^2)$ geschehen, weil nicht alle Paare, sondern alle Kombinationen von $k - d$ Zahlen überprüft werden müssen. Da es davon $\binom {n}{k-d}$ gibt, ist die Zeitkomplexität des Durchsuchens $O(n^{k - d})$. Die gesamte Zeitkomplexität ist also $O(n^d + n^{k-d})$. Daran ist ersichtlich, dass $d = \lfloor \frac k2 \rfloor$ die sinnvollste Wahl ist, denn für die asymptotische Zeitkomplexität ist allein der Summand mit dem größten Exponenten entscheidend, der so minimiert wird. Bei ungeradem $k$ ist abrunden sinnvoller als aufrunden, weil der Speicherbedarf von $H$ exponentiell mit $d$ steigt.

Nun zur Speicherkomplexität. Sie ist wesentlich limiterender, was ich am Beispiel `stapel2.txt` verdeutlichen möchte. Mit der oben genannten Einschätzung der Speicherkomplexität $O(n^d)$ müssten $111^5 \approx 16,9 \cdot 10^9$ 128-Bit Zahlen gespeichert werden, was ungefähr 270 Gigabyte Arbeitsspeicher erfordern würde. So viel steht keinem üblichen Computer zur Verfügung, daher muss $d$ entsprechend klein gehalten werden.

_Anmerkung:_ Bei den bisherigen Einschätzungen der Zeit- und Platzkomplexität habe ich lineare Faktoren außer Acht gelassen, die sich bei der Implementierung zeigen werden.

### Divide and Conquer

Um den Arbeitsspeicherbedarf zu reduzieren kann sich die Eigenschaft des $\text{xor}$ Operators zunutze gemacht werden, dass sein Ergebnis bei einem Bit unabhängig von den anderen Bits ist. Das heißt, eine 128-Bit Zahl kann in 16 8-Bit Zahlen geteilt werden, bei denen jeweils alle Kombinationen von $k$ Zahlen gefunden werden, deren $\text{xor}$ gleich 0 ist. Dann ist die Schnittmenge der Lösungsmengen der Teilprobleme die Lösungsmenge des gesamten Problems. Wenn $d$ aufgrund mangelnden Arbeitsspeichers kleiner als $\lfloor \frac k2 \rfloor$ gewählt werden müsste, kann es mit diesem Trick möglicherweise doch um 1 erhöht werden. Denn der Speicherbedarf wird um den Faktor $\frac m8$ verringert wird, wobei $m$ die Anzahl an Bits der Zahlen ist. Eine kleinere Teilung als in 8-Bit Zahlen ist  nicht möglich bzw. sinnvoll, denn 8 Bits oder 1 Byte sind die kleinste Speichereinheit eines Computers, d. h. kleinere Einheiten sind nicht direkt adressierbar. Außerdem nimmt die Anzahl an Lösungen bei kleineren Zahlen der Erwartung nach stark zu, was wiederum Speicherplatz benötigt.

## Implementierung

## Zeitkomplexität

## Quellcode

## Literaturverzeichnis

1. Bouillaguet, C. & Delaplace, C. (2021). _Faster Algorithms for the Sparse Random 3XOR Problem_. https://hal.archives-ouvertes.fr/hal-02306917v1/document
1. Jafargholi, Z. & Viola, E. (2018). _3SUM, 3XOR, Triangles_. https://arxiv.org/pdf/1305.3827.pdf
1. Lewin, M. (2012). _All about XOR_. https://accu.org/journals/overload/20/109/lewin_1915/
1. Sannemo, J. (2018). _Principles of Algorithmic Problem Solving_. KTH Royal Institute of Technology. https://www.csc.kth.se/~jsannemo/slask/main.pdf
1. Wagner, D. (2002). _A Generalized Birthday Problem (Long version)_. University of California at Berkeley. https://people.eecs.berkeley.edu/~daw/papers/genbday.html
