proj1.out: main.o
	g++ -Wall main.o Reservation.o ReservationManager.o Resource.o ResourceManager.o -o proj1.out

Reservation.o: include/Reservation.h src/Reservation.cpp
	g++ -Wall -c include/Reservation.h src/Reservation.cpp

ReservationManager.o: ResourceManager.o Reservation.o include/ReservationManager.h src/ReservationManager.cpp 
	g++ -Wall -c include/ReservationManager.h src/ReservationManager.cpp

Resource.o: include/Resource.h src/Resource.cpp 
	g++ -Wall -c include/Resource.h src/Resource.cpp

ResourceManager.o: Resource.o include/ResourceManager.h src/ResourceManager.cpp
	g++ -Wall -c include/ResourceManager.h src/ResourceManager.cpp 

main.o: ResourceManager.o ReservationManager.o src/main.cpp
	g++ -Wall -c src/main.cpp 

clean:
	rm include/*.gch *.o proj1.out