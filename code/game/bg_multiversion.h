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
extern void MV_BuildAnimationMappingTable( void );
extern void MV_SetGamePlay( mvversion_t version );

/* Macros */
/* Using macros now to avoid function calls, as lcc doesn't support inline and function calls are rather "expensive" for qvms */
//extern void MV_MapAnimation( int *anim, qboolean revert );
#ifndef MV_MapAnimation
#define MV_MapAnimation( anim, revert ) \
{ \
	if ( !revert ) \
	{ /* 1.02 to 1.04 */\
		if ( anim & ANIM_TOGGLEBIT ) anim = animMappingTable_1_02_to_1_04[anim&~ANIM_TOGGLEBIT] | ANIM_TOGGLEBIT; \
		else						 anim = animMappingTable_1_02_to_1_04[anim]; \
	} \
	else \
	{ /* 1.04 to 1.02 */ \
		if ( anim & ANIM_TOGGLEBIT ) anim = animMappingTable_1_04_to_1_02[anim&~ANIM_TOGGLEBIT] | ANIM_TOGGLEBIT; \
		else						 anim = animMappingTable_1_04_to_1_02[anim]; \
	} \
}
#endif


//extern int MV_VersionMagic_g2ModelParts( int limbType );
#ifndef MV_VersionMagic_g2ModelParts
#ifdef JK2_GAME
	#define MV_VersionMagic_g2ModelParts( limbType ) ( jk2version != VERSION_1_02 ? limbType : (limbType >= G2_MODELPART_RHAND ? limbType-1 : limbType) )
#elif JK2_CGAME
	#define MV_VersionMagic_g2ModelParts( limbType ) ( jk2version != VERSION_1_02 ? limbType : (limbType >= G2_MODELPART_RHAND ? limbType+1 : limbType) )
#endif
#endif


//extern void MV_MapSaberBlocked( int *blocked, qboolean revert );
#ifndef MV_MapSaberBlocked
#define MV_MapSaberBlocked( blocked, revert ) \
{ \
	if ( !revert ) \
	{ /* 1.02 to 1.04 */ \
		if ( blocked > BLOCKED_NONE ) (blocked)++; \
	} \
	else \
	{ /* 1.04 to 1.02 */ \
		if ( blocked > BLOCKED_NONE ) (blocked)--; \
	} \
}
#endif
#endif // #ifndef JK2_UI
