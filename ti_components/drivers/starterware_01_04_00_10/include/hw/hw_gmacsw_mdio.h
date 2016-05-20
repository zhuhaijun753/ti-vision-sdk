/******************************************************************************
*
* hw_gmacsw_mdio.h - register-level header file for GMAC_SW
*
* Copyright (c) 2008-2013 Texas Instruments Incorporated.  All rights reserved.
* Software License Agreement
*
* Texas Instruments (TI) is supplying this software for use solely and
* exclusively on TI devices. The software is owned by TI and/or its
* suppliers, and is protected under applicable patent and copyright laws.
*
* You may not combine this software with any open-source software if such
* combination would cause this software to become subject to any of the
* license terms applicable to such open source software.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
* NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
* NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
* CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
* DAMAGES, FOR ANY REASON WHATSOEVER.
* 
******************************************************************************
*/
#ifndef HW_GMACSW_MDIO_H_
#define HW_GMACSW_MDIO_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_MDIOLINKINTRAW                                                                              (0x10U)
#define GMAC_SW_MDIOUSERACCESS0                                                                             (0x80U)
#define GMAC_SW_MDIOUSERINTMASKSET                                                                          (0x28U)
#define GMAC_SW_MDIOUSERINTMASKCLR                                                                          (0x2cU)
#define GMAC_SW_MDIOVER                                                                                     (0x0U)
#define GMAC_SW_MDIOUSERPHYSEL0                                                                             (0x84U)
#define GMAC_SW_MDIOCONTROL                                                                                 (0x4U)
#define GMAC_SW_MDIOUSERINTRAW                                                                              (0x20U)
#define GMAC_SW_MDIOALIVE                                                                                   (0x8U)
#define GMAC_SW_MDIOUSERINTMASKED                                                                           (0x24U)
#define GMAC_SW_MDIOUSERACCESS1                                                                             (0x88U)
#define GMAC_SW_MDIOLINK                                                                                    (0xcU)
#define GMAC_SW_MDIOLINKINTMASKED                                                                           (0x14U)
#define GMAC_SW_MDIOUSERPHYSEL1                                                                             (0x8cU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_MDIOLINKINTRAW_LINKINTRAW_SHIFT                                                             (0U)
#define GMAC_SW_MDIOLINKINTRAW_LINKINTRAW_MASK                                                              (0x00000003U)

#define GMAC_SW_MDIOLINKINTRAW_RESERVED1_SHIFT                                                              (2U)
#define GMAC_SW_MDIOLINKINTRAW_RESERVED1_MASK                                                               (0xfffffffcU)

#define GMAC_SW_MDIOUSERACCESS0_DATA_SHIFT                                                                  (0U)
#define GMAC_SW_MDIOUSERACCESS0_DATA_MASK                                                                   (0x0000ffffU)

#define GMAC_SW_MDIOUSERACCESS0_PHYADR_SHIFT                                                                (16U)
#define GMAC_SW_MDIOUSERACCESS0_PHYADR_MASK                                                                 (0x001f0000U)

#define GMAC_SW_MDIOUSERACCESS0_REGADR_SHIFT                                                                (21U)
#define GMAC_SW_MDIOUSERACCESS0_REGADR_MASK                                                                 (0x03e00000U)

#define GMAC_SW_MDIOUSERACCESS0_RESERVED1_SHIFT                                                             (26U)
#define GMAC_SW_MDIOUSERACCESS0_RESERVED1_MASK                                                              (0x1c000000U)

#define GMAC_SW_MDIOUSERACCESS0_ACK_SHIFT                                                                   (29U)
#define GMAC_SW_MDIOUSERACCESS0_ACK_MASK                                                                    (0x20000000U)

#define GMAC_SW_MDIOUSERACCESS0_WRITE_SHIFT                                                                 (30U)
#define GMAC_SW_MDIOUSERACCESS0_WRITE_MASK                                                                  (0x40000000U)

#define GMAC_SW_MDIOUSERACCESS0_GO_SHIFT                                                                    (31U)
#define GMAC_SW_MDIOUSERACCESS0_GO_MASK                                                                     (0x80000000U)

#define GMAC_SW_MDIOUSERINTMASKSET_USERINTMASKSET_SHIFT                                                     (0U)
#define GMAC_SW_MDIOUSERINTMASKSET_USERINTMASKSET_MASK                                                      (0x00000003U)

#define GMAC_SW_MDIOUSERINTMASKSET_RESERVED1_SHIFT                                                          (2U)
#define GMAC_SW_MDIOUSERINTMASKSET_RESERVED1_MASK                                                           (0xfffffffcU)

#define GMAC_SW_MDIOUSERINTMASKCLR_USERINTMASKCLEAR_SHIFT                                                   (0U)
#define GMAC_SW_MDIOUSERINTMASKCLR_USERINTMASKCLEAR_MASK                                                    (0x00000003U)

