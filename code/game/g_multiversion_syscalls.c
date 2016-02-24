//g_multiversion_syscalls.c

/*
This file contains functions with the names of the original trap_* methods.
These functions call the multiversion functions before calling the (renamed) original functions.

I didn't intend to "rename & replace" all the trap_* functions,
but given that they're different depending on whether we build qvms or native libraries I am going with this approach now.
*/
#include "g_local.h"
#include "g_multiversion_syscalls.h"

#ifdef MV_SYSCALL_WRAPPER
void trap_Printf( const char *fmt )
{
	MV_VersionMagic( qtrue );
	trap_Printf_real( fmt );
	MV_VersionMagic( qfalse );
}

void trap_Error( const char *fmt )
{
	MV_VersionMagic( qtrue );
	trap_Error_real( fmt );
	MV_VersionMagic( qfalse );
}

int trap_Milliseconds( void )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_Milliseconds_real();
	MV_VersionMagic( qfalse );
	return retVal; 
}

void trap_Cvar_Register( vmCvar_t *cvar, const char *var_name, const char *value, int flags )
{
	MV_VersionMagic( qtrue );
	trap_Cvar_Register_real( cvar, var_name, value, flags );
	MV_VersionMagic( qfalse );
}

void trap_Cvar_Update( vmCvar_t *cvar )
{
	MV_VersionMagic( qtrue );
	trap_Cvar_Update_real( cvar );
	MV_VersionMagic( qfalse );
}

void trap_Cvar_Set( const char *var_name, const char *value )
{
	MV_VersionMagic( qtrue );
	trap_Cvar_Set_real( var_name, value );
	MV_VersionMagic( qfalse );
}

int trap_Cvar_VariableIntegerValue( const char *var_name )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_Cvar_VariableIntegerValue_real( var_name );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize )
{
	MV_VersionMagic( qtrue );
	trap_Cvar_VariableStringBuffer_real( var_name, buffer, bufsize );
	MV_VersionMagic( qfalse );
}

int trap_Argc( void )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_Argc_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_Argv( int n, char *buffer, int bufferLength )
{
	MV_VersionMagic( qtrue );
	trap_Argv_real( n, buffer, bufferLength );
	MV_VersionMagic( qfalse );
}

int trap_FS_FOpenFile( const char *qpath, fileHandle_t *f, fsMode_t mode )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_FS_FOpenFile_real( qpath, f, mode );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_FS_Read( void *buffer, int len, fileHandle_t f )
{
	MV_VersionMagic( qtrue );
	trap_FS_Read_real( buffer, len, f );
	MV_VersionMagic( qfalse );
}

void trap_FS_Write( const void *buffer, int len, fileHandle_t f )
{
	MV_VersionMagic( qtrue );
	trap_FS_Write_real( buffer, len, f );
	MV_VersionMagic( qfalse );
}

void trap_FS_FCloseFile( fileHandle_t f )
{
	MV_VersionMagic( qtrue );
	trap_FS_FCloseFile_real( f );
	MV_VersionMagic( qfalse );
}

void trap_SendConsoleCommand( int exec_when, const char *text )
{
	MV_VersionMagic( qtrue );
	trap_SendConsoleCommand_real( exec_when, text );
	MV_VersionMagic( qfalse );
}

void trap_LocateGameData( gentity_t *gEnts, int numGEntities, int sizeofGEntity_t,
					 playerState_t *clients, int sizeofGClient )
{
	MV_VersionMagic( qtrue );
	trap_LocateGameData_real( gEnts, numGEntities, sizeofGEntity_t, clients, sizeofGClient );
	MV_VersionMagic( qfalse );
}

void trap_DropClient( int clientNum, const char *reason )
{
	MV_VersionMagic( qtrue );
	trap_DropClient_real( clientNum, reason );
	MV_VersionMagic( qfalse );
}

void trap_SendServerCommand( int clientNum, const char *text )
{
	MV_VersionMagic( qtrue );
	trap_SendServerCommand_real( clientNum, text );
	MV_VersionMagic( qfalse );
}

void trap_SetConfigstring( int num, const char *string )
{
	MV_VersionMagic( qtrue );
	trap_SetConfigstring_real( num, string );
	MV_VersionMagic( qfalse );
}

void trap_GetConfigstring( int num, char *buffer, int bufferSize )
{
	MV_VersionMagic( qtrue );
	trap_GetConfigstring_real( num, buffer, bufferSize );
	MV_VersionMagic( qfalse );
}

void trap_GetUserinfo( int num, char *buffer, int bufferSize )
{
	MV_VersionMagic( qtrue );
	trap_GetUserinfo_real( num, buffer, bufferSize );
	MV_VersionMagic( qfalse );
}

void trap_SetUserinfo( int num, const char *buffer )
{
	MV_VersionMagic( qtrue );
	trap_SetUserinfo_real( num, buffer );
	MV_VersionMagic( qfalse );
}

void trap_GetServerinfo( char *buffer, int bufferSize )
{
	MV_VersionMagic( qtrue );
	trap_GetServerinfo_real( buffer, bufferSize );
	MV_VersionMagic( qfalse );
}

