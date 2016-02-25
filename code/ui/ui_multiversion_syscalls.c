//ui_multiversion_syscalls.c

/*
This file contains functions with the names of the original trap_* methods.
These functions call the multiversion functions before calling the (renamed) original functions.

I didn't intend to "rename & replace" all the trap_* functions,
but given that they're different depending on whether we build qvms or native libraries I am going with this approach now.
*/
#include "ui_local.h"
#include "ui_multiversion_syscalls.h"

void trap_Key_KeynumToStringBuf( int keynum, char *buf, int buflen )
{
	trap_Key_KeynumToStringBuf_real( Key_GetProtocolKey(jk2version, keynum), buf, buflen );
}

void trap_Key_GetBindingBuf( int keynum, char *buf, int buflen )
{
	trap_Key_GetBindingBuf_real( Key_GetProtocolKey(jk2version, keynum), buf, buflen );
}

void trap_Key_SetBinding( int keynum, const char *binding )
{
	trap_Key_SetBinding_real( Key_GetProtocolKey(jk2version, keynum), binding );
}

qboolean trap_Key_IsDown( int keynum )
{
	return trap_Key_IsDown_real( Key_GetProtocolKey(jk2version, keynum) );
}
