//bg_multiversion.h - This file contains multiversion variables and functions that are shared accross all modules...
#include "../api/mvapi.h"
#include "../game/q_shared.h"
#include "../game/anims.h"

/* Variables */
extern int jk2version;
extern int jk2gameplay;

#ifndef JK2_UI // Not defined for UI, but still in bg_* for game and cgame
extern int animMappingTable_1_04_to_1_02[MAX_TOTALANIMATIONS];
extern int animMappingTable_1_02_to_1_04[MAX_TOTALANIMATIONS_1_02];
#endif // #ifndef JK2_UI

/* Functions */
#ifndef JK2_UI // Not defined for UI, but still in bg_* for game and cgame
#ifdef MV_GENERATE_ANIMATION_MAPPING_TABLE
extern void MV_DumpAnimationMappingTable( void );
#endif // #ifdef MV_GENERATE_ANIMATION_MAPPING_TABLE
extern int MV_VersionMagic_g2ModelParts( int limbType );
extern void MV_BuildAnimationMappingTable( void );
extern void MV_MapAnimation( int *anim, qboolean revert );
extern void MV_MapSaberBlocked( int *blocked, qboolean revert );
extern void MV_SetGamePlay( mvversion_t version );
#endif // #ifndef JK2_UI