void trap_SetBrushModel( gentity_t *ent, const char *name )
{
	MV_VersionMagic( qtrue );
	trap_SetBrushModel_real( ent, name );
	MV_VersionMagic( qfalse );
}

void trap_Trace( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask )
{
	MV_VersionMagic( qtrue );
	trap_Trace_real( results, start, mins, maxs, end, passEntityNum, contentmask );
	MV_VersionMagic( qfalse );
}

int trap_PointContents( const vec3_t point, int passEntityNum )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_PointContents_real( point, passEntityNum );
	MV_VersionMagic( qfalse );
	return retVal;
}


qboolean trap_InPVS( const vec3_t p1, const vec3_t p2 )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_InPVS_real( p1, p2 );
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_InPVSIgnorePortals( const vec3_t p1, const vec3_t p2 )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_InPVSIgnorePortals_real( p1, p2 );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_AdjustAreaPortalState( gentity_t *ent, qboolean open )
{
	MV_VersionMagic( qtrue );
	trap_AdjustAreaPortalState_real( ent, open );
	MV_VersionMagic( qfalse );
}

qboolean trap_AreasConnected( int area1, int area2 )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AreasConnected_real( area1, area2 );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_LinkEntity( gentity_t *ent )
{
	MV_VersionMagic( qtrue );
	trap_LinkEntity_real( ent );
	MV_VersionMagic( qfalse );
}

void trap_UnlinkEntity( gentity_t *ent )
{
	MV_VersionMagic( qtrue );
	trap_UnlinkEntity_real( ent );
	MV_VersionMagic( qfalse );
}

int trap_EntitiesInBox( const vec3_t mins, const vec3_t maxs, int *list, int maxcount )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_EntitiesInBox_real( mins, maxs, list, maxcount );
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_EntityContact( const vec3_t mins, const vec3_t maxs, const gentity_t *ent )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_EntityContact_real( mins, maxs, ent );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotAllocateClient( void )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotAllocateClient_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotFreeClient( int clientNum )
{
	MV_VersionMagic( qtrue );
	trap_BotFreeClient_real( clientNum );
	MV_VersionMagic( qfalse );
}

void trap_GetUsercmd( int clientNum, usercmd_t *cmd )
{
	MV_VersionMagic( qtrue );
	trap_GetUsercmd_real( clientNum, cmd );
	MV_VersionMagic( qfalse );
}

qboolean trap_GetEntityToken( char *buffer, int bufferSize )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_GetEntityToken_real( buffer, bufferSize );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_FS_GetFileList(  const char *path, const char *extension, char *listbuf, int bufsize )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_FS_GetFileList_real( path, extension, listbuf, bufsize );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_DebugPolygonCreate(int color, int numPoints, vec3_t *points)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_DebugPolygonCreate_real( color, numPoints, points );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_DebugPolygonDelete(int id)
{
	MV_VersionMagic( qtrue );
	trap_DebugPolygonDelete_real( id );
	MV_VersionMagic( qfalse );
}

int trap_RealTime( qtime_t *qtime )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_RealTime_real( qtime );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_SnapVector( float *v )
{
	MV_VersionMagic( qtrue );
	trap_SnapVector_real( v );
	MV_VersionMagic( qfalse );
}

void trap_TraceCapsule( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask )
{
	MV_VersionMagic( qtrue );
	trap_TraceCapsule_real( results, start, mins, maxs, end, passEntityNum, contentmask );
	MV_VersionMagic( qfalse );
}

qboolean trap_EntityContactCapsule( const vec3_t mins, const vec3_t maxs, const gentity_t *ent )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_EntityContactCapsule_real( mins, maxs, ent );
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_SP_RegisterServer( const char *package ) 
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_SP_RegisterServer_real( package );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_SP_GetStringTextString(const char *text, char *buffer, int bufferLength)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_SP_GetStringTextString_real( text, buffer, bufferLength );
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_ROFF_Clean( void ) 
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_ROFF_Clean_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_ROFF_UpdateEntities( void ) 
{
	MV_VersionMagic( qtrue );
	trap_ROFF_UpdateEntities_real();
	MV_VersionMagic( qfalse );
}

int trap_ROFF_Cache( char *file ) 
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_ROFF_Cache_real( file );
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_ROFF_Play( int entID, int roffID, qboolean doTranslation ) 
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_ROFF_Play_real( entID, roffID, doTranslation );
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_ROFF_Purge_Ent( int entID ) 
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_ROFF_Purge_Ent_real( entID );
	MV_VersionMagic( qfalse );
	return retVal;
}

