<h1 style="text-align: center;">Aufgabe 2: Rechenrätsel</h1>
<p style="text-align: center;">Teilnahme-ID: 00968</p>
<p style="text-align: center;">Bearbeiter: Finn Rudolph</p>
<p style="text-align: center;">30.01.2022</p>

## Problembeschreibung

Im ersten Abschnitt werde ich die Anforderungen an ein generiertes Rechenrätsel halbformal präzisieren. Der zweite Abschnitt stellt ein Konstruktionsverfahren vor, das diese Anforderungen alle gleichzeitig erfüllt.

### Rechenrätsel als formale Sprache

Die Aufgabe ist es, ein Wort der formalen Sprache algebraischer Gleichungen zu erzeugen, wobei Rechenoperatoren durch "$\circ$" ersetzt werden. Das Alphabet $\Sigma$ dieser Sprache ist:
$$
\Sigma = \verb |{"0", "1", "2", "3", "4", "5",| \\ 
\verb |"6", "7", "8", "9", "o", " "}| \\
$$
Die Grammatik, in der erweiterten Backus-Naur-Form notiert, sieht folgendermaßen aus:
$$
\verb+Rechenrätsel = ("0" | N) {" o " ("0" | N) " "} " = " E;+ \\
\verb+N = 1" | "2" | "3" | "4" | "5" +\\ 
\verb+| "6" | "7" | "8" | "9";+\\
\verb+E = N {"0" | N};+
$$
### Anforderungen an ein Rechenrätsel

Um die weiteren Bedingungen für ein gültiges Rechenrätsel aufstellen zu können, ist es hilfreich, die Ziffern und Operatoren zu nummerien. Daher werde ich mich auf die folgende Darstellungsweise beziehen, wobei $z_i \in \N_0 \and z_i \leq 9$, für jedes $1 \leq i \leq n $ und $E \in \N$. $n$ ist die gewünschte Operatorenzahl.
$$
z_1 \space \circ_1 \space z_2 \space \circ_2 \dots \circ_{n} \space z_{n+1} = E
$$
Es muss *genau eine* Möglichkeit geben, jedes $\circ_i$ mit einem Operator $\in \{+,-,*,/\}$ zu ersetzen, sodass eine gültige algebraische Gleichung entsteht.

Sei $E_i$ ein Zwischenergebnis, das durch korrekte Anwendung der ersten $i-1$ Operatoren auf die ersten $i$ Operanden entstanden ist. Wenn der nächste Operator $\circ_i = /$ ist, muss gelten:
$$
E_i \equiv 0 \space (\bmod z_{i+1})
$$

## Lösungsidee

Ich beziehe mich hier auf die Erstellung einer Gleichung mit eingesetzen Operatoren, weil diese danach einfach durch "$\circ$" ersetzt werden können.

### Prinzip des Lösungsverfahrens

Die Grundidee meines Lösungsverfahrens ist es, eine zu Beginn einfache Gleichung schrittweise um Operatoren und Ziffern zu ergänzen. Die Ausgangsgleichung ist $z_1 = z_1$, eine natürliche Zahl $\leq 9$ gleich sich selbst. Dann wird in $n$-mal, wobei $n$ die gewünschte Operatorenzahl ist, ein zufälliger Operator und eine zufällige Ziffer an die linke Seite der Gleichung angehängt. Die rechte Seite wird durch Anwendung des Operators auf das aktuelle Ergebnis und die angefügte Ziffer aktualisiert.

In dieser unkontrollierten Form würde das Verfahren gegen die Anforderungen der Eindeutigkeit, einem Ergebnis $E \in \N$, Punkt vor Strich sowie Zwischenergebnissen $\in \Z$ verstoßen. Ich werde im Folgenden die dafür jeweils nötigen Maßnahmen erklären.

### Gewährleistung der verschiedenen Anforderungen

#### Eindeutigkeit

Ein Term ist genau dann uneindeutig, wenn ein Operator ausgetauscht werden kann, ohne das Ergebnis zu verändern.

##### Uneindeutigkeit durch Symmetrie

// BEWEIS in irgendeiner Form

Uneindeutigkeit ist häufig möglich, wenn Symmetrie bei Ziffern oder Operatoren vorliegt, weil dann der betreffende Term in manchen Fällen umgedreht werden kann, während sein Wert unverändert bleibt. Ein gutes Beispiel dafür findet sich im Aufgabenblatt: $3 \space \circ \space 4 \space \circ \space 3 = 15$.

