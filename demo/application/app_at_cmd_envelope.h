/*
 * =====================================================================================
 *
 *       Filename:  app_at_cmd_envelope.h
 *
 *    Description:  the head file
 *
 *        Version:  1.0
 *        Created:  2014-1-11 15:58:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jumping (apple), zhangping@sim.com
 *   Organization:  www.sim.com
 *
 * =====================================================================================
 */

/* #####   HEADER FILE INCLUDES   ################################################### */

/* #####   EXPORTED MACROS   ######################################################## */
#define URC_QUEUE_COUNT 10                      /* global urc count */
#define AT_CMD_QUEUE_COUNT 50
#define AT_CMD_EXECUTE_DELAY  10                /* 10 ms use EAT_TIMER_1*/
#define AT_CMD_EXECUTE_OVERTIME 60000           /* 60s use EAT_TIMER_2*/

#define AT_CMD_DELAY "DELAY:"
#define AT_CMD_END "\x0d\x0a"
#define AT_CMD_CR  '\x0d'
#define AT_CMD_LF  '\x0a'
#define AT_CMD_CTRL_Z "\x1a"

/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */
typedef enum
{
    AT_RSP_ERROR = -1,
    AT_RSP_WAIT= 0, 
    AT_RSP_CONTINUE = 1,                        /* 继续执行下一条AT队列里的命令 */
    AT_RSP_PAUSE= 2,                            /* 暂停执行AT队列命令 */
    AT_RSP_FINISH = 3,                          /* 停止执行AT队列命令 */

    AT_RSP_FUN_OVER = 4,                        /* 功能模块化AT命令组执行完毕，可以把本次运行的功能清除 */
    AT_RSP_STEP_MIN = 10,
    AT_RSP_STEP = 20,                           /* 继续执行本条AT命令 */
    AT_RSP_STEP_MAX = 30,

}AtCmdRsp;

typedef AtCmdRsp (*AtCmdRspCB)(u8 *pRspStr);
typedef void (*UrcCB)(u8 *pUrcStr, u16 len);
typedef void (*ResultNotifyCb)(eat_bool result);
//typedef void (*SmsReadCB)(u16 index,u8* number,u8 *msg);
typedef void (*SmsReadCB)(u8* number,u8 *msg);

typedef struct AtCmdEntityTag
{
    u8* p_atCmdStr;//命令字符串
    u16 cmdLen;//命令长度
    AtCmdRspCB p_atCmdCallBack;//回调函数，对modem的返回值，进行处理。

}AtCmdEntity;

typedef struct UrcEntityTag
{
    u8* p_urcStr;
    UrcCB p_urcCallBack;

}UrcEntity;


/* #####   EXPORTED DATA TYPES   #################################################### */

/* #####   EXPORTED VARIABLES   ##################################################### */

/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */
extern eat_bool simcom_gsm_init(u8* cpin,ResultNotifyCb pResultCb);
extern void simcom_atcmd_queue_init(void);
extern eat_bool simcom_atcmd_queue_append(AtCmdEntity atCmdEntity);
extern eat_bool simcom_atcmd_queue_fun_append(AtCmdEntity* atCmdEntity,u8 funCount,ResultNotifyCb callback);
extern void app_at_cmd_envelope(void *data);
extern eat_bool simcom_atcmd_queue_is_empty(void);
extern eat_bool simcom_ftp_down_file( u8 *username, u8 *pwd, u8 *getName, u8 *getPath, 
        u8 *serv, u8 port, u8 *fileName, ResultNotifyCb pResultCb, ResultNotifyCb finalCb);
extern eat_bool simcom_atcmd_queue_fun_set(u8 funCount,ResultNotifyCb callback);


extern void SendAtComHandle(void);
extern AtCmdRsp AtCmdCbCIFSR(u8* pRspStr);
extern AtCmdRsp AtCmdCbCIPSTART(u8* pRspStr);
extern AtCmdRsp AtCmdCbCIPSHUT(u8* pRspStr);
#if EnableGPSModule
extern void gps_urc_handler(u8* pUrcStr, u16 len);
#endif
extern eat_bool CALL_AT_ATH(ResultNotifyCb pResultCb);
extern eat_bool CALL_AT_ATA(ResultNotifyCb pResultCb);

extern void clear_CallArry(void);