// BotLib traps start here
int trap_BotLibSetup( void )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibSetup_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotLibShutdown( void )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibShutdown_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotLibVarSet(char *var_name, char *value)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibVarSet_real( var_name, value );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotLibVarGet(char *var_name, char *value, int size)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibVarGet_real( var_name, value, size );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotLibDefine(char *string)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibDefine_real( string );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotLibStartFrame(float time)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibStartFrame_real( time );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotLibLoadMap(const char *mapname)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibLoadMap_real( mapname );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotLibUpdateEntity(int ent, void /* struct bot_updateentity_s */ *bue)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibUpdateEntity_real( ent, bue );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotLibTest(int parm0, char *parm1, vec3_t parm2, vec3_t parm3)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLibTest_real( parm0, parm1, parm2, parm3 );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotGetSnapshotEntity( int clientNum, int sequence )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotGetSnapshotEntity_real( clientNum, sequence );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotGetServerCommand(int clientNum, char *message, int size)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotGetServerCommand_real( clientNum, message, size );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotUserCommand(int clientNum, usercmd_t *ucmd)
{
	MV_VersionMagic( qtrue );
	trap_BotUserCommand_real( clientNum, ucmd );
	MV_VersionMagic( qfalse );
}

void trap_AAS_EntityInfo(int entnum, void /* struct aas_entityinfo_s */ *info)
{
	MV_VersionMagic( qtrue );
	trap_AAS_EntityInfo_real( entnum, info );
	MV_VersionMagic( qfalse );
}

int trap_AAS_Initialized(void)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_Initialized_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_AAS_PresenceTypeBoundingBox(int presencetype, vec3_t mins, vec3_t maxs)
{
	MV_VersionMagic( qtrue );
	trap_AAS_PresenceTypeBoundingBox_real( presencetype, mins, maxs );
	MV_VersionMagic( qfalse );
}

float trap_AAS_Time(void)
{
	float retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_Time_real();
	MV_VersionMagic( qfalse );
	return retVal; 
}

int trap_AAS_PointAreaNum(vec3_t point)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_PointAreaNum_real( point );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_PointReachabilityAreaIndex(vec3_t point)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_PointReachabilityAreaIndex_real( point );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_TraceAreas(vec3_t start, vec3_t end, int *areas, vec3_t *points, int maxareas)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_TraceAreas_real( start, end, areas, points, maxareas );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_BBoxAreas(vec3_t absmins, vec3_t absmaxs, int *areas, int maxareas)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_BBoxAreas_real( absmins, absmaxs, areas, maxareas );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_AreaInfo( int areanum, void /* struct aas_areainfo_s */ *info )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_AreaInfo_real( areanum, info );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_PointContents(vec3_t point)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_PointContents_real( point );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_NextBSPEntity(int ent)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_NextBSPEntity_real( ent );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_ValueForBSPEpairKey(int ent, char *key, char *value, int size)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_ValueForBSPEpairKey_real( ent, key, value, size );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_VectorForBSPEpairKey(int ent, char *key, vec3_t v)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_VectorForBSPEpairKey_real( ent, key, v );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_FloatForBSPEpairKey(int ent, char *key, float *value)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_FloatForBSPEpairKey_real( ent, key, value );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_IntForBSPEpairKey(int ent, char *key, int *value)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_IntForBSPEpairKey_real( ent, key, value );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_AreaReachability(int areanum)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_AreaReachability_real( areanum );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_AreaTravelTimeToGoalArea(int areanum, vec3_t origin, int goalareanum, int travelflags)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_AreaTravelTimeToGoalArea_real( areanum, origin, goalareanum, travelflags );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_EnableRoutingArea( int areanum, int enable )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_EnableRoutingArea_real( areanum, enable );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_PredictRoute(void /*struct aas_predictroute_s*/ *route, int areanum, vec3_t origin,
							int goalareanum, int travelflags, int maxareas, int maxtime,
							int stopevent, int stopcontents, int stoptfl, int stopareanum)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_PredictRoute_real( route, areanum, origin, goalareanum, travelflags, maxareas, maxtime, stopevent, stopcontents, stoptfl, stopareanum );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_AlternativeRouteGoals(vec3_t start, int startareanum, vec3_t goal, int goalareanum, int travelflags,
										void /*struct aas_altroutegoal_s*/ *altroutegoals, int maxaltroutegoals,
										int type)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_AlternativeRouteGoals_real( start, startareanum, goal, goalareanum, travelflags, altroutegoals, maxaltroutegoals, type );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_Swimming(vec3_t origin)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_Swimming_real( origin );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_AAS_PredictClientMovement(void /* struct aas_clientmove_s */ *move, int entnum, vec3_t origin, int presencetype, int onground, vec3_t velocity, vec3_t cmdmove, int cmdframes, int maxframes, float frametime, int stopevent, int stopareanum, int visualize)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_AAS_PredictClientMovement_real( move, entnum, origin, presencetype, onground, velocity, cmdmove, cmdframes, maxframes, frametime, stopevent, stopareanum, visualize );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_EA_Say(int client, char *str)
{
	MV_VersionMagic( qtrue );
	trap_EA_Say_real( client, str );
	MV_VersionMagic( qfalse );
}

void trap_EA_SayTeam(int client, char *str)
{
	MV_VersionMagic( qtrue );
	trap_EA_SayTeam_real( client, str );
	MV_VersionMagic( qfalse );
}

void trap_EA_Command(int client, char *command)
{
	MV_VersionMagic( qtrue );
	trap_EA_Command_real( client, command );
	MV_VersionMagic( qfalse );
}

