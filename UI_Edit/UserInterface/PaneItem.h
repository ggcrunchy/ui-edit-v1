#ifndef USER_INTERFACE_PANE_ITEM_H
#define USER_INTERFACE_PANE_ITEM_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int PaneItem_RemoveFromPane (Uint32 name);
int PaneItem_GetPane (Uint32 name, Uint32 * pane);
int PaneItem_GetFocusChainSlot (Uint32 name, Uint32 * slot);

SDL_bool PaneItem_IsFocusChainItem (Uint32 name);
SDL_bool PaneItem_IsLoaded (Uint32 name);
SDL_bool PaneItem_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_PANE_ITEM_H