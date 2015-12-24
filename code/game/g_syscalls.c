// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"

// this file is only included when building a dll
// g_syscalls.asm is included instead when building a qvm

static int (QDECL *syscall)( int arg, ... ) = (int (QDECL *)( int, ...))-1;


LIBEXPORT void dllEntry( int (QDECL *syscallptr)( int arg,... ) ) {
	syscall = syscallptr;
}

int PASSFLOAT( float x ) {
	float	floatTemp;
	floatTemp = x;
	return *(int *)&floatTemp;
}

void	trap_Printf_real( const char *fmt ) {
	syscall( G_PRINT, fmt );
}

void	trap_Error_real( const char *fmt ) {
	syscall( G_ERROR, fmt );
}

int		trap_Milliseconds_real( void ) {
	return syscall( G_MILLISECONDS ); 
}

void	trap_Cvar_Register_real( vmCvar_t *cvar, const char *var_name, const char *value, int flags ) {
	syscall( G_CVAR_REGISTER, cvar, var_name, value, flags );
}

void	trap_Cvar_Update_real( vmCvar_t *cvar ) {
	syscall( G_CVAR_UPDATE, cvar );
}

void trap_Cvar_Set_real( const char *var_name, const char *value ) {
	syscall( G_CVAR_SET, var_name, value );
}

int trap_Cvar_VariableIntegerValue_real( const char *var_name ) {
	return syscall( G_CVAR_VARIABLE_INTEGER_VALUE, var_name );
}

void trap_Cvar_VariableStringBuffer_real( const char *var_name, char *buffer, int bufsize ) {
	syscall( G_CVAR_VARIABLE_STRING_BUFFER, var_name, buffer, bufsize );
}

int		trap_Argc_real( void ) {
	return syscall( G_ARGC );
}

void	trap_Argv_real( int n, char *buffer, int bufferLength ) {
	syscall( G_ARGV, n, buffer, bufferLength );
}

int		trap_FS_FOpenFile_real( const char *qpath, fileHandle_t *f, fsMode_t mode ) {
	return syscall( G_FS_FOPEN_FILE, qpath, f, mode );
}

void	trap_FS_Read_real( void *buffer, int len, fileHandle_t f ) {
	syscall( G_FS_READ, buffer, len, f );
}

void	trap_FS_Write_real( const void *buffer, int len, fileHandle_t f ) {
	syscall( G_FS_WRITE, buffer, len, f );
}

void	trap_FS_FCloseFile_real( fileHandle_t f ) {
	syscall( G_FS_FCLOSE_FILE, f );
}

void	trap_SendConsoleCommand_real( int exec_when, const char *text ) {
	syscall( G_SEND_CONSOLE_COMMAND, exec_when, text );
}

void trap_LocateGameData_real( gentity_t *gEnts, int numGEntities, int sizeofGEntity_t,
						 playerState_t *clients, int sizeofGClient ) {
	syscall( G_LOCATE_GAME_DATA, gEnts, numGEntities, sizeofGEntity_t, clients, sizeofGClient );
}

void trap_DropClient_real( int clientNum, const char *reason ) {
	syscall( G_DROP_CLIENT, clientNum, reason );
}

void trap_SendServerCommand_real( int clientNum, const char *text ) {
	syscall( G_SEND_SERVER_COMMAND, clientNum, text );
}

void trap_SetConfigstring_real( int num, const char *string ) {
	syscall( G_SET_CONFIGSTRING, num, string );
}

void trap_GetConfigstring_real( int num, char *buffer, int bufferSize ) {
	syscall( G_GET_CONFIGSTRING, num, buffer, bufferSize );
}

void trap_GetUserinfo_real( int num, char *buffer, int bufferSize ) {
	syscall( G_GET_USERINFO, num, buffer, bufferSize );
}

void trap_SetUserinfo_real( int num, const char *buffer ) {
	syscall( G_SET_USERINFO, num, buffer );
}

void trap_GetServerinfo_real( char *buffer, int bufferSize ) {
	syscall( G_GET_SERVERINFO, buffer, bufferSize );
}

void trap_SetBrushModel_real( gentity_t *ent, const char *name ) {
	syscall( G_SET_BRUSH_MODEL, ent, name );
}

void trap_Trace_real( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask ) {
	syscall( G_TRACE, results, start, mins, maxs, end, passEntityNum, contentmask, 0, 10 );
}

int trap_PointContents_real( const vec3_t point, int passEntityNum ) {
	return syscall( G_POINT_CONTENTS, point, passEntityNum );
}


qboolean trap_InPVS_real( const vec3_t p1, const vec3_t p2 ) {
	return syscall( G_IN_PVS, p1, p2 );
}

qboolean trap_InPVSIgnorePortals_real( const vec3_t p1, const vec3_t p2 ) {
	return syscall( G_IN_PVS_IGNORE_PORTALS, p1, p2 );
}

void trap_AdjustAreaPortalState_real( gentity_t *ent, qboolean open ) {
	syscall( G_ADJUST_AREA_PORTAL_STATE, ent, open );
}

qboolean trap_AreasConnected_real( int area1, int area2 ) {
	return syscall( G_AREAS_CONNECTED, area1, area2 );
}

void trap_LinkEntity_real( gentity_t *ent ) {
	syscall( G_LINKENTITY, ent );
}

void trap_UnlinkEntity_real( gentity_t *ent ) {
	syscall( G_UNLINKENTITY, ent );
}

