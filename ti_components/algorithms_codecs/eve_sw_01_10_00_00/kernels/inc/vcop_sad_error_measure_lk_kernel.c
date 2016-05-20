#include <vcop\vcop.h>

typedef unsigned char uchar;

#pragma DATA_SECTION(__pblock_vcop_sad_error_measure_lk, ".vcop_parameter_block")
#pragma DATA_ALIGN(__pblock_vcop_sad_error_measure_lk, __ALIGNOF__(int));
unsigned short __pblock_vcop_sad_error_measure_lk[56];

unsigned int vcop_sad_error_measure_lk_param_count(void)
{
   return 56u;
}

unsigned int vcop_sad_error_measure_lk_ctrl_count(void)
{
   return 0u;
}

unsigned int vcop_sad_error_measure_lk_init(
   __vptr_uint8 pPrevBiLinImg_A,
   __vptr_uint8 pCurrBiLinImg_B,
   __vptr_uint16 pNewXYList_X,
   __vptr_uint16 pOutErrorMeasure_C,
   unsigned short inputStride,
   unsigned short frmWidth,
   unsigned short frmHeight,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short numKeyPoints,
   unsigned short shiftValue,
   __vptr_uint16 scratch_a,
   unsigned short pblock[])
{
   int __offset = 0;
   /* Loop 1 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), ((numKeyPoints + (8u)-1)/(8u))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((8u)/2)-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blkHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pCurrBiLinImg_B);
   __vcop_pblock_init32(pblock, __offset+_PREG(8), (uchar *)pPrevBiLinImg_A+inputStride*blkHeight*sizeof(*pPrevBiLinImg_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(10), (uchar *)pCurrBiLinImg_B+inputStride*blkHeight*sizeof(*pPrevBiLinImg_A));
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)scratch_a);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_a+sizeof(*pOutErrorMeasure_C));
   __vcop_pblock_init16(pblock, __offset+_PREG(16), (inputStride*sizeof(*pPrevBiLinImg_A)));
   __vcop_pblock_init16(pblock, __offset+_PREG(17), (2*inputStride*blkHeight*sizeof(*pPrevBiLinImg_A)) -(inputStride*sizeof(*pPrevBiLinImg_A))*((blkHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(18), (8u*blkHeight*inputStride*sizeof(*pPrevBiLinImg_A)) -(2*inputStride*blkHeight*sizeof(*pPrevBiLinImg_A))*(((8u)/2)-1u) -(inputStride*sizeof(*pPrevBiLinImg_A))*((blkHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(19), 4);
   __vcop_pblock_init32(pblock, __offset+_PREG(20), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(22), (uchar *)pPrevBiLinImg_A);
   __offset += 22;

   /* Loop 2 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), ((numKeyPoints + 2*(8u)-1)/(2*(8u)))-1u);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), (blkHeight)-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (uchar *)pOutErrorMeasure_C);
   __vcop_pblock_init16(pblock, __offset+_PREG(8), 36);
   __vcop_pblock_init16(pblock, __offset+_PREG(9), (36*8u) -(36)*((blkHeight)-1u));
   __vcop_pblock_init16(pblock, __offset+_PREG(10), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), 0);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)scratch_a);
   __offset += 14;

   /* Loop 3 PREGS */
   __vcop_pblock_init16(pblock, __offset+_PREG(2), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(3), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(4), 0);
   __vcop_pblock_init16(pblock, __offset+_PREG(5), ((numKeyPoints + (8u)-1)/(8u))-1u);
   __vcop_pblock_init32(pblock, __offset+_PREG(6), (frmHeight - (7)/2-2));
   __vcop_pblock_init32(pblock, __offset+_PREG(8), -shiftValue);
   __vcop_pblock_init32(pblock, __offset+_PREG(10), 0xFFFF);
   __vcop_pblock_init32(pblock, __offset+_PREG(12), (uchar *)pOutErrorMeasure_C);
   __vcop_pblock_init32(pblock, __offset+_PREG(14), (uchar *)pNewXYList_X);
   __vcop_pblock_init16(pblock, __offset+_PREG(16), 16);
   __vcop_pblock_init16(pblock, __offset+_PREG(17), 32);
   __vcop_pblock_init32(pblock, __offset+_PREG(18), ((7)/2+1));
   __vcop_pblock_init32(pblock, __offset+_PREG(20), (frmWidth - (7)/2-2));
   __offset += 20;

   return 56u;
}

