/*==========================================================================*/ 
/*     TEXAS INSTRUMENTS, INC.                                              */ 
/*                                                                          */ 
/*     NAME                                                                 */ 
/*     vcop_canny_non_maximum_suppression_cn                                */ 
/*                                                                          */ 
/*                                                                          */ 
/*     USAGE                                                                */ 
/*     This routine is C-callable and can be called as:                     */ 
/*                                                                          */ 
/*     void vcop_canny_non_maximum_suppression_cn                           */ 
/*     (                                                                    */ 
/*         short          pMag[],                                           */ 
/*         short          pGx[],                                            */ 
/*         short          pGy[],                                            */  
/*         unsigned char  pEdge[],                                          */ 
/*         int            Mag2_array[],                                     */ 
/*         unsigned char  Index[],                                          */ 
/*         int            mag1_array[],                                     */ 
/*         int            mag3_array[],                                     */ 
/*         unsigned short width,                                            */ 
/*         unsigned short pitch,                                            */ 
/*         unsigned short height                                            */ 
/*     )                                                                    */ 
/*                                                                          */ 
/*     pMag       :  Gradient Magnitude array                               */ 
/*     pGx        :  Gradient in X direction array                          */ 
/*     pGy        :  Gradient in Y direction array                          */ 
/*     pEdge      :  Non-maximum suppressed Edge array                      */ 
/*     Index      :  Temporary array to store the edge indices              */ 
/*     mag1_array :  Non-maximum suppressed Edge array                      */ 
/*     mag3_array :  Non-maximum suppressed Edge array                      */ 
/*     Mag2_array :  Non-maximum suppressed Edge array                      */ 
/*     width      :  width of pMag,pGx and pGy images                       */ 
/*     pitch      :  width of pMag,pGx and pGy images                       */ 
/*     height     :  width of pMag,pGx and pGy images                       */ 
/*                                                                          */ 
/*     Returns :  None or void.                                             */ 
/*                                                                          */ 
/*                                                                          */ 
/*     DESCRIPTION                                                          */ 
/*             This routine accepts an pGx,pGy and pMag arrays and outputs  */ 
/*     the non-maxima suppressed edge image in pEdge array.                 */ 
/*                                                                          */ 
/*     ASSUMPTIONS                                                          */ 
/*                                                                          */ 
/*                                                                          */ 
/*==========================================================================*/ 
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */ 
/*                      All Rights Reserved                                 */ 
/*==========================================================================*/ 

void vcop_canny_non_maximum_suppression_1_k    
(                                            
    __vptr_int16   pMag, 
    __vptr_int16   pGx,
    __vptr_int16   pGy,                            
    __vptr_int32   Mag2_array,
    __vptr_uint8   Index,                          
    unsigned short width,                        
    unsigned short pitch,                        
    unsigned short height                        
)
{
            
    __vector magValue;
    __vector Gx;
    __vector Gy;
    __vector magTL;
    __vector magTC;
    __vector magTR;
    __vector magLC;
    __vector magRC;
    
    __vector zero,one,two;

    __vector mag2;
    __vector mag4;
    __vector index;
    __vector temp1, temp2;
            
    zero = 0;
    one  = 1;
    two  = 2;

    /*---------------------------------------------------------------------*/
    /*  The instructions in the C code are manually re-arranged for using  */
    /*  less than 16 registers.                                            */    
    /*---------------------------------------------------------------------*/
            
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width/VCOP_SIMD_WIDTH; col++)
        {
            __agen Addr1,Addr2,Addr3;                                                                       
            
            Addr1 = row*pitch*2 + col*VCOP_SIMD_WIDTH*2;                                                
            Addr2 = row*pitch*1 + col*VCOP_SIMD_WIDTH*1;                                                
            Addr3 = row*pitch*4 + col*VCOP_SIMD_WIDTH*4;                                                
            
            Gx       =  pGx[Addr1];
            Gy       =  pGy[Addr1];
            
            magTL    = (pMag - 2*pitch - 2*1)[Addr1];         
            magTC    = (pMag- 2*pitch)       [Addr1];             
            magTR    = (pMag - 2*pitch + 2*1)[Addr1];         
            magLC    = (pMag - 2*1)          [Addr1];
            magValue = (pMag)                [Addr1];
            magRC    = (pMag + 2*1)          [Addr1];
            
            index = abs(Gx);                                         
            temp1 = abs(Gy);                                         

            mag2  = (index >= temp1);
            mag4  = (Gy >= zero);
                                                                        
            temp1 = (Gx >= zero);
            temp2 = magTR - magTC;
            
            index = temp1^mag4;

            index = index <<one;
            mag4  = (magRC - magTR);     
            
            index = index + mag2;
            temp1 = magValue - magTC;
            
            mag2  = (magRC - magValue);  
            
            magRC = (index ==two);

            mag2  = select(magRC,temp2,mag2);   
            
            mag4  = select(magRC,temp1,mag4);
            temp2 = magTC - magTL;
            
            magRC = (index ==zero);
            temp1 = magValue - magTC;
            
            mag2  = select(magRC,temp2,mag2);  
            mag4  = select(magRC,temp1,mag4); 
                        
            temp1 = (index ==one);
            magRC =  magValue - magLC;
            
            temp2 = magLC - magTL;
            mag2  = select(temp1,magRC,mag2);  
            
            mag4  = select(temp1,temp2,mag4);  

            mag2 = mag2 * Gx;
            mag4 = mag4 * Gy;
            
            temp1 = mag2 + mag4;
            
            Mag2_array[Addr3]= temp1;   
            Index[Addr2]= index;
        }
    }
}   

