# ecen5813-Proj3
##Aakash Kumar / Arunsundar Kannan

The following table shows profiling values for the memory transfers. The values for the FRDM board are in clock cycles and the times for 
Beagle Bone Black is in microseconds.

|                          |          |           |            |            |  |                          |          |           |            |            | 
|--------------------------|----------|-----------|------------|------------|--|--------------------------|----------|-----------|------------|------------| 
| FRDM BOARD               |          |           |            |            |  | FRDM BOARD               |          |           |            |            | 
| (values in Clock Cycles) | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes |  | (values in Clock Cycles) | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes | 
| memmove                  | 142      | 952       | 9052       | 45052      |  | memset                   | 107      | 737       | 7037       | 35037      | 
| my_memmove               | 471      | 3801      | 37101      | 185101     |  | my_memset                | 397      | 3187      | 31087      | 155087     | 
| my_memmove (O3)          | 187      | 1267      | 12067      | 60067      |  | my_memset (O3)           | 152      | 1052      | 10052      | 50052      | 
| my_memmove_dma           | 667      | 775       | 4375       | 20379      |  | my_memset_dma            | 541      | 579       | 2379       | 10379      | 
|                          |          |           |            |            |  |                          |          |           |            |            | 
|                          |          |           |            |            |  |                          |          |           |            |            | 
| BEAGLE BONE BLACK        |          |           |            |            |  | BEAGLE BONE BLACK        |          |           |            |            | 
| (values in uS)           | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes |  | (values in uS)           | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes | 
| memmove                  | 25       | 6         | 8          | 25         |  | memset                   | 18       | 5         | 5          | 13         | 
| my_memmove               | 7        | 17        | 128        | 623        |  | my_memset                | 6        | 13        | 94         | 454        | 
| my_memmove (O3)          | 5        | 7         | 28         | 122        |  | my_memset (O3)           | 4        | 6         | 20         | 88         | 


It can be observed that the on the KL25Z FRDM board the DMA transfers are the fastest, with 10byte transfer being the exception. 
This is probably because the overhead time to setup the DMA transfer is comparable to the transfer time for small transfers, but there is 
significant increase in efficiency for larger transfers. The standard library memmove and memset functions have fastest transfer speeds
after DMA. The O3 optimized my_memmove functions have significantly better transfer speeds than the my_memove function. The transfer speed 
efficiency increases with size.
The efficiency of transfer increases with the  