void vcop_sad_error_measure_lk_vloops(
   unsigned short pblock[])
{
   /* Kernel-wide Vector Registers */

   __vcop_param(&pblock[0]);

   /* VLOOP 1 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("VimC", 16);
   #pragma VCC_VREG("VimC1", 17);
   #pragma VCC_VREG("VimP", 18);
   #pragma VCC_VREG("VimP1", 19);
   #pragma VCC_VREG("VsumAbsDiff", 20);
   #pragma VCC_VREG("VsumAbsDiff1", 21);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr1", "A0");
   #pragma EVE_REG("inAddr2", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I2");
   #pragma EVE_REG("I1", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 14u, 11u, 1u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(20));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(20), _VREG(21));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(16), _PREG(17), _PREG(18), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(19), _PREG(19), _PREG(0));
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(22), _AGEN(0), _VREG(18), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(6), _AGEN(1), _VREG(16), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(8), _AGEN(0), _VREG(19), __vcop_alws());
   __vcop_vload(__vcop_sizeBU(), __vcop_npt(), _PREG(10), _AGEN(1), _VREG(17), __vcop_alws());
   __vcop_vsad(_VREG(16), _VREG(18), _VREG(20));
   __vcop_vsad(_VREG(17), _VREG(19), _VREG(21));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(20), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_offst_np1(), __vcop_last_i4(), _VREG(21), _PREG(14), _AGEN(2), _PREG(0));
   __vcop_vloop_end(1u);

   /* VLOOP 2 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Veven", 22);
   #pragma VCC_VREG("Vodd", 23);
   #pragma VCC_VREG("VsumAbsDiff", 24);
   #pragma VCC_VREG("VsumAbsDiff1", 25);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr1", "A0");
   #pragma EVE_REG("inAddr2", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I3");
   #pragma EVE_REG("I2", "I4");
   

   __vcop_vloop(__vcop_compute(), 10u, 7u, 2u);
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(24));
   __vcop_vinit(__vcop_sizeW(), __vcop_i4_zero(), _PREG(12), _VREG(25));
   __vcop_vagen(_AGEN(0), _PREG(8), _PREG(9), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(0), _PREG(10), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(0), _VPAIR(23,22), __vcop_alws());
   __vcop_vadd(_VREG(24), _VREG(23), _VREG(24));
   __vcop_vadd(_VREG(25), _VREG(22), _VREG(25));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_intrlv(), __vcop_last_i4(), _VPAIR(24,25), _PREG(6), _AGEN(2), _PREG(0));
   __vcop_vloop_end(2u);

   /* VLOOP 3 Start */

   /* VLOOP Local Vector Registers */
   #pragma VCC_VREG("Verror", 26);
   #pragma VCC_VREG("Vflag", 27);
   #pragma VCC_VREG("Vflag1", 28);
   #pragma VCC_VREG("Vflag2", 29);
   #pragma VCC_VREG("Vlimit1", 30);
   #pragma VCC_VREG("Vlimit2", 31);
   #pragma VCC_VREG("Vlimit3", 32);
   #pragma VCC_VREG("Vmaxerror", 33);
   #pragma VCC_VREG("Vshift", 34);
   #pragma VCC_VREG("Vxint", 35);
   #pragma VCC_VREG("Vyint", 36);
   

   /* VLOOP Local Address Generators */
   #pragma EVE_REG("inAddr1", "A0");
   #pragma EVE_REG("inAddr2", "A1");
   #pragma EVE_REG("outAddr", "A2");
   /* VLOOP Loop Control Variables   */
   #pragma EVE_REG("I0", "I4");
   

   __vcop_vloop(__vcop_compute(), 21u, 10u, 3u);
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(18), _VREG(30));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(20), _VREG(31));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(6), _VREG(32));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(8), _VREG(34));
   __vcop_vinit(__vcop_sizeW(), __vcop_alws(), _PREG(10), _VREG(33));
   __vcop_vagen(_AGEN(0), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(1), _PREG(17), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vagen(_AGEN(2), _PREG(16), _PREG(0), _PREG(0), _PREG(0));
   __vcop_vload(__vcop_sizeHU(), __vcop_npt(), _PREG(12), _AGEN(0), _VREG(26), __vcop_alws());
   __vcop_vload(__vcop_sizeHU(), __vcop_dintrlv(), _PREG(14), _AGEN(1), _VPAIR(35,36), __vcop_alws());
   __vcop_vshf(_VREG(35), _VREG(34), _VREG(35));
   __vcop_vshf(_VREG(36), _VREG(34), _VREG(36));
   __vcop_vcmplt(_VREG(35), _VREG(30), _VREG(28));
   __vcop_vcmpge(_VREG(35), _VREG(31), _VREG(29));
   __vcop_vor(_VREG(28), _VREG(29), _VREG(27));
   __vcop_vcmplt(_VREG(36), _VREG(30), _VREG(28));
   __vcop_vcmpge(_VREG(36), _VREG(32), _VREG(29));
   __vcop_vor3(_VREG(28), _VREG(29), _VREG(27));
   __vcop_vsel(_VREG(27), _VREG(33), _VREG(26));
   __vcop_vstore(__vcop_unconditional(), __vcop_sizeHU(), __vcop_npt(), __vcop_alws(), _VREG(26), _PREG(12), _AGEN(2), _PREG(0));
   __vcop_vloop_end(3u);

}

