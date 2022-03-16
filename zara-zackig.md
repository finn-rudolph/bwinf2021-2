<h1 style="text-align: center;">Bonusaufgabe: Zara Zackigs Zurückkehr</h1>
<p style="text-align: center;">Teilnahme-ID: 00968</p>
<p style="text-align: center;">Bearbeiter: Finn Rudolph</p>
<p style="text-align: center;">02.03.2022</p>

## Problembeschreibung

Zunächst einige wichtige Eigenschaften des $\text{xor}$ Operators. Das exklusive Oder zweier gleicher Zahlen ist immer 0, weil sich bei diesen Zahlen kein Bit unterscheidet. Auch ist $\text{xor}$ kommutativ sowie assoziativ, d. h. die Anwendungsreihenfolge auf mehrere Operanden und Anordnung der Operanden sind irrelevant für das Ergebnis (Lewin, 2012). Die Aufgabenstellung verlangt es, aus einer Menge $S$ von Karten oder Binärzahlen, $k$ verschiedene Zahlen zu finden, deren $\text{xor}$ gleich irgendeiner anderen Zahl $\in S$ ist. Mit den oben genannten Eigenschaften kann das Problem umformuliert werden: Finde $k + 1$ Zahlen aus $S$, deren $\text{xor}$ gleich $0$ ist. Von hier an werde ich $k$ für die Anzahl an Zahlen, deren $\text{xor}$ gleich 0 sein soll verwenden, und nicht $k + 1$, weil das der Standard in allen Quellen ist.

Das Problem ist Variation des Teilsummenproblems, das ein Spezialfall des Rucksackproblems ist. Das Teilsummenproblem verlangt es, von einer Menge an ganzen Zahlen $S$ eine Teilmenge $T$ zu bestimmen, deren Summe gleich 0 ist. In diesem Fall wird statt des $+$ Operators der $\text{xor}$ Operator verwendet. Diese Eigenschaft allein würde das Problem, im Gegensatz zum Teilsummenproblem, in polynomialer Zeit lösbar machen (Jafargholi & Viola, 2018, S. 2). Aber da die Größe von $T$ ebenfalls vorgegeben ist, ist es NP-schwer, kann also nur in exponentieller Zeit optimal gelöst werden.

Formal ausgedrückt, soll eine Menge $T$ bestimmt werden, die folgende Eigenschaften erfüllt. $t_i$ bezeichnet die $i$´te Zahl in $T$.

$$
t_1 \text{ xor } t_2 \text{ xor } \dots \text{ xor } t_k = 0 \\
|T| = k \\
T \subseteq S \\
t_i \neq t_j \space \forall \space 1 \leq i < j \leq k
$$

## Lösungsidee

### Teilaufgabe a)

Im Gegensatz zum Müllabfuhr-Problem ist eine Heuristik hier unangebracht, denn fast richtige Schlüsselkarten helfen Zara nicht weiter. Das Ziel ist es also, die exponentielle Laufzeit, die ein optimaler Algorithmus haben wird, mit einigen Tricks im Rahmen zu halten. Dafür verwende ich den Brute-Force Ansatz _Meet in the Middle_ (Sannemo, 2018, S. 138). Das bedeutet, einen Teil, meist die Hälfte, aller möglichen Lösungen im Voraus zu berechnen.

#### Das 3-XOR Problem

Für den Fall $k = 3$ (3-XOR Problem) existiert bereits ein einfacher Algorithmus mit quadratischer Laufzeit (Bouillaguet & Delaplace, 2021, S. 5). Mit einem naiven Ausprobieren aller Kombinationen würde er $O(n^3)$ benötigen, da man $\binom{n}{3} = \frac 16 n^3 - \frac 12 n^2 + \frac 13 n$ Möglichkeiten hat, die Zahlen zu kombinieren. $n = |S|$, wie in der Aufgabenstellung. Durch Speichern aller Zahlen $\in S$ in einer Hashmap, um nicht für jedes $\text{xor}$-verknüpfte Paar von Zahlen die ganze Liste durchgehen zu müssen, kann der Grad des Polynoms um $1$ reduziert werden. Es wird für jede $\text{xor}$-Verknüpfung aus zwei verschiedenen Zahlen geprüft, ob diese in der Hashmap existiert, denn das $\text{xor}$ von zwei gleichen Zahlen ist $0$. Natürlich ist eine Lösung nur gültig, wenn der gefundene Eintrag in der Hashmap nicht zu einer der zwei Zahlen gehört.

Das hier vorliegende Problem kann also, analog zum 3-XOR Problem, als $k$-XOR Problem bezeichnet werden. Der Begriff existiert allerdings bereits und wird für ein ähnliches Problem verwendet, nämlich aus $k$ Listen je ein Element zu wählen, sodass das $\text{xor}$ all dieser Elemente 0 ist. Für dieses Problem existiert ein Algorithmus mit subexponentieller Laufzeit (Wagner, 2002), der allerdings eine bestimmte Größe der Listen voraussetzt, weswegen eine Übertragung auf das hier vorliegende Problem nicht sinnvoll ist.

_Anmerkung:_ Der Algorithmus für das 3-XOR Problem läuft in polynomialer Zeit, weil das Problem für variable $k$ eine Zeitkomplexität mit $k$ im Exponenten hat.