void vcop_canny_non_maximum_suppression_2_k   
(                                             
    __vptr_int16   pMag,                             
    __vptr_uint8   Index,                           
    __vptr_int32   mag1_array,                      
    __vptr_int32   mag3_array,                                                                             
    unsigned short width,                        
    unsigned short pitch,
    unsigned short height
)
{
    __vector mag1;
    __vector mag3;
    
    __vector magValue;
    __vector magLC;
    __vector magRC;
    __vector magBL;
    __vector magBC;
    __vector magBR;
    __vector index;
    
    __vector temp1, temp2, temp3;            
    __vector one,two,three;
    
    one=1;
    two=2;
    three=3;
    
    for (int row = 0; row < height; row++)                     
    {                                                      
        for (int col = 0; col < width/VCOP_SIMD_WIDTH; col++)  
        {                                                  
            __agen Addr1,Addr2,Addr3;                                                                   
                                                                                                        
            Addr1 = row*pitch*2 + col*VCOP_SIMD_WIDTH*2;                                                
            Addr2 = row*pitch*1 + col*VCOP_SIMD_WIDTH*1;                                                
            Addr3 = row*pitch*4 + col*VCOP_SIMD_WIDTH*4;                                                
        
            magLC    = (pMag - 2*1)[Addr1];            
            magValue = pMag[Addr1];                
            magRC    = (pMag + 2*1)[Addr1 ];            
            magBL    = (pMag+ 2*pitch - 2*1)[Addr1 ];    
            magBC    = (pMag + 2*pitch)[Addr1];        
            magBR    = (pMag + 2*pitch + 2*1)[Addr1];    
            index    = Index[Addr2];                  
                                                           
            mag1  = (magBC - magBR);                     
            mag3  = (magValue - magBC);                
                                                           
            temp1 = (index ==one);                           
            temp2 = magValue - magRC;

            temp3 = magRC - magBR;
            mag1  = select(temp1,temp2,mag1);  
            
            mag3  = select(temp1,temp3,mag3);     
            temp2 = (index ==two);                           
            
            temp1 = magBL - magBC;
            temp3 = magValue - magBC;
                                                           
            mag1  = select(temp2,temp1,mag1);       
            mag3  = select(temp2,temp3,mag3);    
            
            temp3 = (index ==three);                           
            temp1 = magLC - magValue;

            temp2 = magLC - magBL;
            mag1  = select(temp3,temp1, mag1);  
            
            mag3  = select(temp3,temp2, mag3);   
                                                           
            mag1_array[Addr3] = mag1;              
            mag3_array[Addr3] = mag3;              
        }                                                  
    }                                                                  
}

void vcop_canny_non_maximum_suppression_3_k
(
    __vptr_int16   pGx,                        
    __vptr_int16   pGy,                        
    __vptr_uint8   pEdge,               
    __vptr_int32   Mag2_array,
    __vptr_int32   mag1_array,
    __vptr_int32   mag3_array,
    unsigned short width,                        
    unsigned short pitch,
    unsigned short height
)
{
    __vector Gx, Gy;               
    __vector mag1,mag3;               
    __vector Mag2;
    __vector Z,C;
    __vector temp1,temp2,b,Mag1,magLeft,magRight,temp3,temp4,edgeLabel;               
    
    Z=0;
    C=127;
    
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width/VCOP_SIMD_WIDTH; col++)
        {
            __agen Addr1,Addr2,Addr3;
            
            Addr1 = row*pitch*2 + col*VCOP_SIMD_WIDTH*2;
            Addr2 = row*pitch*4 + col*VCOP_SIMD_WIDTH*4;
            Addr3 = row*pitch*1 + col*VCOP_SIMD_WIDTH*1;
            
            Gx        =  pGx[Addr1];
            Gy        =  pGy[Addr1];
            mag1      =  mag1_array[Addr2];          
            mag3      =  mag3_array[Addr2];          
            Mag2      =  Mag2_array[Addr2];          
                      
            temp1     = mag1 * Gx;
            temp2     = mag3 * Gy;
                      
            b         = Gy < Z;
            Mag1      = temp1 + temp2;            
                      
            magLeft   = Z-Mag2;
            magRight  = Z-Mag1;         
                      
            magLeft   = select(b,Mag1,magLeft) ;
            magRight  = select(b,Mag2,magRight);
                      
            temp3     = magLeft  <= Z;
            temp4     = magRight <  Z;
                      
            edgeLabel =  temp3 & temp4;
            
            temp1     = C * edgeLabel;
            
            pEdge[Addr3] = temp1;
        }
    }
}
/* ======================================================================== */
/*  End of file:  vcop_canny_non_maximum_suppression_kernel.k               */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


