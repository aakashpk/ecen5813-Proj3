# ecen5813-Proj3


|                          |     |      |       |        |  |                          |     |      |       |        | 
|--------------------------|-----|------|-------|--------|--|--------------------------|-----|------|-------|--------| 
| FRDM BOARD               |     |      |       |        |  | FRDM BOARD               |     |      |       |        | 
| (values in Clock Cycles) | 10  | 100  | 1000  | 5000   |  | (values in Clock Cycles) | 10  | 100  | 1000  | 5000   | 
| memmove                  | 142 | 952  | 9052  | 45052  |  | memset                   | 107 | 737  | 7037  | 35037  | 
| my_memmove               | 471 | 3801 | 37101 | 185101 |  | my_memset                | 397 | 3187 | 31087 | 155087 | 
| my_memmove (O3)          | 187 | 1267 | 12067 | 60067  |  | my_memset (O3)           | 152 | 1052 | 10052 | 50052  | 
| my_memmove_dma           | 667 | 775  | 4375  | 20379  |  | my_memset_dma            | 541 | 579  | 2379  | 10379  | 
|                          |     |      |       |        |  |                          |     |      |       |        | 
|                          |     |      |       |        |  |                          |     |      |       |        | 
| BEAGLE BONE BLACK        |     |      |       |        |  | BEAGLE BONE BLACK        |     |      |       |        | 
| (values in uS)           | 10  | 100  | 1000  | 5000   |  | (values in uS)           | 10  | 100  | 1000  | 5000   | 
| memmove                  | 25  | 6    | 8     | 25     |  | memset                   | 18  | 5    | 5     | 13     | 
| my_memmove               | 7   | 17   | 128   | 623    |  | my_memset                | 6   | 13   | 94    | 454    | 
| my_memmove (O3)          | 5   | 7    | 28    | 122    |  | my_memset (O3)           | 4   | 6    | 20    | 88     | 
