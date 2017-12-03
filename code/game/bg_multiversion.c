//bg_multiversion.c - This file contains multiversion variables and functions that are shared accross all modules...
#include "../game/bg_multiversion.h"

#ifdef JK2_GAME
#include "../game/g_local.h"
#elif JK2_CGAME
#include "../cgame/cg_local.h"
#elif JK2_UI
#include "../ui/ui_local.h"
#endif

mvversion_t	jk2version      = VERSION_UNDEF;  // Current engine gameversion
mvversion_t	jk2gameplay     = VERSION_UNDEF;  // Current gameplay to apply
mvversion_t	jk2startversion = VERSION_UNDEF;  // Gameversion the engine had when the module was loaded

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
	
	for ( i = 0; i < MAX_CLIENTS; i++ ) if ( g_entities[i].client && g_entities[i].inuse ) ClientUserinfoChanged(i); // Update every client's userinfo to reflect the gameplay change (assigning the value to every player opens the possibility to intoduce per-player gameplay in the future)
#endif // #ifdef JK2_GAME
}
#endif // #ifndef JK2_UI // Not defined for UI, but still in bg_* for game and cgame

#ifndef JK2_GAME


// MVSDK: Multiversion Keys...
int Key_GetProtocolKey(mvversion_t version, int key16) {
	if (version != VERSION_1_02)
		return key16;

	// NOTE: We're not checking for K_CHAR_FLAG, as the UI module (at least under normal circumstances) does NOT give keys with K_CHAR_FLAG to the engine.

	switch (key16) {
		case A_TAB:
			return K_TAB;
		case A_ENTER:
			return K_ENTER;
		case A_ESCAPE:
			return K_ESCAPE;
		case A_SPACE:
			return K_SPACE;

		case A_BACKSPACE:
			return K_BACKSPACE;

			/*
			case A_COMMAND:
			return K_COMMAND;
			case A_CAPSLOCK:
			return K_CAPSLOCK;
			case A_POWER:
			return K_POWER;
			*/
		case A_PAUSE:
			return K_PAUSE;

			/*
			case A_UPARROW:
			return K_UPARROW;
			case A_DOWNARROW:
			return K_DOWNARROW;
			case A_LEFTARROW:
			return K_LEFTARROW;
			case A_RIGHTARROW:
			return K_RIGHTARROW;
			*/

		case A_ALT:
			return K_ALT;
		case A_CTRL:
			return K_CTRL;
		case A_SHIFT:
			return K_SHIFT;
		case A_INSERT:
			return K_INS;
		case A_DELETE:
			return K_DEL;
		case A_PAGE_DOWN:
			return K_PGDN;
		case A_PAGE_UP:
			return K_PGUP;
		case A_HOME:
			return K_HOME;
		case A_END:
			return K_END;

		case A_F1:
			return K_F1;
		case A_F2:
			return K_F2;
		case A_F3:
			return K_F3;
		case A_F4:
			return K_F4;
		case A_F5:
			return K_F5;
		case A_F6:
			return K_F6;
		case A_F7:
			return K_F7;
		case A_F8:
			return K_F8;
		case A_F9:
			return K_F9;
		case A_F10:
			return K_F10;
		case A_F11:
			return K_F11;
		case A_F12:
			return K_F12;
			/*
			case A_F13:
			return K_F13;
			case A_F14:
			return K_F14;
			case A_F15:
			return K_F15;
			*/

			/*
			case A_KP_HOME:
			return K_KP_HOME;
			case A_KP_UPARROW:
			return K_KP_UPARROW;
			case A_KP_PGUP:
			return K_KP_PGUP;
			case A_KP_LEFTARROW:
			return K_KP_LEFTARROW;
			*/
		case A_KP_5:
			return K_KP_5;
			/*
			case A_KP_RIGHTARROW:
			return K_KP_RIGHTARROW;
			case A_KP_END:
			return K_KP_END;
			case A_KP_DOWNARROW:
			return K_KP_DOWNARROW;
			case A_KP_PGDN:
			return K_KP_PGDN;
			*/
		case A_KP_ENTER:
			return K_KP_ENTER;
			/*
			case A_KP_INS:
			return K_KP_INS;
			case A_KP_DEL:
			return K_KP_DEL;
			*/
		case A_DIVIDE:
			return K_KP_SLASH;
		case A_KP_MINUS:
			return K_KP_MINUS;
		case A_KP_PLUS:
			return K_KP_PLUS;
			/*
			case A_KP_NUMBLOCK:
			return K_KP_NUMLOCK;
			*/
		case A_MULTIPLY:
			return K_KP_STAR;
			/*
			case A_KP_EQUALS:
			return K_KP_EQUALS;
			*/

		case A_MOUSE1:
			return K_MOUSE1;
		case A_MOUSE2:
			return K_MOUSE2;
		case A_MOUSE3:
			return K_MOUSE3;
		case A_MOUSE4:
			return K_MOUSE4;
		case A_MOUSE5:
			return K_MOUSE5;

		case A_MWHEELDOWN:
			return K_MWHEELDOWN;
		case A_MWHEELUP:
			return K_MWHEELUP;

		case A_JOY0:
			return K_JOY1;
		case A_JOY1:
			return K_JOY2;
		case A_JOY2:
			return K_JOY3;
		case A_JOY3:
			return K_JOY4;
		case A_JOY4:
			return K_JOY5;
		case A_JOY5:
			return K_JOY6;
		case A_JOY6:
			return K_JOY7;
		case A_JOY7:
			return K_JOY8;
		case A_JOY8:
			return K_JOY9;
		case A_JOY9:
			return K_JOY10;
		case A_JOY10:
			return K_JOY11;
		case A_JOY11:
			return K_JOY12;
		case A_JOY12:
			return K_JOY13;
		case A_JOY13:
			return K_JOY14;
		case A_JOY14:
			return K_JOY15;
		case A_JOY15:
			return K_JOY16;
		case A_JOY16:
			return K_JOY17;
		case A_JOY17:
			return K_JOY18;
		case A_JOY18:
			return K_JOY19;
		case A_JOY19:
			return K_JOY20;
		case A_JOY20:
			return K_JOY21;
		case A_JOY21:
			return K_JOY22;
		case A_JOY22:
			return K_JOY23;
		case A_JOY23:
			return K_JOY24;
		case A_JOY24:
			return K_JOY25;
		case A_JOY25:
			return K_JOY26;
		case A_JOY26:
			return K_JOY27;
		case A_JOY27:
			return K_JOY28;
		case A_JOY28:
			return K_JOY29;
		case A_JOY29:
			return K_JOY30;
		case A_JOY30:
			return K_JOY31;
		case A_JOY31:
			return K_JOY32;

		case A_AUX1:
			return K_AUX1;
		case A_AUX2:
			return K_AUX2;
		case A_AUX3:
			return K_AUX3;
		case A_AUX4:
			return K_AUX4;
		case A_AUX5:
			return K_AUX5;
		case A_AUX6:
			return K_AUX6;
		case A_AUX7:
			return K_AUX7;
		case A_AUX8:
			return K_AUX8;
		case A_AUX9:
			return K_AUX9;
		case A_AUX10:
			return K_AUX10;
		case A_AUX11:
			return K_AUX11;
		case A_AUX12:
			return K_AUX12;
		case A_AUX13:
			return K_AUX13;
		case A_AUX14:
			return K_AUX14;
		case A_AUX15:
			return K_AUX15;
		case A_AUX16:
			return K_AUX16;

		case MAX_KEYS:
			return K_LAST_KEY;
	}

	// Prevent double entries for 1.02 (Example: if 1.02 asks for K_CTRL it will be as if it asked for A_CTRL, if 1.02 asks for something that has the same number as A_CTRL it will count as A_CTRL, too: the CTRL key is handled twice. Solution: check if key15 would get altered by the inverse replacement).
	// -> Other way round when we are inside the qvm - Key_GetProtocolKey has to check for Key_GetProtocolKey15, NOT the other way round.
	if ( Key_GetProtocolKey15(version, key16) != key16 ) return -1;
	if ( key16 >= K_LAST_KEY ) return -1;

	return key16;
}

