all: Jake_The_Snake

Jake_The_Snake: Game.o Snake_Engine.o Abstract_State.o Menu_State.o Collision_Handler.o Gameover_State.o Highscore_State.o Multi_State.o Obstacles.o Single_State.o Snake.o Sprite.o
	g++ Game.o Snake_Engine.o Abstract_State.o Menu_State.o Collision_Handler.o Gameover_State.o Highscore_State.o Multi_State.o Obstacles.o Single_State.o Snake.o Sprite.o -o Jake_The_Snake -lSDL

Abstract_State.o: Abstract_State.cpp Abstract_State.h
	g++ -c Abstract_State.cpp

Collision_Handler.o: Collision_Handler.cpp Collision_Handler.h
	g++ -c Collision_Handler.cpp

Game.o: Game.cpp Game.h Snake_Engine.h Abstract_State.h Menu_State.h
	g++ -c Game.cpp

Gameover_State.o: Gameover_State.cpp Gameover_State.h
	g++ -c Gameover_State.cpp

Highscore_State.o: Highscore_State.cpp Highscore_State.h
	g++ -c Highscore_State.cpp

Menu_State.o: Menu_State.cpp Menu_State.h
	g++ -c Menu_State.cpp

Multi_State.o: Multi_State.cpp Multi_State.h
	g++ -c Multi_State.cpp

Obstacles.o: Obstacles.cpp Obstacles.h
	g++ -c Obstacles.cpp

Single_State.o: Single_State.cpp Single_State.h
	g++ -c Single_State.cpp

Snake.o: Snake.cpp Snake.h
	g++ -c Snake.cpp

Snake_Engine.o: Snake_Engine.cpp Snake_Engine.h
	g++ -c Snake_Engine.cpp

Sprite.o: Sprite.cpp Sprite.h
	g++ -c Sprite.cpp

clean:
	rm -rf *.o Jake_The_Snake
run:
	./Jake_The_Snake

