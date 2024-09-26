# Hash funkcija

# Versija v0.1
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
| 1 | 0 |
| 2 | 0 |
| 4 | 0 |
| 8 | 0 |
| 16 | 1 |
| 32 | 1 |
| 64 | 1 |
| 128 | 2.076 |
| 256 | 4.509 |
| 512 | 10.136 |
