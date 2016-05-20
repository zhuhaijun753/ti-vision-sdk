/* =============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *  Property of Texas Instruments
 *  For Unrestricted Internal Use Only 
 *  Unauthorized reproduction and/or distribution is strictly
 *  prohibited.
 *  This product is protected under copyright law and trade secret law  
 *  as an unpublished work.
 *  Created 2008, (C) Copyright 2008 Texas Instruments.  All rights 
 *  reserved.
 */
/*
 *  @Component    INTH_dsp - Project specific Interrupt handler fucntions for dsp
 *
 *  @Filename     INTH_dsp.h
 *
 *  @Description  Contains Interrupt (IRQ) handler functions allowing
 *                the registering of interrupt handlers for specific vectors.
 *                This file allso contains primary ARM11 irq handler.
 *
 *                Available Functions:
 *                   INTH_InitHandler - Initialisess all interrupt handlers
 *                   EVE_HOST_INTH_InterruptSetup - registers and sets up interupt handler
 *                   INTH_RegisterHandler - registers specific handlers
 *                   INTH_GetIntCount - Get interupt count for a vector
 *                   INTH_IRQHandler - HLL IRQ Handler
 *                   INTH_FIQHandler - HLL FIQ Handler
 *                   INTH_BusError - UMA Bus Error handler
 *
 *//*======================================================================== */
/**
*  @file       INTH.h
*
*  @brief      Contains Interrupt (IRQ) handler functions allowing
*              the registering of interrupt handlers for specific vectors.
*              This file allso contains primary ARM11 irq handler.
*
*  This header defines all interrupt handler API's and events for the DSP host
*
*/
#ifndef __INTH_H
#define __INTH_H

/* ============================================================================
* INCLUDE FILES (only if necessary)
* =============================================================================
*/