int trap_EntitiesInBox_real( const vec3_t mins, const vec3_t maxs, int *list, int maxcount ) {
	return syscall( G_ENTITIES_IN_BOX, mins, maxs, list, maxcount );
}

qboolean trap_EntityContact_real( const vec3_t mins, const vec3_t maxs, const gentity_t *ent ) {
	return syscall( G_ENTITY_CONTACT, mins, maxs, ent );
}

int trap_BotAllocateClient_real( void ) {
	return syscall( G_BOT_ALLOCATE_CLIENT );
}

void trap_BotFreeClient_real( int clientNum ) {
	syscall( G_BOT_FREE_CLIENT, clientNum );
}

void trap_GetUsercmd_real( int clientNum, usercmd_t *cmd ) {
	syscall( G_GET_USERCMD, clientNum, cmd );
}

qboolean trap_GetEntityToken_real( char *buffer, int bufferSize ) {
	return syscall( G_GET_ENTITY_TOKEN, buffer, bufferSize );
}

int trap_FS_GetFileList_real(  const char *path, const char *extension, char *listbuf, int bufsize ) {
	return syscall( G_FS_GETFILELIST, path, extension, listbuf, bufsize );
}

int trap_DebugPolygonCreate_real(int color, int numPoints, vec3_t *points) {
	return syscall( G_DEBUG_POLYGON_CREATE, color, numPoints, points );
}

void trap_DebugPolygonDelete_real(int id) {
	syscall( G_DEBUG_POLYGON_DELETE, id );
}

int trap_RealTime_real( qtime_t *qtime ) {
	return syscall( G_REAL_TIME, qtime );
}

void trap_SnapVector_real( float *v ) {
	syscall( G_SNAPVECTOR, v );
}

void trap_TraceCapsule_real( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask ) {
	syscall( G_TRACECAPSULE, results, start, mins, maxs, end, passEntityNum, contentmask, 0, 10 );
}

qboolean trap_EntityContactCapsule_real( const vec3_t mins, const vec3_t maxs, const gentity_t *ent ) {
	return syscall( G_ENTITY_CONTACTCAPSULE, mins, maxs, ent );
}

qboolean trap_SP_RegisterServer_real( const char *package ) 
{
	return syscall( SP_REGISTER_SERVER_CMD, package );
}

int trap_SP_GetStringTextString_real(const char *text, char *buffer, int bufferLength)
{
	return syscall( SP_GETSTRINGTEXTSTRING, text, buffer, bufferLength );
}

qboolean trap_ROFF_Clean_real( void ) 
{
	return syscall( G_ROFF_CLEAN );
}

void trap_ROFF_UpdateEntities_real( void ) 
{
	syscall( G_ROFF_UPDATE_ENTITIES );
}

int trap_ROFF_Cache_real( char *file ) 
{
	return syscall( G_ROFF_CACHE, file );
}

qboolean trap_ROFF_Play_real( int entID, int roffID, qboolean doTranslation ) 
{
	return syscall( G_ROFF_PLAY, entID, roffID, doTranslation );
}

qboolean trap_ROFF_Purge_Ent_real( int entID ) 
{
	return syscall( G_ROFF_PURGE_ENT, entID );
}

// BotLib traps start here
int trap_BotLibSetup_real( void ) {
	return syscall( BOTLIB_SETUP );
}

int trap_BotLibShutdown_real( void ) {
	return syscall( BOTLIB_SHUTDOWN );
}

int trap_BotLibVarSet_real(char *var_name, char *value) {
	return syscall( BOTLIB_LIBVAR_SET, var_name, value );
}

int trap_BotLibVarGet_real(char *var_name, char *value, int size) {
	return syscall( BOTLIB_LIBVAR_GET, var_name, value, size );
}

int trap_BotLibDefine_real(char *string) {
	return syscall( BOTLIB_PC_ADD_GLOBAL_DEFINE, string );
}

int trap_BotLibStartFrame_real(float time) {
	return syscall( BOTLIB_START_FRAME, PASSFLOAT( time ) );
}

int trap_BotLibLoadMap_real(const char *mapname) {
	return syscall( BOTLIB_LOAD_MAP, mapname );
}

int trap_BotLibUpdateEntity_real(int ent, void /* struct bot_updateentity_s */ *bue) {
	return syscall( BOTLIB_UPDATENTITY, ent, bue );
}

int trap_BotLibTest_real(int parm0, char *parm1, vec3_t parm2, vec3_t parm3) {
	return syscall( BOTLIB_TEST, parm0, parm1, parm2, parm3 );
}

int trap_BotGetSnapshotEntity_real( int clientNum, int sequence ) {
	return syscall( BOTLIB_GET_SNAPSHOT_ENTITY, clientNum, sequence );
}

int trap_BotGetServerCommand_real(int clientNum, char *message, int size) {
	return syscall( BOTLIB_GET_CONSOLE_MESSAGE, clientNum, message, size );
}

void trap_BotUserCommand_real(int clientNum, usercmd_t *ucmd) {
	syscall( BOTLIB_USER_COMMAND, clientNum, ucmd );
}

void trap_AAS_EntityInfo_real(int entnum, void /* struct aas_entityinfo_s */ *info) {
	syscall( BOTLIB_AAS_ENTITY_INFO, entnum, info );
}

int trap_AAS_Initialized_real(void) {
	return syscall( BOTLIB_AAS_INITIALIZED );
}

