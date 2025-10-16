для запуска однопоточного алгоритма 
gcc sequential.c -o sequential -O2
./sequential

для запуска многопоточного алгоритма
gcc parallel.c -o parallel -O2 -pthread
./parallel
