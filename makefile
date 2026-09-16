main: main.cpp
	g++ src/main.cpp

main.cpp: ResourceManager.cpp ReservationManager.cpp
	g++ -c src/ResourceManager.cpp src/ReservationManager.cpp

ResourceManager.cpp: 
	g++ -c include/Resource.h include/ResourceManager.h

ReservationManager.cpp: 
	g++ -c include/Reservation.h include/ReservationManager