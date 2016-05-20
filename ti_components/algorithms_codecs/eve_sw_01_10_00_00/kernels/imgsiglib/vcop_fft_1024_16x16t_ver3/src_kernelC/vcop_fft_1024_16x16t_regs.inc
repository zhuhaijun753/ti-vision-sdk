/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/* Loop Allocations for loops_stages_1_2, stage 3, stage 4 */

 #define  VX0_76543210    V8      
 #define  VY0_76543210    V9  
 #define  VX1_76543210    V2  
 #define  VY1_76543210    V3  
 #define  VX2_76543210    V4  
 #define  VY2_76543210    V5  
 #define  VX3_76543210    V6  
 #define  VY3_76543210    V7  
 #define  VS1_76543210    V0  
 #define  VC1_76543210    V1  
 #define  VS2_76543210    V10 
 #define  VC2_76543210    V11 
 #define  VS3_76543210    V12 
 #define  VC3_76543210    V13 

 #define  Vxh0_76543210    V8  
 #define  Vxl0_76543210    V4  
 #define  Vxh1_76543210    V9  
 #define  Vxl1_76543210    V5  

 #define  Vxh20_76543210   V2  
 #define  Vxl20_76543210   V6
 #define  Vxh21_76543210   V3
 #define  Vxl21_76543210   V7

 #define  Vxt0             V8           
 #define  Vxt2             V2           
 #define  Vyt0             V9           
 #define  Vyt2             V3           
                 
 #define  Vxt1             V4           
 #define  Vxt3             V7           
 #define  Vyt1             V6           
 #define  Vyt3             V5           

 #define  V_x0r            V8            
 #define  V_y0i            V9            
 #define  V_x2r            V14           
 #define  V_y2i            V15

 #define  V_x1r            V10           
 #define  V_y1i            V11           
 #define  V_x3r            V2             
 #define  V_y3i            V3  

/* Loop Allocations for stage 5 */

 #define   VnX0_76543210   V0       
 #define   VnX2_76543210   V4       
 #define   Vxh0_0          V0       
 #define   Vxl0_0          V4       
                       
                       
 #define   VnY0_76543210   V1       
 #define   VnY2_76543210   V5       
 #define   Vxh1_0          V1       
 #define   Vxl1_0          V5       
                       
                                                              
 #define   VnX1_76543210   V2       
 #define   VnX3_76543210   V6       
 #define   Vxh0_1          V2       
 #define   Vxl0_1          V6       
                       
                       
 #define   VnY1_76543210   V3       
 #define   VnY3_76543210   V7       
 #define   Vxh1_1          V3       
 #define   Vxl1_1          V7       
                       
                       
 // #define   Vxh0_0          V0       
 // #define   Vxh0_1          V2       
 #define   V_n00           V0       
 #define   V_n20           V2       
                       
                      
 // #define   Vxl0_0          V4       
 // #define   Vxl1_1          V6       
 #define   V_n10           V4       
 #define   V_n11           V6       
                       
                                                             
 // #define   Vxh1_0          V1       
 // #define   Vxh1_1          V3       
 #define   V_n01           V1       
 #define   V_n21           V3       
                       
                       
 // #define   Vxl1_0          V5       
 // #define   Vxl1_1          V7       
 #define   V_n31           V5       
 #define   V_n30           V7       
                       
 #define   V_n30c          V6       
 #define   V_n31c          V7  
 #define   Vcond           V8

