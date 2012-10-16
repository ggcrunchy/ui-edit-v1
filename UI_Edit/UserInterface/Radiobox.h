#ifndef USER_INTERFACE_RADIOBOX_H
#define USER_INTERFACE_RADIOBOX_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int Radiobox_Create (Uint32 * name);
int Radiobox_Setup (Uint32 name, Uint32 count, Uint32 choice);
int Radiobox_GetOptionCount (Uint32 name, Uint32 * count);
int Radiobox_SetChoice (Uint32 name, Uint32 choice);
int Radiobox_GetChoice (Uint32 name, Uint32 * choice);
int Radiobox_GetHeldOption (Uint32 name, Uint32 * option);
int Radiobox_GetInOption (Uint32 name, Uint32 * option);
int Radiobox_AllowClick (Uint32 name, SDL_bool bAllow);

void Radiobox_SignalCursorOverOption (Uint32 option);

SDL_bool Radiobox_IsClickAllowed (Uint32 name);
SDL_bool Radiobox_IsOptionValid (Uint32 name, Uint32 option);
SDL_bool Radiobox_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_RADIOBOX_H
