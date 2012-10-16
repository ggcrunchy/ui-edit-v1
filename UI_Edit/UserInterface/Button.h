#ifndef USER_INTERFACE_BUTTON_H
#define USER_INTERFACE_BUTTON_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int Button_Create (Uint32 * name);
int Button_AllowPush (Uint32 name, SDL_bool bAllow);

SDL_bool Button_IsPushAllowed (Uint32 name);
SDL_bool Button_IsPushed (Uint32 name);
SDL_bool Button_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_BUTTON_H