#ifdef __cplusplus
extern "C"
{
#endif

/* ============================================================================
* EXPORTED DEFINITIONS
* =============================================================================
*/

/*-------------------------------------------------------------------------*//*
 * @DEFINITION   INTH_INT_ID_*
 *
 * @BRIEF        Interrupt IDs for all ARM11 interrupts
 *
 * @DESCRIPTION  Interrupt IDs for all ARM11 interrupts
 *
 *//*------------------------------------------------------------------------ */
/**
 *  @brief      Interrupt IDs definitions for all ARM11 interrupts
 */
#define C64

#define INTH_INT_ID_EVT0                0               /**< event 0 from event combiner */ 
#define INTH_INT_ID_EVT1                1               /**< event 1 from event combiner */
#define INTH_INT_ID_EVT2                2               /**< event 2 from event combiner */
#define INTH_INT_ID_EVT3                3               /**< event 3 from event combiner */
                                                        
#define INTH_INT_ID_EMU_DTDMA           9               /**< emu_dtdma */
                                                        
#define INTH_INT_ID_EMU_RDTXRX          11              /**< emu_rdtxrx */
#define INTH_INT_ID_EMU_RDTXTX          12              /**< emu_rdtxtx */
#define INTH_INT_ID_IDMAINT0            13              /**< idma interrupt 0 */
#define INTH_INT_ID_IDMAINT1            14              /**< idma interrupt 1 */
#define INTH_INT_ID_SDINT0              15              /**< IRQOQN */
#define INTH_INT_ID_SPIINT0             16              /**< SINTERRUPTN */
#define INTH_INT_ID_VCPINT             	17              /**< vcp_int */
#define INTH_INT_ID_ELM_IRQ            	18              /**< ELM_IRQ */
#define INTH_INT_ID_ELM            	    18              /**< ELM_IRQ */
#define INTH_INT_ID_IDEINTR            	19              /**< PATA ide_int */
#define INTH_INT_ID_EDMACOMPINT         20              /**< tpcc_int_pend_n[0] */
#define INTH_INT_ID_EDMAERRINT          21              /**< tpcc_errint_pend_n */
#define INTH_INT_ID_TCERRINT0           22              /**< tptc_errint_pend_n */
#define INTH_INT_ID_ISS_IRQ4            23              /**< iss_irq[4] */
#define INTH_INT_ID_TPPMBOXINT          24              /**< TPPSS_MAIL_U0_INTR_PEND_N */
#define INTH_INT_ID_TPPDMAPKT           25              /**< TPPSS_DMAPC0_INTR_PEND_N */
#define INTH_INT_ID_TPPDMABS            26              /**< TPPSS_DMABS0_INTR_PEND_N */
#define HOST_TPPSS_DMABS0_INTRNUM       26              /**< TPPSS_DMABS0_INTR_PEND_N */
#define INTH_INT_ID_TCERRINT1           27              /**< tptc_lerrint_po */
#define INTH_INT_ID_TCERRINT2           28              /**< tptc_lerrint_po */
#define INTH_INT_ID_TCERRINT3           29              /**< tptc_lerrint_po */
#define INTH_INT_ID_SDINT1              30              /**< IRQOQN */
#define INTH_INT_ID_SDINT2              31              /**< IRQOQN */
#define INTH_INT_ID_3PGSWRXTHR0         32              /**< c0_rx_thresh_intr_pend */
#define INTH_INT_ID_3PGSWRXINT0         33              /**< c0_rx_intr_pend */
#define INTH_INT_ID_3PGSWTXINT0         34              /**< c0_tx_intr_pend */
#define INTH_INT_ID_3PGSWMISC0          35              /**< c0_misc_intr_pend */
#define INTH_INT_ID_PCIINTA             36              /**< pcie_int_i_intr_pend_n0 */
#define INTH_INT_ID_PCIINTB             37              /**< pcie_int_i_intr_pend_n1 */
#define INTH_INT_ID_PCIINTC             38              /**< pcie_int_i_intr_pend_n2 */
#define INTH_INT_ID_PCIINTD             39              /**< pcie_int_i_intr_pend_n3 */
#define INTH_INT_ID_HDDSS               40              /**< intr0_intr_pend_n */
#define INTH_INT_ID_HDMIINT             41              /**< intro_intr_pend_n */
#define INTH_INT_ID_SATAINT             42              /**< intrq_pend_n */
#define INTH_INT_ID_GFXINT              43              /**< THALIAIRQ */
#define INTH_INT_ID_SECURESS_PUBLIC_INT 44              /**< nss_pub_top_intr_pending */
#define INTH_INT_ID_SECURESS_MBINT      45              /**< nss_swi_pub_top_intr_pending */
#define INTH_INT_ID_FDIFINT             46              /**< FDIF_IRQ3 */
#define INTH_INT_ID_WDINT               47              /**< PO_INT_REQ */
#define INTH_INT_ID_TINT0               48              /**< POINTR_PEND */
#define INTH_INT_ID_TINT1               49              /**< POINTR_PEND */
#define INTH_INT_ID_TINT2               50              /**< POINTR_PEND */
#define INTH_INT_ID_TINT3               51              /**< POINTR_PEND */
#define INTH_INT_ID_TINT4               52              /**< POINTR_PEND */
#define INTH_INT_ID_TINT5               53              /**< POINTR_PEND */
#define INTH_INT_ID_TINT6               54              /**< POINTR_PEND */
#define INTH_INT_ID_TINT7               55              /**< POINTR_PEND */
#define INTH_INT_ID_MBINT               56              /**< mail_u0_irq */
#define INTH_INT_ID_GPIOINT3A           57              /**< POINTRPEND1 */
#define INTH_INT_ID_I2CINT0             58              /**< POINTRPEND */
#define INTH_INT_ID_I2CINT1             59              /**< POINTRPEND */
#define INTH_INT_ID_UARTINT0            60              /**< uart0_nirq */
#define INTH_INT_ID_UARTINT1            61              /**< uart1_nirq */
#define INTH_INT_ID_UARTINT2            62              /**< uart2_nirq */
#define INTH_INT_ID_GPIOINT3B           63              /**< POINTRPEND2 */
#define INTH_INT_ID_GPIOINT0A           64              /**< POINTRPEND0 */
#define INTH_INT_ID_GPIOINT0B           65              /**< POINTRPEND0 */
#define INTH_INT_ID_GPIOINT1A           66              /**< POINTRPEND1 */
#define INTH_INT_ID_GPIOINT1B           67              /**< POINTRPEND1 */
#define INTH_INT_ID_GPIOINT2A           68              /**< POINTRPEND1 */
#define INTH_INT_ID_GPIOINT2B           69              /**< POINTRPEND2 */
#define INTH_INT_ID_MCATXINT0           70              /**< mcasp_t_intr_pend */
#define INTH_INT_ID_MCARXINT0           71              /**< mcasp_r_intr_pend */
#define INTH_INT_ID_MCATXINT1           72              /**< mcasp_t_intr_pend */
#define INTH_INT_ID_MCARXINT1           73              /**< mcasp_r_intr_pend */
#define INTH_INT_ID_MCATXINT2           74              /**< mcasp_t_intr_pend */
#define INTH_INT_ID_MCARXINT2           75              /**< mcasp_r_intr_pend */
#define INTH_INT_ID_MCBSPINT            76              /**< PORCOMMONIRQ */
#define INTH_INT_ID_UARTINT3            77              /**< uart3_nirq */
#define INTH_INT_ID_UARTINT4            78              /**< uart4_nirq */
#define INTH_INT_ID_UARTINT5            79              /**< uart5_nirq */
#define INTH_INT_ID_MCATXINT3           80              /**< mcasp_x_intr_pend */
#define INTH_INT_ID_MCARXINT3           81              /**< mcasp_r_intr_pend */
#define INTH_INT_ID_MCATXINT4           82              /**< mcasp_x_intr_pend */
#define INTH_INT_ID_MCARXINT4           83              /**< mcasp_r_intr_pend */
#define INTH_INT_ID_MCATXINT5           84              /**< mcasp_x_intr_pend */
#define INTH_INT_ID_MCARXINT5           85              /**< mcasp_r_intr_pend */
#define INTH_INT_ID_SPIINT1             86              /**< SINTERRUPTN */
#define INTH_INT_ID_SPIINT2             87              /**< SINTERRUPTN */
#define INTH_INT_ID_SPIINT3             88              /**< SINTERRUPTN */
#define INTH_INT_ID_I2CINT2             89              /**< POINTRPEND */
#define INTH_INT_ID_IVA0CONT1SYNC       90              /**< IVA_HD0_POSYNCINTRPEDN1 */
#define INTH_INT_ID_IVA0CONT2SYNC       91              /**< IVA_HD0_POSYNCINTRPEDN2 */
#define INTH_INT_ID_I2CINT3             92              /**< POINTRPEND */
#define INTH_INT_ID_MCMMUINT            93              /**< POMMUHOSTINTTR */
#define INTH_INT_ID_IVA0MBOXINT         94              /**< IVA_HD0_POMBINTRPEND0 */
#define INTH_INT_ID_GPMCINT             95              /**< gpmc_sinterrupt */
#define INTH_INT_ID_INTERR              96              /**< error interrupt */
#define INTH_INT_ID_EMC_IDMAERR         97              /**< emc_idmaerr */
#define INTH_INT_ID_PBISTINTERR         98              /**< PBISTINTERR */
                                                        
#define INTH_INT_ID_EFINTA              100	            /**< EFINTA */
#define INTH_INT_ID_EFINTB              101	            /**< EFINTB */
                                                        
#define INTH_INT_ID_PMC_ED              113	            /**< PMC_ED */
                                                        
#define INTH_INT_ID_UMCED1              116	            /**< UMCED1 */
#define INTH_INT_ID_UMCED2              117	            /**< UMCED2 */
#define INTH_INT_ID_PDC_INT             118	            /**< PDC_INT */
#define INTH_INT_ID_SYS_CMPA            119	            /**< SYS_CMPA */
#define INTH_INT_ID_PMC_CMPA            120	            /**< PMC_CMPA */
#define INTH_INT_ID_PMC_DMPA            121	            /**< PMC_DMPA */
#define INTH_INT_ID_DMC_CMPA            122             /**< DMC_CMPA */
#define INTH_INT_ID_DMC_DMPA            123             /**< DMC_CMPA */
#define INTH_INT_ID_UMCCMPA             124             /**< UMCCMPA */
#define INTH_INT_ID_UMCDMPA             125             /**< UMCDMPA */
#define INTH_INT_ID_EMC_CMPA            126             /**< EMC_CMPA */
#define INTH_INT_ID_EMC_BUSERR          127             /**< EMC_BUSERR */

/* GEM Crossbar Mapping */

#define INTH_INT_ID_DCAN0_INT0          15              /**< dcan_int0 */
#define INTH_INT_ID_DCAN0_INT1          16              /**< dcan_int1 */
#define INTH_INT_ID_DCAN0_PARIT         17              /**< dcan_parity_int */
#define INTH_INT_ID_DCAN1_INT0          18              /**< dcan_int0 */
#define INTH_INT_ID_DCAN1_INT1          19              /**< dcan_int1 */
#define INTH_INT_ID_DCAN1_PARIT         20              /**< dcan_parity_int */
#define INTH_INT_ID_MLB_SYS_INT0        21              /**< MLB_SYS_INT0  */
#define INTH_INT_ID_MLB_SYS_INT1        22              /**< MLB_SYS_INT1  */
#define INTH_INT_ID_MLB_INT             23              /**< MLB_INT */
#define INTH_INT_ID_SEC_EVNT           	24              /**< security_events_irq */
#define INTH_INT_ID_L3DEBUG             25              /**< l3_dbg_irq */
#define INTH_INT_ID_L3APPINT            26              /**< l3_app_irq */
#define INTH_INT_ID_EDMAMPERR           27              /**< tpcc_mpint_pend_n */
#define INTH_INT_ID_TINT8               28              /**< POINTR_PEND */
#define INTH_INT_ID_WDINT0              29              /**< PO_INT_REQ */
#define INTH_INT_ID_USBSSINT            30              /**< usbss_intr_pend */
#define INTH_INT_ID_USBINT0             31              /**< usb0_intr_pend */
#define INTH_INT_ID_USBINT1             32              /**< usb1_intr_pend */
#define INTH_INT_ID_RTCINT              33              /**< timer_intr_pend */
#define INTH_INT_ID_RTC_ALARM           34              /**< alarm_intr_pend */
#define INTH_INT_ID_SMCDINT0            35              /**< icc_irq0 */
#define INTH_INT_ID_SMCDINT1            36              /**< icc_irq1 */
#define INTH_INT_ID_DDRERR0             37              /**< mem_err_intr_pend_n */
#define INTH_INT_ID_DDRERR1             38              /**< mem_err_intr_pend_n */

/* -------------------------------------------------------------------------- */

#define INTH_DEFAULT_INTERRUPT_KIND     INTH_TYPE_IRQ     /**< type of default interrupt */
#define INTH_DEFAULT_PRIORITY           0                 /**< default priority of interrupt */

/* ============================================================================
* EXPORTED TYPES
* =============================================================================
*/

/*-------------------------------------------------------------------------*//**
 *
 * @brief        function pointer to interrupt handlers
 *
 * @details      A function pointer to interrupt handlers. The functions should
 *               be defined in the following format:
 *
 *               void PREFIX_IntHandler(UWORD8 inInterrupt);
 *
 *//*------------------------------------------------------------------------ */
typedef void (*INTH_Handler_t)(UWORD32);


/*-------------------------------------------------------------------------*//**
 *
 * @brief        Specifies the type of interrupt
 *
 * @details      Specifies the type of interrupt
 *
 *//*------------------------------------------------------------------------ */
typedef enum INTH_Type_label
{
    INTH_TYPE_MAX1 = 0   // this should not be used any more 

} INTH_Type_t, *pINTH_Type_t;     /**< INTH_Type_t, *pINTH_Type_t */

/*-------------------------------------------------------------------------*//**
 *
 * @brief        Copy from INTCTL
 *
 * @details      Copy from INTCTL
 *
 *//*------------------------------------------------------------------------ */
typedef enum INTH_InterruptKind_label
{
    INTH_TYPE_IRQ,                     /**< IRQ TYPE */
    INTH_TYPE_FIQ,                     /**< FIQ TYPE */
    INTH_TYPE_MAX = INTH_TYPE_FIQ      /**< Max Value for INT TYPE */

} INTH_InterruptKind_t;
#define INTH_IRQ INTCTL_IRQ     /**< IRQ INTCTL */
#define INTH_FIQ INTCTL_FIQ     /**< FIQ INTCTL */

/*-------------------------------------------------------------------------*//**
 *
 * @brief        Copy from INTCTL
 *
 * @details      Copy from INTCTL
 *
 *//*------------------------------------------------------------------------ */
typedef UWORD8 INTH_Priority_t;

/* ============================================================================
* EXPORTED VARIABLES
* =============================================================================
*/

/* ============================================================================
* EXPORTED FUNCTIONS/MACROS
* =============================================================================
*/

/* ------------------------------------------------------------------------*//**
 *
 * @brief         Interrupt handler initialisation
 *
 * @param[in]     intHandler (default interrupt handler (NULL is valid input))
 * @param[in]     intType (Specifies type of interrupt)
 *
 * @return        ReturnCode_t       
 *                     RET_OK                    No errors occured
 *                     RET_PARAM_OUT_OF_RANGE    intType parameter invalid
 *
 * @details       Carries out Interrupt handler initialisation for all interrupt
 *                vectors of a specified type
 *
 * @remarks       Check input parameter correct.
 *                assigns all interrupt vectors of the specified type
 *                the hanlder specified.
 *
 * @note         This function should not be called directly by test cases.
 *
 *//*------------------------------------------------------------------------ */
extern ReturnCode_t EVE_HOST_INTH_InitHandler( const INTH_Handler_t intHandler,
                                      const INTH_Type_t    intType );

/* ------------------------------------------------------------------------*//**
 *
 * @brief         Installs the specified interrupt handler
 *
 * @param[in]     intVector (Interrupt vector for which to install interrupt)
 * @param[in]     intHandler (interrupt handler for specified vector (NULL is valid input))
 * @param[in]     intType (Specifies type of interrupt)
 *
 * @return        ReturnCode_t       
 *                     RET_OK                    No errors occured
 *                     RET_BAD_NULL_PARAM        Address/pointer Paramater was set to 0/NULL
 *                     RET_PARAM_OUT_OF_RANGE    intType parameter invalid
 *
 * @details       Installs the specified interrupt handler for the specified
 *                interrupt vector/type and clears the interrupt counter
 *
 * @remarks       Checks input parameters
 *                installs handler in array with offset on vector
 *                Reset interrupt counter.
 *
 * @note          In general it is better to use the function EVE_HOST_INTH_InterruptSetup
 *
 *//*------------------------------------------------------------------------ */
#if defined (SEC)
extern ReturnCode_t EVE_HOST_INTH_RegisterHandler( const UWORD16            intVector,
                                          const INTH_Handler_t    intHandler,
                                          const INTH_Type_t       intType);
#else
extern ReturnCode_t EVE_HOST_INTH_RegisterHandler( const UWORD8            intVector,
                                          const INTH_Handler_t    intHandler,
                                          const INTH_Type_t       intType);
#endif

/* ------------------------------------------------------------------------*//**
 *
 * @brief         Installs the specified interrupt handler
 *
 * @param[in]     intVector (Interrupt vector for which to install interrupt)
 * @param[in]     intHandler (interrupt handler for specified vector (NULL is valid input))
 * @param[in]     intKind (Specifies type of interrupt)
 * @param[in]     intPriority (Specifies interrupt priority)
 *
 * @return        ReturnCode_t       
 *                     RET_OK                    No errors occured
 *                     RET_BAD_NULL_PARAM        Address/pointer Paramater was set to 0/NULL
 *                     RET_PARAM_OUT_OF_RANGE    intType parameter invalid
 *
 * @details       Installs the specified interrupt handler for the specified
 *                interrupt vector/type, clears the interrupt counter and
 *                configure interrupt controler specific stuff
 *
 * @remarks       Checks input parameters
 *                installs handler in array with offset on vector
 *                Reset interrupt counter.
 *
 *//*------------------------------------------------------------------------ */
#if defined (SEC)
extern ReturnCode_t EVE_HOST_INTH_InterruptSetup( const UWORD16              intVector,
                                         const INTH_Handler_t       intHandler,
                                         const INTH_InterruptKind_t intKind,
                                         const INTH_Priority_t      intPriority);
#else
extern ReturnCode_t EVE_HOST_INTH_InterruptSetup( const UWORD8               intVector,
                                         const INTH_Handler_t       intHandler,
                                         const INTH_InterruptKind_t intKind,
                                         const INTH_Priority_t      intPriority);
#endif


/* ------------------------------------------------------------------------*//**
 *
 * @brief         Enable the specified interrupt
 *
 * @param[in]     intVector (Interrupt vector for which to enable interrupt)
 *
 * @return        ReturnCode_t       
 *                     RET_OK                    No errors occured
 *                     RET_BAD_NULL_PARAM        Address/pointer Paramater was set to 0/NULL
 *                     RET_PARAM_OUT_OF_RANGE    intType parameter invalid
 *
 * @details       Enable the specified interrupt
 *
 * @remarks       Call Interrupt Controler enable.
 *
 *//*------------------------------------------------------------------------ */
#if defined (SEC)
extern ReturnCode_t EVE_HOST_INTH_InterruptEnable( const UWORD16  intVector);
#else
extern ReturnCode_t EVE_HOST_INTH_InterruptEnable( const UWORD8   intVector);
#endif

/* ------------------------------------------------------------------------*//**
 *
 * @brief         Disable the specified interrupt
 *
 * @param[in]     intVector (Interrupt vector for which to disable interrupt)
 *
 * @return        ReturnCode_t       
 *                     RET_OK                    No errors occured
 *                     RET_BAD_NULL_PARAM        Address/pointer Paramater was set to 0/NULL
 *                     RET_PARAM_OUT_OF_RANGE    intType parameter invalid
 *
 * @details       Disable the specified interrupt
 *
 * @remarks       Call Interrupt Controler disable.
 *
 *//*------------------------------------------------------------------------ */
#if defined (SEC)
extern ReturnCode_t EVE_HOST_INTH_InterruptDisable( const UWORD16  intVector);
#else
extern ReturnCode_t EVE_HOST_INTH_InterruptDisable( const UWORD8   intVector);
#endif


/* ------------------------------------------------------------------------*//**
 *
 * @brief         Gives the number of interrupts
 *
 * @param[in]     intVector (Interrupt vector for which to get count value)
 * @param[out]    pIntCount (Number of interrupts since Handler registered)
 *
 * @return        ReturnCode_t       
 *                     RET_OK                    No errors occured
 *                     RET_BAD_NULL_PARAM        Address/pointer Paramater was set to 0/NULL
 *                     RET_PARAM_OUT_OF_RANGE    intType parameter invalid
 *
 * @details       Gives the number of interrupts for a given type that occured
 *                since the interrupt handler was registered or count cleared
 *
 * @remarks       Checks input parameters
 *                read value from array  with vector as the offset
 *
 *//*------------------------------------------------------------------------ */
#if defined (SEC)
extern ReturnCode_t EVE_HOST_INTH_IntCountGet( const UWORD16          intVector,
                                      UWORD32 *const        pIntCount);
#else
extern ReturnCode_t EVE_HOST_INTH_IntCountGet( const UWORD8          intVector,
                                      UWORD32 *const        pIntCount);
#endif

/* ------------------------------------------------------------------------*//**
 *
 * @brief         Gives interrupt handler address
 *
 * @param[in]     intVector (Interrupt vector for which to get handler address)
 * @param[out]    pIntHandler (Address of the current interrupts Handler)
 *
 * @return        ReturnCode_t       
 *                     RET_OK                    No errors occured
 *                     RET_BAD_NULL_PARAM        Address/pointer Paramater was set to 0/NULL
 *                     RET_PARAM_OUT_OF_RANGE    intType parameter invalid
 *
 * @details       Gives the interrupt handler address for a specific interrupt type
 *
 * @remarks       Checks input parameters
 *                read value from array  with vector as the offset
 *
 *//*------------------------------------------------------------------------ */
#if defined (SEC)
extern ReturnCode_t EVE_HOST_INTH_IntHandlerGet( const UWORD16          	intVector,
                                        INTH_Handler_t *const   pIntHandler);
#else
extern ReturnCode_t EVE_HOST_INTH_IntHandlerGet( const UWORD8          	intVector,
                                        INTH_Handler_t *const   pIntHandler);
#endif

/* ------------------------------------------------------------------------*//**
 *
 * @brief         Reset interrupt count to 0
 *
 * @param[in]     intVector (Interrupt vector for which to clear count value)
 *
 * @return        ReturnCode_t       
 *                     RET_OK                    No errors occured
 *                     RET_BAD_NULL_PARAM        Address/pointer Paramater was set to 0/NULL
 *                     RET_PARAM_OUT_OF_RANGE    intType parameter invalid
 *
 * @details       Reset interrupt count to 0
 *
 * @remarks       Checks input parameters
 *                Set count for specified register to 0
 *
 *//*------------------------------------------------------------------------ */
#if defined (SEC)
extern ReturnCode_t EVE_HOST_INTH_IntCountClear( const UWORD16          intVector);
#else
extern ReturnCode_t EVE_HOST_INTH_IntCountClear( const UWORD8           intVector);
#endif

/* ------------------------------------------------------------------------*//**
 *
 * @brief         primary/HLL interrupt handler
 *
 *
 * @return        void
 *
 * @details       This is primary/HLL interrupt handler that CPU will jump to
 *                when ARM11/UMA IRQ interrupt occurs
 *
 * @remarks       Get active interrupt vector
 *                increment interrupt vector counter
 *                Jump to registered handler if exists
 *                validate next interrupt
 *
 * @note          This function should not be called directly by test cases.
 *
 *//*------------------------------------------------------------------------ */
    extern void EVE_HOST_INTH_IRQHandler (UWORD8);


/* ------------------------------------------------------------------------*//**
 *
 * @brief         primary/HLL interrupt handler
 *
 *
 * @return        void
 *
 * @details       This is primary/HLL interrupt handler that CPU will jump to
 *                when ARM11/UMA FIQ interrupt occurs
 *
 * @remarks       Get active interrupt vector
 *                increment interrupt vector counter
 *                Jump to registered handler if exists
 *                validate next interrupt
 *
 * @note          This function should not be called directly by test cases.
 *
 *//*------------------------------------------------------------------------ */
#if defined(SEDNA2) || defined(MODEM)
#ifndef __TITOOLCHAIN__


  extern void
    #if defined(CORTEXA8) || (defined(CORTEXM3) && defined(ARM9))
      __irq
    #endif
           EVE_HOST_INTH_FIQHandler( void );

#else /*__TITOOLCHAIN__*/

  #if defined(__UMA__) || defined(C64M)
    extern void EVE_HOST_INTH_FIQHandler (void );
  #else /*__UMA__*/
//    #pragma INTERRUPT(INTH_FIQHandler, fiq)
//    extern void INTH_FIQHandler (void );
  #endif /*__UMA__*/

#endif /*__TITOOLCHAIN__*/

#else /* SEDNA2 */

#ifndef __TITOOLCHAIN__

  extern void
    #if defined(CORTEXA8) || defined(CORTEXM3) || defined(ARM9)
      __irq
    #endif
           EVE_HOST_INTH_FIQHandler( void );

#else /*__TITOOLCHAIN__*/

  #if defined(__UMA__) || defined(C64)
    extern void INTH_FIQHandler (void );
  #else /*__UMA__*/
//    #pragma INTERRUPT(INTH_FIQHandler, fiq)
//    extern void EVE_HOST_INTH_FIQHandler (void );
  #endif /*__UMA__*/

#endif /*__TITOOLCHAIN__*/
#endif /* SEDNA2 */

/* ------------------------------------------------------------------------*//**
 *
 * @brief         HLL interrupt handler
 *
 * @return        void
 *
 * @details       This is HLL interrupt handler that CPU will jump to
 *                when UMA Bus Error interrupt occurs
 *
 * @remarks       Get active interrupt cause and stop here
 *
 * @note          This function should not be called directly by test cases.
 *
 *//*------------------------------------------------------------------------ */
#if defined(__UMA__) || defined(C64)
extern void INTH_BusError( void );
#endif




#ifdef __cplusplus
}
#endif

#endif    /* __INTH_H */

/* Nothing past this point */
