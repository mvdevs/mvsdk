//g_multiversion_syscalls.h

/*
Just like with g_multiversion_syscalls.c, this is not the desired solution.
The prototypes in this file do not even belong to g_multiversion_syscalls.c, but to g_syscalls.c (dll) / g_syscalls.asm (qvm).
*/

void	trap_Printf_real( const char *fmt );
void	trap_Error_real( const char *fmt );
int		trap_Milliseconds_real( void );
int		trap_Argc_real( void );
void	trap_Argv_real( int n, char *buffer, int bufferLength );
void	trap_Args_real( char *buffer, int bufferLength );
int		trap_FS_FOpenFile_real( const char *qpath, fileHandle_t *f, fsMode_t mode );
void	trap_FS_Read_real( void *buffer, int len, fileHandle_t f );
void	trap_FS_Write_real( const void *buffer, int len, fileHandle_t f );
void	trap_FS_FCloseFile_real( fileHandle_t f );
int		trap_FS_GetFileList_real( const char *path, const char *extension, char *listbuf, int bufsize );
void	trap_SendConsoleCommand_real( int exec_when, const char *text );
void	trap_Cvar_Register_real( vmCvar_t *cvar, const char *var_name, const char *value, int flags );
void	trap_Cvar_Update_real( vmCvar_t *cvar );
void	trap_Cvar_Set_real( const char *var_name, const char *value );
int		trap_Cvar_VariableIntegerValue_real( const char *var_name );
float	trap_Cvar_VariableValue_real( const char *var_name );
void	trap_Cvar_VariableStringBuffer_real( const char *var_name, char *buffer, int bufsize );
void	trap_LocateGameData_real( gentity_t *gEnts, int numGEntities, int sizeofGEntity_t, playerState_t *gameClients, int sizeofGameClient );
void	trap_DropClient_real( int clientNum, const char *reason );
void	trap_SendServerCommand_real( int clientNum, const char *text );
void	trap_SetConfigstring_real( int num, const char *string );
void	trap_GetConfigstring_real( int num, char *buffer, int bufferSize );
void	trap_GetUserinfo_real( int num, char *buffer, int bufferSize );
void	trap_SetUserinfo_real( int num, const char *buffer );
void	trap_GetServerinfo_real( char *buffer, int bufferSize );
void	trap_SetBrushModel_real( gentity_t *ent, const char *name );
void	trap_Trace_real( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask );
int		trap_PointContents_real( const vec3_t point, int passEntityNum );
qboolean trap_InPVS_real( const vec3_t p1, const vec3_t p2 );
qboolean trap_InPVSIgnorePortals_real( const vec3_t p1, const vec3_t p2 );
void	trap_AdjustAreaPortalState_real( gentity_t *ent, qboolean open );
qboolean trap_AreasConnected_real( int area1, int area2 );
void	trap_LinkEntity_real( gentity_t *ent );
void	trap_UnlinkEntity_real( gentity_t *ent );
int		trap_EntitiesInBox_real( const vec3_t mins, const vec3_t maxs, int *entityList, int maxcount );
qboolean trap_EntityContact_real( const vec3_t mins, const vec3_t maxs, const gentity_t *ent );
int		trap_BotAllocateClient_real( void );
void	trap_BotFreeClient_real( int clientNum );
void	trap_GetUsercmd_real( int clientNum, usercmd_t *cmd );
qboolean	trap_GetEntityToken_real( char *buffer, int bufferSize );

#ifdef BOT_ZMALLOC
void	*trap_BotGetMemoryGame_real(int size);
void	trap_BotFreeMemoryGame_real(void *ptr);
#endif

int		trap_DebugPolygonCreate_real(int color, int numPoints, vec3_t *points);
void	trap_DebugPolygonDelete_real(int id);

int		trap_BotLibSetup_real( void );
int		trap_BotLibShutdown_real( void );
int		trap_BotLibVarSet_real(char *var_name, char *value);
int		trap_BotLibVarGet_real(char *var_name, char *value, int size);
int		trap_BotLibDefine_real(char *string);
int		trap_BotLibStartFrame_real(float time);
int		trap_BotLibLoadMap_real(const char *mapname);
int		trap_BotLibUpdateEntity_real(int ent, void /* struct bot_updateentity_s */ *bue);
int		trap_BotLibTest_real(int parm0, char *parm1, vec3_t parm2, vec3_t parm3);

