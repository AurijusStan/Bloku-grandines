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
hash("a")=EEF28D240D0CCAA7E795D194530EABA7E7119C7D24740A2A298430B74043A87D
hasb("b")=34005DDFA4BCAFCB6F5C9E5AC5B77559BB5C08E81BDE52366C436D5DB7613877
3. Sukūrus 2 failus, kuriuose yra 1200 simbolių eilutės, kurios skiriasi vienu simboliu, hash'ai gauti tokie:
t1=9F3DAC5BA1BD214A00EFA12EE4951BAD04430F75DF8C67C1BEB52AC895838C11
t2=3CFCA9A00502F7DCDEDE675307840FF5030E5340E855FF771E72886B1AE262CD
4. Su tuo pačiu input'u, rezultatas visada vienodas

### Efektyvumo skaičiavimai (3 testų vidurkis)
| Eilučių sk. | Hash'inimo trukmė (ms) |
| :--- | ---- |
| 1 | 1.18 |
| 2 | 1.79 |
| 4 | 1.81 |
| 8 | 2.75 |
| 16 | 6.02 |
| 32 | 12.26 |
| 64 | 25.42 |
| 128 | 59.29 |
| 256 | 130.21 |
| 512 | 294.05 |

5. Ištestavus su 200000 eilučių, pasitaikė 0/100000 atvejų, kai porų hash'ai sutapo.

## Išvados
v0.1 hash funkcija nėra pakankamai gera.
Ji nepasižymi labai matomu lavinos efektu, ypač kai apdorojami inputai ilgi, jau nuo keliasdešimties simbolių matydavosi, kad hash'ai išeina labai panašūs.
Tai reikia patobulinti v2.0 ir jau turiu idėjų kaip tai padaryti.