#define GMAC_SW_MDIOUSERINTMASKCLR_RESERVED1_SHIFT                                                          (2U)
#define GMAC_SW_MDIOUSERINTMASKCLR_RESERVED1_MASK                                                           (0xfffffffcU)

#define GMAC_SW_MDIOVER_REVMIN_SHIFT                                                                        (0U)
#define GMAC_SW_MDIOVER_REVMIN_MASK                                                                         (0x000000ffU)

#define GMAC_SW_MDIOVER_REVMAJ_SHIFT                                                                        (8U)
#define GMAC_SW_MDIOVER_REVMAJ_MASK                                                                         (0x0000ff00U)

#define GMAC_SW_MDIOVER_MODID_SHIFT                                                                         (16U)
#define GMAC_SW_MDIOVER_MODID_MASK                                                                          (0xffff0000U)

#define GMAC_SW_MDIOUSERPHYSEL0_PHYADDRMON_SHIFT                                                            (0U)
#define GMAC_SW_MDIOUSERPHYSEL0_PHYADDRMON_MASK                                                             (0x0000001fU)

#define GMAC_SW_MDIOUSERPHYSEL0_RESERVED2_SHIFT                                                             (5U)
#define GMAC_SW_MDIOUSERPHYSEL0_RESERVED2_MASK                                                              (0x00000020U)

#define GMAC_SW_MDIOUSERPHYSEL0_LINKINTENB_SHIFT                                                            (6U)
#define GMAC_SW_MDIOUSERPHYSEL0_LINKINTENB_MASK                                                             (0x00000040U)

#define GMAC_SW_MDIOUSERPHYSEL0_LINKSEL_SHIFT                                                               (7U)
#define GMAC_SW_MDIOUSERPHYSEL0_LINKSEL_MASK                                                                (0x00000080U)

#define GMAC_SW_MDIOUSERPHYSEL0_RESERVED1_SHIFT                                                             (8U)
#define GMAC_SW_MDIOUSERPHYSEL0_RESERVED1_MASK                                                              (0xffffff00U)

#define GMAC_SW_MDIOCONTROL_CLKDIV_SHIFT                                                                    (0U)
#define GMAC_SW_MDIOCONTROL_CLKDIV_MASK                                                                     (0x0000ffffU)

#define GMAC_SW_MDIOCONTROL_RESERVED3_SHIFT                                                                 (16U)
#define GMAC_SW_MDIOCONTROL_RESERVED3_MASK                                                                  (0x00010000U)

#define GMAC_SW_MDIOCONTROL_INTTESTENB_SHIFT                                                                (17U)
#define GMAC_SW_MDIOCONTROL_INTTESTENB_MASK                                                                 (0x00020000U)

#define GMAC_SW_MDIOCONTROL_FAULTENB_SHIFT                                                                  (18U)
#define GMAC_SW_MDIOCONTROL_FAULTENB_MASK                                                                   (0x00040000U)

#define GMAC_SW_MDIOCONTROL_FAULT_SHIFT                                                                     (19U)
#define GMAC_SW_MDIOCONTROL_FAULT_MASK                                                                      (0x00080000U)

#define GMAC_SW_MDIOCONTROL_PREAMBLE_SHIFT                                                                  (20U)
#define GMAC_SW_MDIOCONTROL_PREAMBLE_MASK                                                                   (0x00100000U)

#define GMAC_SW_MDIOCONTROL_RESERVED2_SHIFT                                                                 (21U)
#define GMAC_SW_MDIOCONTROL_RESERVED2_MASK                                                                  (0x00e00000U)

#define GMAC_SW_MDIOCONTROL_HIGHEST_USER_CHANNEL_SHIFT                                                      (24U)
#define GMAC_SW_MDIOCONTROL_HIGHEST_USER_CHANNEL_MASK                                                       (0x1f000000U)

#define GMAC_SW_MDIOCONTROL_RESERVED1_SHIFT                                                                 (29U)
#define GMAC_SW_MDIOCONTROL_RESERVED1_MASK                                                                  (0x20000000U)

#define GMAC_SW_MDIOCONTROL_ENABLE_SHIFT                                                                    (30U)
#define GMAC_SW_MDIOCONTROL_ENABLE_MASK                                                                     (0x40000000U)

#define GMAC_SW_MDIOCONTROL_IDLE_SHIFT                                                                      (31U)
#define GMAC_SW_MDIOCONTROL_IDLE_MASK                                                                       (0x80000000U)

#define GMAC_SW_MDIOUSERINTRAW_USERINTRAW_SHIFT                                                             (0U)
#define GMAC_SW_MDIOUSERINTRAW_USERINTRAW_MASK                                                              (0x00000003U)

