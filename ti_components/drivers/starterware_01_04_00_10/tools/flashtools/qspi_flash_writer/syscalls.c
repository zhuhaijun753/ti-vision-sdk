/* ====================================================================== 
 *   Copyright (C) 2013 Texas Instruments Incorporated                    
 *                                                                        
 *   All rights reserved. Property of Texas Instruments Incorporated.     
 *   Restricted rights to use, duplicate or disclose this code are        
 *   granted through contract.                                            
 *                                                                        
 *   The program may not be used without the written permission           
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been        
 *   supplied.                                                            
 * ==================================================================== */


#include "stdint.h"
#include <sys/stat.h>
#include <errno.h>

#undef errno
extern int32_t errno;

char *__env[1] = { 0 };
char **environ = __env;

/*
 *  ======== _close ========
 */
int32_t _close(int32_t file) 
{
    return -1;
}

/*
 *  ======== execve ========
 */
int32_t execve(char *name, char **argv, char **env) 
{
    errno = ENOMEM;
    return -1;
}

/*
 *  ======== _exit ========
 */
void _exit(int32_t code) 
{
    asm(" .global C$$EXIT");
    asm("C$$EXIT:");
    while(1){};
}

/*
 *  ======== _fork ========
 */
int32_t fork(void) 
{
    errno = EAGAIN;
    return -1;
}

/*
 *  ======== _fstat ========
 */
int32_t _fstat(int32_t file, struct stat *st) 
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 *  ======== _getpid ========
 */
int32_t _getpid(void) 
{
    return 1;
}

/*
 *  ======== _isatty ========
 */
int32_t _isatty(int32_t file) 
{
    return 1;
}

/*
 *  ======== _kill ========
 */
int32_t _kill(int32_t pid, int32_t sig) 
{
    errno = EINVAL;
    return -1;
}

/*
 *  ======== link ========
 */
int32_t link(char *old, char *new) 
{
    errno = EMLINK;
    return -1;
}

/*
 *  ======== _lseek ========
 */
int32_t _lseek(int32_t file, int32_t ptr, int32_t dir) 
{
    return 0;
}

/*
 *  ======== open ========
 */
int32_t open(const char *name, int32_t flags, int32_t mode) 
{
    return (-1);
}

/*
 *  ======== _open ========
 */
int32_t _open(const char *name, int32_t flags, int32_t mode) 
{
    return (-1);
}

/*
 *  ======== _read ========
 */
int32_t _read(int32_t file, char *ptr, int32_t len) 
{
    return (0);
}

extern uint32_t __heap_start__;
extern uint32_t __heap_end__;

/*
 *  ======== _sbrk ========
 */
int32_t _sbrk(int32_t incr) 
{
    static int32_t heap_size = 0;
    static char * heap_start;
    static char * heap_end;
    uint8_t * prev_heap_end;

    /* init pointers on first call */
    if (heap_size == 0) {
        heap_start = (char *) & __heap_start__;
        heap_end = heap_start;
        heap_size = ((char *) & __heap_end__) - heap_start;
    }
     
    prev_heap_end = heap_end;

    /* check if not enough remaining heap for request */
    if (heap_end + incr - heap_start > heap_size) {
        errno = ENOMEM;
        return(-1);
    }

    heap_end += incr;

    return ((int32_t)prev_heap_end);
}

/*
 *  ======== times ========
 */
int32_t times(void  *buf) 
{
    return (-1);
}

/*
 *  ======== unlink ========
 */
int32_t unlink(char *name) 
{
    errno = ENOENT;
    return (-1);
}

/*
 *  ======== wait ========
 */
int32_t wait(int32_t *status) 
{
    errno = ECHILD;
    return (-1);
}

/*
 *  ======== _write ========
 */
int32_t _write(int32_t file, char *ptr, int32_t len) 
{
    return len;
}

