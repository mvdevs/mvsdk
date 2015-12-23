//ui_multiversion_syscalls.h

/*
Just like with ui_multiversion_syscalls.c, this is not the desired solution.
The prototypes in this file do not even belong to ui_multiversion_syscalls.c, but to ui_syscalls.c (dll) / ui_syscalls.asm (qvm).
*/

void trap_Key_KeynumToStringBuf_real( int keynum, char *buf, int buflen );
void trap_Key_GetBindingBuf_real( int keynum, char *buf, int buflen );
void trap_Key_SetBinding_real( int keynum, const char *binding );
qboolean trap_Key_IsDown_real( int keynum );