void trap_AAS_PresenceTypeBoundingBox_real(int presencetype, vec3_t mins, vec3_t maxs) {
	syscall( BOTLIB_AAS_PRESENCE_TYPE_BOUNDING_BOX, presencetype, mins, maxs );
}

float trap_AAS_Time_real(void) {
	int temp;
	temp = syscall( BOTLIB_AAS_TIME );
	return (*(float*)&temp);
}

int trap_AAS_PointAreaNum_real(vec3_t point) {
	return syscall( BOTLIB_AAS_POINT_AREA_NUM, point );
}

int trap_AAS_PointReachabilityAreaIndex_real(vec3_t point) {
	return syscall( BOTLIB_AAS_POINT_REACHABILITY_AREA_INDEX, point );
}

int trap_AAS_TraceAreas_real(vec3_t start, vec3_t end, int *areas, vec3_t *points, int maxareas) {
	return syscall( BOTLIB_AAS_TRACE_AREAS, start, end, areas, points, maxareas );
}

int trap_AAS_BBoxAreas_real(vec3_t absmins, vec3_t absmaxs, int *areas, int maxareas) {
	return syscall( BOTLIB_AAS_BBOX_AREAS, absmins, absmaxs, areas, maxareas );
}

int trap_AAS_AreaInfo_real( int areanum, void /* struct aas_areainfo_s */ *info ) {
	return syscall( BOTLIB_AAS_AREA_INFO, areanum, info );
}

int trap_AAS_PointContents_real(vec3_t point) {
	return syscall( BOTLIB_AAS_POINT_CONTENTS, point );
}

int trap_AAS_NextBSPEntity_real(int ent) {
	return syscall( BOTLIB_AAS_NEXT_BSP_ENTITY, ent );
}

int trap_AAS_ValueForBSPEpairKey_real(int ent, char *key, char *value, int size) {
	return syscall( BOTLIB_AAS_VALUE_FOR_BSP_EPAIR_KEY, ent, key, value, size );
}

int trap_AAS_VectorForBSPEpairKey_real(int ent, char *key, vec3_t v) {
	return syscall( BOTLIB_AAS_VECTOR_FOR_BSP_EPAIR_KEY, ent, key, v );
}

int trap_AAS_FloatForBSPEpairKey_real(int ent, char *key, float *value) {
	return syscall( BOTLIB_AAS_FLOAT_FOR_BSP_EPAIR_KEY, ent, key, value );
}

int trap_AAS_IntForBSPEpairKey_real(int ent, char *key, int *value) {
	return syscall( BOTLIB_AAS_INT_FOR_BSP_EPAIR_KEY, ent, key, value );
}

int trap_AAS_AreaReachability_real(int areanum) {
	return syscall( BOTLIB_AAS_AREA_REACHABILITY, areanum );
}

int trap_AAS_AreaTravelTimeToGoalArea_real(int areanum, vec3_t origin, int goalareanum, int travelflags) {
	return syscall( BOTLIB_AAS_AREA_TRAVEL_TIME_TO_GOAL_AREA, areanum, origin, goalareanum, travelflags );
}

int trap_AAS_EnableRoutingArea_real( int areanum, int enable ) {
	return syscall( BOTLIB_AAS_ENABLE_ROUTING_AREA, areanum, enable );
}

int trap_AAS_PredictRoute_real(void /*struct aas_predictroute_s*/ *route, int areanum, vec3_t origin,
							int goalareanum, int travelflags, int maxareas, int maxtime,
							int stopevent, int stopcontents, int stoptfl, int stopareanum) {
	return syscall( BOTLIB_AAS_PREDICT_ROUTE, route, areanum, origin, goalareanum, travelflags, maxareas, maxtime, stopevent, stopcontents, stoptfl, stopareanum );
}

int trap_AAS_AlternativeRouteGoals_real(vec3_t start, int startareanum, vec3_t goal, int goalareanum, int travelflags,
										void /*struct aas_altroutegoal_s*/ *altroutegoals, int maxaltroutegoals,
										int type) {
	return syscall( BOTLIB_AAS_ALTERNATIVE_ROUTE_GOAL, start, startareanum, goal, goalareanum, travelflags, altroutegoals, maxaltroutegoals, type );
}

int trap_AAS_Swimming_real(vec3_t origin) {
	return syscall( BOTLIB_AAS_SWIMMING, origin );
}

int trap_AAS_PredictClientMovement_real(void /* struct aas_clientmove_s */ *move, int entnum, vec3_t origin, int presencetype, int onground, vec3_t velocity, vec3_t cmdmove, int cmdframes, int maxframes, float frametime, int stopevent, int stopareanum, int visualize) {
	return syscall( BOTLIB_AAS_PREDICT_CLIENT_MOVEMENT, move, entnum, origin, presencetype, onground, velocity, cmdmove, cmdframes, maxframes, PASSFLOAT(frametime), stopevent, stopareanum, visualize );
}

void trap_EA_Say_real(int client, char *str) {
	syscall( BOTLIB_EA_SAY, client, str );
}

void trap_EA_SayTeam_real(int client, char *str) {
	syscall( BOTLIB_EA_SAY_TEAM, client, str );
}

void trap_EA_Command_real(int client, char *command) {
	syscall( BOTLIB_EA_COMMAND, client, command );
}

void trap_EA_Action_real(int client, int action) {
	syscall( BOTLIB_EA_ACTION, client, action );
}

void trap_EA_Gesture_real(int client) {
	syscall( BOTLIB_EA_GESTURE, client );
}

