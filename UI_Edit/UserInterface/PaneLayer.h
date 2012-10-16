#ifndef USER_INTERFACE_PANE_LAYER_H
#define USER_INTERFACE_PANE_LAYER_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int PaneLayer_Create (Uint32 * name);
int PaneLayer_Destroy (Uint32 name);
int PaneLayer_AddPane (Uint32 name, Uint32 pane, float fX, float fY, float fW, float fH);
int PaneLayer_SetTag (Uint32 name, wchar_t const * tag);
int PaneLayer_GetTag (Uint32 name, wchar_t * tag);
int PaneLayer_Untag (Uint32 name);
int PaneLayer_GetSlot (Uint32 name, Uint32 * slot);
int PaneLayer_GetPaneCount (Uint32 name, Uint32 * count);

SDL_bool PaneLayer_IsLoaded (Uint32 name);
SDL_bool PaneLayer_IsTagged (Uint32 name);
SDL_bool PaneLayer_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_PANE_LAYER_H
