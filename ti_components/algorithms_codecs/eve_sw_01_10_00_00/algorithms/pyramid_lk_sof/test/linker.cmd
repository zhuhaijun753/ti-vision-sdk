/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

//-e _c_int00
-e _reset_handler
-heap  0x2800000 /* For EXTDMEM heap allocation. .sysmem is in EXTDMEM */
-stack 0x1800

MEMORY
{
    PAGE 0:
      VECMEM  :    origin      = 0x80000000, length = 0x0100
      CMDMEM  :    origin      = 0x80000100, length = 0x1000
      EXTMEM  :    origin      = 0x80001100, length = 0x40000

    PAGE 1:
      DATMEM  :    origin = 0x40020000 length = 0x8000
      WMEM    :    origin = 0x40040000 length = 0x7FE0
      IMEMLA  :    origin = 0x40050000 length = 0x4000
      IMEMHA  :    origin = 0x40054000 length = 0x4000
      IMEMLB  :    origin = 0x40070000 length = 0x4000
      IMEMHB  :    origin = 0x40074000 length = 0x4000
      GEM0_L2_MEM: origin = 0x40800000 length = 0x8000
      EXTDMEM :    origin = 0x80050000 length = 0x3000000
      L3MEM   :    origin = 0x40300000, length = 0x100000
}

#ifdef VCOP_CAMA
/*---------------------------------------------------------------------------*/
/* VCOP Compiler Assisted Memory Allocation                                  */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Define VCOP heap sizes. These can be smaller than the actual memory region*/
/*---------------------------------------------------------------------------*/

IMEML_SIZE = 0x4000;
IMEMH_SIZE = 0x4000;
WMEM_SIZE  = 0x7E00; /*for FAST9 corner detect*/
/*WMEM_SIZE  = 0x4000;*/

/*--------------------------------------------------------------------------*/
/* Define VCOP heap locations and ensure heaps span the appropriate size    */
/*--------------------------------------------------------------------------*/
SECTIONS
{
  .imemla: { *(.imemla) . += (IMEML_SIZE - 8); } > IMEMLA PAGE 1
  .imemha: { *(.imemha) . += (IMEMH_SIZE - 8); } > IMEMHA PAGE 1
  .imemlb: { *(.imemlb) . += (IMEML_SIZE - 8); } > IMEMLB PAGE 1
  .imemhb: { *(.imemhb) . += (IMEMH_SIZE - 8); } > IMEMHB PAGE 1
  .wmem  : { *(.wmem)   . += (WMEM_SIZE  - 8); } > WMEM   PAGE 1
}

#else

/*-----------------------------------------------------------------------------*/
/* Disable VCOP Compiler Assisted Memory Allocation by setting heapsize to zero*/
/*-----------------------------------------------------------------------------*/
IMEML_SIZE = 0x0;
IMEMH_SIZE = 0x0;
WMEM_SIZE  = 0x0;

#endif

/*---------------------------------------------------------------------------*/
/* VCOP Manual Allocation                                                    */
/*---------------------------------------------------------------------------*/