int		trap_BotGetSnapshotEntity_real( int clientNum, int sequence );
int		trap_BotGetServerCommand_real(int clientNum, char *message, int size);
void	trap_BotUserCommand_real(int client, usercmd_t *ucmd);

int		trap_AAS_BBoxAreas_real(vec3_t absmins, vec3_t absmaxs, int *areas, int maxareas);
int		trap_AAS_AreaInfo_real( int areanum, void /* struct aas_areainfo_s */ *info );
void	trap_AAS_EntityInfo_real(int entnum, void /* struct aas_entityinfo_s */ *info);

int		trap_AAS_Initialized_real(void);
void	trap_AAS_PresenceTypeBoundingBox_real(int presencetype, vec3_t mins, vec3_t maxs);
float	trap_AAS_Time_real(void);

int		trap_AAS_PointAreaNum_real(vec3_t point);
int		trap_AAS_PointReachabilityAreaIndex_real(vec3_t point);
int		trap_AAS_TraceAreas_real(vec3_t start, vec3_t end, int *areas, vec3_t *points, int maxareas);

int		trap_AAS_PointContents_real(vec3_t point);
int		trap_AAS_NextBSPEntity_real(int ent);
int		trap_AAS_ValueForBSPEpairKey_real(int ent, char *key, char *value, int size);
int		trap_AAS_VectorForBSPEpairKey_real(int ent, char *key, vec3_t v);
int		trap_AAS_FloatForBSPEpairKey_real(int ent, char *key, float *value);
int		trap_AAS_IntForBSPEpairKey_real(int ent, char *key, int *value);

int		trap_AAS_AreaReachability_real(int areanum);

int		trap_AAS_AreaTravelTimeToGoalArea_real(int areanum, vec3_t origin, int goalareanum, int travelflags);
int		trap_AAS_EnableRoutingArea_real( int areanum, int enable );
int		trap_AAS_PredictRoute_real(void /*struct aas_predictroute_s*/ *route, int areanum, vec3_t origin,
							int goalareanum, int travelflags, int maxareas, int maxtime,
							int stopevent, int stopcontents, int stoptfl, int stopareanum);

int		trap_AAS_AlternativeRouteGoals_real(vec3_t start, int startareanum, vec3_t goal, int goalareanum, int travelflags,
										void /*struct aas_altroutegoal_s*/ *altroutegoals, int maxaltroutegoals,
										int type);
int		trap_AAS_Swimming_real(vec3_t origin);
int		trap_AAS_PredictClientMovement_real(void /* aas_clientmove_s */ *move, int entnum, vec3_t origin, int presencetype, int onground, vec3_t velocity, vec3_t cmdmove, int cmdframes, int maxframes, float frametime, int stopevent, int stopareanum, int visualize);


void	trap_EA_Say_real(int client, char *str);
void	trap_EA_SayTeam_real(int client, char *str);
void	trap_EA_Command_real(int client, char *command);

void	trap_EA_Action_real(int client, int action);
void	trap_EA_Gesture_real(int client);
void	trap_EA_Talk_real(int client);
void	trap_EA_Attack_real(int client);
void	trap_EA_Use_real(int client);
void	trap_EA_Respawn_real(int client);
void	trap_EA_Crouch_real(int client);
void	trap_EA_MoveUp_real(int client);
void	trap_EA_MoveDown_real(int client);
void	trap_EA_MoveForward_real(int client);
void	trap_EA_MoveBack_real(int client);
void	trap_EA_MoveLeft_real(int client);
void	trap_EA_MoveRight_real(int client);
void	trap_EA_SelectWeapon_real(int client, int weapon);
void	trap_EA_Jump_real(int client);
void	trap_EA_DelayedJump_real(int client);
void	trap_EA_Move_real(int client, vec3_t dir, float speed);
void	trap_EA_View_real(int client, vec3_t viewangles);
void	trap_EA_Alt_Attack_real(int client);
void	trap_EA_ForcePower_real(int client);

