#ifndef USER_INTERFACE_CHECKBOX_H
#define USER_INTERFACE_CHECKBOX_H

#include <SDL/SDL_types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int Checkbox_Create (Uint32 * name);
int Checkbox_Check (Uint32 name, SDL_bool bCheck);
int Checkbox_ToggleCheck (Uint32 name);
int Checkbox_AllowClick (Uint32 name, SDL_bool bAllow);

SDL_bool Checkbox_IsClickAllowed (Uint32 name);
SDL_bool Checkbox_IsChecked (Uint32 name);
SDL_bool Checkbox_IsValid (Uint32 name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USER_INTERFACE_CHECKBOX_H
