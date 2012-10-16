#ifndef USER_INTERFACE_LISTBOX_H
#define USER_INTERFACE_LISTBOX_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int Listbox_Create (Uint32 * name);
int Listbox_GetItemCount (Uint32 name, Uint32 * count);
int Listbox_SetOffset (Uint32 name, Uint32 offset);
int Listbox_GetOffset (Uint32 name, Uint32 * offset);
int Listbox_SetCapacity (Uint32 name, Uint32 capacity);
int Listbox_GetCapacity (Uint32 name, Uint32 * capacity);
int Listbox_GetHeldItem (Uint32 name, Uint32 * item);
int Listbox_GetInItem (Uint32 name, Uint32 * item);
int Listbox_SetItemContext (Uint32 name, Uint32 item, Uint32 context);
int Listbox_GetItemContext (Uint32 name, Uint32 item, Uint32 * context);
int Listbox_SelectItem (Uint32 name, Uint32 item, SDL_bool bSelect);
int Listbox_SelectItemRange (Uint32 name, Uint32 start, Uint32 * numItems, SDL_bool bSelect);
int Listbox_AddItem (Uint32 name, Uint32 where);
int Listbox_RemoveItem (Uint32 name, Uint32 item);
int Listbox_RemoveItemRange (Uint32 name, Uint32 start, Uint32 * numItems);
int Listbox_AllowItemClick (Uint32 name, SDL_bool bAllow);
int Listbox_AllowDragOver (Uint32 name, SDL_bool bAllow);
int Listbox_SetFitBestItem (Uint32 name, Uint32 (*fitBestItem)(Uint32, float, float, void *)); 

void Listbox_SignalCursorOverItem (Uint32 item);

SDL_bool Listbox_IsItemClickAllowed (Uint32 name);
SDL_bool Listbox_IsDragOverAllowed (Uint32 name);
SDL_bool Listbox_IsItemSelected (Uint32 name, Uint32 item);
SDL_bool Listbox_IsItemValid (Uint32 name, Uint32 item, SDL_bool bAddSpot);
SDL_bool Listbox_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_LISTBOX_H