void trap_EA_Talk_real(int client) {
	syscall( BOTLIB_EA_TALK, client );
}

void trap_EA_Attack_real(int client) {
	syscall( BOTLIB_EA_ATTACK, client );
}

void trap_EA_Alt_Attack_real(int client) {
	syscall( BOTLIB_EA_ALT_ATTACK, client );
}

void trap_EA_ForcePower_real(int client) {
	syscall( BOTLIB_EA_FORCEPOWER, client );
}

void trap_EA_Use_real(int client) {
	syscall( BOTLIB_EA_USE, client );
}

void trap_EA_Respawn_real(int client) {
	syscall( BOTLIB_EA_RESPAWN, client );
}

void trap_EA_Crouch_real(int client) {
	syscall( BOTLIB_EA_CROUCH, client );
}

void trap_EA_MoveUp_real(int client) {
	syscall( BOTLIB_EA_MOVE_UP, client );
}

void trap_EA_MoveDown_real(int client) {
	syscall( BOTLIB_EA_MOVE_DOWN, client );
}

void trap_EA_MoveForward_real(int client) {
	syscall( BOTLIB_EA_MOVE_FORWARD, client );
}

void trap_EA_MoveBack_real(int client) {
	syscall( BOTLIB_EA_MOVE_BACK, client );
}

void trap_EA_MoveLeft_real(int client) {
	syscall( BOTLIB_EA_MOVE_LEFT, client );
}

void trap_EA_MoveRight_real(int client) {
	syscall( BOTLIB_EA_MOVE_RIGHT, client );
}

void trap_EA_SelectWeapon_real(int client, int weapon) {
	syscall( BOTLIB_EA_SELECT_WEAPON, client, weapon );
}

void trap_EA_Jump_real(int client) {
	syscall( BOTLIB_EA_JUMP, client );
}

void trap_EA_DelayedJump_real(int client) {
	syscall( BOTLIB_EA_DELAYED_JUMP, client );
}

void trap_EA_Move_real(int client, vec3_t dir, float speed) {
	syscall( BOTLIB_EA_MOVE, client, dir, PASSFLOAT(speed) );
}

void trap_EA_View_real(int client, vec3_t viewangles) {
	syscall( BOTLIB_EA_VIEW, client, viewangles );
}

void trap_EA_EndRegular_real(int client, float thinktime) {
	syscall( BOTLIB_EA_END_REGULAR, client, PASSFLOAT(thinktime) );
}

void trap_EA_GetInput_real(int client, float thinktime, void /* struct bot_input_s */ *input) {
	syscall( BOTLIB_EA_GET_INPUT, client, PASSFLOAT(thinktime), input );
}

void trap_EA_ResetInput_real(int client) {
	syscall( BOTLIB_EA_RESET_INPUT, client );
}

int trap_BotLoadCharacter_real(char *charfile, float skill) {
	return syscall( BOTLIB_AI_LOAD_CHARACTER, charfile, PASSFLOAT(skill));
}

void trap_BotFreeCharacter_real(int character) {
	syscall( BOTLIB_AI_FREE_CHARACTER, character );
}

float trap_Characteristic_Float_real(int character, int index) {
	int temp;
	temp = syscall( BOTLIB_AI_CHARACTERISTIC_FLOAT, character, index );
	return (*(float*)&temp);
}

float trap_Characteristic_BFloat_real(int character, int index, float min, float max) {
	int temp;
	temp = syscall( BOTLIB_AI_CHARACTERISTIC_BFLOAT, character, index, PASSFLOAT(min), PASSFLOAT(max) );
	return (*(float*)&temp);
}

int trap_Characteristic_Integer_real(int character, int index) {
	return syscall( BOTLIB_AI_CHARACTERISTIC_INTEGER, character, index );
}

int trap_Characteristic_BInteger_real(int character, int index, int min, int max) {
	return syscall( BOTLIB_AI_CHARACTERISTIC_BINTEGER, character, index, min, max );
}

void trap_Characteristic_String_real(int character, int index, char *buf, int size) {
	syscall( BOTLIB_AI_CHARACTERISTIC_STRING, character, index, buf, size );
}

int trap_BotAllocChatState_real(void) {
	return syscall( BOTLIB_AI_ALLOC_CHAT_STATE );
}

void trap_BotFreeChatState_real(int handle) {
	syscall( BOTLIB_AI_FREE_CHAT_STATE, handle );
}

void trap_BotQueueConsoleMessage_real(int chatstate, int type, char *message) {
	syscall( BOTLIB_AI_QUEUE_CONSOLE_MESSAGE, chatstate, type, message );
}

void trap_BotRemoveConsoleMessage_real(int chatstate, int handle) {
	syscall( BOTLIB_AI_REMOVE_CONSOLE_MESSAGE, chatstate, handle );
}

int trap_BotNextConsoleMessage_real(int chatstate, void /* struct bot_consolemessage_s */ *cm) {
	return syscall( BOTLIB_AI_NEXT_CONSOLE_MESSAGE, chatstate, cm );
}

int trap_BotNumConsoleMessages_real(int chatstate) {
	return syscall( BOTLIB_AI_NUM_CONSOLE_MESSAGE, chatstate );
}

void trap_BotInitialChat_real(int chatstate, char *type, int mcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 ) {
	syscall( BOTLIB_AI_INITIAL_CHAT, chatstate, type, mcontext, var0, var1, var2, var3, var4, var5, var6, var7 );
}