SECTIONS
{
  .const       > EXTDMEM  PAGE 1 //moving to extmem due to dmem space constraint
  .cint        > DATMEM  PAGE 1
  .stack       > DATMEM  PAGE 1
  .sysmem      > EXTDMEM  PAGE 1
  .cinit       > DATMEM  PAGE 1
  .dmemSect    > DATMEM  PAGE 1
  .cio         > EXTDMEM  PAGE 1
  .far         > EXTDMEM  PAGE 1
  .fardata     > EXTDMEM  PAGE 1
  .init_array  > DATMEM  PAGE 1
  .vcop_parameter_block > WMEM PAGE 1
  .intvecs      > VECMEM  PAGE 0
  .inthandler   > CMDMEM  PAGE 0
  .exitlocation > CMDMEM  PAGE 0
 
  GROUP (my_funcs)
  {
  .text:vcop_weight_computation_vloops
  .text:vcop_multiblock_gradient_xy_vloops
  .text:vcop_multiblock_bilinear_interp_intlv_7x7_s16_vloops
  .text:vcop_multiblock_bilinear_interp_7x7_u8_vloops
  .text:vcop_tensor_matrix_7x7_s16_grad_vloops
  .text:vcop_calc_determinant_tensor_matrix_vloops
  .text:vcop_calc_inverse_structure_tensor_2x2_vloops
  .text:vcop_weight_address_bilinear_interpolation_vloops
  .text:vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops 
  .text:vcop_sum_grad_cross_inter_frame_diff_7x7_vloops
  .text:vcop_calc_new_lk_xy_vloops
  .text:Bam_LK_Iterative_Loop_computeFrame
  .text:vcop_copy_new_lk_xy_vloops
  .text:BAM_execute
  .text:EDMA_UTILS_autoIncrement1D_triggerInChannel
  .text:EDMA_UTILS_autoIncrement1D_waitInChannel
  .text:BAM_DMA_PYRAMID_LK_TRACKER_triggerInChannel
  .text:EDMA_UTILS_scattherGather_updateSrcNtrigger
  .text:BAM_DMA_PYRAMID_LK_TRACKER_waitInChannel
  .text:EDMA_UTILS_scattherGather_wait
  .text:EDMA_UTILS_autoIncrement_triggerOutChannel
  .text:EDMA_UTILS_autoIncrement_waitOutChannel
  .text:vcop_vec_gradients_xy_and_magnitude_vloops
  .text:vcop_nonMaxSuppress_mxn_32s_vloops
  .text:BAM_generateList_compute
  .text:vcop_generateList_vloops
  .text:vcop_updateGenerateList_vloops
  .text:vcop_copyListToOutBuff_vloops
  .text:vcop_blockAverage2x2_uchar_vloops
  .text:BAM_harrisScore_32_7x7_compute
  .text:vcop_harrisScore_32_7x7_1_vloops
  .text:vcop_harrisScore_32_7x7_2_vloops
  .text
  } align = 0x8000 > EXTDMEM   PAGE 1
 

    .rts_fardata
  {
    rtsarp32_v200.lib<*.o*> (.far)
    rtsarp32_v200.lib<*.o*> (.fardata)
  } SIZE(_rts_fardata_size) > EXTDMEM  PAGE 1


  .algo_fardata
  {
    libevekernels.eve.lib<*.o*> (.fardata)
  } SIZE(_algo_fardata_size) > EXTDMEM  PAGE 1

  .starterware_fardata
  {
    libevestarterware_eve.lib<*.o*> (.fardata)
  } SIZE(_starterware_fardata_size) > EXTDMEM  PAGE 1

  .bam_fardata
  {
    libevealgframework.eve.lib<*.o*> (.far)
    libevealgframework.eve.lib<*.o*> (.fardata)
  } SIZE(_bam_fardata_size) > EXTDMEM  PAGE 1

  .bam_neardata
  {
  } SIZE(_bam_neardata_size) > EXTDMEM   PAGE 1

  .algo_neardata
  {
  } SIZE(_algo_neardata_size) > DATMEM   PAGE 1

  .starterware_neardata
  {
  } SIZE(_starterware_neardata_size) > DATMEM  PAGE 1

  .rts_neardata
  {
    rtsarp32_v200.lib<*.o*> (.const)
  } SIZE(_rts_neardata_size) > EXTDMEM  PAGE 1

  .bam_text
  {
    libevealgframework.eve.lib<*.o*> (.text)
  } SIZE(_bam_text_size) > EXTMEM   PAGE 0

  .algo_text
  {
    libevekernels.eve.lib<*.o*> (.text)
    libevePyramidLKTracker.eve.lib<*.o*> (.text)
    libevesof.eve.lib<*.o*> (.text)
    libeveFast9CornerDetect.eve.lib<*.o*> (.text)
    libeveFAST9BestFeatureToFront.eve.lib<*.o*> (.text)
    libeveHarrisCornerDetection32.eve.lib<*.o*> (.text)
    libeveImagePyramid_u8.eve.lib<*.o*> (.text)
    libeveYUVPAdding.eve.lib<*.o*> (.text)
  } SIZE(_algo_text_size) > EXTMEM   PAGE 0

  .starterware_text
  {
    libevestarterware_eve.lib<*.o*> (.text)
  } SIZE(_starterware_text_size) > EXTMEM   PAGE 0

  .rts_text
  {
    rtsarp32_v200.lib<*.o*> (.text)
  } SIZE(_rts_text_size) > EXTMEM   PAGE 0

  .text
  {
    *(.text)
  } SIZE(_text_size) > EXTMEM   PAGE 0
  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1

}