void	trap_EA_EndRegular_real(int client, float thinktime);
void	trap_EA_GetInput_real(int client, float thinktime, void /* struct bot_input_s */ *input);
void	trap_EA_ResetInput_real(int client);


int		trap_BotLoadCharacter_real(char *charfile, float skill);
void	trap_BotFreeCharacter_real(int character);
float	trap_Characteristic_Float_real(int character, int index);
float	trap_Characteristic_BFloat_real(int character, int index, float min, float max);
int		trap_Characteristic_Integer_real(int character, int index);
int		trap_Characteristic_BInteger_real(int character, int index, int min, int max);
void	trap_Characteristic_String_real(int character, int index, char *buf, int size);

int		trap_BotAllocChatState_real(void);
void	trap_BotFreeChatState_real(int handle);
void	trap_BotQueueConsoleMessage_real(int chatstate, int type, char *message);
void	trap_BotRemoveConsoleMessage_real(int chatstate, int handle);
int		trap_BotNextConsoleMessage_real(int chatstate, void /* struct bot_consolemessage_s */ *cm);
int		trap_BotNumConsoleMessages_real(int chatstate);
void	trap_BotInitialChat_real(int chatstate, char *type, int mcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 );
int		trap_BotNumInitialChats_real(int chatstate, char *type);
int		trap_BotReplyChat_real(int chatstate, char *message, int mcontext, int vcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 );
int		trap_BotChatLength_real(int chatstate);
void	trap_BotEnterChat_real(int chatstate, int client, int sendto);
void	trap_BotGetChatMessage_real(int chatstate, char *buf, int size);
int		trap_StringContains_real(char *str1, char *str2, int casesensitive);
int		trap_BotFindMatch_real(char *str, void /* struct bot_match_s */ *match, unsigned long int context);
void	trap_BotMatchVariable_real(void /* struct bot_match_s */ *match, int variable, char *buf, int size);
void	trap_UnifyWhiteSpaces_real(char *string);
void	trap_BotReplaceSynonyms_real(char *string, unsigned long int context);
int		trap_BotLoadChatFile_real(int chatstate, char *chatfile, char *chatname);
void	trap_BotSetChatGender_real(int chatstate, int gender);
void	trap_BotSetChatName_real(int chatstate, char *name, int client);
void	trap_BotResetGoalState_real(int goalstate);
void	trap_BotRemoveFromAvoidGoals_real(int goalstate, int number);
void	trap_BotResetAvoidGoals_real(int goalstate);
void	trap_BotPushGoal_real(int goalstate, void /* struct bot_goal_s */ *goal);
void	trap_BotPopGoal_real(int goalstate);
void	trap_BotEmptyGoalStack_real(int goalstate);
void	trap_BotDumpAvoidGoals_real(int goalstate);
void	trap_BotDumpGoalStack_real(int goalstate);
void	trap_BotGoalName_real(int number, char *name, int size);
int		trap_BotGetTopGoal_real(int goalstate, void /* struct bot_goal_s */ *goal);
int		trap_BotGetSecondGoal_real(int goalstate, void /* struct bot_goal_s */ *goal);
int		trap_BotChooseLTGItem_real(int goalstate, vec3_t origin, int *inventory, int travelflags);
int		trap_BotChooseNBGItem_real(int goalstate, vec3_t origin, int *inventory, int travelflags, void /* struct bot_goal_s */ *ltg, float maxtime);
int		trap_BotTouchingGoal_real(vec3_t origin, void /* struct bot_goal_s */ *goal);
int		trap_BotItemGoalInVisButNotVisible_real(int viewer, vec3_t eye, vec3_t viewangles, void /* struct bot_goal_s */ *goal);
int		trap_BotGetNextCampSpotGoal_real(int num, void /* struct bot_goal_s */ *goal);
int		trap_BotGetMapLocationGoal_real(char *name, void /* struct bot_goal_s */ *goal);
int		trap_BotGetLevelItemGoal_real(int index, char *classname, void /* struct bot_goal_s */ *goal);
float	trap_BotAvoidGoalTime_real(int goalstate, int number);
void	trap_BotSetAvoidGoalTime_real(int goalstate, int number, float avoidtime);
void	trap_BotInitLevelItems_real(void);
void	trap_BotUpdateEntityItems_real(void);
int		trap_BotLoadItemWeights_real(int goalstate, char *filename);
void	trap_BotFreeItemWeights_real(int goalstate);
void	trap_BotInterbreedGoalFuzzyLogic_real(int parent1, int parent2, int child);
void	trap_BotSaveGoalFuzzyLogic_real(int goalstate, char *filename);
void	trap_BotMutateGoalFuzzyLogic_real(int goalstate, float range);
int		trap_BotAllocGoalState_real(int state);
void	trap_BotFreeGoalState_real(int handle);

