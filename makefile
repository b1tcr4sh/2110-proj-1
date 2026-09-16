main: ResourceManager.cpp ReservationManager.cpp
	g++ src/main.cpp

ResourceManager.cpp: ResourceManager.h
	g++ -c src/ResourceManager.cpp

ResourceManager.h: Resource.cpp
	g++ -c include/ResourceManager.h

Resource.cpp: Resource.h
	g++ -c src/Resource.cpp

Resource.h:
	g++ -c include/Resource.h

ReservationManager.cpp: ReservationManager.h
	g++ -c src/ReservationManager.cpp

ReservationManager.h: Reservation.cpp
	g++ -c include/ReservationManager.h

Reservation.cpp: Reservation.h
	g++ -c src/Reservation.cpp

Reservation.h:
	g++ -c include/Reservation.h


clean:
	rm include/*.gch *.o