int	trap_BotNumInitialChats_real(int chatstate, char *type) {
	return syscall( BOTLIB_AI_NUM_INITIAL_CHATS, chatstate, type );
}

int trap_BotReplyChat_real(int chatstate, char *message, int mcontext, int vcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 ) {
	return syscall( BOTLIB_AI_REPLY_CHAT, chatstate, message, mcontext, vcontext, var0, var1, var2, var3, var4, var5, var6, var7 );
}

int trap_BotChatLength_real(int chatstate) {
	return syscall( BOTLIB_AI_CHAT_LENGTH, chatstate );
}

void trap_BotEnterChat_real(int chatstate, int client, int sendto) {
	syscall( BOTLIB_AI_ENTER_CHAT, chatstate, client, sendto );
}

void trap_BotGetChatMessage_real(int chatstate, char *buf, int size) {
	syscall( BOTLIB_AI_GET_CHAT_MESSAGE, chatstate, buf, size);
}

int trap_StringContains_real(char *str1, char *str2, int casesensitive) {
	return syscall( BOTLIB_AI_STRING_CONTAINS, str1, str2, casesensitive );
}

int trap_BotFindMatch_real(char *str, void /* struct bot_match_s */ *match, unsigned long int context) {
	return syscall( BOTLIB_AI_FIND_MATCH, str, match, context );
}

void trap_BotMatchVariable_real(void /* struct bot_match_s */ *match, int variable, char *buf, int size) {
	syscall( BOTLIB_AI_MATCH_VARIABLE, match, variable, buf, size );
}

void trap_UnifyWhiteSpaces_real(char *string) {
	syscall( BOTLIB_AI_UNIFY_WHITE_SPACES, string );
}

void trap_BotReplaceSynonyms_real(char *string, unsigned long int context) {
	syscall( BOTLIB_AI_REPLACE_SYNONYMS, string, context );
}

int trap_BotLoadChatFile_real(int chatstate, char *chatfile, char *chatname) {
	return syscall( BOTLIB_AI_LOAD_CHAT_FILE, chatstate, chatfile, chatname );
}

void trap_BotSetChatGender_real(int chatstate, int gender) {
	syscall( BOTLIB_AI_SET_CHAT_GENDER, chatstate, gender );
}

void trap_BotSetChatName_real(int chatstate, char *name, int client) {
	syscall( BOTLIB_AI_SET_CHAT_NAME, chatstate, name, client );
}

void trap_BotResetGoalState_real(int goalstate) {
	syscall( BOTLIB_AI_RESET_GOAL_STATE, goalstate );
}

void trap_BotResetAvoidGoals_real(int goalstate) {
	syscall( BOTLIB_AI_RESET_AVOID_GOALS, goalstate );
}

void trap_BotRemoveFromAvoidGoals_real(int goalstate, int number) {
	syscall( BOTLIB_AI_REMOVE_FROM_AVOID_GOALS, goalstate, number);
}

void trap_BotPushGoal_real(int goalstate, void /* struct bot_goal_s */ *goal) {
	syscall( BOTLIB_AI_PUSH_GOAL, goalstate, goal );
}

void trap_BotPopGoal_real(int goalstate) {
	syscall( BOTLIB_AI_POP_GOAL, goalstate );
}

void trap_BotEmptyGoalStack_real(int goalstate) {
	syscall( BOTLIB_AI_EMPTY_GOAL_STACK, goalstate );
}

void trap_BotDumpAvoidGoals_real(int goalstate) {
	syscall( BOTLIB_AI_DUMP_AVOID_GOALS, goalstate );
}

void trap_BotDumpGoalStack_real(int goalstate) {
	syscall( BOTLIB_AI_DUMP_GOAL_STACK, goalstate );
}

void trap_BotGoalName_real(int number, char *name, int size) {
	syscall( BOTLIB_AI_GOAL_NAME, number, name, size );
}

int trap_BotGetTopGoal_real(int goalstate, void /* struct bot_goal_s */ *goal) {
	return syscall( BOTLIB_AI_GET_TOP_GOAL, goalstate, goal );
}

int trap_BotGetSecondGoal_real(int goalstate, void /* struct bot_goal_s */ *goal) {
	return syscall( BOTLIB_AI_GET_SECOND_GOAL, goalstate, goal );
}

int trap_BotChooseLTGItem_real(int goalstate, vec3_t origin, int *inventory, int travelflags) {
	return syscall( BOTLIB_AI_CHOOSE_LTG_ITEM, goalstate, origin, inventory, travelflags );
}

int trap_BotChooseNBGItem_real(int goalstate, vec3_t origin, int *inventory, int travelflags, void /* struct bot_goal_s */ *ltg, float maxtime) {
	return syscall( BOTLIB_AI_CHOOSE_NBG_ITEM, goalstate, origin, inventory, travelflags, ltg, PASSFLOAT(maxtime) );
}

int trap_BotTouchingGoal_real(vec3_t origin, void /* struct bot_goal_s */ *goal) {
	return syscall( BOTLIB_AI_TOUCHING_GOAL, origin, goal );
}

int trap_BotItemGoalInVisButNotVisible_real(int viewer, vec3_t eye, vec3_t viewangles, void /* struct bot_goal_s */ *goal) {
	return syscall( BOTLIB_AI_ITEM_GOAL_IN_VIS_BUT_NOT_VISIBLE, viewer, eye, viewangles, goal );
}

