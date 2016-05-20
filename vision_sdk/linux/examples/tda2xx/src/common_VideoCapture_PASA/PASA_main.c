#include <linux/examples/tda2xx/include/chains.h>
#include <linux/examples/tda2xx/src/usecases/vip_single_cam_sgx_display_PASA/chains_vipSingleCam_SgxDisplay_PASA.h>

#include "chains_main.h"
Chains_Ctrl gChains_usecaseCfg;

Bool fileFlag = 0;//fileFlag 0 -> save to multiple files, 1-> overwrite single file
Bool displayFlag = 1;//displayFlag 0 -> no display 1-> enable display

int main(int argc, char **argv)
{
    char ch;
    UInt32 done = FALSE;

    if (argc == 1)
    {
        fileFlag = 0;
        displayFlag = 1;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1],"1") == 0)
        {
            fileFlag = 1;
        }
        else if (strcmp(argv[1],"no-display") == 0)
        {
            displayFlag = 0;
        }
        else
        {
            fileFlag = 0;
            displayFlag = 1;
            printf("/n unsupported arguments!!!");
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1],"1") == 0 || strcmp(argv[2],"1") == 0)
        {
            fileFlag = 1;
        }
        else
        {
            fileFlag = 0;
            printf("\n   Unsupported file argument : try '1' for single file write  \n");
        }
        if (strcmp(argv[1],"no-display") == 0 || strcmp(argv[2],"no-display") == 0)
        {
            displayFlag = 0;
        }
        else
        {
            displayFlag = 1;
            printf("\n   Unsupported display argument : try 'no-display' for disabling display  \n");
        }
     }
    if (fileFlag == 0)
    {
        printf("\n**** Writing Image Frames to Multiple Files ***\n");
    }
    else
    {
        printf("\n*** Writing Image Frames to Single File ***\n");
    }

    if (displayFlag == 0)
    {
        printf("\n**** Display Disabled ***\n\n");
    }
    else
    {
        printf("\n*** Display Enabled ***\n\n");
    }

    chains_vipSingleCam_SgxDisplay_PASAAppObj chainsObj;

    chains_PASA_Init();

    chainsObj.chainsCfg = &gChains_usecaseCfg;

    chains_vipSingleCam_SgxDisplay_PASA_Create(&chainsObj.ucObj, &chainsObj);

    chains_vipSingleCam_SgxDisplay_PASA_StartApp(&chainsObj);

    while(!done)
    {
        ch = Chains_menuRunTime();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
            case 'P':
                ChainsCommon_prfCpuLoadPrint();
                ChainsCommon_statCollectorPrint();
                chains_vipSingleCam_SgxDisplay_PASA_printStatistics(&chainsObj.ucObj);
                chains_vipSingleCam_SgxDisplay_PASA_printBufferStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    printf("\n\n******** Usecase Execution Completed ************\n\n");

    chains_vipSingleCam_SgxDisplay_PASA_StopApp(&chainsObj);

    ChainsCommon_appCtrlCommonDeInit();
    System_deInit(0);

    return 0;

}
