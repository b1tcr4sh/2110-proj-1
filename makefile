main: main.cpp
	g++ src/main.cpp

main.cpp: src/ResourceManager.cpp, src/ReservationManager.cpp
	g++ src/ResourceManager.cpp src/ReservationManager.cpp

src/ResourceManager.cpp: include/ResourceManager.h, include/Resource.h
	g++ include/Resource.h include/ResourceManager.h

src/ReservationManager.cpp: include/ReservationManager.h, include/Reservation.h
	g++ include/Reservation.h include/ReservationManager

clean: