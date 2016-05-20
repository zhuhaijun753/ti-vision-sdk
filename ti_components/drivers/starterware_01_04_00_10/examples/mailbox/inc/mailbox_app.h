
#ifndef MAILBOX_APP_H_
#define MAILBOX_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAILBOX_APP_A8_MSG  'A'
#define MAILBOX_APP_A15_MSG 'B'
#define MAILBOX_APP_M3_MSG  'C'
#define MAILBOX_APP_M4_MSG  'D'
#define MAILBOX_APP_DSP_MSG 'E'

#ifdef BUILD_A8
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_A8_MSG
#elif defined (BUILD_A15)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_A15_MSG
#elif defined (BUILD_M3)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_M3_MSG
#elif defined (BUILD_M4)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_M4_MSG
#elif defined (BUILD_DSP)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_DSP_MSG
#endif

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* MAILBOX_APP_H_ */

