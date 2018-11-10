CC = gcc
CFLAGS = -Wall -Wpedantic -O3
CLFLAGS = -lpthread

OUT_QI = qi
OBJ_QI = q_i_sort.o

OUT_MQI = mqi
OBJ_MQI = m_quicksort.o

qi: $(OBJ_QI)
	$(CC) $(CFLAGS) -o $(OUT_QI) $(OBJ_QI)

mqi: $(OBJ_MQI)
	$(CC) $(CFLAGS) -o $(OUT_MQI) $(OBJ_MQI) $(CLFLAGS)

clean:
	$(RM) $(OUT_QI) $(OUT_MQI) $(OBJ_QI) $(OBJ_MQI)