void trap_EA_Action(int client, int action)
{
	MV_VersionMagic( qtrue );
	trap_EA_Action_real( client, action );
	MV_VersionMagic( qfalse );
}

void trap_EA_Gesture(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_Gesture_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_Talk(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_Talk_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_Attack(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_Attack_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_Alt_Attack(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_Alt_Attack_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_ForcePower(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_ForcePower_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_Use(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_Use_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_Respawn(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_Respawn_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_Crouch(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_Crouch_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_MoveUp(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_MoveUp_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_MoveDown(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_MoveDown_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_MoveForward(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_MoveForward_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_MoveBack(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_MoveBack_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_MoveLeft(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_MoveLeft_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_MoveRight(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_MoveRight_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_SelectWeapon(int client, int weapon)
{
	MV_VersionMagic( qtrue );
	trap_EA_SelectWeapon_real( client, weapon );
	MV_VersionMagic( qfalse );
}

void trap_EA_Jump(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_Jump_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_DelayedJump(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_DelayedJump_real( client );
	MV_VersionMagic( qfalse );
}

void trap_EA_Move(int client, vec3_t dir, float speed)
{
	MV_VersionMagic( qtrue );
	trap_EA_Move_real( client, dir, speed );
	MV_VersionMagic( qfalse );
}

void trap_EA_View(int client, vec3_t viewangles)
{
	MV_VersionMagic( qtrue );
	trap_EA_View_real( client, viewangles );
	MV_VersionMagic( qfalse );
}

void trap_EA_EndRegular(int client, float thinktime)
{
	MV_VersionMagic( qtrue );
	trap_EA_EndRegular_real( client, thinktime );
	MV_VersionMagic( qfalse );
}

void trap_EA_GetInput(int client, float thinktime, void /* struct bot_input_s */ *input)
{
	MV_VersionMagic( qtrue );
	trap_EA_GetInput_real( client, thinktime, input );
	MV_VersionMagic( qfalse );
}

void trap_EA_ResetInput(int client)
{
	MV_VersionMagic( qtrue );
	trap_EA_ResetInput_real( client );
	MV_VersionMagic( qfalse );
}

int trap_BotLoadCharacter(char *charfile, float skill)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLoadCharacter_real( charfile, skill);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotFreeCharacter(int character)
{
	MV_VersionMagic( qtrue );
	trap_BotFreeCharacter_real( character );
	MV_VersionMagic( qfalse );
}

float trap_Characteristic_Float(int character, int index)
{
	float retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_Characteristic_Float_real( character, index );
	MV_VersionMagic( qfalse );
	return retVal;
}

float trap_Characteristic_BFloat(int character, int index, float min, float max)
{
	float retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_Characteristic_BFloat_real( character, index, min, max );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_Characteristic_Integer(int character, int index)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_Characteristic_Integer_real( character, index );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_Characteristic_BInteger(int character, int index, int min, int max)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_Characteristic_BInteger_real( character, index, min, max );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_Characteristic_String(int character, int index, char *buf, int size)
{
	MV_VersionMagic( qtrue );
	trap_Characteristic_String_real( character, index, buf, size );
	MV_VersionMagic( qfalse );
}

int trap_BotAllocChatState(void)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotAllocChatState_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotFreeChatState(int handle)
{
	MV_VersionMagic( qtrue );
	trap_BotFreeChatState_real( handle );
	MV_VersionMagic( qfalse );
}

void trap_BotQueueConsoleMessage(int chatstate, int type, char *message)
{
	MV_VersionMagic( qtrue );
	trap_BotQueueConsoleMessage_real( chatstate, type, message );
	MV_VersionMagic( qfalse );
}

void trap_BotRemoveConsoleMessage(int chatstate, int handle)
{
	MV_VersionMagic( qtrue );
	trap_BotRemoveConsoleMessage_real( chatstate, handle );
	MV_VersionMagic( qfalse );
}

int trap_BotNextConsoleMessage(int chatstate, void /* struct bot_consolemessage_s */ *cm)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotNextConsoleMessage_real( chatstate, cm );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotNumConsoleMessages(int chatstate)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotNumConsoleMessages_real( chatstate );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotInitialChat(int chatstate, char *type, int mcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 )
{
	MV_VersionMagic( qtrue );
	trap_BotInitialChat_real( chatstate, type, mcontext, var0, var1, var2, var3, var4, var5, var6, var7 );
	MV_VersionMagic( qfalse );
}

int trap_BotNumInitialChats(int chatstate, char *type)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotNumInitialChats_real( chatstate, type );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotReplyChat(int chatstate, char *message, int mcontext, int vcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotReplyChat_real( chatstate, message, mcontext, vcontext, var0, var1, var2, var3, var4, var5, var6, var7 );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotChatLength(int chatstate)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotChatLength_real( chatstate );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotEnterChat(int chatstate, int client, int sendto)
{
	MV_VersionMagic( qtrue );
	trap_BotEnterChat_real( chatstate, client, sendto );
	MV_VersionMagic( qfalse );
}

void trap_BotGetChatMessage(int chatstate, char *buf, int size)
{
	MV_VersionMagic( qtrue );
	trap_BotGetChatMessage_real( chatstate, buf, size);
	MV_VersionMagic( qfalse );
}

int trap_StringContains(char *str1, char *str2, int casesensitive)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_StringContains_real( str1, str2, casesensitive );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotFindMatch(char *str, void /* struct bot_match_s */ *match, unsigned long int context)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotFindMatch_real( str, match, context );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotMatchVariable(void /* struct bot_match_s */ *match, int variable, char *buf, int size)
{
	MV_VersionMagic( qtrue );
	trap_BotMatchVariable_real( match, variable, buf, size );
	MV_VersionMagic( qfalse );
}

void trap_UnifyWhiteSpaces(char *string)
{
	MV_VersionMagic( qtrue );
	trap_UnifyWhiteSpaces_real( string );
	MV_VersionMagic( qfalse );
}

void trap_BotReplaceSynonyms(char *string, unsigned long int context)
{
	MV_VersionMagic( qtrue );
	trap_BotReplaceSynonyms_real( string, context );
	MV_VersionMagic( qfalse );
}

int trap_BotLoadChatFile(int chatstate, char *chatfile, char *chatname)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLoadChatFile_real( chatstate, chatfile, chatname );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotSetChatGender(int chatstate, int gender)
{
	MV_VersionMagic( qtrue );
	trap_BotSetChatGender_real( chatstate, gender );
	MV_VersionMagic( qfalse );
}

void trap_BotSetChatName(int chatstate, char *name, int client)
{
	MV_VersionMagic( qtrue );
	trap_BotSetChatName_real( chatstate, name, client );
	MV_VersionMagic( qfalse );
}

void trap_BotResetGoalState(int goalstate)
{
	MV_VersionMagic( qtrue );
	trap_BotResetGoalState_real( goalstate );
	MV_VersionMagic( qfalse );
}

void trap_BotResetAvoidGoals(int goalstate)
{
	MV_VersionMagic( qtrue );
	trap_BotResetAvoidGoals_real( goalstate );
	MV_VersionMagic( qfalse );
}

void trap_BotRemoveFromAvoidGoals(int goalstate, int number)
{
	MV_VersionMagic( qtrue );
	trap_BotRemoveFromAvoidGoals_real( goalstate, number);
	MV_VersionMagic( qfalse );
}

void trap_BotPushGoal(int goalstate, void /* struct bot_goal_s */ *goal)
{
	MV_VersionMagic( qtrue );
	trap_BotPushGoal_real( goalstate, goal );
	MV_VersionMagic( qfalse );
}

void trap_BotPopGoal(int goalstate)
{
	MV_VersionMagic( qtrue );
	trap_BotPopGoal_real( goalstate );
	MV_VersionMagic( qfalse );
}

void trap_BotEmptyGoalStack(int goalstate)
{
	MV_VersionMagic( qtrue );
	trap_BotEmptyGoalStack_real( goalstate );
	MV_VersionMagic( qfalse );
}

void trap_BotDumpAvoidGoals(int goalstate)
{
	MV_VersionMagic( qtrue );
	trap_BotDumpAvoidGoals_real( goalstate );
	MV_VersionMagic( qfalse );
}

void trap_BotDumpGoalStack(int goalstate)
{
	MV_VersionMagic( qtrue );
	trap_BotDumpGoalStack_real( goalstate );
	MV_VersionMagic( qfalse );
}

void trap_BotGoalName(int number, char *name, int size)
{
	MV_VersionMagic( qtrue );
	trap_BotGoalName_real( number, name, size );
	MV_VersionMagic( qfalse );
}

int trap_BotGetTopGoal(int goalstate, void /* struct bot_goal_s */ *goal)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotGetTopGoal_real( goalstate, goal );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotGetSecondGoal(int goalstate, void /* struct bot_goal_s */ *goal)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotGetSecondGoal_real( goalstate, goal );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotChooseLTGItem(int goalstate, vec3_t origin, int *inventory, int travelflags)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotChooseLTGItem_real( goalstate, origin, inventory, travelflags );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotChooseNBGItem(int goalstate, vec3_t origin, int *inventory, int travelflags, void /* struct bot_goal_s */ *ltg, float maxtime)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotChooseNBGItem_real( goalstate, origin, inventory, travelflags, ltg, maxtime );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotTouchingGoal(vec3_t origin, void /* struct bot_goal_s */ *goal)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotTouchingGoal_real( origin, goal );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotItemGoalInVisButNotVisible(int viewer, vec3_t eye, vec3_t viewangles, void /* struct bot_goal_s */ *goal)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotItemGoalInVisButNotVisible_real( viewer, eye, viewangles, goal );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotGetLevelItemGoal(int index, char *classname, void /* struct bot_goal_s */ *goal)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotGetLevelItemGoal_real( index, classname, goal );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotGetNextCampSpotGoal(int num, void /* struct bot_goal_s */ *goal)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotGetNextCampSpotGoal_real( num, goal );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotGetMapLocationGoal(char *name, void /* struct bot_goal_s */ *goal)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotGetMapLocationGoal_real( name, goal );
	MV_VersionMagic( qfalse );
	return retVal;
}

float trap_BotAvoidGoalTime(int goalstate, int number)
{
	float retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotAvoidGoalTime_real( goalstate, number );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotSetAvoidGoalTime(int goalstate, int number, float avoidtime)
{
	MV_VersionMagic( qtrue );
	trap_BotSetAvoidGoalTime_real( goalstate, number, avoidtime);
	MV_VersionMagic( qfalse );
}

void trap_BotInitLevelItems(void)
{
	MV_VersionMagic( qtrue );
	trap_BotInitLevelItems_real();
	MV_VersionMagic( qfalse );
}

void trap_BotUpdateEntityItems(void)
{
	MV_VersionMagic( qtrue );
	trap_BotUpdateEntityItems_real();
	MV_VersionMagic( qfalse );
}

int trap_BotLoadItemWeights(int goalstate, char *filename)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLoadItemWeights_real( goalstate, filename );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotFreeItemWeights(int goalstate)
{
	MV_VersionMagic( qtrue );
	trap_BotFreeItemWeights_real( goalstate );
	MV_VersionMagic( qfalse );
}

void trap_BotInterbreedGoalFuzzyLogic(int parent1, int parent2, int child)
{
	MV_VersionMagic( qtrue );
	trap_BotInterbreedGoalFuzzyLogic_real( parent1, parent2, child );
	MV_VersionMagic( qfalse );
}

void trap_BotSaveGoalFuzzyLogic(int goalstate, char *filename)
{
	MV_VersionMagic( qtrue );
	trap_BotSaveGoalFuzzyLogic_real( goalstate, filename );
	MV_VersionMagic( qfalse );
}

void trap_BotMutateGoalFuzzyLogic(int goalstate, float range)
{
	MV_VersionMagic( qtrue );
	trap_BotMutateGoalFuzzyLogic_real( goalstate, range );
	MV_VersionMagic( qfalse );
}

int trap_BotAllocGoalState(int state)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotAllocGoalState_real( state );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotFreeGoalState(int handle)
{
	MV_VersionMagic( qtrue );
	trap_BotFreeGoalState_real( handle );
	MV_VersionMagic( qfalse );
}

void trap_BotResetMoveState(int movestate)
{
	MV_VersionMagic( qtrue );
	trap_BotResetMoveState_real( movestate );
	MV_VersionMagic( qfalse );
}

void trap_BotAddAvoidSpot(int movestate, vec3_t origin, float radius, int type)
{
	MV_VersionMagic( qtrue );
	trap_BotAddAvoidSpot_real( movestate, origin, radius, type);
	MV_VersionMagic( qfalse );
}

void trap_BotMoveToGoal(void /* struct bot_moveresult_s */ *result, int movestate, void /* struct bot_goal_s */ *goal, int travelflags)
{
	MV_VersionMagic( qtrue );
	trap_BotMoveToGoal_real( result, movestate, goal, travelflags );
	MV_VersionMagic( qfalse );
}

int trap_BotMoveInDirection(int movestate, vec3_t dir, float speed, int type)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotMoveInDirection_real( movestate, dir, speed, type );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotResetAvoidReach(int movestate)
{
	MV_VersionMagic( qtrue );
	trap_BotResetAvoidReach_real( movestate );
	MV_VersionMagic( qfalse );
}

void trap_BotResetLastAvoidReach(int movestate)
{
	MV_VersionMagic( qtrue );
	trap_BotResetLastAvoidReach_real(movestate  );
	MV_VersionMagic( qfalse );
}

int trap_BotReachabilityArea(vec3_t origin, int testground)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotReachabilityArea_real( origin, testground );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotMovementViewTarget(int movestate, void /* struct bot_goal_s */ *goal, int travelflags, float lookahead, vec3_t target)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotMovementViewTarget_real( movestate, goal, travelflags, lookahead, target );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotPredictVisiblePosition(vec3_t origin, int areanum, void /* struct bot_goal_s */ *goal, int travelflags, vec3_t target)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotPredictVisiblePosition_real( origin, areanum, goal, travelflags, target );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotAllocMoveState(void)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotAllocMoveState_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotFreeMoveState(int handle)
{
	MV_VersionMagic( qtrue );
	trap_BotFreeMoveState_real( handle );
	MV_VersionMagic( qfalse );
}

void trap_BotInitMoveState(int handle, void /* struct bot_initmove_s */ *initmove)
{
	MV_VersionMagic( qtrue );
	trap_BotInitMoveState_real( handle, initmove );
	MV_VersionMagic( qfalse );
}

int trap_BotChooseBestFightWeapon(int weaponstate, int *inventory)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotChooseBestFightWeapon_real( weaponstate, inventory );
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotGetWeaponInfo(int weaponstate, int weapon, void /* struct weaponinfo_s */ *weaponinfo)
{
	MV_VersionMagic( qtrue );
	trap_BotGetWeaponInfo_real( weaponstate, weapon, weaponinfo );
	MV_VersionMagic( qfalse );
}

int trap_BotLoadWeaponWeights(int weaponstate, char *filename)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotLoadWeaponWeights_real( weaponstate, filename );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_BotAllocWeaponState(void)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_BotAllocWeaponState_real();
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_BotFreeWeaponState(int weaponstate)
{
	MV_VersionMagic( qtrue );
	trap_BotFreeWeaponState_real( weaponstate );
	MV_VersionMagic( qfalse );
}

void trap_BotResetWeaponState(int weaponstate)
{
	MV_VersionMagic( qtrue );
	trap_BotResetWeaponState_real( weaponstate );
	MV_VersionMagic( qfalse );
}

int trap_GeneticParentsAndChildSelection(int numranks, float *ranks, int *parent1, int *parent2, int *child)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_GeneticParentsAndChildSelection_real( numranks, ranks, parent1, parent2, child );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_PC_LoadSource( const char *filename )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_PC_LoadSource_real( filename );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_PC_FreeSource( int handle )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_PC_FreeSource_real( handle );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_PC_ReadToken( int handle, pc_token_t *pc_token )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_PC_ReadToken_real( handle, pc_token );
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_PC_SourceFileAndLine( int handle, char *filename, int *line )
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_PC_SourceFileAndLine_real( handle, filename, line );
	MV_VersionMagic( qfalse );
	return retVal;
}


/*
Ghoul2 Insert Start
*/
// CG Specific API calls
void trap_G2_ListModelBones(void *ghlInfo, int frame)
{
	MV_VersionMagic( qtrue );
	trap_G2_ListModelBones_real( ghlInfo, frame);
	MV_VersionMagic( qfalse );
}

void trap_G2_ListModelSurfaces(void *ghlInfo)
{
	MV_VersionMagic( qtrue );
	trap_G2_ListModelSurfaces_real( ghlInfo);
	MV_VersionMagic( qfalse );
}

qboolean trap_G2_HaveWeGhoul2Models(void *ghoul2)
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2_HaveWeGhoul2Models_real( ghoul2);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2_SetGhoul2ModelIndexes(void *ghoul2, qhandle_t *modelList, qhandle_t *skinList)
{
	MV_VersionMagic( qtrue );
	trap_G2_SetGhoul2ModelIndexes_real( ghoul2, modelList, skinList);
	MV_VersionMagic( qfalse );
}

qboolean trap_G2API_GetBoltMatrix(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix,
								const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale)
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_GetBoltMatrix_real( ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_G2API_GetBoltMatrix_NoReconstruct(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix,
								const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale)
{ //Same as above but force it to not reconstruct the skeleton before getting the bolt position
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_GetBoltMatrix_NoReconstruct_real( ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
	MV_VersionMagic( qfalse );
	return retVal;
}


/* 1.04 */
qboolean trap_G2API_GetBoltMatrix_NoRecNoRot_1_04(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix,
								const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale)
{ //Same as above but force it to not reconstruct the skeleton before getting the bolt position
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_GetBoltMatrix_NoRecNoRot_1_04_real( ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_G2API_InitGhoul2Model_1_04(void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin,
					  qhandle_t customShader, int modelFlags, int lodBias)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_InitGhoul2Model_1_04_real( ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias);
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_G2API_AddBolt_1_04(void *ghoul2, int modelIndex, const char *boneName)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_AddBolt_1_04_real( ghoul2, modelIndex, boneName);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2API_SetBoltInfo_1_04(void *ghoul2, int modelIndex, int boltInfo)
{
	MV_VersionMagic( qtrue );
	trap_G2API_SetBoltInfo_1_04_real( ghoul2, modelIndex, boltInfo);
	MV_VersionMagic( qfalse );
}

qboolean trap_G2API_SetBoneAngles_1_04(void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags,
								const int up, const int right, const int forward, qhandle_t *modelList,
								int blendTime , int currentTime )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_SetBoneAngles_1_04_real( ghoul2, modelIndex, boneName, angles, flags, up, right, forward, modelList, blendTime, currentTime);
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_G2API_SetBoneAnim_1_04(void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame,
						  const int flags, const float animSpeed, const int currentTime, const float setFrame , const int blendTime )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_SetBoneAnim_1_04_real( ghoul2, modelIndex, boneName, startFrame, endFrame, flags, animSpeed, currentTime, setFrame, blendTime);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2API_GetGLAName_1_04(void *ghoul2, int modelIndex, char *fillBuf)
{
	MV_VersionMagic( qtrue );
	trap_G2API_GetGLAName_1_04_real( ghoul2, modelIndex, fillBuf);
	MV_VersionMagic( qfalse );
}

int trap_G2API_CopyGhoul2Instance_1_04(void *g2From, void *g2To, int modelIndex)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_CopyGhoul2Instance_1_04_real( g2From, g2To, modelIndex);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2API_CopySpecificGhoul2Model_1_04(void *g2From, int modelFrom, void *g2To, int modelTo)
{
	MV_VersionMagic( qtrue );
	trap_G2API_CopySpecificGhoul2Model_1_04_real( g2From, modelFrom, g2To, modelTo);
	MV_VersionMagic( qfalse );
}

void trap_G2API_DuplicateGhoul2Instance_1_04(void *g2From, void **g2To)
{
	MV_VersionMagic( qtrue );
	trap_G2API_DuplicateGhoul2Instance_1_04_real( g2From, g2To);
	MV_VersionMagic( qfalse );
}

qboolean trap_G2API_HasGhoul2ModelOnIndex_1_04(void *ghlInfo, int modelIndex)
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_HasGhoul2ModelOnIndex_1_04_real( ghlInfo, modelIndex);
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_G2API_RemoveGhoul2Model_1_04(void *ghlInfo, int modelIndex)
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_RemoveGhoul2Model_1_04_real( ghlInfo, modelIndex);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2API_CleanGhoul2Models_1_04(void **ghoul2Ptr)
{
	MV_VersionMagic( qtrue );
	trap_G2API_CleanGhoul2Models_1_04_real( ghoul2Ptr);
	MV_VersionMagic( qfalse );
}

void trap_G2API_CollisionDetect_1_04 ( 
	CollisionRecord_t *collRecMap, 
	void* ghoul2, 
	const vec3_t angles, 
	const vec3_t position,
	int frameNumber, 
	int entNum, 
	vec3_t rayStart, 
	vec3_t rayEnd, 
	vec3_t scale, 
	int traceFlags, 
	int useLod,
	float fRadius
	)
{
	MV_VersionMagic( qtrue );
	trap_G2API_CollisionDetect_1_04_real ( collRecMap, ghoul2, angles, position, frameNumber, entNum, rayStart, rayEnd, scale, traceFlags, useLod, fRadius );
	MV_VersionMagic( qfalse );
}

/* 1.02 */
int trap_G2API_InitGhoul2Model_1_02(void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin,
					  qhandle_t customShader, int modelFlags, int lodBias)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_InitGhoul2Model_1_02_real( ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias);
	MV_VersionMagic( qfalse );
	return retVal;
}

int trap_G2API_AddBolt_1_02(void *ghoul2, int modelIndex, const char *boneName)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_AddBolt_1_02_real( ghoul2, modelIndex, boneName);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2API_SetBoltInfo_1_02(void *ghoul2, int modelIndex, int boltInfo)
{
	MV_VersionMagic( qtrue );
	trap_G2API_SetBoltInfo_1_02_real( ghoul2, modelIndex, boltInfo);
	MV_VersionMagic( qfalse );
}

qboolean trap_G2API_SetBoneAngles_1_02(void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags,
								const int up, const int right, const int forward, qhandle_t *modelList,
								int blendTime , int currentTime )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_SetBoneAngles_1_02_real( ghoul2, modelIndex, boneName, angles, flags, up, right, forward, modelList, blendTime, currentTime);
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_G2API_SetBoneAnim_1_02(void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame,
						  const int flags, const float animSpeed, const int currentTime, const float setFrame , const int blendTime )
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_SetBoneAnim_1_02_real( ghoul2, modelIndex, boneName, startFrame, endFrame, flags, animSpeed, currentTime, setFrame, blendTime);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2API_GetGLAName_1_02(void *ghoul2, int modelIndex, char *fillBuf)
{
	MV_VersionMagic( qtrue );
	trap_G2API_GetGLAName_1_02_real( ghoul2, modelIndex, fillBuf);
	MV_VersionMagic( qfalse );
}

int trap_G2API_CopyGhoul2Instance_1_02(void *g2From, void *g2To, int modelIndex)
{
	int retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_CopyGhoul2Instance_1_02_real( g2From, g2To, modelIndex);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2API_CopySpecificGhoul2Model_1_02(void *g2From, int modelFrom, void *g2To, int modelTo)
{
	MV_VersionMagic( qtrue );
	trap_G2API_CopySpecificGhoul2Model_1_02_real( g2From, modelFrom, g2To, modelTo);
	MV_VersionMagic( qfalse );
}

void trap_G2API_DuplicateGhoul2Instance_1_02(void *g2From, void **g2To)
{
	MV_VersionMagic( qtrue );
	trap_G2API_DuplicateGhoul2Instance_1_02_real( g2From, g2To);
	MV_VersionMagic( qfalse );
}

qboolean trap_G2API_HasGhoul2ModelOnIndex_1_02(void *ghlInfo, int modelIndex)
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_HasGhoul2ModelOnIndex_1_02_real( ghlInfo, modelIndex);
	MV_VersionMagic( qfalse );
	return retVal;
}

qboolean trap_G2API_RemoveGhoul2Model_1_02(void *ghlInfo, int modelIndex)
{
	qboolean retVal;
	MV_VersionMagic( qtrue );
	retVal = trap_G2API_RemoveGhoul2Model_1_02_real( ghlInfo, modelIndex);
	MV_VersionMagic( qfalse );
	return retVal;
}

void trap_G2API_CleanGhoul2Models_1_02(void **ghoul2Ptr)
{
	MV_VersionMagic( qtrue );
	trap_G2API_CleanGhoul2Models_1_02_real( ghoul2Ptr);
	MV_VersionMagic( qfalse );
}

/*
Ghoul2 Insert End
*/
#endif
