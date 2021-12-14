FLAGS = -Wall -Werror -Wconversion

main: main.o city.o building.o tile.o inaccesible_tile.o buildable_tile.o passable_tile.o building_handler.o map.o material_handler.o record.o utils.o menu.o material.o mine.o school.o factory.o obelisk.o sawmill.o power_plant.o file_utils.o empty_passable_tiles.o
		g++ main.o city.o building.o tile.o inaccesible_tile.o buildable_tile.o passable_tile.o building_handler.o map.o material_handler.o record.o utils.o menu.o material.o mine.o school.o factory.o obelisk.o sawmill.o power_plant.o file_utils.o empty_passable_tiles.o $(FLAGS) -o main

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

city.o: city.cpp
	g++ $(FLAGS) -c city.cpp

building.o: building.cpp
	g++ $(FLAGS) -c building.cpp

tile.o: tile.cpp
	g++ $(FLAGS) -c tile.cpp

inaccesible_tile.o: inaccesible_tile.cpp
	g++ $(FLAGS) -c inaccesible_tile.cpp

buildable_tile.o: buildable_tile.cpp
	g++ $(FLAGS) -c buildable_tile.cpp

passable_tile.o: passable_tile.cpp
	g++ $(FLAGS) -c passable_tile.cpp

building_handler.o: building_handler.cpp
	g++ $(FLAGS) -c building_handler.cpp

material_handler.o: material_handler.cpp
	g++ $(FLAGS) -c material_handler.cpp

utils.o: utils.cpp
	g++ $(FLAGS) -c utils.cpp

menu.o: menu.cpp
	g++ $(FLAGS) -c menu.cpp

material.o: material.cpp
	g++ $(FLAGS) -c material.cpp

mine.o: mine.cpp
	g++ $(FLAGS) -c mine.cpp

school.o: school.cpp
	g++ $(FLAGS) -c school.cpp

factory.o: factory.cpp
	g++ $(FLAGS) -c factory.cpp

obelisk.o: obelisk.cpp
	g++ $(FLAGS) -c obelisk.cpp

sawmill.o: sawmill.cpp
	g++ $(FLAGS) -c sawmill.cpp

power_plant.o: power_plant.cpp
	g++ $(FLAGS) -c power_plant.cpp

file_utils.o: file_utils.cpp
	g++ $(FLAGS) -c file_utils.cpp

empty_passable_tiles.o: empty_passable_tiles.cpp
	g++ $(FLAGS) -c empty_passable_tiles.cpp

clean:
	rm *.o main
