//bg_multiversion.c - This file contains multiversion variables and functions that are shared accross all modules...
#include "../game/bg_multiversion.h"

#ifdef JK2_GAME
#include "../game/g_local.h"
#elif JK2_CGAME
#include "../cgame/cg_local.h"
#elif JK2_UI
#include "../ui/ui_local.h"
#endif

int	jk2version	= VERSION_UNDEF;
int	jk2gameplay	= VERSION_UNDEF;

#ifndef JK2_UI // Not defined for UI, but still in bg_* for game and cgame
/* Additional functions */
extern stringID_table_t animTable_1_02[MAX_ANIMATIONS_1_02+1];
extern stringID_table_t animTable[MAX_ANIMATIONS+1];
//int animMappingTable_1_04_to_1_02[MAX_TOTALANIMATIONS];
//int animMappingTable_1_02_to_1_04[MAX_TOTALANIMATIONS_1_02];

#ifdef MV_GENERATE_ANIMATION_MAPPING_TABLE
void MV_DumpAnimationMappingTable( void )
{
	fileHandle_t dumpFile;
	char		 line[512];
	int			 i, j;

	trap_FS_FOpenFile("animMappingTableDump.txt", &dumpFile, FS_WRITE);
	if ( !dumpFile )
	{
		trap_FS_FCloseFile(dumpFile);
		return;
	}

	Q_strncpyz( line, "animNumber_1_02_t animMappingTable_1_04_to_1_02[MAX_TOTALANIMATIONS] = \n"
					"{\n", sizeof(line) );
	trap_FS_Write( line, strlen(line), dumpFile );

	for ( i = 0; i < MAX_TOTALANIMATIONS; i++ )
	{
		for ( j = 0; j < sizeof(animTable_1_02); j++ )
		{
			if ( animTable_1_02[j].id == animMappingTable_1_04_to_1_02[i] )
			{
				Q_strncpyz( line, va("	%s, // %s\n", animTable_1_02[j].name, animTable[i].name), sizeof(line) ); // It's only an assumption that animTable[i].name is the right 1.04 name. :/
				trap_FS_Write( line, strlen(line), dumpFile );
				break;
			}
		}
	}

	Q_strncpyz( line, "};\n\n", sizeof(line) );
	trap_FS_Write( line, strlen(line), dumpFile );

	Q_strncpyz( line, "animNumber_t animMappingTable_1_02_to_1_04[MAX_TOTALANIMATIONS_1_02] = \n"
					"{\n", sizeof(line) );
	trap_FS_Write( line, strlen(line), dumpFile );

	for ( i = 0; i < MAX_TOTALANIMATIONS_1_02; i++ )
	{
		for ( j = 0; j < sizeof(animTable); j++ )
		{
			if ( animTable[j].id == animMappingTable_1_02_to_1_04[i] )
			{
				Q_strncpyz( line, va("	%s, // %s\n", animTable[j].name, animTable_1_02[i].name), sizeof(line) ); // It's only an assumption that animTable_1_02[i].name is the right 1.02 name. :/
				trap_FS_Write( line, strlen(line), dumpFile );
				break;
			}
		}
	}

	Q_strncpyz( line, "};\n\n", sizeof(line) );
	trap_FS_Write( line, strlen(line), dumpFile );

	trap_FS_FCloseFile( dumpFile );
	return;
}
#endif // #ifdef MV_GENERATE_ANIMATION_MAPPING_TABLE

