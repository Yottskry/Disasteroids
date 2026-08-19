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


#include "resources.h"

void loadResources(ResourceFactory* f, SDL_Renderer* renderer)
{
  af_loadanimation(f, renderer, "FatHorseGames.png", "logo", 100, 100);

  // And some sound
  
	af_loadsample(f, "barkanoid-getready.wav", "getready");
  af_loadsample(f, "barkanoid-brick.wav", "brick");
  af_loadsample(f, "barkanoid-brick-high.wav", "brick-high");
  af_loadsample(f, "barkanoid-brick-laser.wav", "brick-laser");
  af_loadsample(f, "barkanoid-bat.wav", "bat");
  af_loadsample(f, "barkanoid-dead.wav", "dead");
  af_loadsample(f, "barkanoid-1up.wav", "1up");
  af_loadsample(f, "barkanoid-warp.wav", "warp");
  af_loadsample(f, "barkanoid-hitcat.wav", "cat-hit");
  af_loadsample(f, "barkanoid-laser.wav", "laser");
  af_loadsample(f, "barkanoid-wormhole-in.wav", "wormhole-in");
  af_loadsample(f, "barkanoid-wormhole-out.wav", "wormhole-out");
  af_loadsample(f, "barkanoid-victory.wav", "victory");
  af_loadsample(f, "barkanoid-explosion.wav", "explosion");
  af_loadsample(f, "barkanoid-meow.wav", "meow");
  af_loadsample(f, "barkanoid-ow.wav", "ow");
  af_loadsample(f, "barkanoid-wallbounce.wav", "wallbounce");
}
