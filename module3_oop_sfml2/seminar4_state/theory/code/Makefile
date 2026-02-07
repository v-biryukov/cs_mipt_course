path = ../../3rdparty/SFML-2.5.1

all: 0enums 1enums 2fsm 4fsm_using_polymorphism 5player_animations 6player_states

0enums:
	gcc ./0enums.c -std=c99 -o 0enums

1enums:
	g++ ./1enums.cpp -std=c++17 -o 1enums

2fsm.cpp:
	g++ ./2fsm.cpp.cpp -std=c++17 -o 2fsm.cpp

4fsm_using_polymorphism:
	g++ ./4fsm_using_polymorphism.cpp.cpp -std=c++17 -o 4fsm_using_polymorphism.cpp

5textures:
	g++ ./5textures.cpp -std=c++17 -o 5textures -I $(path)/include -L $(path)/lib/ -lsfml-graphics -lsfml-window -lsfml-system 

6player_animations:
	g++ ./6player_animations.cpp -std=c++17 -o 6player_animations -I $(path)/include -L $(path)/lib/ -lsfml-graphics -lsfml-window -lsfml-system 

7player_states:
	g++ ./7player_states.cpp -std=c++17 -o 7player_states -I $(path)/include -L $(path)/lib/ -lsfml-graphics -lsfml-window -lsfml-system 

8view:
	g++ ./8view.cpp -std=c++17 -o 8view -I $(path)/include -L $(path)/lib/ -lsfml-graphics -lsfml-window -lsfml-system 


clear:
	rm ./*.exe