int Key_GetProtocolKey15(mvversion_t version, int key15) {
	int charFlag = (key15 & K_CHAR_FLAG);

	if (version != VERSION_1_02)
		return key15;

	key15 &= ~K_CHAR_FLAG; // FIXME: Can something like (K_SHIFT | K_CHAR_FLAG) actually end up here or could we just return any (key15 & K_CHAR_FLAG) without conversion?
						   // Normal jk2mv should only send actual characters as (key15 | K_CHAR_FLAG), so we could return. But let's still attempt the conversion, in case we're running on a different version of the engine...

	switch (key15) {
		case K_TAB:
			return A_TAB;
		case K_ENTER:
			return A_ENTER;
		case K_ESCAPE:
			return A_ESCAPE;
		case K_SPACE:
			return A_SPACE;

		case K_BACKSPACE:
			return A_BACKSPACE;

			/*
			case K_COMMAND:
			return A_COMMAND;
			case K_CAPSLOCK:
			return A_CAPSLOCK;
			case K_POWER:
			return A_POWER;
			*/
		case K_PAUSE:
			return A_PAUSE;

			/*
			case K_UPARROW:
			return A_UPARROW;
			case K_DOWNARROW:
			return A_DOWNARROW;
			case K_LEFTARROW:
			return A_LEFTARROW;
			case K_RIGHTARROW:
			return A_RIGHTARROW;
			*/

		case K_ALT:
			return A_ALT;
		case K_CTRL:
			return A_CTRL;
		case K_SHIFT:
			return A_SHIFT;
		case K_INS:
			return A_INSERT;
		case K_DEL:
			return A_DELETE;
		case K_PGDN:
			return A_PAGE_DOWN;
		case K_PGUP:
			return A_PAGE_UP;
		case K_HOME:
			return A_HOME;
		case K_END:
			return A_END;

		case K_F1:
			return A_F1;
		case K_F2:
			return A_F2;
		case K_F3:
			return A_F3;
		case K_F4:
			return A_F4;
		case K_F5:
			return A_F5;
		case K_F6:
			return A_F6;
		case K_F7:
			return A_F7;
		case K_F8:
			return A_F8;
		case K_F9:
			return A_F9;
		case K_F10:
			return A_F10;
		case K_F11:
			return A_F11;
		case K_F12:
			return A_F12;
			/*
			case K_F13:
			return A_F13;
			case K_F14:
			return A_F14;
			case K_F15:
			return A_F15;
			*/

			/*
			case K_KP_HOME:
			return A_KP_HOME;
			case K_KP_UPARROW:
			return A_KP_UPARROW;
			case K_KP_PGUP:
			return A_KP_PGUP;
			case K_KP_LEFTARROW:
			return A_KP_LEFTARROW;
			*/
		case K_KP_5:
			return A_KP_5;
			/*
			case K_KP_RIGHTARROW:
			return A_KP_RIGHTARROW;
			case K_KP_END:
			return A_KP_END;
			case K_KP_DOWNARROW:
			return A_KP_DOWNARROW;
			case K_KP_PGDN:
			return A_KP_PGDN;
			*/
		case K_KP_ENTER:
			return A_KP_ENTER;
			/*
			case K_KP_INS:
			return A_KP_INS;
			case K_KP_DEL:
			return A_KP_DEL;
			*/
		case K_KP_SLASH:
			return A_DIVIDE;
		case K_KP_MINUS:
			return A_KP_MINUS;
		case K_KP_PLUS:
			return A_KP_PLUS;
			/*
			case K_KP_NUMBLOCK:
			return A_KP_NUMLOCK;
			*/
		case K_KP_STAR:
			return A_MULTIPLY;
			/*
			case K_KP_EQUALS:
			return A_KP_EQUALS;
			*/

		case K_MOUSE1:
			return A_MOUSE1;
		case K_MOUSE2:
			return A_MOUSE2;
		case K_MOUSE3:
			return A_MOUSE3;
		case K_MOUSE4:
			return A_MOUSE4;
		case K_MOUSE5:
			return A_MOUSE5;

		case K_MWHEELDOWN:
			return A_MWHEELDOWN;
		case K_MWHEELUP:
			return A_MWHEELUP;

		case K_JOY1:
			return A_JOY0;
		case K_JOY2:
			return A_JOY1;
		case K_JOY3:
			return A_JOY2;
		case K_JOY4:
			return A_JOY3;
		case K_JOY5:
			return A_JOY4;
		case K_JOY6:
			return A_JOY5;
		case K_JOY7:
			return A_JOY6;
		case K_JOY8:
			return A_JOY7;
		case K_JOY9:
			return A_JOY8;
		case K_JOY10:
			return A_JOY9;
		case K_JOY11:
			return A_JOY10;
		case K_JOY12:
			return A_JOY11;
		case K_JOY13:
			return A_JOY12;
		case K_JOY14:
			return A_JOY13;
		case K_JOY15:
			return A_JOY14;
		case K_JOY16:
			return A_JOY15;
		case K_JOY17:
			return A_JOY16;
		case K_JOY18:
			return A_JOY17;
		case K_JOY19:
			return A_JOY18;
		case K_JOY20:
			return A_JOY19;
		case K_JOY21:
			return A_JOY20;
		case K_JOY22:
			return A_JOY21;
		case K_JOY23:
			return A_JOY22;
		case K_JOY24:
			return A_JOY23;
		case K_JOY25:
			return A_JOY24;
		case K_JOY26:
			return A_JOY25;
		case K_JOY27:
			return A_JOY26;
		case K_JOY28:
			return A_JOY27;
		case K_JOY29:
			return A_JOY28;
		case K_JOY30:
			return A_JOY29;
		case K_JOY31:
			return A_JOY30;
		case K_JOY32:
			return A_JOY31;

		case K_AUX1:
			return A_AUX1;
		case K_AUX2:
			return A_AUX2;
		case K_AUX3:
			return A_AUX3;
		case K_AUX4:
			return A_AUX4;
		case K_AUX5:
			return A_AUX5;
		case K_AUX6:
			return A_AUX6;
		case K_AUX7:
			return A_AUX7;
		case K_AUX8:
			return A_AUX8;
		case K_AUX9:
			return A_AUX9;
		case K_AUX10:
			return A_AUX10;
		case K_AUX11:
			return A_AUX11;
		case K_AUX12:
			return A_AUX12;
		case K_AUX13:
			return A_AUX13;
		case K_AUX14:
			return A_AUX14;
		case K_AUX15:
			return A_AUX15;
		case K_AUX16:
			return A_AUX16;

		case K_LAST_KEY:
			return MAX_KEYS;
	}

	// Prevent double entries for 1.02 (Example: if 1.02 asks for K_CTRL it will be as if it asked for A_CTRL, if 1.02 asks for something that has the same number as A_CTRL it will count as A_CTRL, too: the CTRL key is handled twice. Solution: check if key15 would get altered by the inverse replacement).
	// -> Other way round when we are inside the qvm - Key_GetProtocolKey has to check for Key_GetProtocolKey15, NOT the other way round.
	//if ( Key_GetProtocolKey(version, key15) != key15 ) return -1;

	if ( key15 >= K_LAST_KEY && !charFlag ) return -1;

	return (charFlag ? (key15 | K_CHAR_FLAG) : key15);
}
#endif // #ifndef JK2_GAME
