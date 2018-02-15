/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2017 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"
#include "libretro.h"

#if defined(__LIBRETRO__)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* System dependent filesystem routines                                */

#include "SDL_error.h"
#include "SDL_filesystem.h"

/**
 * libretro_environment_cb needs to be implemented in the Libretro core
 */
extern short int __attribute__((weak)) libretro_environment_cb(unsigned, void*);

/*
 * Returns an absolute path in UTF-8 encoding to the application data directory.
 * NULL will be returned on error or when the platform doesn't implement this
 * functionality, call SDL_GetError() for more information.
 * The return path will be guaranteed to end with a path separator ('\' or '/').
 */
char *
SDL_GetBasePath(void)
{
  char *content_dir = 0;
  if(libretro_environment_cb) {
    libretro_environment_cb(RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY, &content_dir);
  } else {
    SDL_Unsupported();
  }
  return content_dir;
}

/*
 * Returns a UTF-8 string of the user directory in platform-dependent notation.
 * NULL if there's a problem (creating directory failed, etc.).
 * The return path will be guaranteed to end with a path separator ('\' or '/').
*/
char *
SDL_GetPrefPath(const char *org, const char *app)
{
  char *save_dir = NULL;
 if(libretro_environment_cb) {
    libretro_environment_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_dir);
  } else {
    SDL_Unsupported();
  }
  return save_dir;
}

#endif /* __LIBRETRO__ */

/* vi: set ts=4 sw=4 expandtab: */
