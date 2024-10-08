# Hash funkcija

# Versija v0.2
## Pseudo-kodas

### myhash(input)

```
Inicializuojamos konstantos:
blockSize=64;
targetHashSize=64;
Pradedamas pats hash'inimas:
binary=stobinary(input)
Pad'inama, kad binary sudarytų 512 bitų kartotinis skaičius simbolių
Inicializuojamas bitset<256> finalHash;
Toliau dirbama su kiekvienu 512 bitų bloku:
Blokas suskaidomas į 32 stringus h[i];
Kiekvienam h[i]:
char=input[i%input.size()];
bitset<8> ogbin(char);
h[i]+=7*(i+1);
h[i]=stobinary(h[i]);
for(h[i].size()){
    h[i][m] XOR ogbin[m%8];
}
if(0<i<31){
    h[i] XOR h[i-1] XOR h[i+1];
}
if(i>0){
    h[0] XOR h[i];
}
h[i] paverčiamas į ull su vertimo viduje esančiu XOR'u;
for(4){
    įvairios XOR ir shiftinimo operacijos su konstantomis ir originaliu string'u
}
Konvertuojamas finalHash į teisingą ilgį
```

## Eksperimentine analize

1. Visi rezultatai gaunami 64 simbolių ilgio
2. Rezultatai, kai input'inta po vieną simbolį, drastiškai skiriasi:
hash("a")=4EE68DE631D18732BCDF9D41AE88AB89FAB16A29564776EA6D5EF0C40B6FFA66
hasb("b")=6143765589BC0356705CAAE7D0275840F9343FCD611C7A8D11CC4C790A39B8EA
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