void	trap_BotResetMoveState_real(int movestate);
void	trap_BotMoveToGoal_real(void /* struct bot_moveresult_s */ *result, int movestate, void /* struct bot_goal_s */ *goal, int travelflags);
int		trap_BotMoveInDirection_real(int movestate, vec3_t dir, float speed, int type);
void	trap_BotResetAvoidReach_real(int movestate);
void	trap_BotResetLastAvoidReach_real(int movestate);
int		trap_BotReachabilityArea_real(vec3_t origin, int testground);
int		trap_BotMovementViewTarget_real(int movestate, void /* struct bot_goal_s */ *goal, int travelflags, float lookahead, vec3_t target);
int		trap_BotPredictVisiblePosition_real(vec3_t origin, int areanum, void /* struct bot_goal_s */ *goal, int travelflags, vec3_t target);
int		trap_BotAllocMoveState_real(void);
void	trap_BotFreeMoveState_real(int handle);
void	trap_BotInitMoveState_real(int handle, void /* struct bot_initmove_s */ *initmove);
void	trap_BotAddAvoidSpot_real(int movestate, vec3_t origin, float radius, int type);

int		trap_BotChooseBestFightWeapon_real(int weaponstate, int *inventory);
void	trap_BotGetWeaponInfo_real(int weaponstate, int weapon, void /* struct weaponinfo_s */ *weaponinfo);
int		trap_BotLoadWeaponWeights_real(int weaponstate, char *filename);
int		trap_BotAllocWeaponState_real(void);
void	trap_BotFreeWeaponState_real(int weaponstate);
void	trap_BotResetWeaponState_real(int weaponstate);

int		trap_GeneticParentsAndChildSelection_real(int numranks, float *ranks, int *parent1, int *parent2, int *child);

void	trap_SnapVector_real( float *v );

qboolean trap_SP_RegisterServer_real( const char *package );
qboolean trap_SP_Register_real(char *file );
int trap_SP_GetStringTextString_real(const char *text, char *buffer, int bufferLength);

qboolean	trap_ROFF_Clean_real( void );
void		trap_ROFF_UpdateEntities_real( void );
int			trap_ROFF_Cache_real( char *file );
qboolean	trap_ROFF_Play_real( int entID, int roffID, qboolean doTranslation );
qboolean	trap_ROFF_Purge_Ent_real( int entID );




int			trap_RealTime_real( qtime_t *qtime );
void		trap_TraceCapsule_real( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask );
qboolean	trap_EntityContactCapsule_real( const vec3_t mins, const vec3_t maxs, const gentity_t *ent );
int			trap_BotLibStartFrame_real(float time);
int			trap_AAS_PredictClientMovement_real(void /* struct aas_clientmove_s */ *move, int entnum, vec3_t origin, int presencetype, int onground, vec3_t velocity, vec3_t cmdmove, int cmdframes, int maxframes, float frametime, int stopevent, int stopareanum, int visualize);
void		trap_EA_Move_real(int client, vec3_t dir, float speed);
void		trap_EA_EndRegular_real(int client, float thinktime);
void		trap_EA_GetInput_real(int client, float thinktime, void /* struct bot_input_s */ *input);
int			trap_BotLoadCharacter_real(char *charfile, float skill);
int			trap_PC_SourceFileAndLine_real( int handle, char *filename, int *line );
int			trap_PC_ReadToken_real( int handle, pc_token_t *pc_token );
int			trap_PC_LoadSource_real( const char *filename );
int			trap_PC_FreeSource_real( int handle );
qboolean	trap_G2API_GetBoltMatrix_real(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale);
qboolean	trap_G2API_GetBoltMatrix_NoReconstruct_real(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale);
void		trap_G2_SetGhoul2ModelIndexes_real(void *ghoul2, qhandle_t *modelList, qhandle_t *skinList);
void		trap_G2_ListModelSurfaces_real(void *ghlInfo);
void		trap_G2_ListModelBones_real(void *ghlInfo, int frame);
qboolean	trap_G2_HaveWeGhoul2Models_real(void *ghoul2);

