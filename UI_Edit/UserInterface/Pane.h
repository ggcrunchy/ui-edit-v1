#ifndef USER_INTERFACE_PANE_H
#define USER_INTERFACE_PANE_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int Pane_Create (Uint32 * name);
int Pane_AddItem (Uint32 name, Uint32 item, float fX, float fY, float fW, float fH);
int Pane_RemoveFromLayer (Uint32 name);
int Pane_GetLayer (Uint32 name, Uint32 * layer);
int Pane_GetItemCount (Uint32 name, Uint32 * count);
int Pane_RemoveFocusChainItem (Uint32 name, Uint32 slot);
int Pane_ClearFocusChain (Uint32 name);
int Pane_LoadFocusChain (Uint32 name, Uint32 const * items, Uint32 count, SDL_bool bBackOnFocusDelete);
int Pane_SwapFocusChainItems (Uint32 name, Uint32 one, Uint32 two);
int Pane_GetFocusChainItem (Uint32 name, Uint32 slot, Uint32 * item);
int Pane_GetFocusChainItemCount (Uint32 name, Uint32 * count);
int Pane_SetFocusSlot (Uint32 name, Uint32 slot);
int Pane_GetFocusSlot (Uint32 name, Uint32 * slot);
int Pane_GetFocusPriorSlot (Uint32 name, Uint32 * slot);
int Pane_GetFocusNextSlot (Uint32 name, Uint32 * slot);
int Pane_AllowDrag (Uint32 name, SDL_bool bAllow);
int Pane_SetFitBestXY (Uint32 name, void (*fitBestXY)(Uint32, float, float, void *, float *, float *));

SDL_bool Pane_IsCaught (Uint32 name);
SDL_bool Pane_IsDragAllowed (Uint32 name);
SDL_bool Pane_IsFocusChainSlotValid (Uint32 name, Uint32 slot);
SDL_bool Pane_IsLoaded (Uint32 name);
SDL_bool Pane_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_PANE_H