int trap_BotGetLevelItemGoal_real(int index, char *classname, void /* struct bot_goal_s */ *goal) {
	return syscall( BOTLIB_AI_GET_LEVEL_ITEM_GOAL, index, classname, goal );
}

int trap_BotGetNextCampSpotGoal_real(int num, void /* struct bot_goal_s */ *goal) {
	return syscall( BOTLIB_AI_GET_NEXT_CAMP_SPOT_GOAL, num, goal );
}

int trap_BotGetMapLocationGoal_real(char *name, void /* struct bot_goal_s */ *goal) {
	return syscall( BOTLIB_AI_GET_MAP_LOCATION_GOAL, name, goal );
}

float trap_BotAvoidGoalTime_real(int goalstate, int number) {
	int temp;
	temp = syscall( BOTLIB_AI_AVOID_GOAL_TIME, goalstate, number );
	return (*(float*)&temp);
}

void trap_BotSetAvoidGoalTime_real(int goalstate, int number, float avoidtime) {
	syscall( BOTLIB_AI_SET_AVOID_GOAL_TIME, goalstate, number, PASSFLOAT(avoidtime));
}

void trap_BotInitLevelItems_real(void) {
	syscall( BOTLIB_AI_INIT_LEVEL_ITEMS );
}

void trap_BotUpdateEntityItems_real(void) {
	syscall( BOTLIB_AI_UPDATE_ENTITY_ITEMS );
}

int trap_BotLoadItemWeights_real(int goalstate, char *filename) {
	return syscall( BOTLIB_AI_LOAD_ITEM_WEIGHTS, goalstate, filename );
}

void trap_BotFreeItemWeights_real(int goalstate) {
	syscall( BOTLIB_AI_FREE_ITEM_WEIGHTS, goalstate );
}

void trap_BotInterbreedGoalFuzzyLogic_real(int parent1, int parent2, int child) {
	syscall( BOTLIB_AI_INTERBREED_GOAL_FUZZY_LOGIC, parent1, parent2, child );
}

void trap_BotSaveGoalFuzzyLogic_real(int goalstate, char *filename) {
	syscall( BOTLIB_AI_SAVE_GOAL_FUZZY_LOGIC, goalstate, filename );
}

void trap_BotMutateGoalFuzzyLogic_real(int goalstate, float range) {
	syscall( BOTLIB_AI_MUTATE_GOAL_FUZZY_LOGIC, goalstate, range );
}

int trap_BotAllocGoalState_real(int state) {
	return syscall( BOTLIB_AI_ALLOC_GOAL_STATE, state );
}

void trap_BotFreeGoalState_real(int handle) {
	syscall( BOTLIB_AI_FREE_GOAL_STATE, handle );
}

void trap_BotResetMoveState_real(int movestate) {
	syscall( BOTLIB_AI_RESET_MOVE_STATE, movestate );
}

void trap_BotAddAvoidSpot_real(int movestate, vec3_t origin, float radius, int type) {
	syscall( BOTLIB_AI_ADD_AVOID_SPOT, movestate, origin, PASSFLOAT(radius), type);
}

void trap_BotMoveToGoal_real(void /* struct bot_moveresult_s */ *result, int movestate, void /* struct bot_goal_s */ *goal, int travelflags) {
	syscall( BOTLIB_AI_MOVE_TO_GOAL, result, movestate, goal, travelflags );
}

int trap_BotMoveInDirection_real(int movestate, vec3_t dir, float speed, int type) {
	return syscall( BOTLIB_AI_MOVE_IN_DIRECTION, movestate, dir, PASSFLOAT(speed), type );
}

void trap_BotResetAvoidReach_real(int movestate) {
	syscall( BOTLIB_AI_RESET_AVOID_REACH, movestate );
}

void trap_BotResetLastAvoidReach_real(int movestate) {
	syscall( BOTLIB_AI_RESET_LAST_AVOID_REACH,movestate  );
}

int trap_BotReachabilityArea_real(vec3_t origin, int testground) {
	return syscall( BOTLIB_AI_REACHABILITY_AREA, origin, testground );
}

int trap_BotMovementViewTarget_real(int movestate, void /* struct bot_goal_s */ *goal, int travelflags, float lookahead, vec3_t target) {
	return syscall( BOTLIB_AI_MOVEMENT_VIEW_TARGET, movestate, goal, travelflags, PASSFLOAT(lookahead), target );
}

int trap_BotPredictVisiblePosition_real(vec3_t origin, int areanum, void /* struct bot_goal_s */ *goal, int travelflags, vec3_t target) {
	return syscall( BOTLIB_AI_PREDICT_VISIBLE_POSITION, origin, areanum, goal, travelflags, target );
}

int trap_BotAllocMoveState_real(void) {
	return syscall( BOTLIB_AI_ALLOC_MOVE_STATE );
}

void trap_BotFreeMoveState_real(int handle) {
	syscall( BOTLIB_AI_FREE_MOVE_STATE, handle );
}

void trap_BotInitMoveState_real(int handle, void /* struct bot_initmove_s */ *initmove) {
	syscall( BOTLIB_AI_INIT_MOVE_STATE, handle, initmove );
}

int trap_BotChooseBestFightWeapon_real(int weaponstate, int *inventory) {
	return syscall( BOTLIB_AI_CHOOSE_BEST_FIGHT_WEAPON, weaponstate, inventory );
}

