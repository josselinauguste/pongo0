CC=gcc -Wall -ggdb3
TARGET=../build_linux/pongo

PACKAGES=clanCore-0.8 clanDisplay-0.8 clanApp-0.8 clanGL-0.8 clanGUI-0.8 clanGUIStyleSilver-0.8 clanNetwork-0.8 clanSound-0.8
LIBS=`pkg-config --libs $(PACKAGES)`

OBJS=	../build_linux/app.o \
		../build_linux/game.o \
        ../build_linux/gameentity.o \
		../build_linux/intromanager.o \
		../build_linux/log.o \
        ../build_linux/world.o \
		../build_linux/playersettings.o \
		../build_linux/settingsmanager.o \
		../build_linux/button.o \
		../build_linux/stylemanager.o \
		../build_linux/menugeneric.o \
		../build_linux/menuingame.o \
		../build_linux/menumanager.o \
        ../build_linux/player.o \
        ../build_linux/localplayer.o \
        ../build_linux/netplayer.o \
		../build_linux/humanplayer.o \
		../build_linux/aiplayer.o \
        ../build_linux/projectile.o \
        ../build_linux/localprojectile.o \
        ../build_linux/netprojectile.o \
		../build_linux/menumain.o \
		../build_linux/menumultiplayer.o \
		../build_linux/menuoptions.o \
		../build_linux/menuoptionsgraphiques.o \
		../build_linux/menuoptionssonores.o


all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

../build_linux/app.o: app.cpp app.hpp
	$(CC) -c -o $(@) app.cpp

../build_linux/gameentity.o: gameentity.cpp gameentity.hpp
	$(CC) -c -o $(@) gameentity.cpp

../build_linux/game.o: game.cpp
	$(CC) -c -o $(@) game.cpp

../build_linux/intromanager.o: intromanager.cpp
	$(CC) -c -o $(@) intromanager.cpp

../build_linux/menugeneric.o: menu/menugeneric.cpp menu/menugeneric.hpp
	$(CC) -c -o $(@) menu/menugeneric.cpp

../build_linux/menumanager.o: menu/menumanager.cpp menu/menumanager.hpp
	$(CC) -c -o $(@) menu/menumanager.cpp

../build_linux/menuingame.o: menu/menuingame.cpp menu/menuingame.hpp
	$(CC) -c -o $(@) menu/menuingame.cpp

../build_linux/menumain.o: menu/menumain.cpp menu/menumain.hpp
	$(CC) -c -o $(@) menu/menumain.cpp

../build_linux/menumultiplayer.o: menu/menumultiplayer.cpp menu/menumultiplayer.hpp
	$(CC) -c -o $(@) menu/menumultiplayer.cpp

../build_linux/menuoptionsgraphiques.o: menu/menuoptionsgraphiques.cpp menu/menuoptionsgraphiques.hpp
	$(CC) -c -o $(@) menu/menuoptionsgraphiques.cpp

../build_linux/menuoptions.o: menu/menuoptions.cpp menu/menuoptions.hpp
	$(CC) -c -o $(@) menu/menuoptions.cpp

../build_linux/menuoptionssonores.o: menu/menuoptionssonores.cpp menu/menuoptionssonores.hpp
	$(CC) -c -o $(@) menu/menuoptionssonores.cpp

../build_linux/settingsmanager.o: gamesettings/settingsmanager.cpp gamesettings/settingsmanager.hpp
	$(CC) -c -o $(@) gamesettings/settingsmanager.cpp

../build_linux/playersettings.o: gamesettings/playersettings.cpp gamesettings/playersettings.hpp
	$(CC) -c -o $(@) gamesettings/playersettings.cpp

../build_linux/log.o: log.cpp log.hpp
	$(CC) -c -o $(@) log.cpp

../build_linux/world.o: world.cpp world.hpp
	$(CC) -c -o $(@) world.cpp

../build_linux/button.o: guistyle/button.cpp guistyle/button.hpp
	$(CC) -c -o $(@) guistyle/button.cpp

../build_linux/stylemanager.o: guistyle/stylemanager.cpp guistyle/stylemanager.hpp
	$(CC) -c -o $(@) guistyle/stylemanager.cpp

../build_linux/player.o: player/player.cpp player/player.hpp
	$(CC) -c -o $(@) player/player.cpp

../build_linux/localplayer.o: player/localplayer.cpp player/localplayer.hpp
	$(CC) -c -o $(@) player/localplayer.cpp

../build_linux/netplayer.o: player/netplayer.cpp player/netplayer.hpp
	$(CC) -c -o $(@) player/netplayer.cpp

../build_linux/aiplayer.o: player/aiplayer.cpp player/aiplayer.hpp
	$(CC) -c -o $(@) player/aiplayer.cpp

../build_linux/humanplayer.o: player/humanplayer.cpp player/humanplayer.hpp
	$(CC) -c -o $(@) player/humanplayer.cpp

../build_linux/projectile.o: projectile/projectile.cpp projectile/projectile.hpp
	$(CC) -c -o $(@) projectile/projectile.cpp

../build_linux/localprojectile.o: projectile/localprojectile.cpp projectile/localprojectile.hpp
	$(CC) -c -o $(@) projectile/localprojectile.cpp

../build_linux/netprojectile.o: projectile/netprojectile.cpp projectile/netprojectile.hpp
	$(CC) -c -o $(@) projectile/netprojectile.cpp

clean:
	rm -rf ../build_linux/*
