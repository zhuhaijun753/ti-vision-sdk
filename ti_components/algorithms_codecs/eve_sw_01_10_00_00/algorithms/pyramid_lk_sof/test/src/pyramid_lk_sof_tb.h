#ifndef PYRAMID_LK_SOF_TB
#define PYRAMID_LK_SOF_TB
//#define CREATE_FIXED_MOTION
#define MOTION_u (10)
#define MOTION_v (10)

#define MAX_HEIGHT (1024)
#define MAX_WIDTH  (1280)
#define MAX_PIXEL_DIFF (3)

typedef struct 
{
  float u;
  float v;
  char  valid ;
} sSOFFlow;
void printConfigParams(config_params *params);
#endif /* PYRAMID_LK_SOF_TB */