void MV_BuildAnimationMappingTable( void )
{
#ifdef MV_GENERATE_ANIMATION_MAPPING_TABLE
	qboolean found = qfalse;
	int i, j;

	// 1.04 to 1.02
	Com_Printf("Building animationMappingTable 1.04 to 1.02!\n");
	for ( i = 0; i < MAX_TOTALANIMATIONS; i++ )
	{
		found = qfalse;
		for ( j = 0; j < MAX_TOTALANIMATIONS_1_02; j++ )
		{
			if ( !Q_stricmp(va("%s_1_02", animTable[i].name), animTable_1_02[j].name) )
			{
				animMappingTable_1_04_to_1_02[animTable[i].id] = animTable_1_02[j].id;
				found = qtrue;
			}
		}
		if ( !found ) animMappingTable_1_04_to_1_02[i] = 0;
	}

#ifdef _DEBUG
	for ( i = 0; i < MAX_TOTALANIMATIONS; i++ )
	{
		Com_Printf("%s to %s\n", animTable[i].name, animTable_1_02[animMappingTable_1_04_to_1_02[i]].name);
	}
#endif
	
	// 1.02 to 1.04
	Com_Printf("Building animationMappingTable 1.02 to 1.04!\n");
	for ( i = 0; i < MAX_TOTALANIMATIONS_1_02; i++ )
	{
		found = qfalse;
		for ( j = 0; j < MAX_TOTALANIMATIONS; j++ )
		{
			if ( !Q_stricmp(animTable_1_02[i].name, va("%s_1_02", animTable[j].name)) )
			{
				animMappingTable_1_02_to_1_04[animTable_1_02[i].id] = animTable[j].id;
				found = qtrue;
			}
		}
		if ( !found ) animMappingTable_1_02_to_1_04[i] = 0;
	}

#ifdef _DEBUG
	for ( i = 0; i < MAX_TOTALANIMATIONS_1_02; i++ )
	{
		Com_Printf("%s to %s\n", animTable_1_02[i].name, animTable[animMappingTable_1_02_to_1_04[i]].name);
	}
#endif

	Com_Printf("AnimTable built!\n");
#endif // #ifdef MV_GENERATE_ANIMATION_MAPPING_TABLE
}

extern int forcePowerNeeded_1_02[NUM_FORCE_POWER_LEVELS][NUM_FORCE_POWERS];
extern int forcePowerNeeded_1_04[NUM_FORCE_POWER_LEVELS][NUM_FORCE_POWERS];
extern int (*forcePowerNeeded)[NUM_FORCE_POWERS];
void MV_SetGamePlay( mvversion_t version )
{ /* Set weaponData (ammo costs, ...), forcePowerNeeded (force costs) and the gameplay value according to the new version. */
#ifdef JK2_GAME
	gentity_t *saberent;
	gentity_t *ent;
	int		   i;
#endif // #ifdef JK2_GAME

	/* Find the settings for the version we want to switch to */
	switch ( version )
	{
		case VERSION_1_02:
			weaponData = weaponData_1_02;
			forcePowerNeeded = forcePowerNeeded_1_02;
			jk2gameplay = VERSION_1_02;
			break;
		case VERSION_1_03:
			weaponData = weaponData_1_03;
			forcePowerNeeded = forcePowerNeeded_1_04;
			jk2gameplay = VERSION_1_03;
			break;
		default:
		case VERSION_1_04:
			weaponData = weaponData_1_04;
			forcePowerNeeded = forcePowerNeeded_1_04;
			jk2gameplay = VERSION_1_04;
			break;
	}
	
#ifdef JK2_GAME
	/* Client specific changes */
	for ( i = 0; i < MAX_CLIENTS; i++ )
	{
		ent = &g_entities[i];

		if ( ent && ent->client && ent->inuse )
		{
			/* Adjust the size of the saberbox (8.0f in 1.02, 16.0f in 1.03 and 1.04). The define for SABER_BOX_SIZE already contains the check for the current version, so we can just use the same code for all 3 versions here. */
			saberent = &g_entities[ent->client->ps.saberEntityNum];
			if (saberent)
			{
				VectorSet( saberent->r.mins, -SABER_BOX_SIZE, -SABER_BOX_SIZE, -SABER_BOX_SIZE );
				VectorSet( saberent->r.maxs, SABER_BOX_SIZE, SABER_BOX_SIZE, SABER_BOX_SIZE );
			}
		}
	}
	
	trap_Cvar_Set( "mv_gameplay", va("%i", jk2gameplay) );
#endif // #ifdef JK2_GAME
}
#endif // #ifndef JK2_UI // Not defined for UI, but still in bg_* for game and cgame
