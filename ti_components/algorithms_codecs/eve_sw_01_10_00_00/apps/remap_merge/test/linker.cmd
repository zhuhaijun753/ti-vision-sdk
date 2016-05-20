/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
-e _reset_handler
-heap  0x1C00000 /* For EXTDMEM heap allocation. .sysmem is in EXTDMEM */
-stack 0x4000
//--define VCOP_CAMA

MEMORY
{
    PAGE 0:
      VECMEM  :    origin      = 0x80000000, length = 0x0100
      CMDMEM  :    origin      = 0x80000100, length = 0x1000
      EXTMEM  :    origin      = 0x80001100, length = 0x2EF00

    PAGE 1:
      DATMEM  :    origin = 0x40020000 length = 0x8000
      WMEM    :    origin = 0x40040000 length = 0x7FE0
      IMEMLA  :    origin = 0x40050000 length = 0x4000
      IMEMHA  :    origin = 0x40054000 length = 0x4000
      IMEMLB  :    origin = 0x40070000 length = 0x4000
      IMEMHB  :    origin = 0x40074000 length = 0x4000
      GEM0_L2_MEM: origin = 0x40800000 length = 0x8000
      EXTDMEM :    origin = 0x80030000 length = 0x2000000
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
WMEM_SIZE  = 0x7D00;

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
  .const       > EXTDMEM PAGE 1
  EOutdata     > DATMEM  PAGE 1
  .dmemSect    > DATMEM  PAGE 1
  .cint        > DATMEM  PAGE 1
  .stack       > DATMEM  PAGE 1
  .sysmem      > EXTDMEM PAGE 1
  .cinit       > DATMEM  PAGE 1
  .cio         > DATMEM  PAGE 1
  .far         > EXTDMEM PAGE 1
  .fardata     > EXTDMEM PAGE 1
  .init_array  > DATMEM  PAGE 1
  .vcop_parameter_block      > WMEM   PAGE 1
}