qboolean	trap_G2API_GetBoltMatrix_NoRecNoRot_1_04_real(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale);
qboolean	trap_G2API_SetBoneAnim_1_04_real(void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame, const int flags, const float animSpeed, const int currentTime, const float setFrame , const int blendTime );
qboolean	trap_G2API_SetBoneAngles_1_04_real(void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags, const int up, const int right, const int forward, qhandle_t *modelList, int blendTime , int currentTime );
int			trap_G2API_AddBolt_1_04_real(void *ghoul2, int modelIndex, const char *boneName);
void		trap_G2API_SetBoltInfo_1_04_real(void *ghoul2, int modelIndex, int boltInfo);
qboolean	trap_G2API_RemoveGhoul2Model_1_04_real(void *ghlInfo, int modelIndex);
int			trap_G2API_InitGhoul2Model_1_04_real(void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias);
qboolean	trap_G2API_HasGhoul2ModelOnIndex_1_04_real(void *ghlInfo, int modelIndex);
void		trap_G2API_GetGLAName_1_04_real(void *ghoul2, int modelIndex, char *fillBuf);
int			trap_G2API_CopyGhoul2Instance_1_04_real(void *g2From, void *g2To, int modelIndex);
void		trap_G2API_DuplicateGhoul2Instance_1_04_real(void *g2From, void **g2To);
void		trap_G2API_CopySpecificGhoul2Model_1_04_real(void *g2From, int modelFrom, void *g2To, int modelTo);
void		trap_G2API_DuplicateGhoul2Instance_1_04_real(void *g2From, void **g2To);
qboolean	trap_G2API_HasGhoul2ModelOnIndex_1_04_real(void *ghlInfo, int modelIndex);
qboolean	trap_G2API_RemoveGhoul2Model_1_04_real(void *ghlInfo, int modelIndex);
void		trap_G2API_CleanGhoul2Models_1_04_real(void **ghoul2Ptr);
void		trap_G2API_CollisionDetect_1_04_real( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod,	float fRadius );

qboolean	trap_G2API_SetBoneAnim_1_02_real(void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame, const int flags, const float animSpeed, const int currentTime, const float setFrame , const int blendTime );
qboolean	trap_G2API_SetBoneAngles_1_02_real(void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags, const int up, const int right, const int forward, qhandle_t *modelList, int blendTime , int currentTime );
int			trap_G2API_AddBolt_1_02_real(void *ghoul2, int modelIndex, const char *boneName);
void		trap_G2API_SetBoltInfo_1_02_real(void *ghoul2, int modelIndex, int boltInfo);
qboolean	trap_G2API_RemoveGhoul2Model_1_02_real(void *ghlInfo, int modelIndex);
int			trap_G2API_InitGhoul2Model_1_02_real(void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias);
qboolean	trap_G2API_HasGhoul2ModelOnIndex_1_02_real(void *ghlInfo, int modelIndex);
void		trap_G2API_GetGLAName_1_02_real(void *ghoul2, int modelIndex, char *fillBuf);
int			trap_G2API_CopyGhoul2Instance_1_02_real(void *g2From, void *g2To, int modelIndex);
void		trap_G2API_DuplicateGhoul2Instance_1_02_real(void *g2From, void **g2To);
void		trap_G2API_CopySpecificGhoul2Model_1_02_real(void *g2From, int modelFrom, void *g2To, int modelTo);
void		trap_G2API_DuplicateGhoul2Instance_1_02_real(void *g2From, void **g2To);
qboolean	trap_G2API_HasGhoul2ModelOnIndex_1_02_real(void *ghlInfo, int modelIndex);
qboolean	trap_G2API_RemoveGhoul2Model_1_02_real(void *ghlInfo, int modelIndex);
void		trap_G2API_CleanGhoul2Models_1_02_real(void **ghoul2Ptr);

