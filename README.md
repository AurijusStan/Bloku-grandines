# Hash funkcija

# Versija v0.2
## Pseudo-kodas

1. input(by hand/from file);
2. myhash(input);
3. binary = stringtobinary(input);
4. if(binary.size()%32!=0) pad out;
5. h[] = splitintostringarrayof32(binary)
6. for(i; i<32){
7.   num = stringtolonglong(h[i])
8.   change num based on original string and flat values
9.   while(num>-1){
10.  h2[i] = convert groups of numbers into their ASCII counterparts (num) 
11.  }
13. }
14. for(i; i<32){
15.   add an extra character
16.   h[i] = stringtobinary(h2[i])
17.   XOR changes with original string
18.   XOR changes with neighbors
19.   pad h[i] so (h[i].size % 16 == 0)
20.   while(h[i].size>8){
21.   (h[i] not even) make even;
22.   XOR first half of binary with second half;
23.   }
24.   make sure h[i].size == 8;
25. }
26. return binarytohex(h[i])

## Eksperimentine analize

1. Visi rezultatai gaunami 64 simbolių ilgio
2. Rezultatai, kai input'inta po vieną simbolį, drastiškai skiriasi
3. Rezultatai, kai input'inta labai daug simbolių, identiški
4. Su tuo pačiu input'u, rezultatas visada vienodas

### Efektyvumo skaičiavimai (3 testų vidurkis)
| Eilučių sk. | Hash'inimo trukmė (ms) |
| :--- | ---- |
| 1 | 1.18 |
| 2 | 1.79 |
| 4 | 1.81 |
| 8 | 2.15 |
| 16 | 5.67 |
| 32 | 10.18 |
| 64 | 19.54 |
| 128 | 48.54 |
| 256 | 103.67 |
| 512 | 243.77 |

5. Ištestavus su 200000 eilučių, pasitaikė 0/100000 atvejų, kai porų hash'ai sutapo.

## Išvados
v0.1 hash funkcija nėra pakankamai gera.
Ji nepasižymi labai matomu lavinos efektu, ypač kai apdorojami inputai ilgi, jau nuo keliasdešimties simbolių matydavosi, kad hash'ai išeina labai panašūs.
Tai reikia patobulinti v2.0 ir jau turiu idėjų kaip tai padaryti.