void vcop_sad_error_measure_lk(
   __vptr_uint8 pPrevBiLinImg_A,
   __vptr_uint8 pCurrBiLinImg_B,
   __vptr_uint16 pNewXYList_X,
   __vptr_uint16 pOutErrorMeasure_C,
   unsigned short inputStride,
   unsigned short frmWidth,
   unsigned short frmHeight,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short numKeyPoints,
   unsigned short shiftValue,
   __vptr_uint16 scratch_a)
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sad_error_measure_lk_init(pPrevBiLinImg_A, pCurrBiLinImg_B, pNewXYList_X, pOutErrorMeasure_C, inputStride, frmWidth, frmHeight, blkWidth, blkHeight, numKeyPoints, shiftValue, scratch_a, __pblock_vcop_sad_error_measure_lk);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sad_error_measure_lk_vloops(__pblock_vcop_sad_error_measure_lk);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

void vcop_sad_error_measure_lk_custom(
   __vptr_uint8 pPrevBiLinImg_A,
   __vptr_uint8 pCurrBiLinImg_B,
   __vptr_uint16 pNewXYList_X,
   __vptr_uint16 pOutErrorMeasure_C,
   unsigned short inputStride,
   unsigned short frmWidth,
   unsigned short frmHeight,
   unsigned short blkWidth,
   unsigned short blkHeight,
   unsigned short numKeyPoints,
   unsigned short shiftValue,
   __vptr_uint16 scratch_a,
   unsigned short pblock[])
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
   vcop_sad_error_measure_lk_init(pPrevBiLinImg_A, pCurrBiLinImg_B, pNewXYList_X, pOutErrorMeasure_C, inputStride, frmWidth, frmHeight, blkWidth, blkHeight, numKeyPoints, shiftValue, scratch_a, pblock);

   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                   IBUFHA_VCOP, IBUFLA_VCOP);
   vcop_sad_error_measure_lk_vloops(pblock);

   _vcop_vloop_done();
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                   IBUFHA_SYST, IBUFLA_SYST);
}