void trap_BotGetWeaponInfo_real(int weaponstate, int weapon, void /* struct weaponinfo_s */ *weaponinfo) {
	syscall( BOTLIB_AI_GET_WEAPON_INFO, weaponstate, weapon, weaponinfo );
}

int trap_BotLoadWeaponWeights_real(int weaponstate, char *filename) {
	return syscall( BOTLIB_AI_LOAD_WEAPON_WEIGHTS, weaponstate, filename );
}

int trap_BotAllocWeaponState_real(void) {
	return syscall( BOTLIB_AI_ALLOC_WEAPON_STATE );
}

void trap_BotFreeWeaponState_real(int weaponstate) {
	syscall( BOTLIB_AI_FREE_WEAPON_STATE, weaponstate );
}

void trap_BotResetWeaponState_real(int weaponstate) {
	syscall( BOTLIB_AI_RESET_WEAPON_STATE, weaponstate );
}

int trap_GeneticParentsAndChildSelection_real(int numranks, float *ranks, int *parent1, int *parent2, int *child) {
	return syscall( BOTLIB_AI_GENETIC_PARENTS_AND_CHILD_SELECTION, numranks, ranks, parent1, parent2, child );
}

int trap_PC_LoadSource_real( const char *filename ) {
	return syscall( BOTLIB_PC_LOAD_SOURCE, filename );
}

int trap_PC_FreeSource_real( int handle ) {
	return syscall( BOTLIB_PC_FREE_SOURCE, handle );
}

int trap_PC_ReadToken_real( int handle, pc_token_t *pc_token ) {
	return syscall( BOTLIB_PC_READ_TOKEN, handle, pc_token );
}

int trap_PC_SourceFileAndLine_real( int handle, char *filename, int *line ) {
	return syscall( BOTLIB_PC_SOURCE_FILE_AND_LINE, handle, filename, line );
}


/*
Ghoul2 Insert Start
*/
// CG Specific API calls
void trap_G2_ListModelBones_real(void *ghlInfo, int frame)
{
	syscall( G_G2_LISTBONES, ghlInfo, frame);
}

void trap_G2_ListModelSurfaces_real(void *ghlInfo)
{
	syscall( G_G2_LISTSURFACES, ghlInfo);
}

qboolean trap_G2_HaveWeGhoul2Models_real(	void *ghoul2)
{
	return (qboolean)(syscall(G_G2_HAVEWEGHOULMODELS, ghoul2));
}

void trap_G2_SetGhoul2ModelIndexes_real(void *ghoul2, qhandle_t *modelList, qhandle_t *skinList)
{
	syscall( G_G2_SETMODELS, ghoul2, modelList, skinList);
}

qboolean trap_G2API_GetBoltMatrix_real(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix,
								const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale)
{
	return (qboolean)(syscall(G_G2_GETBOLT, ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale));
}

qboolean trap_G2API_GetBoltMatrix_NoReconstruct_real(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix,
								const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale)
{ //Same as above but force it to not reconstruct the skeleton before getting the bolt position
	return (qboolean)(syscall(G_G2_GETBOLT_NOREC, ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale));
}


/* 1.04 */
qboolean trap_G2API_GetBoltMatrix_NoRecNoRot_1_04_real(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix,
								const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale)
{ //Same as above but force it to not reconstruct the skeleton before getting the bolt position
	return (qboolean)(syscall(G_G2_GETBOLT_NOREC_NOROT, ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale));
}

int trap_G2API_InitGhoul2Model_1_04_real(void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin,
						  qhandle_t customShader, int modelFlags, int lodBias)
{
	return syscall(G_G2_INITGHOUL2MODEL, ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias);
}

int trap_G2API_AddBolt_1_04_real(void *ghoul2, int modelIndex, const char *boneName)
{
	return syscall(G_G2_ADDBOLT, ghoul2, modelIndex, boneName);
}

void trap_G2API_SetBoltInfo_1_04_real(void *ghoul2, int modelIndex, int boltInfo)
{
	syscall(G_G2_SETBOLTINFO, ghoul2, modelIndex, boltInfo);
}

qboolean trap_G2API_SetBoneAngles_1_04_real(void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags,
								const int up, const int right, const int forward, qhandle_t *modelList,
								int blendTime , int currentTime )
{
	return (syscall(G_G2_ANGLEOVERRIDE, ghoul2, modelIndex, boneName, angles, flags, up, right, forward, modelList, blendTime, currentTime));
}

qboolean trap_G2API_SetBoneAnim_1_04_real(void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame,
							  const int flags, const float animSpeed, const int currentTime, const float setFrame , const int blendTime )
{
	return syscall(G_G2_PLAYANIM, ghoul2, modelIndex, boneName, startFrame, endFrame, flags, PASSFLOAT(animSpeed), currentTime, PASSFLOAT(setFrame), blendTime);
}

void trap_G2API_GetGLAName_1_04_real(void *ghoul2, int modelIndex, char *fillBuf)
{
	syscall(G_G2_GETGLANAME, ghoul2, modelIndex, fillBuf);
}

int trap_G2API_CopyGhoul2Instance_1_04_real(void *g2From, void *g2To, int modelIndex)
{
	return syscall(G_G2_COPYGHOUL2INSTANCE, g2From, g2To, modelIndex);
}

void trap_G2API_CopySpecificGhoul2Model_1_04_real(void *g2From, int modelFrom, void *g2To, int modelTo)
{
	syscall(G_G2_COPYSPECIFICGHOUL2MODEL, g2From, modelFrom, g2To, modelTo);
}