#define GMAC_SW_MDIOUSERINTRAW_RESERVED1_SHIFT                                                              (2U)
#define GMAC_SW_MDIOUSERINTRAW_RESERVED1_MASK                                                               (0xfffffffcU)

#define GMAC_SW_MDIOALIVE_ALIVE_SHIFT                                                                       (0U)
#define GMAC_SW_MDIOALIVE_ALIVE_MASK                                                                        (0xffffffffU)

#define GMAC_SW_MDIOUSERINTMASKED_USERINTMASKED_SHIFT                                                       (0U)
#define GMAC_SW_MDIOUSERINTMASKED_USERINTMASKED_MASK                                                        (0x00000003U)

#define GMAC_SW_MDIOUSERINTMASKED_RESERVED1_SHIFT                                                           (2U)
#define GMAC_SW_MDIOUSERINTMASKED_RESERVED1_MASK                                                            (0xfffffffcU)

#define GMAC_SW_MDIOUSERACCESS1_DATA_SHIFT                                                                  (0U)
#define GMAC_SW_MDIOUSERACCESS1_DATA_MASK                                                                   (0x0000ffffU)

#define GMAC_SW_MDIOUSERACCESS1_PHYADR_SHIFT                                                                (16U)
#define GMAC_SW_MDIOUSERACCESS1_PHYADR_MASK                                                                 (0x001f0000U)

#define GMAC_SW_MDIOUSERACCESS1_REGADR_SHIFT                                                                (21U)
#define GMAC_SW_MDIOUSERACCESS1_REGADR_MASK                                                                 (0x03e00000U)

#define GMAC_SW_MDIOUSERACCESS1_RESERVED1_SHIFT                                                             (26U)
#define GMAC_SW_MDIOUSERACCESS1_RESERVED1_MASK                                                              (0x1c000000U)

#define GMAC_SW_MDIOUSERACCESS1_ACK_SHIFT                                                                   (29U)
#define GMAC_SW_MDIOUSERACCESS1_ACK_MASK                                                                    (0x20000000U)

#define GMAC_SW_MDIOUSERACCESS1_WRITE_SHIFT                                                                 (30U)
#define GMAC_SW_MDIOUSERACCESS1_WRITE_MASK                                                                  (0x40000000U)

#define GMAC_SW_MDIOUSERACCESS1_GO_SHIFT                                                                    (31U)
#define GMAC_SW_MDIOUSERACCESS1_GO_MASK                                                                     (0x80000000U)

#define GMAC_SW_MDIOLINK_LINK_SHIFT                                                                         (0U)
#define GMAC_SW_MDIOLINK_LINK_MASK                                                                          (0xffffffffU)

#define GMAC_SW_MDIOLINKINTMASKED_LINKINTMASKED_SHIFT                                                       (0U)
#define GMAC_SW_MDIOLINKINTMASKED_LINKINTMASKED_MASK                                                        (0x00000003U)

#define GMAC_SW_MDIOLINKINTMASKED_RESERVED1_SHIFT                                                           (2U)
#define GMAC_SW_MDIOLINKINTMASKED_RESERVED1_MASK                                                            (0xfffffffcU)

#define GMAC_SW_MDIOUSERPHYSEL1_DATA_SHIFT                                                                  (0U)
#define GMAC_SW_MDIOUSERPHYSEL1_DATA_MASK                                                                   (0x0000ffffU)

#define GMAC_SW_MDIOUSERPHYSEL1_PHYADR_SHIFT                                                                (16U)
#define GMAC_SW_MDIOUSERPHYSEL1_PHYADR_MASK                                                                 (0x001f0000U)

#define GMAC_SW_MDIOUSERPHYSEL1_REGADR_SHIFT                                                                (21U)
#define GMAC_SW_MDIOUSERPHYSEL1_REGADR_MASK                                                                 (0x03e00000U)

#define GMAC_SW_MDIOUSERPHYSEL1_RESERVED1_SHIFT                                                             (26U)
#define GMAC_SW_MDIOUSERPHYSEL1_RESERVED1_MASK                                                              (0x1c000000U)

#define GMAC_SW_MDIOUSERPHYSEL1_ACK_SHIFT                                                                   (29U)
#define GMAC_SW_MDIOUSERPHYSEL1_ACK_MASK                                                                    (0x20000000U)

#define GMAC_SW_MDIOUSERPHYSEL1_WRITE_SHIFT                                                                 (30U)
#define GMAC_SW_MDIOUSERPHYSEL1_WRITE_MASK                                                                  (0x40000000U)

#define GMAC_SW_MDIOUSERPHYSEL1_GO_SHIFT                                                                    (31U)
#define GMAC_SW_MDIOUSERPHYSEL1_GO_MASK                                                                     (0x80000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_MDIO_H_ */
