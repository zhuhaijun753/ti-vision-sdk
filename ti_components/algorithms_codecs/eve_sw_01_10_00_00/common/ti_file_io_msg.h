
#ifndef _OP_STRUCT_H_
#define _OP_STRUCT_H_


#define FILE_IO_SHARED_MEM_BASE      (0x87000000)
#define FILE_IO_SHARED_MEM_CORE_SYNC (FILE_IO_SHARED_MEM_BASE + 0x1000)

#define MAX_NUM_FILES (20U)
#define MAX_FILE_SIZE (200U)
#define MAX_NUM_MSG   (10U)

typedef struct HOSTFILE
{
    uint32_t     id;
    FILE        *fp;
} HOSTFILE;

typedef struct RETVALUE
{
    int32_t      ret;
} RETVALUE;

typedef struct OpStruct
{
    int32_t      opCode;
    char         fileName[MAX_FILE_SIZE];
    char         mode[4];
    uint32_t     fid;
    int32_t      offset;
    size_t       size;
    size_t       count;
} OpStruct;

typedef struct send_recv_Struct
{
    uint8_t      msgType;  //0 - send, 1 - receive
    char        *ptr;
    uint32_t     size;
} send_recv_Struct;


typedef struct MSG_Q
{
    volatile uint8_t   numMsg;
    send_recv_Struct   msgList[MAX_NUM_MSG];
} MSG_Q;

#endif /* _OP_STRUCT_H_ */
