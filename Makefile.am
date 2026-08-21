# Automakes makefile template - this is processed by ./configure to create a Makefile
# This uses the same structure as a regular Makefile

# Automake can pull in files from subdirectories but build in the main directory.
AUTOMAKE_OPTIONS = subdir-objects
# Add the -D option to the INSTALL (/usr/bin/install) command to prevent it omitting directories
INSTALL = @INSTALL@ -D
# The build target (the exe name)
bin_PROGRAMS = asteroids
# Source files must be listed manually. No wildcards.
asteroids_SOURCES = src/asteroids.c src/app.h \
		src/arena.c src/arena.h \
		src/bounds.c src/bounds.h \
		src/config.c src/config.h \
		src/intro.c src/intro.h \
		src/menu.c src/menu.h \
		src/resourcefactory.c src/resourcefactory.h \
		src/scores.c src/scores.h \
		src/text.c src/text.h \
		src/vector.c src/vector.h \
		src/resources.c src/resources.h \
		src/ship.c src/ship.h \
		src/sparkle.h \
		src/rock.c src/rock.h \
		src/letters.c src/letters.h
# Additional platform-independent data files
FONTS = 	Fonts/Nordine.ttf \
		Fonts/Vectroid.otf \
		Fonts/Oxanium-Light.ttf
#LEVELS = 	Levels/level1.lvl \
#		Levels/level2.lvl \
#		Levels/level3.lvl \
#		Levels/level4.lvl \
#		Levels/level5.lvl \
#		Levels/level6.lvl \
#		Levels/level7.lvl \
#		Levels/level8.lvl \
#		Levels/level9.lvl \
#		Levels/level10.lvl \
#		Levels/level11.lvl \
#		Levels/level12.lvl \
#		Levels/level13.lvl \
#		Levels/level14.lvl \
#		Levels/level15.lvl \
#		Levels/level16.lvl \
#		Levels/level17.lvl \
#		Levels/level18.lvl \
#		Levels/level19.lvl \
#		Levels/level20.lvl \
#		Levels/level21.lvl \
#		Levels/level22.lvl \
#		Levels/level23.lvl \
#		Levels/level24.lvl \
#		Levels/level25.lvl
SOUNDS = 	Sounds/barkanoid-1up.wav \
		Sounds/barkanoid-bat.wav \
		Sounds/barkanoid-brick.wav \
		Sounds/barkanoid-brick-high.wav \
		Sounds/barkanoid-brick-laser.wav \
		Sounds/barkanoid-dead.wav \
		Sounds/barkanoid-explosion.wav \
		Sounds/barkanoid-getready.wav \
		Sounds/barkanoid-hitcat.wav \
		Sounds/barkanoidiii.mp3 \
		Sounds/barkanoid-laser.wav \
		Sounds/barkanoid-victory.wav \
		Sounds/barkanoid-warp.wav \
		Sounds/barkanoid-wormhole-in.wav \
		Sounds/barkanoid-wormhole-out.wav \
		Sounds/barkanoid-meow.wav \
		Sounds/barkanoid-ow.wav \
		Sounds/barkanoid-wallbounce.wav
Sprites =	Sprites/FatHorseGames.png 

# nobase tells it to include the prefixing directory names in the destination (i.e. not just dump the files into the single data folder)
nobase_dist_pkgdata_DATA = $(FONTS) $(SOUNDS) $(SPRITES)

# Flags passed to the C Preprocessor; in this case the install directory
# The game tests if an installed file exists and then sets a variable (see config.c)
AM_CPPFLAGS = -DINSTALLDIR=\"$(datadir)/@PACKAGE@\"
#AM_LDFLAGS = -fsanitize=leak -static-libasan
