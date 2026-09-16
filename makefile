main: ResourceManager.o ReservationManager.o
	g++ src/main.cpp

ResourceManager.o: ResourceManager.h
	g++ -c src/ResourceManager.cpp

ResourceManager.h: Resource.o
	g++ -c include/ResourceManager.h

Resource.o: Resource.h
	g++ -c src/Resource.cpp

Resource.h:
	g++ -c include/Resource.h

ReservationManager.o: ReservationManager.h ResourceManager.h
	g++ -c src/ReservationManager.cpp

ReservationManager.h: Reservation.o ResourceManager.h
	g++ -c include/ReservationManager.h

Reservation.o: Reservation.h
	g++ -c src/Reservation.cpp

Reservation.h:
	g++ -c include/Reservation.h


clean:
	rm include/*.gch *.o