Symmetrie bei der schrittweisen Konstruktion eines Terms zu vermeiden kann auf ein einfacheres Problem reduziert werden. Denn Symmetrie kann nur entstehen, wenn folgendes zutrifft:
$$
\big ( z_i = z_{i+1} \or z_i = z_{i + 2} \or 
\circ_i = \circ_{i + 1} \or \circ_i = \circ_{i + 2} \big )
\forall \space  1 \leq i \leq n
$$
Das heißt: Wenn an irgendeinem Punkt zwei gleiche Zahlen oder Operatoren direkt aufeinander folgen, oder nur durch eine Zahl oder Operator getrennt sind, ist das der zentrale Baustein eines jeden größeren symmetrischen Terms. Durch das Ausschließen eines solchen zentralen Bausteins wird jede Form von Symmetrie vermieden. Und das ist leicht machbar: Bei der zufälligen Auswahl einer Ziffer und eines Operators werden die letzten zwei gebrauchten nicht in Betracht gezogen.

##### Uneindeutigkeit durch komplementäre Operatoren vor gleichen Termen

##### Spezialfälle für Uneindeutigkeit

Einige Ziffern liefern bei unterschiedlichen Operatoren dennoch das gleiche Ergebnis, z. B. $2 \cdot 2 = 2 + 2$. Beim Auftreten von folgenden Kombinationen generierter Ziffern und Operatoren wird eine neue zufällige Ziffer generiert:

- $0$ mit $+$ oder $-$, weil die Addition mit $0$ das gleiche ergibt wie die Subtraktion mit $0$.
- $1$ mit $*$ oder $/$, weil Multiplikation und Division mit $1$ das gleiche Ergebnis liefert.
- $2$ mit einer vorhergehenden $2$ und $+$ oder $*$, weil $2+2 = 2*2$.

#### Endergebnis $\in \N$

#### Punkt vor Strich

Um die Operatorenrangfolge zu beachten, verwende ich ein selbst entwickeltes Konzept von *Zwischenergebnissen auf jedem Operatorenrang*. Es löst das Problem, dass Ausdrücke von Operatoren zweiten Rangs ($*,/$) nicht zuerst zusammengefasst werden, bevor das Endergebnis aktualisiert wird.

Um das Ergebnis einer Kette von Zahlen, die durch höherrangige Operatoren verknüpft sind, zuerst auswerten zu können, wird ein Teilergebnis nur für diese Kette eingeführt. Diese wird separat aktualisiert, bis die Folge von $*,/$ endet. Dann wird ihr Ergebnis mit vorgehenden $+$ oder $-$ Operator verknüpft.

Es folgt, dass ständig ein Zwischenergebnis $e_{r}$ und der zuletzt vorgekommene Operator $o_{r}$ für jeden Operatorenrang $r$ (in diesem Fall nur zwei) gespeichtert werden muss. Ein Ergebnis niedrigeren Operatorenrangs wird erst aktualisiert, wenn wieder ein Operator seines Rangs auftritt. Das Endergebnis wird durch absteigende Verknüpfung aller Zwischenergebnisse der Operatorenränge erreicht.

Dieses Konzept soll nun an einem Beispiel mit einigen Iterationsschritten verdeutlicht werden, wobei $1$ der Operatorenrang von $+,-$ und $2$ der Operatorenrang von $*,/$ ist.

$$
3 \hspace{70pt} e_1 = \text{undef}; o_1 = \text{undef}; e_2 = 3; o_2 = \text{undef} \\

3 + 9 \hspace{70pt} e_1 = 3; o_1 = +; e_2 = 9; o_2 = \text{undef}; \\

3 + 9 * 4 \hspace{70pt} e_1 = 3; o_1 = +; e_2 = 36; o_2 = *; \\

3 + 9 * 4 / 6 \hspace{70pt} e_1 = 3; o_1 = +; e_2 = 6; o_2 = /;  \\

3 + 9 * 4 / 6 - 1 \hspace{70pt} e_1 = 9; o_1 = -; e_2 = 1; o_2 = \text{undef}; \\

\\
\text{Endergebnis: } e_1 - e_2 = 9 - 1 = 8
$$
#### Zwischenergebnisse $\in \Z$

Nicht-ganzzahlige Zwischenergebnisse können nur bei Division entstehen. Sie entstehen genauer nur dann, wenn beim Konstruktionsschritt $i$ die aktuelle rechte Seite der Gleichung $E_i$ inkongruent zu $0$ ist, modulo der gerade zufällig ausgewählten Ziffer $z_{i+1}$. Diese Bedingung wurde bereits in *[Anforderungen an ein Rechenrätsel](#Anforderungen an ein Rechenrätsel)* beschrieben.

Wenn also $/$ als zufälliger Operator ausgewählt wurde, wird der Rest der Division von $E_i$ und $z_{i+1}$ überprüft und gegebenenfalls eine neue zufällige Ziffer gewählt.

## Literaturverzeichnis

- Sannemo, J. (2018). _Principles of Algorithmic Problem Solving_. KTH Royal Institute of Technology. https://www.csc.kth.se/~jsannemo/slask/main.pdf Aufrufdatum: 23.12.2021