void trap_G2API_DuplicateGhoul2Instance_1_04_real(void *g2From, void **g2To)
{
	syscall(G_G2_DUPLICATEGHOUL2INSTANCE, g2From, g2To);
}

qboolean trap_G2API_HasGhoul2ModelOnIndex_1_04_real(void *ghlInfo, int modelIndex)
{
	return syscall(G_G2_HASGHOUL2MODELONINDEX, ghlInfo, modelIndex);
}

qboolean trap_G2API_RemoveGhoul2Model_1_04_real(void *ghlInfo, int modelIndex)
{
	return syscall(G_G2_REMOVEGHOUL2MODEL, ghlInfo, modelIndex);
}

void trap_G2API_CleanGhoul2Models_1_04_real(void **ghoul2Ptr)
{
	syscall(G_G2_CLEANMODELS, ghoul2Ptr);
}

void trap_G2API_CollisionDetect_1_04_real ( 
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
	syscall ( G_G2_COLLISIONDETECT, collRecMap, ghoul2, angles, position, frameNumber, entNum, rayStart, rayEnd, scale, traceFlags, useLod, PASSFLOAT(fRadius) );
}

/* 1.02 */
int trap_G2API_InitGhoul2Model_1_02_real(void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin,
						  qhandle_t customShader, int modelFlags, int lodBias)
{
	return syscall(G_G2_INITGHOUL2MODEL_1_02, ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias);
}

int trap_G2API_AddBolt_1_02_real(void *ghoul2, int modelIndex, const char *boneName)
{
	return syscall(G_G2_ADDBOLT_1_02, ghoul2, modelIndex, boneName);
}

void trap_G2API_SetBoltInfo_1_02_real(void *ghoul2, int modelIndex, int boltInfo)
{
	syscall(G_G2_SETBOLTINFO_1_02, ghoul2, modelIndex, boltInfo);
}

qboolean trap_G2API_SetBoneAngles_1_02_real(void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags,
								const int up, const int right, const int forward, qhandle_t *modelList,
								int blendTime , int currentTime )
{
	return (syscall(G_G2_ANGLEOVERRIDE_1_02, ghoul2, modelIndex, boneName, angles, flags, up, right, forward, modelList, blendTime, currentTime));
}

qboolean trap_G2API_SetBoneAnim_1_02_real(void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame,
							  const int flags, const float animSpeed, const int currentTime, const float setFrame , const int blendTime )
{
	return syscall(G_G2_PLAYANIM_1_02, ghoul2, modelIndex, boneName, startFrame, endFrame, flags, PASSFLOAT(animSpeed), currentTime, PASSFLOAT(setFrame), blendTime);
}

void trap_G2API_GetGLAName_1_02_real(void *ghoul2, int modelIndex, char *fillBuf)
{
	syscall(G_G2_GETGLANAME_1_02, ghoul2, modelIndex, fillBuf);
}

int trap_G2API_CopyGhoul2Instance_1_02_real(void *g2From, void *g2To, int modelIndex)
{
	return syscall(G_G2_COPYGHOUL2INSTANCE_1_02, g2From, g2To, modelIndex);
}

void trap_G2API_CopySpecificGhoul2Model_1_02_real(void *g2From, int modelFrom, void *g2To, int modelTo)
{
	syscall(G_G2_COPYSPECIFICGHOUL2MODEL_1_02, g2From, modelFrom, g2To, modelTo);
}

void trap_G2API_DuplicateGhoul2Instance_1_02_real(void *g2From, void **g2To)
{
	syscall(G_G2_DUPLICATEGHOUL2INSTANCE_1_02, g2From, g2To);
}

qboolean trap_G2API_HasGhoul2ModelOnIndex_1_02_real(void *ghlInfo, int modelIndex)
{
	return syscall(G_G2_HASGHOUL2MODELONINDEX_1_02, ghlInfo, modelIndex);
}

qboolean trap_G2API_RemoveGhoul2Model_1_02_real(void *ghlInfo, int modelIndex)
{
	return syscall(G_G2_REMOVEGHOUL2MODEL_1_02, ghlInfo, modelIndex);
}

void trap_G2API_CleanGhoul2Models_1_02_real(void **ghoul2Ptr)
{
	syscall(G_G2_CLEANMODELS_1_02, ghoul2Ptr);
}

/*
Ghoul2 Insert End
*/

/* JK2MV Syscalls */
int trap_MVAPI_GetCurrentGameversion( void )
{
	return syscall( MVAPI_GET_VERSION );
}

qboolean trap_MVAPI_ControlFixes( mvfix_t fixes )
{
	return syscall( MVAPI_CONTROL_FIXES, fixes );
}

qboolean trap_MVAPI_LocateGameData( mvsharedEntity_t *mvEnts, int numGEntities, int sizeofmvsharedEntity_t )
{
	return syscall( MVAPI_LOCATE_GAME_DATA, mvEnts, numGEntities, sizeofmvsharedEntity_t );
}

qboolean trap_MVAPI_SendConnectionlessPacket( const mvaddr_t *addr, const char *message )
{
	return syscall( MVAPI_SEND_CONNECTIONLESSPACKET, addr, message );
}

qboolean trap_MVAPI_GetConnectionlessPacket( mvaddr_t *addr, char *buf, unsigned int bufsize )
{
	return syscall( MVAPI_GET_CONNECTIONLESSPACKET, addr, buf, bufsize );
}
