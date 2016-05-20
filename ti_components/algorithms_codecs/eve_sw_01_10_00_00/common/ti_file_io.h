
#ifndef _FILE_IO_TEST_H_
#define _FILE_IO_TEST_H_

#include "ti_file_io_msg.h"

#ifndef USE_HOST_FILE_IO
#define TI_FILE FILE
#define FOPEN   fopen
#define FCLOSE  fclose
#define FREAD   fread
#define FWRITE  fwrite
#define FSEEK   fseek
#define FTELL   ftell
#define FGETS   fgets
#define FPRINTF fprintf
#define FSCANF  fscanf
#else
#define TI_FILE HOSTFILE
#define FOPEN   ti_fileio_fopen
#define FCLOSE  ti_fileio_fclose
#define FREAD   ti_fileio_fread
#define FWRITE  ti_fileio_fwrite
#define FSEEK   ti_fileio_fseek
#define FTELL   ti_fileio_ftell
#define FGETS   ti_fileio_fgets
#define FPRINTF ti_fileio_fprintf
#define FSCANF  ti_fileio_fscanf

typedef enum {
    TI_FILEIO_OPCODE_FOPEN = 1,
    TI_FILEIO_OPCODE_FCLOSE,
    TI_FILEIO_OPCODE_FREAD,
    TI_FILEIO_OPCODE_FWRITE,
    TI_FILEIO_OPCODE_FSEEK,
    TI_FILEIO_OPCODE_FTELL,
    TI_FILEIO_OPCODE_FGETS,
    TI_FILEIO_OPCODE_FPRINTF,
    TI_FILEIO_OPCODE_FSCANF
} TI_FILEIO_OPCODE;


HOSTFILE* ti_fileio_fopen(const char * filename, const char * mode);
int8_t    ti_fileio_fclose(HOSTFILE * fp);
size_t    ti_fileio_fread(void * ptr, size_t size, size_t count, HOSTFILE * fp);
size_t    ti_fileio_fwrite(void * ptr, size_t size, size_t count, HOSTFILE * fp);
int8_t    ti_fileio_fseek(HOSTFILE * fp, int32_t offset, int32_t origin);
int32_t   ti_fileio_ftell(HOSTFILE * fp);
char *    ti_fileio_fgets(char * str, int32_t num, HOSTFILE * fp);
int32_t   ti_fileio_fprintf(HOSTFILE *fp, char *format, ...);
int32_t   ti_fileio_fscanf(HOSTFILE *fp, char *format, ...);
#endif

#endif /* _FILE_IO_TEST_H_ */
