/*
*
* Disasteroids - Copyright 2024 Stephen Branley.
*
* This file is part of Disasteroids.
*
* Disasteroids is free software: you can redistribute it and/or modify 
* it under the terms of the GNU General Public License as published by 
* the Free Software Foundation, either version 3 of the License, 
* or (at your option) any later version.
*
* Disasteroids is distributed in the hope that it will be useful, but 
* WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License 
* along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*
*/


#include "config.h"
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <winreg.h>
#else
#include <sys/stat.h>
#endif

static Config config;

void config_load()
{
  config.fullscreen = false;
  config.trailparticles = 50;
  config.installed = false;
  config.debug = false;
  config.startlives = 3;

  #ifdef _WIN32
  HKEY newKey;
  long retval;
  retval = RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FatHorseGames\\disasteroids", 0, KEY_READ, &newKey);
  if(retval == ERROR_SUCCESS)
  {
    long unsigned int lpSize = sizeof(int);
    retval = RegQueryValueExA(newKey, "trailparticles", 0, NULL, (BYTE*)(&config.trailparticles), &lpSize);
    retval = RegQueryValueExA(newKey, "fullscreen", 0, NULL, (BYTE*)(&config.fullscreen), &lpSize);
    retval = RegQueryValueExA(newKey, "startlives", 0, NULL, (BYTE*)(&config.startlives), &lpSize);
  }
  else
  {
    RegCloseKey(newKey);
  }
  #else // assume linux / BSD
  char* homedir = getenv("HOME");
  if(homedir == NULL)
    return;
  char barkdata[255] = "";
  strcat(barkdata, homedir);
  strcat(barkdata, "/.disasteroids/options");
  FILE* datafile = fopen(barkdata, "r");
  if(datafile != NULL)
  {
    char key[100] = "";
    int val = 0;
    while(fscanf(datafile, "%s%d", key, &val) == 2)
    {
      if(strcmp("TRAILPARTICLES", key) == 0)
        config.trailparticles = val;
      if(strcmp("FULLSCREEN", key) == 0)
        config.fullscreen = (bool)val;
      if(strcmp("STARTLIVES", key) == 0)
        config.startlives = val;
    }

    fclose(datafile);
  }

  // Test for installed resource file

  #ifdef INSTALLDIR
  FILE *testfile = fopen(INSTALLDIR "/Sprites/ball.png", "r");
  if(testfile != NULL)
  {
    config.installed = true;
    fclose(testfile);
  }
  #endif // INSTALLDIR

  #endif
}

int config_gettrailparticles()
{
  return config.trailparticles;
}

int config_getstartlives()
{
  return config.startlives;
}

bool config_getinstalled()
{
  return config.installed;
}

bool config_getdebug()
{
  return config.debug;
}

bool* config_getfullscreen()
{
  return &(config.fullscreen);
}

bool config_isfullscreen()
{
  return config.fullscreen;
}

void config_settrailparticles(int brickparticles)
{
  config.trailparticles = brickparticles;
}

void config_setfullscreen(bool fullscreen)
{
  config.fullscreen = fullscreen;
}

void config_setdebug(bool debug)
{
  config.debug = debug;
}

void config_save(void)
{
  #ifdef _WIN32
  HKEY newKey;
  long retval;
  retval = RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FatHorseGames\\disasteroids", 0, "", 0, KEY_WRITE, 0, &newKey, NULL);
  if(retval == ERROR_SUCCESS)
  {
    RegSetValueExA(newKey, "fullscreen", 0, REG_DWORD, (BYTE*)(&config.fullscreen), sizeof(int));
    RegCloseKey(newKey);
  }
  #else // Assume linux / BSD
  char* homedir = getenv("HOME");
  if(homedir == NULL)
    return;
  char barkdata[255] = "";
  strcat(barkdata, homedir);
  strcat(barkdata, "/.disasteroids");
  mkdir(barkdata, 0777);
  strcat(barkdata, "/options");
  remove(barkdata);
  FILE* optionsfile = fopen(barkdata, "w");
  fprintf(optionsfile, "FULLSCREEN %d\n", config.fullscreen);
  fprintf(optionsfile, "TRAILPARTICLES %d\n", config.trailparticles);
  fclose(optionsfile);
  #endif
}