SECTIONS
{
  .intvecs      > VECMEM  PAGE 0
  .inthandler   > CMDMEM  PAGE 0
  .exitlocation > CMDMEM  PAGE 0

  .rts_fardata
  {
    rtsarp32_v200.lib<*.o*> (.far)
    rtsarp32_v200.lib<*.o*> (.fardata)
  } SIZE(_rts_fardata_size) > EXTDMEM  PAGE 1


  .algo_fardata
  {
    libeveRemapMerge.eve.lib<*.o*> (.far)
    libeveRemapMerge.eve.lib<*.o*> (.fardata)
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
    libevealgframework.eve.lib<*.o*> (.bss)
    libevealgframework.eve.lib<*.o*> (.data)
    libevealgframework.eve.lib<*.o*> (.rodata)
    libevealgframework.eve.lib<*.o*> (.const)
  } SIZE(_bam_neardata_size) > DATMEM   PAGE 1

  .algo_neardata
  {
    libeveRemapMerge.eve.lib<*.o*> (.bss)
    libeveRemapMerge.eve.lib<*.o*> (.rodata)
    libeveRemapMerge.eve.lib<*.o*> (.const)
    libevekernels.eve.lib<*.o*> (.rodata)
    libevekernels.eve.lib<*.o*> (.const)
  } SIZE(_algo_neardata_size) > DATMEM   PAGE 1

  .starterware_neardata
  {
    libevestarterware_eve.lib<*.o*> (.bss)
    libevestarterware_eve.lib<*.o*> (.data)
  } SIZE(_starterware_neardata_size) > DATMEM  PAGE 1

  .rts_neardata
  {
    rtsarp32_v200.lib<*.o*> (.const)
  } SIZE(_rts_neardata_size) > DATMEM  PAGE 1

  .bam_text
  {
    //libevealgframework.eve.lib<*.o*> (.text)
  } SIZE(_bam_text_size) > EXTMEM   PAGE 0

  .algo_text
  {
    //libevekernels.eve.lib<*.o*> (.text)
    //libeveRemapMerge.eve.lib<*.o*> (.text)
  } SIZE(_algo_text_size) > EXTMEM   PAGE 0

  .starterware_text
  {
    //libevestarterware_eve.lib<*.o*> (.text)
  } SIZE(_starterware_text_size) > EXTMEM   PAGE 0

  .rts_text
  {
    rtsarp32_v200.lib<*.o*> (.text)
  } SIZE(_rts_text_size) > EXTMEM   PAGE 0

   .text
  {
//    *(.text)
  } SIZE(_text_size) > EXTMEM   PAGE 0

  GROUP (my_funcs_perframe)
{
.text:EVE_SCTM_CounterRead
.text:REMAP_MERGE_TI_process
.text:REMAP_MERGE_TI_activate
.text:EDMA_UTILS_memcpy2D_init
.text:EDMA_UTILS_memcpy2D
.text:REMAP_MERGE_TI_graphDmaControl
.text:BAM_controlNode
.text:REMAP_MERGE_TI_execute
.text:BAM_process
.text:BAM_getKernelsExecCycles
.text:BAM_getKernelsInitCycles
.text:BAM_ARP32_computeWrapper
.text:EDMA_UTILS_globalReset
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr
.text:EDMA_UTILS_autoIncrement_update
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_frameInitChannel
.text:EDMA_UTILS_autoIncrement1D_getContextSize
.text:EDMA_UTILS_autoIncrement1D_init
.text:EDMA_UTILS_autoIncrement1D_update
.text:EDMA_UTILS_autoIncrement1D_configure
.text:EDMA_UTILS_scattherGather_getContextSize
.text:EDMA_UTILS_scattherGather_init
.text:EDMA_UTILS_autoIncrement_configure
.text:DMA_resourceAllocator_initResources
.text:DMA_resourceAllocator_allocateResources
.text:DMA_funcs_hardwareRegSetup
.text:DMA_funcs_writeTransferParams
.text:DMA_utils_updateStateStruct
.text:Bam_RemapMerge_initFrame
.text:Bam_Memcpy_initFrame
.text:BAM_initKernelDB
.text:Bam_Remap_initFrame
.text:_deInterleaveYUV422I_init
.text:vcop_deInterleaveYUV422IBE_init
.text:vcop_deInterleaveYUV422IBE_param_count
.text:vcop_deInterleaveYUV422ILE_init
.text:vcop_deInterleaveYUV422ILE_param_count
.text:_bilinearInterpolate_init
.text:vcop_bilinearInterpolate16b_init
.text:vcop_bilinearInterpolate16b_param_count
.text:vcop_bilinearInterpolate8b_init
.text:vcop_bilinearInterpolate8b_param_count
.text:vcop_bilinearInterpolateYUV422Ichroma_init
.text:vcop_bilinearInterpolateYUV422Ichroma_param_count
.text:vcop_bilinearInterpolateYUV422Iluma_init
.text:vcop_bilinearInterpolateYUV422Iluma_param_count
.text:_nnInterpolate_init
.text:vcop_nnInterpolate420SPchroma_init
.text:vcop_nnInterpolate420SPchroma_param_count
.text:vcop_nnInterpolate422Ichroma_init
.text:vcop_nnInterpolate422Ichroma_param_count
.text:vcop_nnInterpolate8b_init
.text:vcop_nnInterpolate8b_param_count
.text:vcop_chromaTLUIndexCalcBilInterpolate_init
.text:vcop_chromaTLUIndexCalcBilInterpolate_param_count
.text:vcop_chromaTLUIndexCalcNNInterpolate_init
.text:vcop_chromaTLUIndexCalcNNInterpolate_param_count
.text:vcop_dsTLUindexAndFracBilInterpolate_init
.text:vcop_dsTLUindexAndFracBilInterpolate_param_count
.text:vcop_dsTLUindexAndFracNNInterpolate_init
.text:vcop_dsTLUindexAndFracNNInterpolate_param_count
.text:vcop_bilinearInterpolateYUV420SPchroma_init
.text:vcop_bilinearInterpolateYUV420SPchroma_param_count
.text:Bam_Yuv_420nv12_to_422uyvy_initFrame
.text:vcop_yuv_420nv12_to_422uyvy_init
.text:vcop_yuv_420nv12_to_422uyvy_param_count
.text:Bam_Yuv_422uyvy_to_420nv12_initFrame
.text:vcop_yuv_422uyvy_to_420nv12_init
.text:vcop_yuv_422uyvy_to_420nv12_param_count
.text:Bam_Alpha_Blend_YUV420nv12_initFrame
.text:vcop_alpha_blend_yuv420nv12_init
.text:vcop_alpha_blend_yuv420nv12_param_count
.text:Bam_Alpha_Blend_YUV422i_initFrame
.text:vcop_alpha_blend_yuv422i_init
.text:vcop_alpha_blend_yuv422i_param_count
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SINK_frameInitChannel
.text:vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_init
.text:vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_init
.text:vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_init
.text:vcop_bilinearInterpolateLumaPblockUpdate_init
.text:vcop_bilinearInterpolateYUV420SPchromaPblockUpdate_init
.text:vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_init
.text:vcop_nnInterpolate422IchromaVPblockUpdate_init
.text:vcop_nnInterpolate420SPchromaPblockUpdate_init
.text:vcop_nnInterpolate422IchromaUPblockUpdate_init
.text:vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_init
.text:vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_init
.text:vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_param_count
.text:vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_param_count
.text:vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_param_count
.text:vcop_bilinearInterpolateLumaPblockUpdate_param_count
.text:vcop_bilinearInterpolateYUV420SPchromaPblockUpdate_param_count
.text:vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_param_count
.text:vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_param_count
.text:vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_param_count
.text:vcop_memcpy_param_count
.text:vcop_memcpy_init
.text:vcop_nnInterpolate420SPchromaPblockUpdate_param_count
.text:vcop_nnInterpolate422IchromaUPblockUpdate_param_count
.text:vcop_nnInterpolate422IchromaVPblockUpdate_param_count
.text:REMAP_MERGE_TI_deactivate
.text:vcop_remap_tile_approach_init
.text:vcop_remap_bb_approach_init
.text:vcop_bilinearInterpolateYUV420SPchromaBB_init
.text:vcop_chromaTLUIndexCalcBilInterpolateBB_init
.text:vcop_dsTLUindexAndFracBilInterpolateBB_init
.text:vcop_nnInterpolate422IchromaBB_init
.text:vcop_nnInterpolate420SPchromaBB_init
.text:vcop_chromaTLUIndexCalcNNInterpolateBB_param_count
.text:EDMA_UTILS_autoIncrement_init
.text:vcop_chromaTLUIndexCalcNNInterpolateBB_init
.text:vcop_dsTLUindexAndFracNNInterpolateBB_init
.text:vcop_bilinearInterpolateYUV420SPchromaBB_param_count
.text:vcop_chromaTLUIndexCalcBilInterpolateBB_param_count
.text:vcop_dsTLUindexAndFracBilInterpolateBB_param_count
.text:vcop_dsTLUindexAndFracNNInterpolateBB_param_count
.text:vcop_nnInterpolate420SPchromaBB_param_count
.text:vcop_nnInterpolate422IchromaBB_param_count
} align = 0x4000 > EXTMEM   PAGE 0
 
  GROUP (my_funcs_perblock)
{
.text:BAM_execute
.text:Bam_RemapMerge_compute
.text:Bam_Remap_compute
.text:VCOP_SET_MEM_VIEW
.text:BAM_dummyKernelFunc
.text:EDMA_UTILS_autoIncrement_triggerOutChannel
.text:EDMA_UTILS_autoIncrement1D_triggerInChannel
.text:EDMA_UTILS_autoIncrement_triggerInChannel
.text:EDMA_UTILS_scattherGather_updateNtrigger
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SINK_trigger
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SINK_wait
.text:vcop_dsTLUindexAndFracBilInterpolatePblockUpdate_vloops
.text:vcop_dsTLUindexAndFracNNInterpolatePblockUpdate_vloops
.text:vcop_bilinearInterpolateYUV422IchromaVPblockUpdate_vloops
.text:vcop_bilinearInterpolateYUV420SPchromaPblockUpdate_vloops
.text:vcop_nnInterpolate422IchromaVPblockUpdate_vloops
.text:vcop_bilinearInterpolateLumaPblockUpdate_vloops
.text:vcop_bilinearInterpolateYUV422IchromaUPblockUpdate_vloops
.text:vcop_nnInterpolate420SPchromaPblockUpdate_vloops
.text:vcop_nnInterpolate422IchromaUPblockUpdate_vloops
.text:vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate_vloops
.text:vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate_vloops
.text:vcop_memcpy_vloops
.text:vcop_remap_dummy
.text:vcop_deInterleaveYUV422IBE_vloops
.text:vcop_deInterleaveYUV422ILE_vloops
.text:vcop_bilinearInterpolate16b_vloops
.text:vcop_bilinearInterpolate8b_vloops
.text:vcop_bilinearInterpolateYUV422Ichroma_vloops
.text:vcop_bilinearInterpolateYUV422Iluma_vloops
.text:vcop_bilinearInterpolateYUV420SPchroma_vloops
.text:vcop_nnInterpolate420SPchroma_vloops
.text:vcop_nnInterpolate422Ichroma_vloops
.text:vcop_nnInterpolate8b_vloops
.text:vcop_chromaTLUIndexCalcBilInterpolate_vloops
.text:vcop_chromaTLUIndexCalcNNInterpolate_vloops
.text:vcop_dsTLUindexAndFracBilInterpolate_vloops
.text:vcop_dsTLUindexAndFracNNInterpolate_vloops
.text:vcop_yuv_420nv12_to_422uyvy_vloops
.text:vcop_yuv_422uyvy_to_420nv12_vloops
.text:vcop_alpha_blend_yuv420nv12_vloops
.text:vcop_alpha_blend_yuv422i_vloops
.text:EDMA_UTILS_autoIncrement_waitOutChannel
.text:EDMA_UTILS_autoIncrement1D_waitInChannel
.text:EDMA_UTILS_autoIncrement_waitInChannel
.text:EDMA_UTILS_scattherGather_wait
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_TileApproach_wait
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_TileApproach_trigger
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_BBApproach_trigger
.text:vcop_bilinearInterpolateYUV420SPchromaBB_vloops
.text:vcop_chromaTLUIndexCalcBilInterpolateBB_vloops
.text:vcop_chromaTLUIndexCalcNNInterpolateBB_vloops
.text:vcop_dsTLUindexAndFracBilInterpolateBB_vloops
.text:vcop_dsTLUindexAndFracNNInterpolateBB_vloops
.text:vcop_nnInterpolate422IchromaBB_vloops
.text:vcop_remap_tile_approach
.text:vcop_remap_bb_approach
.text:vcop_nnInterpolate420SPchromaBB_vloops
.text:BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_BBApproach_wait
 } align = 0x4000 > EXTMEM   PAGE 0

  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1
}