#### Verallgemeinerung des 3-XOR Problems

Ich möchte diese Idee des Vorberechnens für größere $k$ generalisieren. Allerdings verwende ich wegen des großen Speicherbedarfs keine Hashmap, sondern eine sortierte Liste, in der ein bestimmtes Element mithilfe von Binärsuche in $O(\log_2n)$ gefunden werden kann. Obwohl das zunächst langsamer ist als $O(1)$ bei einer Hashmap, lohnt es sich insgesamt für den Zeitaufwand, da der Speicherplatz für die Zeitkomplexität limitierend ist, wie ich später erklären werde.

Um das Problem beispielsweise für $k = 4$ zu lösen, wird eine Liste $L$ mit allen $\text{xor}$-Verknüpfungen von zwei ungleichen Zahlen $\in S$ gefüllt:

$$
L = \{s_1 \text{ xor } s_2 \space
\forall \space (s_1, s_2 \in S \space | \space s_1 \neq s_2)
$$

Damit ist das Problem für $k = 4$ in $O(n^2 \log_2 n)$ lösbar, weil die Erstellung von $L$ in $O(n^2)$, und das Überprüfen der Existenz jedes $\text{xor}$-verknüpften Paares in $L$ in $O(n^2 )$ ausgeführt werden kann.

Für allgemeine $k$: Sei $d$ die Anzahl an Zahlen, die für einen Eintrag in $L$ mit $\text{xor}$ verknüpft werden (im obigen Fall $d = 2$). Das heißt $L$ hat $\binom nd$ Einträge und benötigt $O(n^d)$ Zeit zur Erstellung sowie Speicherplatz. Um die Karten im Auge zu behalten, die für einen vorberechneten $\text{xor}$-Wert benutzt wurden, wird eine zweite Liste $Q$ angelegt, in der jeweils die Indizes in $S$ der verwendeten Karten gespeichert werden. $L$ und $Q$ können durch folgende Rekursion erzeugt werden. $\larr$ bedeutet die Zuweisung einer Variable.

$$
\text{Vorberechnen}(a, x, b) = \begin{cases}
L \larr L \cup x; \space Q \larr Q \cup b& \quad a = 0 \\
\text{Vorberechnen}(a - 1, x \text{ xor }s, b \cup s) \space \forall \space s \in S
& \quad \text{else}
\end{cases}
$$

$a$ ist die verbleibende Anzahl von Zahlen, die noch für eine vollständige Kombination hinzugefügt werden müssen, also zu Beginn $d$. $x$ ist der $\text{xor}$-verknüpfte Wert aller $s$ der höher liegenden rekursiven Aufrufe. Für den ersten Aufruf eignet sich $x=0$, da $0$ der Identitätsoperand von $\text{xor}$ ist. $b$ ist die Liste aller bisher benutzten $s$ und sollte zu Beginn leer sein. Bei größeren $k$ muss beachtet werden, dass der Speicherbedarf sowie die Zeit zur Erstellung von $L$ mit $O(n^d)$ zunimmt, weshlb es nicht immer sinnvoll ist $d = k - 2$ zu wählen, wie in den bisherigen Beispielen. Man stößt hier auf ein _Space-Time-Tradeoff_, das durch ein gut ausgewähltes $d$ optimiert werden kann.

// aufgerundet k / 2, begründung??

**Optimierung der Zeitkomplexität.** Wenn $d \neq k - 2$, kann das spätere Durchsuchen der Liste auch nicht mehr in $O(n^2 \log_2 n)$ geschehen, weil nicht alle Paare, sondern alle Kombinationen von $k - d$ Zahlen überprüft werden müssen. Da es davon $\binom {n}{k-d}$ gibt, ist die Zeitkomplexität des Durchsuchens $O(n^{k - d} \log_2 n^d)$. Die gesamte Zeitkomplexität ist also $O(n^d + n^{k - d} \log_2n^d)$. Daran sieht man, dass $d = \lfloor \frac k2 \rfloor$ die sinnvollste Wahl ist, denn für die asymptotische Zeitkomplexität ist allein der Summand mit dem größten Exponenten entscheidend, der so minimiert wird. Bei ungeradem $k$ ist abrunden sinnvoller als aufrunden, weil der Speicherbedarf von $L$ exponentiell mit $d$ steigt.

**Limitierung durch die Speicherkomplexität.** Bei großen Eingabedateien muss der Speicherverbrauch beachtet werden. Z. B. bei `stapel4.txt`: Mit der oben genannten Einschätzung der Speicherkomplexität $\binom {n}{d}$ müssten $\binom {181}{5} \approx 1,53 \cdot 10^9$ 128-Bit Zahlen gespeichert werden, was ungefähr 24,5 Gigabyte Arbeitsspeicher erfordern würde. Wenn der Computer nicht so viel Arbeitsspeicher besitzt, muss $d$ entsprechend verringert werden.

Nachdem $L$ und $Q$ erstellt und sortiert wurden, wird jede $\text{xor}$-Verknüpfung aus $k - d$ Zahlen generiert und überprüft, ob diese in $L$ existiert. Das kann wie bei der Erstellung rekursiv gelöst werden.

$$
\text{Durchsuchen}(a, x, b) = \begin{cases}
i \larr \text{BinarySearch}(L, x) & \quad a = 0 \\
\text{if } (i \neq -1 \and b \cap q_i = \empty) \space \text{ausgeben}(b \cup q_i) \\
\text{Durchsuchen}(a - 1, x \text{ xor }s, b \cup s) \space \forall \space s \in S
& \quad \text{else}
\end{cases}
$$

Hier muss $a$ beim ersten Aufruf, im Gegensatz zu $\text{Vorberechnen}(a, x, b)$, $k - d$ sein.

Zusammenfassend sieht der Pseudocode des Algorithmus wie folgt aus. $q_i$ ist der $i$´te Eintrag in $Q$.

```pseudocode
prcoedure XorZuNull(S, k)
	d ← ⌊k / 2⌋;
	while (Speicher von L und Q > Arbeitsspeicher) d ← d - 1;

	L ← ∅;
	Q ← ∅;
	Vorberechnen(d, 0, ∅);
	RadixSort(L, Q, m);
	Durchsuchen(k - d, 0, ∅);
```

#### Radix Sort (MSD)

Radix Sort eignet sich besonders, um Zahlen mit gleicher oder ähnlicher Länge zu sortieren, weil er in diesem Fall in $O(n^d \cdot m)$ Zeit läuft. Jeder vergleichsbasierte Algorithmus würde mindestens $O(n^d \log_2 n^d)$ Zeit benötigen, was asymptotisch schlechter ist, wenn man $m$ mit 128 begrenzt. Ich habe mich für die _Most Significant Digit (MSD)_ Variante von Radix Sort entschieden, um keinen zusätzlichen Speicherplatz zu verbrauchen.

Die Zahlen werden sortiert, indem sie zunächst nach dem wichtigsten Bit gruppiert werden, dann beide Gruppen rekursiv nach dem zweitwichtigsten Bit etc., bis alle Bits ausgewertet wurden. Ein Rekursionsschritt, der die Liste nach dem $h$´ten Bit (vom niedrigstwertigen Bit aus gezählt, d. h. $h = m$ zu Beginn) gruppiert, läuft wie folgt ab: Zwei Indizes $u$ und $v$ werden mit dem Anfangs- und Endindex von $L$ initialisiert. Vor $u$ befinden sich alle Zahlen mit $h$´ten Bit $0$, nach $v$ alle Zahlen mit $h$´ten Bit $1$. Wenn der $h$´te Bit des $u$´ten Eintrags in $L$ ($l_u$) $0$ ist, wird $u$ einfach um $1$ vergrößert (Z. 12). Andernfalls wird $l_u$ dem Teil mit $h$´ten Bit $1$ hinzugefügt, indem es mit $l_v$ getauscht wird (Z. 8). Dann wird der $1$-Abschnitt um $1$ vergrößert, indem $v$ um $1$ verringert wird. So werden alle Einträge der Liste betrachtet, bis $u$ und $v$ gleich sind. Bevor der $0$- und $1$-Abschnitt jeweils rekursiv sortiert werden können muss beachtet werden, dass $u$ am Ende des $0$-Abschnitts steht, falls der $h$´te Bit von $l_u$ beim letzten Iterationsschritt $1$ war. Damit das weitere Sortieren fehlerlos funktioniert, soll $u$ immer am Anfang des $1$-Abschnitts stehen, das wird in Z. 14 - 15 sichergestellt.

Damit die Einträge in $Q$ nach dem Sortieren noch stimmen, wird jede Veränderung von $L$ auch für $Q$ übernommen (Z. 9).

```pseudocode
procedure RadixSort(L, M, h)
	if (h = 0) return;

	u ← 1;
	v ← |L|;
	while (u < v)
		if (h`ter Bit von lᵤ = 1)
			tausche lᵤ und lᵥ;
			tausche qᵤ und qᵥ;
			v ← v - 1;
		else
			u ← u + 1;

	if (h`ter Bit von lᵤ = 0)
		u ← u + 1;

	RadixSort(L bis u, Q bis u, h - 1);
	RadixSort(L ab u, Q ab u, h - 1);
```

#### Binärsuche

Binärsuche findet die Position eines gesuchten Werts in einer sortierten Liste, indem das betrachtete Intervall $[u, v]$ schrittweise verkleinert wird. Wenn der Wert in der Mitte des Intervalls kleiner als der gesuchte ist, muss der gesuchte Wert $x$, falls er existiert, in der zweiten Hälfte liegen, d. h. die untere Grenze $u$ kann auf die Mitte $+\space1$ angehoben werden. Wenn er größer ist, wird die obere Grenze $v$ abgesenkt. Wenn in der Mitte der gesuchte Wert liegt, kann sie sofort zurückgegeben werden. $-1$ zeigt an, dass das $x \neq L$, was eintritt, wenn die Länge von $[u, v]$ $0$ ist.

```pseudocode
procedure BinarySearch(L, x)
	u ← 1;
	v ← |L|;

	while (u < v)
		h ← ⌊(u + v) / 2⌋;
		if (lₕ < x) u ← h + 1;
		else if (lₕ > x) v ← h - 1;
		else return h;

	return -1;
```

Neben Binärsuche habe ich als Suchalgorithmus auch Interpolationssuche in Betracht gezogen. Weil eine Gleichverteilung der vorberechneten $\text{xor}$-Werte aber nicht garantiert werden kann bzw. unwahrscheinlich ist, benutze ich Binärsuche.

#### Möglicher Divide and Conquer-Ansatz

Ich hatte die Idee, bei nicht ausreichendem Speicher jede Zahl in kleinere Zahlen mit $c$ Bits aufzuteilen, um $\frac mc$ neue Kartensets zu erhalten. Nachdem alle Lösungen für jedes dieser Sets berechnet wurden, wird die Schnittmenge aller Lösungen genommen, die die Lösung des gesamten Problems ist. Beispielsweise würde sich bei 128-Bit Zahlen mit $c = 8$ der Speicherverbrauch auf $\frac 1{16}$ reduzieren. Ich habe diesen Ansatz implementiert und getestet, er war aber nicht gewinnbringend. Die Testergebnisse finden sich im [Anhang](#teilung-der-zahlen). Ein weiteres Problem war, dass bei großem $n$ und $k$, also genau den speicherkritischen Fällen, und gleichzeitig kleinem $c$ die Anzahl an Lösungen jedes Kartensets sehr groß ist, wodurch teilweise mehr Speicher als ohne Teilung verbraucht wurde. Wenn man noch größere $m$ als 128 mit einbeziehen würde, kann die Idee hilfreich sein.

### Teilaufgabe b)

Damit Zara sicher weniger als zwei Fehlversuche benötigt, muss sie wissen, welches Haus sie gerade öffnen möchte, daher setzt ich das voraus. Außerdem muss sie die Karten aufsteigend sortieren. Möchte sie das $i$´te Haus öffnen, sollte sie es zunächst mit der $i$´ten Karte versuchen. Für die Position der $\text{xor}$-Sicherungskarte ergeben sich drei Fälle.

1. **Hinter der ausgwählten Karte.** Die ausgewählte Karte ist die richtige.
2. **Vor der ausgewählten Karte. ** Die $i$´te Karte ist ein Fehlversuch. Die $i+1$´te Karte ist die richtige, da die Schlüsselkarte des Hauses durch die vorhergehende $\text{xor}$-Karte um eins nach hinten geschoben wurde.
3. **Die $\text{xor}$-Karte ist die ausgewählte Karte.** Auch hier ist die $i$´te Karte ein Fehlversuch. Aber aufgrund der selben Logik wie bei 2. ist die $i+1$´te Karte die richtige.

Zusammenfassend sind die Anweisungen für das $i$´te Haus also wie folgt:

1. Sortiere die Karten aufsteigend.
2. Probiere es mit der $i$´ten Karte.
3. Wenn das fehlgeschlagen ist, probiere es mit der $i+1$´ten Karte.

Um wieder herauszufinden, welche der Karten ihre Sicherungskarte war, gibt es keine andere Möglichkeit, als die oben beschriebenen Schritte bei allen Häusern anzuwenden. Währenddessen sollte Zara sich natürlich merken, welche Karten ein Haus öffnen konnten, die am Ende übrig bleibende ist die Sicherungskarte.

## Implementierung

Die Idee setzte ich in C++ mit dem Compiler clang um. Das Programm ist auf x86-64 Linux Systemen ausführbar. Da Schlüsselwörter und Ähnliches in C++ englisch sind, schreibe ich meine Code auch in Englisch. C++ eignet sich sehr gut für diese Aufgabe, weil $\text{xor}$ mit dem `^`-Operator und 128-Bit Zahlen nativ unterstützt werden. Auch werde ich den Code durch parametrischen Polymorphismus mit C++ Templatefunktionen generisch halten, sodass er für alle Bitlängen funktioniert. Der Teil des Programms, der die Karten findet, ist in Funktionen unterteilt und steht in `k_xor.hpp`. Weil viele der Funktionen generisch sind, muss eine Headerdatei benutzt werden. In `main.cpp` wird mit der Bitlänge $m$ der entsprechende Integertyp ausgewählt, die Karten eingelesen und die `xor_to_zero` Funktion mit dem Integertyp als Templateparameter `T` aufgerufen. Ab hier läuft alles generisch ab, wobei `T` auch bei jeder anderen Funktion der zu $m$ zugegötige Integertyp ist.

Das Programm gibt die $k$ Zahlen aus, deren $\text{xor } 0$ ist. Logischerweise sind alle nicht ausgegebenen Zahlen die hinzugefügten Karten.

### Der Hauptalgorithmus

// Zeilenangaben

#### Initialisierung

&rarr; zugehörige Funktion: `xor_to_zero` (Z. 1 - 13)

Ich werde zunächst nur die Teile des Codes berücksichtigen, die für das eigentliche Berechnen der Lösung zuständig sind. Teile, die die Parallelisierung betreffen, werden im Abschnitt [_Parallelisierung_](#parallelisierung) erklärt.

// memory

Die Liste an vorberechneten $\text{xor}$-Werten $L$ wird mit dem Namen `val` genau wie im Pseudocode umgesetzt, nur $Q$ wird als eindimensionale Liste `ind` mit $|L| \cdot d$ Einträgen gehandhabt. Die zum $i$´ten Eintrag in `val` zugehörigen Indizes stehen in `ind` bei Index $i \cdot d$ bis $i \cdot d + d$. `val` und `ind` sind C-style Arrays, um nur so wie Speicherplatz wie nötig zu verbrauchen. Ein C-style Array besteht nur aus sequentiell angeordneten Werten des angegebenen Typs, der Variablenname ist ein Zeiger zum ersten dieser Werte.

Zunächst wird $d$ zu dem optimalen Wert $\lfloor \frac k2 \rfloor$ initialisiert (Z. 6). Da die Länge von `val` $\binom nd$ sein wird und jeder Eintrag in `val` ein `T` ist, kann die Menge an verbrauchtem Arbeitsspeicher einfach vorhergesehen werden. Denn jedes `T` verbraucht wiederum `sizeof (T)` Bytes (Z. 7). Dazu kommen für jeden Eintrag in `val` $d$ Einträge in `ind`, für die aber jeweils ein 8-Bit, also 1-Byte positiver Integer ausreicht, da die Anzahl an Karten in keiner Eingabedatei 255 überschreitet. Nachdem $d$ festgesetzt wurde, wird in `num_comb` die Länge von `val` gespeichert, die für den weiteren Verlauf häufig benötigt wird.

#### Zusammensetzung von Kartenkombinationen

&rarr; zugehörige Funktion: `xor_combine`

Wie schon in den Rekursionsformeln bei der Lösungsidee ersichtlich war, liegt für das Vorberechnen der $\text{xor}$-Werte und das spätere Suchen eines passenden Gegenstücks die gleiche Rekursion zugrunde. Nur bei den Anweisungen nach Eintreten der Abbruchbedingung $a=0$ werden unterschiedliche Befehle ausgeführt. Um Codewiederholung zu vermeiden, implementiere ich eine höherwertige, rekursive Funktion `xor_combine`, die ein `std::function`-Objekt, also irgendeine Art Funktion, als Parameter nimmt. Diese wird beim Eintreten der Abbruchbedingung ausgeführt.

`xor_combine` erstellt alle $\text{xor}$-Verknüpfungen aus `a` Zahlen, indem eine Zahl fixiert wird und dann rekursiv alle Kombinationen aus `a - 1` Zahlen mit der fixierten Zahl $\text{xor}$-verknüpft werden. Das Fixieren geschieht für jede Zahl, allerdings werden beim rekursiven Aufruf nur noch Zahlen in Betracht gezogen, die in `cards` nach der gewählten Zahl stehen, um Dopplungen zu vermeiden.

#### Vorberechnung

Das Vorberechnen funktioniert mithilfe der Funktion `xor_combine`, der eine Lambdafunktion als Callback mitgegeben wird. In dieser sind die Schritte festgelegt, die für eine generierte Kombination ausgeführt werden. In `pos` ist die Position in dem Array `val` abgespeichert, in die der nächste $\text{xor}$-Wert vom aktuellen Thread geschrieben werden soll, die genaue Initialisierung dieser Variable wird bei [_Parallelisierung_](#parallelisierung) erklärt. Nachdem der $\text{xor}$-verknüpfte Wert der aktuellen Zahlenkombination dort eingetragen wurden, und die Indizes der verwendeten Zahlen in `ind`, wird `pos` um eins vergrößert.

#### Suche nach Gegenstücken

Auch hier wird `xor_combine` eine Lambdafunktion mitgegeben. Zunächst wird durch [Binärsuche](#binärsuche-2) über `val` überprüft, ob es zu der als Argument mitgegebenen Zahl ($\text{xor}$-Verknüpfung meherer Karten) einen vorberechnete gibt. Ist das nicht der Fall, kann die zugehörige Kombination sofort verworfen werden. Andernfalls muss die Möglichkeit beachtet werden, dass es mehrere vorberechnete Kombinationen mit dieser Zahl als $\text{xor}$-Summe gibt und Binärsuche nur eine davon gefunden hat. Daher wird die Position der gefundenen Zahl `j` zum Anfang der Folge gleicher Zahlen bewegt. Im Folgenden wird für jede Zahl / vorberechnete Kombination in dieser Folge überprüft, ob sich ihre zugehörigen Karten mit denen der aktuell betrachteten Kombination überschneiden (&rarr; [Überprüfen von Überschneidungen](#überprüfen-von-überschneidungen)). Wenn das nicht der Fall ist, wird die gefundene Lösung ausgegeben, der Arbeitsspeciher von `val` und `ind` freigegeben und der Prozess beendet.

#### Überprüfen von Überschneidungen

&rarr; zugehörige Funktion: `no_intersection`

Die Funktion liefert einen Wahrheitswert, ob zwei gleiche Zahlen in den zwei mitgegebenen Arrays auftreten, was in diesem Fall die doppelte Benutzung einer Karte bedeuten würde. Dazu wird ein `std::unordered_set` aus der zweiten der beiden Listen erstellt. So kann dann für jedes Element des ersten Arrays in $O(1)$ Zeit überprüft werden, ob es ebenfalls im zweiten Array vohanden ist.

#### Der Binomialkoeffizient

&rarr; zugehörige Funktion: `binom`

Würde man zur Berechnung des Binomialkoeffizienten einfach die Formel anwenden, über die er definiert ist, würde durch $n!$ ein Integer Overflow entstehen. Daher implementiere ich ihn rekursiv über folgende Beziehungen:

$$
\binom nk = \frac nk \binom {n-1}{k-1} \\
\binom n0 = 1
$$

Die Erste Beziehung kann wie folgt bewiesen werden:

$$
\binom nk = \frac {n!}{k!(n - k)!} = \\
\frac {n \cdot (n - 1)!}{k \cdot (k - 1)!(n - k)!} = \\
\frac nk \cdot \frac {(n-1)!}{(k-1)!(n - 1 - (k - 1))!} = \\
\frac nk \binom {n-1}{k-1}
$$

Die zweite Beziehung kann man durch die Überlegung bestätigen, dass man nur eine Möglichkeit hat, eine leere Menge aus einer Menge auszuwählen, nämlich indem man einfach kein Element nimmt.

### Radix Sort

Meine Implementierung von RadixSort unterscheidet sich kaum vom Pseudocode. Unterschiede sind, dass die Indexierung der Arrays in der Implementierung mit 0 statt mit 1 beginnt. Der `h`´te Bit der betrachteten Zahl wird herausgefunden, indem die Bits `h` mal nach rechts verschoben werden und die verbleibende Zahl mit 1 $\text{und}$-verknüpft wird. So bleibt eine 1 übrig, wenn der `h`´te Bit 1 war, was in C++ gleich zu `true` ist.

### Binärsuche

Binärsuche ist genau wie im Pseudocode beschrieben implementiert, daher werde ich die dort beschriebene Funktionsweise nicht wiederholen. Ein Detail habe ich mir bei der Implementierung aber überlegt: In den meisten Fällen findet Binärsuche bei dieser Anwendung keine Lösung, weswegen fast immer eine der Bedingungen `val[mid] < target` oder `val[mid] > target` zutrifft. Es ist daher sinnvoll, die Codezeilen so anzuordnen, dass diese zuerst überprüft werden, um insgesamt weniger Überprüfungen durchführen zu müssen. Normalerweise wäre so etwas irrelevant, aber Binärsuche wird bei meinem Algorithmus sehr oft durchgeführt und ist das begrenzende Element der Laufzeit.

### Parallelisierung

Ich parallelisiere das Vorberechnen und das spätere Durchsuchen der vorberechneten Werte durch Multithreading. Optimalerweise soll die Anzahl an Threads `cores` gleich zur Anzahl der Prozessorkerne des Computers sein, die in Z. ? abgefragt wird. Wenn dazu keine Informationen vorhanden sind, wird 8 verwendet.

#### Parallelisierung von `xor_combine`

Das Aufteilen der Arbeit der `xor_combine` Funktion geschieht, indem sie `cores`-mal aufgerufen wird, wobei jeweils der Umfang der Zahlen (in `xor_combine` die Parameter `start` bis `end`), die auf der obersten Rekursionsebene betrachtet werden, begrenzt ist. Die von `assign_threads` zurückgegebene Aufteilung enthält für den `i`´ten Thread den Index der Karte, bei der er beginnen soll, bei Index `i * 2`. Darauf folgt jeweils bei `i * 2 + 1` die Anzahl an Kombinationen, die von allen niedriger nummerierten Threads berechnet werden. Das ist entscheidend, weil so jedem Thread ein Teil von `val` und `ind` zugeteilt wird, in den er seine Kombinationen hineinschreiben kann. Damit ist keine Synchronsierung erforderlich, was die Performance erheblich verbessert. Diese Zuteilung geschieht durch die entsprechende Initialisierung von `pos`. Nachdem alle Threads erstellt wurden, wird bei jedem die `std::thread::join` Methode aufgerufen, um mit der weiteren Ausführung des Hauptthreads auf die nebenläufigen Threads zu warten.

Beim späteren Durchsuchen unterscheidet sich die Parallelisierung nur darin, dass eine gewisse Synchronisation notwendig ist. Denn sobald ein Thread eine Lösung gefunden und ausgegeben hat, gibt er den Arbeitsspeicher von `val` und `ind` frei, und beendet erst danach den Prozess und damit die anderen Threads. Da `val` und `ind` bei großen Eingabedateien mehrere Gigabyte groß sind, benötigt das Freigeben relativ viel Zeit, während der die anderen Threads auf diese Arrays zugreifen. Es kommt sehr wahrscheinlich zu einem Speicherzugriffsfehler / _Segmentation Fault_ und das Program stürzt ab. Auch wenn die korrekte Lösung bereits ausgegeben wurde, ist das natürlich kein geeigneter Weg, ein Programm zu beenden. Mit einer `std::atomic_bool` Variable wird daher überwacht, ob eine Lösung gefunden wurde. Ist sie `true`, greift kein Thread mehr auf `val` bzw. `ind` zu, weil die Lambdafunktion sofort beendet wird. Der erste Thread, der eine Lösung findet, setzt `found` also auf `true`.

#### Zuteilung der Arbeit

&rarr; zugehörige Funktion: `assign_threads`

Da von `xor_combine` auf unteren Rekursionsebenen immer alle nachfolgenden Zahlen betrachtet werden, ist der Aufwand für Karten höher, die früher in `cards` stehen. Die Indizes von `cards` in gleiche Teile zu teilen führt also zu einer ungleichmäßigen Verteiling. `assign_threads` teilt die Indizes auf, indem als Mindestpensum `min` zunächst $\frac {\text{Gesamtanzahl Kombinationen}}{\text{Anzahl Threads}}$ festgelegt wird. Dann wird über jeden Index iteriert und eine Zuteilung für den `j`´ten Thread zu den Zuteilungen `alloc` hinzugefügt, sobald die bisherige Gesamtanzahl zu erstellender Kombinationen das `j`-fach des Mindestpensums überschritten hat. Die Anzahl an Kombinationen, die für die `i`´te Karte anfallen, sind $\binom{n-i-1}{a-1}$, weil durch Fixierung der `i`´ten Karte noch $a-1$ Karten gewählt werden müssen. Dafür sind aber nicht mehr alle $n$ Karten verfügbar, sondern eine weniger für die fixierte, und $i$ weniger, weil durch `xor_combine` nur die nachfolgenden Karten einbezogen werden.

#### Parallelisierung von Radix Sort

Radix Sort teilt die Arbeit schon von sich aus rekursiv mit einem Verzweigungsfaktor von 2 auf. Daher ist es naheliegend, einfach bis zu einer gewissen Rekursionstiefe `t_depth` für jeden rekursiven Aufruf einen neuen Thread zu erstellen. Die Anzahl an arbeitenden Threads ist nach Erreichen dieser Tiefe $2^{\text{t\_depth}}$ und solle optimalerweise der Anzahl an Rechenkernen `cores` entsprechen. Daher wird für `t_depth` zu Beginn $\lceil \log_2 (\text{cores}) \rceil$ als Argument gegeben. Falls `cores` keine Potenz von zwei ist, sollten eher zu viele als zu wenige Threads arbeiten, da eine unvollständige Auslastung des Prozessors wesentlich mehr Zeit kostet als einige zusätzliche Threadwechsel. Das konnte ich durch kurze Experimente bestätigen.

## Zeitkomplexität

Die Zeitkomplexität wird durch das Vorberechnen, Radix Sort und das Durchsuchen der vorberechneten Lösungen dominiert. Es werden insgesamt $\binom nd$ Kombinationen vorberechnet, für die jeweils die $d$ Indizes der verwendeten Karten nach `ind` kopiert werden. Das Vorberechnen wird immer vollständig ausgeführt, daher ist seine Best- und Worst-Case Komplexität $O(\binom nd \cdot d)$. Radix Sort iteriert im schlechtesten Fall $m$-mal über alle Elemente von `val` und führt dabei im schlechtesten Fall jeweils $d$ Swaps aus. Daher ist seine Worst-Case Komplexität $O(\binom nd \cdot d \cdot m)$. Im besten Fall müssen keine Swaps ausgeführt werden und es werden deutlich weniger als $m$ Bits betrachtet. Daher ist die Best Case Komplexität $O(\binom nk)$. Beim nachträglichen Durchsuchen werden im schlechtesten Fall $\binom n{k-d}$ Kombinationen überprüft, für die jeweils eine Binärsuche über `val` durchgeführt wird. Für diese Binärsuche wird im Worst-Case und Average-Case $O(\log_2\binom nd)$ Zeit benötigt, da meist keine passende Zahl gefunden wird. In einem sehr ungünsigen Fall würde für jede dieser Kombinationen ein passendes Gegenstück in `val` gefunden werden und `no_intersection` augeführt werden, und sich dann herausstellen, dass sich die Indizes überschneiden. Da `no_intersection` in $O(d)$ läuft, ergibt sich für die (Worst-)Worst-Case Zeitkomplexität des Durchsuchens $O(\binom n{k-d} \cdot \log_2 \binom nd \cdot d)$. Dieser zweite Fall ist aber sehr unwahrscheinlich, da Binärsuche, wie oben gesagt, so gut wie immer kein Ergebnis findet. Es ist also nicht falsch, für die Worst-Case Zeitkomplexität des Durchsuchens $O(\binom n{k-d} \log_2 \binom nd)$ anzugeben. Eine Average- oder Best-Case Komplexität abzuschätzen ist sehr schwierig bzw. nicht sinnvoll, weil der Algorithmus beendet wird, sobald eine Lösung gefunden wurde. Der Zeitpunkt der Lösungsfindung ist aber allein von der Anordnung der Karten abhängt, die zufällig ist. Die  Worst-Case Komplexität des gesamten Programms ist folglich

$$
O \Bigg (\binom nd \cdot d + \binom nd \cdot m \cdot d + \binom n{k-d} \log_2 \binom nd \Bigg)
$$

_Anmerkung:_ Wenn man voraussetzt, dass jede Verteilung der Schlüsselkarten gleich wahrscheinlich ist, wäre es möglich, eine Average-Case Abschätzung für das Durchsuchen zu anzugeben. Aber dann müsste auch die Threadzuteilung beachtet werden, weil von ihr maßgeblich abhängt, welche Kombinationen zuerst betrachtet werden.

## Beispiele

## Quellcode

### Der Hauptalgorithmus

```c++
template <typename T>
void xor_to_zero(std::vector<T> cards, int n, int k) {
    long long memory_limit = memory() - (((long long) 1) << 31);
    std::cout << "Memory Limit: " << (memory_limit) / pow(10, 6) << " MB\n";

    int d = k / 2;
    while (binom(n, d) * (sizeof (T) + d) > memory_limit) d -= 1;
    long long num_comb = binom(n, d);

    auto begin = std::chrono::system_clock::now();

    T* val = new T[num_comb];
    uint8_t* ind = new uint8_t[num_comb * d];

    int cores = std::thread::hardware_concurrency();
    if (cores == 0) cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (cores == 0) cores = 8;

    std::vector<int> alloc = assign_threads(num_comb, cores, n, d);
    std::cout << "Using " << cores << " threads\n";
    std::vector<std::thread> threads;

    for (int i = 0; i < cores; i++) {
        threads.emplace_back([i, &cards, &val, &ind, &n, &d, &cores, &alloc] {
            int pos = alloc[i * 2 + 1];
            uint8_t used[d];
            xor_combine<T>(cards, d,
                [&val, &ind, &used, &pos, &d](T &xor_val) {
                    val[pos] = xor_val;
                    std::move(used, used + d, ind + pos * d);
                    pos += 1;
                },
                used, alloc[i * 2], i == cores - 1 ? n : alloc[i * 2 + 2]);
        });
    }

    for (std::thread &t: threads) t.join();

    std::cout << "Precomputed " << num_comb << " combinations, d = " << d << "\n";
    radix_sort_msd<T>(val, ind, num_comb, d);
    std::cout << "Sorted\n";

    alloc = assign_threads(num_comb, cores, n, k - d);
    threads.clear();
    std::atomic_bool found(false);

    for (int i = 0; i < cores; i++) {
        threads.emplace_back([i, &cards, &val, &ind, &num_comb,
            &n, &k, &d, &cores, &alloc, &begin, &found] {
            uint8_t used[k - d];
            xor_combine<T>(cards, k - d,
                [&cards, &val, &ind, &num_comb, &k, &d, &used, &begin, &found] (T &xor_val) {
                    if (found) return;
                    long long j = bs<T>(val, num_comb, xor_val);
                    if (j != -1) {
                        while (j > 0 && val[j - 1] == xor_val) j -= 1;

                        while (val[j] == xor_val && j < num_comb) {
                            if (no_intersection(used, ind + j * d, k - d, d) && !found) {
                                found.store(true);

                                std::vector<uint8_t> res(used, used + (k - d));
                                res.insert(res.end(), ind+ j * d, ind + j * d + d);
                                print_cards(res, cards);
                                std::cout << ((std::chrono::duration<float>)
                                    (std::chrono::system_clock::now() - begin)).count()
                                    << " s \n";

                                delete[] ind;
                                delete[] val;
                                exit(EXIT_SUCCESS);
                            }
                            j += 1;
                        }
                    }
                },
                used, alloc[i * 2], i == cores - 1 ? n : alloc[i * 2 + 2]);
        });
    }

    for (std::thread &t: threads) t.join();

    delete[] val;
    delete[] ind;
}
```

## Literaturverzeichnis

1. Bouillaguet, C. & Delaplace, C. (2021). _Faster Algorithms for the Sparse Random 3XOR Problem_. https://hal.archives-ouvertes.fr/hal-02306917v1/document
2. Jafargholi, Z. & Viola, E. (2018). _3SUM, 3XOR, Triangles_. https://arxiv.org/pdf/1305.3827.pdf
3. Lewin, M. (2012). _All about XOR_. https://accu.org/journals/overload/20/109/lewin_1915/
4. Sannemo, J. (2018). _Principles of Algorithmic Problem Solving_. KTH Royal Institute of Technology. https://www.csc.kth.se/~jsannemo/slask/main.pdf
5. Wagner, D. (2002). _A Generalized Birthday Problem (Long version)_. University of California at Berkeley. https://people.eecs.berkeley.edu/~daw/papers/genbday.html
6. Williams, A. (2019). _C++ Concurrency in Action_. https://beefnoodles.cc/assets/book/C++%20Concurrency%20in%20Action.pdf
7. Woeginger, G. (2003). _Exact Algorithms for NP-Hard Problems: A Survey_. https://people.engr.tamu.edu/j-chen3/courses/689/2006/reading/w1.pdf

## Anhang

### Teilung der Zahlen

Es wurden jeweils 5 Tests mit $n = 20$ und $k = 4$ durchgeführt, die Karten wurden zufällig generiert. Links stehen die Ergebnisse mit Teilung der Karten in $c$-Bit Stücke, rechts die Ergebnisse ohne Teilung. Ohne Teilung muss $d$ um 1 reduziert werden, um den Speicherverbrauch gleich gering zu halten und den Vergleich fair zu machen. Zeitangaben in Durchschnitt ± Standardabweichung.

| m   | c   | d   | Zeit (ms)  |     | m   | d   | Zeit (ms)   |
| --- | --- | --- | ---------- | --- | --- | --- | ----------- |
| 8   | 8   | 2   | 2.3 ± 0.13 |     | 8   | 1   | 0.51 ± 0.48 |
| 16  | 8   | 2   | 5.7 ± 0.52 |     | 16  | 1   | 1.7 ± 0.37  |
| 32  | 8   | 2   | 13 ± 1.2   |     | 32  | 1   | 1.9 ± 0.28  |
| 64  | 8   | 2   | 26 ± 1.7   |     | 64  | 1   | 2.0 ± 0.41  |
| 128 | 8   | 2   | 53 ± 2.7   |     | 128 | 1   | 2.3 ± 0.23  |
