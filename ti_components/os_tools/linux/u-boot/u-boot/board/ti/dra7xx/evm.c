/*
 * (C) Copyright 2013
 * Texas Instruments Incorporated, <www.ti.com>
 *
 * Lokesh Vutla <lokeshvutla@ti.com>
 *
 * Based on previous work by:
 * Aneesh V       <aneesh@ti.com>
 * Steve Sakoman  <steve@sakoman.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <palmas.h>
#include <sata.h>
#include <asm/gpio.h>
#include <asm/arch/gpio.h>
#include <usb.h>
#include <linux/usb/gadget.h>
#include <asm/arch/dra7xx_iodelay.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/arch/sata.h>
#include <environment.h>
#include <dwc3-uboot.h>
#include <dwc3-omap-uboot.h>
#include <ti-usb-phy-uboot.h>
#include <pcf8575.h>
#include <spl.h>
#include <remoteproc.h>

#include "mux_data.h"

#ifdef CONFIG_DRIVER_TI_CPSW
#include <cpsw.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

/* GPIO 7_11 */
#define GPIO_DDR_VTT_EN 203

/* pcf chip address enet_mux_s0 */
#define PCF_ENET_MUX_ADDR	0x21
#define PCF_SEL_ENET_MUX_S0	4

const struct omap_sysinfo sysinfo = {
	"Board: DRA7xx\n"
};

#ifdef CONFIG_LATE_ATTACH
#define DPLL_TIMEOUT                 5000
#define L4_CFG_TARG                  0x4A000000
#define L4_WKUP_TARG                 0x4AE00000
#define IPU2_TARGET_TARG             0x55000000
#define IPU1_TARGET_TARG             0x58800000
#define CTRL_MODULE_CORE             (L4_CFG_TARG + 0x2000)
#define CM_CORE_AON                  (L4_CFG_TARG + 0x5000)
#define CM_CORE                      (L4_CFG_TARG + 0x8000)
#define PRM                          (L4_WKUP_TARG + 0x6000)
#define MPU_CM_CORE_AON              (CM_CORE_AON + 0x300)
#define IPU_CM_CORE_AON              (CM_CORE_AON + 0x500)
#define RTC_CM_CORE_AON              (CM_CORE_AON + 0x740)
#define VPE_CM_CORE_AON              (CM_CORE_AON + 0x760)
#define COREAON_CM_CORE              (CM_CORE + 0x600)
#define CORE_CM_CORE                 (CM_CORE + 0x700)
#define CAM_CM_CORE                  (CM_CORE + 0x1000)
#define DSS_CM_CORE                  (CM_CORE + 0x1100)
#define L3INIT_CM_CORE               (CM_CORE + 0x1300)
#define L4PER_CM_CORE                (CM_CORE + 0x1700)
#define CKGEN_PRM                    (PRM + 0x100)
#define IPU_PRM                      (PRM + 0x500)
#define CORE_PRM                     (PRM + 0x700)
#define WKUPAON_CM                   (PRM + 0x1800)

#define CM_CLKMODE_DPLL_DSP          (0x4A005234)
#define CM_DSP1_CLKSTCTRL            (0x4A005400)
#define CM_DSP2_CLKSTCTRL            (0x4A005600)
#define DSP1_PRM_BASE                (0x4AE06400)
#define DSP2_PRM_BASE                (0x4AE07B00)
#define DSP1_SYS_MMU_CONFIG          (0x40D00018)
#define DSP2_SYS_MMU_CONFIG          (0x41500018)

/* CTRL_CORE_CONTROL_DSP1_RST_VECTOR in TRM */
#define DSP1_BOOTADDR                (0x4A00255C)
/* CTRL_CORE_CONTROL_DSP2_RST_VECTOR in TRM */
#define DSP2_BOOTADDR                (0x4A002560)
#define DRA7XX_CTRL_CORE_DSP_RST_VECT_MASK	(0x3FFFFF << 0)

#define CM_L3MAIN1_CLKSTCTRL         (CORE_CM_CORE + 0x000)
#define CM_IPU2_CLKSTCTRL            (CORE_CM_CORE + 0x200)
#define CM_DMA_CLKSTCTRL             (CORE_CM_CORE + 0x300)
#define CM_EMIF_CLKSTCTRL            (CORE_CM_CORE + 0x400)
#define CM_L4CFG_CLKSTCTRL           (CORE_CM_CORE + 0x600)

#define CM_DSS_CLKSTCTRL             (DSS_CM_CORE + 0x00)
#define CM_CAM_CLKSTCTRL             (CAM_CM_CORE + 0x00)
#define CM_COREAON_CLKSTCTRL         (COREAON_CM_CORE + 0x00)
#define CM_L3INIT_CLKSTCTRL          (L3INIT_CM_CORE + 0x00)
#define CM_GMAC_CLKSTCTRL            (L3INIT_CM_CORE + 0xC0)
#define CM_L4PER_CLKSTCTRL           (L4PER_CM_CORE + 0x000)
#define CM_L4PER_TIMER11_CLKCTRL     (CM_L4PER_CLKSTCTRL + 0x30)
#define CM_L4PER_TIMER3_CLKCTRL      (CM_L4PER_CLKSTCTRL + 0x40)
#define CM_L4PER_TIMER4_CLKCTRL      (CM_L4PER_CLKSTCTRL + 0x48)
#define CM_L4PER_TIMER9_CLKCTRL      (CM_L4PER_CLKSTCTRL + 0x50)
#define CM_L4PER2_CLKSTCTRL          (L4PER_CM_CORE + 0x1FC)
#define CM_L4PER3_CLKSTCTRL          (L4PER_CM_CORE + 0x210)
#define CM_MPU_CLKSTCTRL             (MPU_CM_CORE_AON + 0x00)
#define CM_RTC_CLKSTCTRL             (RTC_CM_CORE_AON + 0x00)
#define CM_VPE_CLKSTCTRL             (VPE_CM_CORE_AON + 0x00)
#define CM_WKUPAON_CLKSTCTRL         (WKUPAON_CM + 0x00)

#define RM_IPU1_RSTCTRL              (IPU_PRM + 0x10)
#define RM_IPU1_RSTST                (IPU_PRM + 0x14)
#define CM_IPU1_CLKSTCTRL            (IPU_CM_CORE_AON + 0x0)
#define CM_IPU1_IPU1_CLKCTRL         (IPU_CM_CORE_AON + 0x20)
#define CM_IPU2_IPU2_CLKCTRL         (CORE_CM_CORE + 0x220)
#define CM_IPU_CLKSTCTRL             (IPU_CM_CORE_AON + 0x40)
#define CM_IPU_MCASP1_CLKCTRL        (IPU_CM_CORE_AON + 0x50)
#define CM_IPU_TIMER5_CLKCTRL        (IPU_CM_CORE_AON + 0x58)
#define CM_IPU_TIMER6_CLKCTRL        (IPU_CM_CORE_AON + 0x60)
#define CM_IPU_TIMER7_CLKCTRL        (IPU_CM_CORE_AON + 0x68)
#define CM_IPU_TIMER8_CLKCTRL        (IPU_CM_CORE_AON + 0x70)
#define CM_L4PER2_L4_PER2_CLKCTRL    (L4PER_CM_CORE + 0x0C)
#define CM_L4PER3_L4_PER3_CLKCTRL    (L4PER_CM_CORE + 0x14)
#define CM_L4PER_I2C1_CLKCTRL        (L4PER_CM_CORE + 0xA0)
#define CM_L4PER_I2C2_CLKCTRL        (L4PER_CM_CORE + 0xA8)
#define CM_L4PER_I2C3_CLKCTRL        (L4PER_CM_CORE + 0xB0)
#define CM_L4PER_I2C4_CLKCTRL        (L4PER_CM_CORE + 0xB8)
#define CM_L4PER_L4_PER1_CLKCTRL     (L4PER_CM_CORE + 0xC0)
#define CM_CAM_VIP1_CLKCTRL          (CAM_CM_CORE + 0x20)
#define CM_CAM_VIP2_CLKCTRL          (CAM_CM_CORE + 0x28)
#define CM_CAM_VIP3_CLKCTRL          (CAM_CM_CORE + 0x30)
#define CM_DMA_DMA_SYSTEM_CLKCTRL    (CORE_CM_CORE + 0x320)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL (CORE_CM_CORE + 0x728)
#define CM_DSS_DSS_CLKCTRL           (DSS_CM_CORE + 0x20)
#define CM_VPE_VPE_CLKCTRL           (VPE_CM_CORE_AON + 0x04)

#define RM_IPU2_RSTCTRL              (CORE_PRM + 0x210)
#define RM_IPU2_RSTST                (CORE_PRM + 0x214)

#define CTRL_CORE_CONTROL_IO_2       (CTRL_MODULE_CORE + 0x558)

#define CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR 0x4A002358
#define CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR  0x4A00235C

#define PAGESIZE_1M                          0x0
#define PAGESIZE_64K                         0x1
#define PAGESIZE_4K                          0x2
#define PAGESIZE_16M                         0x3
#define LE                                   0
#define BE                                   1
#define ELEMSIZE_8                           0x0
#define ELEMSIZE_16                          0x1
#define ELEMSIZE_32                          0x2
#define MIXED_TLB                            0x0
#define MIXED_CPU                            0x1

#define PGT_SMALLPAGE_SIZE                   0x00001000
#define PGT_LARGEPAGE_SIZE                   0x00010000
#define PGT_SECTION_SIZE                     0x00100000
#define PGT_SUPERSECTION_SIZE                0x01000000

#define PGT_L1_DESC_PAGE                     0x00001
#define PGT_L1_DESC_SECTION                  0x00002
#define PGT_L1_DESC_SUPERSECTION             0x40002

#define PGT_L1_DESC_PAGE_MASK                0xfffffC00
#define PGT_L1_DESC_SECTION_MASK             0xfff00000
#define PGT_L1_DESC_SUPERSECTION_MASK        0xff000000

#define PGT_L1_DESC_SMALLPAGE_INDEX_SHIFT    12
#define PGT_L1_DESC_LARGEPAGE_INDEX_SHIFT    16
#define PGT_L1_DESC_SECTION_INDEX_SHIFT      20
#define PGT_L1_DESC_SUPERSECTION_INDEX_SHIFT 24

#define PGT_L2_DESC_SMALLPAGE               0x02
#define PGT_L2_DESC_LARGEPAGE               0x01

#define PGT_L2_DESC_SMALLPAGE_MASK          0xfffff000
#define PGT_L2_DESC_LARGEPAGE_MASK          0xffff0000

#define DRA7_RPROC_CMA_BASE_IPU1             0x9d000000
#define DRA7_RPROC_CMA_BASE_IPU2             0x95800000
#define DRA7_RPROC_CMA_BASE_DSP1             0x99000000
#define DRA7_RPROC_CMA_BASE_DSP2             0x9f000000

#define DRA7_RPROC_CMA_SIZE_IPU1             0x02000000
#define DRA7_RPROC_CMA_SIZE_IPU2             0x03800000
#define DRA7_RPROC_CMA_SIZE_DSP1             0x04000000
#define DRA7_RPROC_CMA_SIZE_DSP2             0x00800000

/*
 * The page table (32 KB) is placed at the end of the CMA reserved area.
 * It's possible that this location is needed by the firmware (in which
 * case the firmware is using pretty much *all* of the reserved area), but
 * there doesn't seem to be a better location to place it.
 *
 * We only need 16 KB memory for the page table if we are using all 1
 * MB sections.  There might be cases where we need to allocate memory
 * at a lower granularity.  For these cases, we are allocating 16 KB
 * additional memory.
 */
#define PAGE_TABLE_SIZE_L1 (0x00004000)
#define PAGE_TABLE_SIZE_L2 (0x400)
#define MAX_NUM_L2_PAGE_TABLES (16)
#define PAGE_TABLE_SIZE_L2_TOTAL (MAX_NUM_L2_PAGE_TABLES*PAGE_TABLE_SIZE_L2)
#define PAGE_TABLE_SIZE (PAGE_TABLE_SIZE_L1+(PAGE_TABLE_SIZE_L2_TOTAL))

#define PAGE_SHIFT 12
#define PAGE_SIZE  (1 << PAGE_SHIFT)

#define BITS_PER_BYTE 8
#undef BITS_PER_LONG
#define BITS_PER_LONG (sizeof(long) * BITS_PER_BYTE)
#define BITS_TO_LONGS(nbits) (((nbits) + BITS_PER_LONG - 1) / BITS_PER_LONG)

#define BIT_WORD(nr) ((nr) / BITS_PER_LONG)
#define BITOP_WORD(nr) BIT_WORD(nr)

#define BITMAP_FIRST_WORD_MASK(start) (~0UL << ((start) % BITS_PER_LONG))
#define BITMAP_LAST_WORD_MASK(nbits)                                    \
(                                                                       \
	((nbits) % BITS_PER_LONG) ?                                     \
		(1UL<<((nbits) % BITS_PER_LONG))-1 : ~0UL               \
)

unsigned int *page_table_l1 = (unsigned int *)0x0;
unsigned int *page_table_l2 = (unsigned int *)0x0;

/* Set maximum carveout size to 96 MB */
#define DRA7_RPROC_MAX_CMA_SIZE (96*0x100000)

/* These global variables are used for deriving the MMU page tables.
 * They are initialized for each core with the appropriate values.
 *
 * The length of the array mem_bitmap is set as per a 96 MB carveout which
 * the maximum set aside in the current memory map.
 */
unsigned long mem_base = 0;
unsigned long mem_size = 0;
unsigned long mem_bitmap[BITS_TO_LONGS(DRA7_RPROC_MAX_CMA_SIZE >> PAGE_SHIFT)];
unsigned long mem_count = 0;

unsigned int pgtable_l2_map[MAX_NUM_L2_PAGE_TABLES];
unsigned int pgtable_l2_cnt = 0;

void bitmap_set(unsigned long *map, int start, int nr)
{
	unsigned long *p = map + BIT_WORD(start);
	const int size = start + nr;
	int bits_to_set = BITS_PER_LONG - (start % BITS_PER_LONG);
	unsigned long mask_to_set = BITMAP_FIRST_WORD_MASK(start);

	while (nr - bits_to_set >= 0) {
		*p |= mask_to_set;
		nr -= bits_to_set;
		bits_to_set = BITS_PER_LONG;
		mask_to_set = ~0UL;
		p++;
	}
	if (nr) {
		mask_to_set &= BITMAP_LAST_WORD_MASK(size);
		*p |= mask_to_set;
	}
}

static unsigned long __ffs(unsigned long word)
{
	int num = 0;

	if ((word & 0xffff) == 0) {
		num += 16;
		word >>= 16;
	}
	if ((word & 0xff) == 0) {
		num += 8;
		word >>= 8;
	}
	if ((word & 0xf) == 0) {
		num += 4;
		word >>= 4;
	}
	if ((word & 0x3) == 0) {
		num += 2;
		word >>= 2;
	}
	if ((word & 0x1) == 0)
		num += 1;
	return num;
}

#define ffz(x) __ffs(~(x))

/*
 * This has an "evm_" prefix since without the prefix it clashes with the
 * non-existant-yet-declared "find_next_zero_bit" in
 * arch/arm/include/asm/bitops.h.
 */
unsigned long evm_find_next_zero_bit(const unsigned long *addr,
				     unsigned long size, unsigned long offset)
{
	const unsigned long *p = addr + BITOP_WORD(offset);
	unsigned long result = offset & ~(BITS_PER_LONG - 1);
	unsigned long tmp;

	if (offset >= size)
		return size;
	size -= result;
	offset %= BITS_PER_LONG;
	if (offset) {
		tmp = *(p++);
		tmp |= ~0UL >> (BITS_PER_LONG - offset);
		if (size < BITS_PER_LONG)
			goto found_first;
		if (~tmp)
			goto found_middle;
		size -= BITS_PER_LONG;
		result += BITS_PER_LONG;
	}
	while (size & ~(BITS_PER_LONG - 1)) {
		if (~(tmp = *(p++)))
			goto found_middle;
		result += BITS_PER_LONG;
		size -= BITS_PER_LONG;
	}
	if (!size)
		return result;
	tmp = *p;

found_first:
	tmp |= ~0UL << size;
	if (tmp == ~0UL)	/* Are any bits zero? */
		return result + size;	/* Nope. */
found_middle:
	return result + ffz(tmp);
}

unsigned long find_next_bit(const unsigned long *addr, unsigned long size,
			    unsigned long offset)
{
	const unsigned long *p = addr + BITOP_WORD(offset);
	unsigned long result = offset & ~(BITS_PER_LONG - 1);
	unsigned long tmp;

	if (offset >= size)
		return size;
	size -= result;
	offset %= BITS_PER_LONG;
	if (offset) {
		tmp = *(p++);
		tmp &= (~0UL << offset);
		if (size < BITS_PER_LONG)
			goto found_first;
		if (tmp)
			goto found_middle;
		size -= BITS_PER_LONG;
		result += BITS_PER_LONG;
	}
	while (size & ~(BITS_PER_LONG - 1)) {
		if ((tmp = *(p++)))
			goto found_middle;
		result += BITS_PER_LONG;
		size -= BITS_PER_LONG;
	}
	if (!size)
		return result;
	tmp = *p;

found_first:
	tmp &= (~0UL >> (BITS_PER_LONG - size));
	if (tmp == 0UL)		/* Are any bits set? */
		return result + size;	/* Nope. */
found_middle:
	return result + __ffs(tmp);
}

unsigned long bitmap_find_next_zero_area(unsigned long *map,
					 unsigned long size,
					 unsigned long start,
					 unsigned int nr,
					 unsigned long align_mask)
{
	unsigned long index, end, i;
again:
	index = evm_find_next_zero_bit(map, size, start);

	/* Align allocation */
	index = (index + align_mask) & ~align_mask;

	end = index + nr;
	if (end > size)
		return end;
	i = find_next_bit(map, end, index);
	if (i < end) {
		start = i + 1;
		goto again;
	}
	return index;
}

void *alloc_mem(unsigned long len, unsigned long align)
{
	unsigned long mask;
	unsigned long pageno;
	int count;

	count = ((len + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1)) >> PAGE_SHIFT;
	mask = (1 << align) - 1;
	pageno = bitmap_find_next_zero_area(mem_bitmap, mem_count, 0, count,
					    mask);
	debug("alloc_mem: count %d mask %#lx pageno %#lx\n", count, mask,
	      pageno);

	if (pageno >= mem_count)
		return NULL;

	bitmap_set(mem_bitmap, pageno, count);
	return (void *)(mem_base + (pageno << PAGE_SHIFT));
}

int find_pagesz(unsigned int virt, unsigned int phys, unsigned int len)
{
	int pg_sz_ind = -1;
	unsigned int min_align = __ffs(virt);

	if (min_align > __ffs(phys))
		min_align = __ffs(phys);

	if ((min_align >= PGT_L1_DESC_SUPERSECTION_INDEX_SHIFT) &&
	    (len >= 0x1000000)) {
		pg_sz_ind = PAGESIZE_16M;
		goto ret_block;
	}
	if ((min_align >= PGT_L1_DESC_SECTION_INDEX_SHIFT) &&
	    (len >= 0x100000)) {
		pg_sz_ind = PAGESIZE_1M;
		goto ret_block;
	}
	if ((min_align >= PGT_L1_DESC_LARGEPAGE_INDEX_SHIFT) &&
	    (len >= 0x10000)) {
		pg_sz_ind = PAGESIZE_64K;
		goto ret_block;
	}
	if ((min_align >= PGT_L1_DESC_SMALLPAGE_INDEX_SHIFT) &&
	    (len >= 0x1000)) {
		pg_sz_ind = PAGESIZE_4K;
		goto ret_block;
	}

ret_block:
	return pg_sz_ind;
}

int get_l2_pg_tbl_addr(unsigned int virt, unsigned int *pg_tbl_addr)
{
	int ret = -1;
	int i = 0;
	int match_found = 0;
	unsigned int tag = (virt & PGT_L1_DESC_SECTION_MASK);

	*pg_tbl_addr = 0;
	for (i = 0; (i < pgtable_l2_cnt) && (match_found == 0); i++) {
		if (tag == pgtable_l2_map[i]) {
			*pg_tbl_addr =
			    ((unsigned int)page_table_l2) +
			    (i * PAGE_TABLE_SIZE_L2);
			match_found = 1;
			ret = 0;
		}
	}

	if ((match_found == 0) && (i < MAX_NUM_L2_PAGE_TABLES)) {
		pgtable_l2_map[i] = tag;
		pgtable_l2_cnt++;
		*pg_tbl_addr =
		    ((unsigned int)page_table_l2) + (i * PAGE_TABLE_SIZE_L2);
		ret = 0;
	}

	return ret;
}

int config_l2_pagetable(unsigned int virt, unsigned int phys,
			unsigned int pg_sz, unsigned int pg_tbl_addr)
{
	int ret = -1;
	unsigned int desc = 0;
	int32_t i = 0;
	unsigned int *pg_tbl = (unsigned int *)pg_tbl_addr;

	/* Pick bit 19:12 of the virtual address as index */
	unsigned int index = (virt & (~PGT_L1_DESC_SECTION_MASK)) >> PAGE_SHIFT;

	switch (pg_sz) {
	case PAGESIZE_64K:
		desc =
		    (phys & PGT_L2_DESC_LARGEPAGE_MASK) | PGT_L2_DESC_LARGEPAGE;
		for (i = 0; i < 16; i++)
			pg_tbl[index + i] = desc;
		ret = 0;
		break;
	case PAGESIZE_4K:
		desc =
		    (phys & PGT_L2_DESC_SMALLPAGE_MASK) | PGT_L2_DESC_SMALLPAGE;
		pg_tbl[index] = desc;
		ret = 0;
		break;
	default:
		break;
	}

	return ret;
}

unsigned int config_pagetable(unsigned int virt, unsigned int phys,
			      unsigned int len)
{
	unsigned int index;
	unsigned int l = len;
	unsigned int desc;
	int pg_sz = 0;
	int32_t i = 0;
	int32_t err = 0;
	unsigned int pg_tbl_l2_addr = 0;
	unsigned int tmp_pgsz;

	if ((len & 0x0FFF) != 0)
		return 0;

	while (l > 0) {
		pg_sz = find_pagesz(virt, phys, l);
		index = virt >> PGT_L1_DESC_SECTION_INDEX_SHIFT;
		switch (pg_sz) {
			/* 16 MB super section */
		case PAGESIZE_16M:
			/* Program the next 16 descriptors */
			desc =
			    (phys & PGT_L1_DESC_SUPERSECTION_MASK) |
			    PGT_L1_DESC_SUPERSECTION;
			for (i = 0; i < 16; i++)
				page_table_l1[index + i] = desc;
			l -= PGT_SUPERSECTION_SIZE;
			phys += PGT_SUPERSECTION_SIZE;
			virt += PGT_SUPERSECTION_SIZE;
			break;
			/* 1 MB section */
		case PAGESIZE_1M:
			desc =
			    (phys & PGT_L1_DESC_SECTION_MASK) |
			    PGT_L1_DESC_SECTION;
			page_table_l1[index] = desc;
			l -= PGT_SECTION_SIZE;
			phys += PGT_SECTION_SIZE;
			virt += PGT_SECTION_SIZE;
			break;
			/* 64 KB large page */
		case PAGESIZE_64K:
		case PAGESIZE_4K:
			if (pg_sz == PAGESIZE_64K)
				tmp_pgsz = 0x10000;
			else
				tmp_pgsz = 0x1000;

			err = get_l2_pg_tbl_addr(virt, &pg_tbl_l2_addr);
			if (err != 0) {
				printf("error: Unable to get level 2 page table addresss\n");
				hang();
			}
			err =
			    config_l2_pagetable(virt, phys, pg_sz,
						pg_tbl_l2_addr);
			desc =
			    (pg_tbl_l2_addr & PGT_L1_DESC_PAGE_MASK) |
			    PGT_L1_DESC_PAGE;
			page_table_l1[index] = desc;
			l -= tmp_pgsz;
			phys += tmp_pgsz;
			virt += tmp_pgsz;
			break;
		case -1:
		default:
			return 0;
		}
	}

	return len;
}

void enable_common_clocks(void)
{
	static u32 do_config = 1;

	if (do_config != 1)
		return;

	/* TODO: Review if all of these are actually
	 * necessary.
	 */

	/* enable CORE domain transitions */
	__raw_writel(0x2, CM_CAM_CLKSTCTRL);
	__raw_writel(0x2, CM_L3INIT_CLKSTCTRL);
	__raw_writel(0x2, CM_GMAC_CLKSTCTRL);
	__raw_writel(0x2, CM_EMIF_CLKSTCTRL);
	__raw_writel(0x2, CM_L4CFG_CLKSTCTRL);
	__raw_writel(0x2, CM_DMA_CLKSTCTRL);
	__raw_writel(0x2, CM_COREAON_CLKSTCTRL);
	__raw_writel(0x2, CM_L4PER_CLKSTCTRL);

	/* Some of the timers are on the IPU clock domain */
	__raw_writel(0x2, CM_IPU_CLKSTCTRL);
	do_config = 0;

	return;
}

u32 ipu_start_clocks(u32 core_id, struct rproc *cfg)
{
	u32 reg;
	u32 ipu_clkstctrl = 0;
	u32 ipu_clkctrl = 0;
	u32 tick_timerctrl = 0;
	u32 wdt_ctrl[2] = { 0, 0 };
	u32 ipu_rstctrl = 0;
	u32 ipu_rstst = 0;
	u32 i = 0;

	if (!((core_id == IPU1) || (core_id == IPU2))) {
		printf("Error: %s invoked with incorrect core id: %d\n",
		       __func__, core_id);
		return 1;
	}

	debug("Configuring IPU\n");

	enable_common_clocks();

	if (core_id == IPU1) {
		ipu_clkstctrl = CM_IPU1_CLKSTCTRL;
		ipu_clkctrl = CM_IPU1_IPU1_CLKCTRL;
		ipu_rstctrl = RM_IPU1_RSTCTRL;
		ipu_rstst = RM_IPU1_RSTST;

		tick_timerctrl = CM_L4PER_TIMER11_CLKCTRL;
		wdt_ctrl[0] = CM_IPU_TIMER7_CLKCTRL;
		wdt_ctrl[1] = CM_IPU_TIMER8_CLKCTRL;
	} else {
		ipu_clkstctrl = CM_IPU2_CLKSTCTRL;
		ipu_clkctrl = CM_IPU2_IPU2_CLKCTRL;
		ipu_rstctrl = RM_IPU2_RSTCTRL;
		ipu_rstst = RM_IPU2_RSTST;

		tick_timerctrl = CM_L4PER_TIMER3_CLKCTRL;
		wdt_ctrl[0] = CM_L4PER_TIMER4_CLKCTRL;
		wdt_ctrl[1] = CM_L4PER_TIMER9_CLKCTRL;
	}

	__raw_writel(0x2, ipu_clkstctrl);

	/* Using TIMER_SYS_CLK as the clock source */
	reg = __raw_readl(tick_timerctrl);
	__raw_writel((reg & ~0x0F000003) | 0x00000002, tick_timerctrl);

	for (i = 0; i < 2; i++) {
		if (wdt_ctrl[i] != 0) {
			/*
			 * Using SYS_CLK1_32K_CLK as the clock source for the
			 * watch dog timers. IPU will eventually configure
			 * these timers with the right clock source. If we use
			 * a higher frequency clock as the clock source, the
			 * timer will overflow and trigger a watchdog interrupt
			 * even before the kernel has a chance to connect to
			 * IPU.
			 */
			reg = __raw_readl(wdt_ctrl[i]);
			__raw_writel((reg & ~0x0F000003) | 0x01000002,
				     wdt_ctrl[i]);
		}
	}

	/* enable IPU clocks / hw_auto mode */
	reg = __raw_readl(ipu_clkctrl);
	__raw_writel(((reg & ~0x00000003) | 0x01000000 | 0x1), ipu_clkctrl);

	/* checking if IPU module is enabled */
	while ((__raw_readl(ipu_clkctrl) & 0x00030000) == 0x00030000);

	/* checking if clocks are enabled */
	while (((__raw_readl(ipu_clkstctrl) & 0x100) >> 8) != 1);

	/*Assert the IPU - CPU0,CPU1 & MMU,cache */
	__raw_writel(0x7, ipu_rstctrl);

	/* Bring the IPU Unicache/MMU out of reset */
	__raw_writel(0x7, ipu_rstst);
	__raw_writel(0x3, ipu_rstctrl);

	while ((__raw_readl(ipu_rstst) & 0x4) != 0x4);

	return 0;
}

u32 ipu_config_mmu(u32 core_id, struct rproc *cfg)
{
	u32 i = 0;
	u32 reg = 0;

	/*
	 * Clear the entire pagetable location before programming the
	 * address into the MMU
	 */
	memset((void *)cfg->page_table_addr, 0x00, PAGE_TABLE_SIZE);
	debug("Cleared the page table for MMU\n");

	for (i = 0; i < cfg->num_iommus; i++) {

		u32 mmu_base = cfg->mmu_base_addr[i];

		__raw_writel((int)cfg->page_table_addr, mmu_base + 0x4c);
		reg = __raw_readl(mmu_base + 0x88);

		/* enable bus-error back */
		__raw_writel(reg | 0x1, mmu_base + 0x88);

		/*
		 * Enable the MMU IRQs during MMU programming for the
		 * late attachcase. This is to allow the MMU fault to be
		 * detected by the kernel.
		 *
		 * MULTIHITFAULT|EMMUMISS|TRANSLATIONFAULT|TABLEWALKFAULT
		 */
		__raw_writel(0x1E, mmu_base + 0x1c);

		/* emutlbupdate|TWLENABLE|MMUENABLE */
		__raw_writel(0x6, mmu_base + 0x44);
	}

	return 0;
}

u32 ipu_start_core(u32 core_id, struct rproc *cfg)
{
	u32 retVal = 1;
	u32 RST_CTRL = 0;	/* Reset control */
	u32 RST_ST = 0;		/* Reset State */

	if (core_id == IPU2) {
		RST_CTRL = RM_IPU2_RSTCTRL;
		RST_ST = RM_IPU2_RSTST;
		retVal = 0;
	} else if (core_id == IPU1) {
		RST_CTRL = RM_IPU1_RSTCTRL;
		RST_ST = RM_IPU1_RSTST;
		retVal = 0;
	}

	if (retVal == 0) {
		/* bring the IPU2 out of reset */
		__raw_writel(0x0, RST_CTRL);

		/* check module is functional or not */
		while (((__raw_readl(RST_ST) & 0x7) != 0x7));

		retVal = 0;
	}

	return retVal;
}

/******************************************************************************
 * dpll_lock_sequence() : DPLL lock sequence
 *****************************************************************************/
void dpll_lock_sequence(u32 base_address)
{
	int timer = DPLL_TIMEOUT;
	u32 reg = 0;

	reg = __raw_readl(base_address);

	/* Enable the DPLL lock mode. The bit field is 3 bits long.
	 * So not clearing the bit field before setting it.
	 */
	reg = (reg | 0x7);

	/* Put DPLL into lock mode */
	__raw_writel(reg, base_address);

	/* Wait for DPLL to be locked */
	while (((__raw_readl(base_address + 0x4) & 0x1) != 0x1) && (timer--));

	if (timer <= 0)
		printf("\tERROR: timeout while locking DPLL\n");
}

/******************************************************************************
 * dpll_unlock_sequence() : DPLL unlock sequence
 *****************************************************************************/
void dpll_unlock_sequence(u32 base_address)
{
	u32 reg = 0;

	reg = __raw_readl(base_address);

	/* Take DPLL out of lock mode */
	__raw_writel((reg & (~0x1)), base_address);
}

/* Configuring to 600 MHz DSP with 20 MHz sys_clk.
 * Code based on the DRA7xx_prcm_config.gel
 */
u32 dsp_enable_dpll(void)
{
	static u32 dpll_do_init = 1;
	u32 dpll_m = 150;
	u32 dpll_n = 4;
	u32 divm2 = 1;
	u32 dpll_base_addr = CM_CLKMODE_DPLL_DSP;

	/* return if the DPLL is already configured */
	if (dpll_do_init == 0) {
		debug("DSP DPLL configuration already configured\n");
		return 0;
	}

	/* We are assuming that the DPLL is unlocked and
	   we do not need to unlock it.
	 */

	debug("DSP DPLL configuration in progress\n");

	if (__raw_readl(dpll_base_addr + 0x4) & 0x1) {
		debug("DSP DPLL already locked, now unlocking....\n");
		dpll_unlock_sequence(dpll_base_addr);
	}

	__raw_writel(((dpll_m << 8) | dpll_n), dpll_base_addr + 0x0C);
	__raw_writel(divm2, dpll_base_addr + 0x10);

	/* CM_DIV_M3_DPLL - not used in default configuration */
	/* Output of M3 divider can be routed to EVE if required */
	__raw_writel(0x3, dpll_base_addr + 0x14);

	dpll_lock_sequence(dpll_base_addr);

	debug("DSP DPLL configuration is DONE!\n");
	dpll_do_init = 0;

	return 0;
}

u32 dsp_start_clocks(u32 core_id, struct rproc *cfg)
{
	u32 reg = 0;
	u32 timer_reg = 0;
	u32 dsp_clkstctrl = 0;
	u32 prm_base = 0;
	u32 mmu_config = 0;

	if ((core_id != DSP1) && (core_id != DSP2))
		return 1;

	debug("DSP initialization in progress\n");
	enable_common_clocks();

	/* Configure the DSP PLL */
	dsp_enable_dpll();

	if (core_id == DSP1) {
		/* Enable Timer 5 for DSP1 */
		timer_reg = CM_IPU_TIMER5_CLKCTRL;
		prm_base = DSP1_PRM_BASE;
		dsp_clkstctrl = CM_DSP1_CLKSTCTRL;
		mmu_config = DSP1_SYS_MMU_CONFIG;

		/* TODO: Enable watch dog timers for the 32K timer when they are
		 * defined in the device tree.  */

	} else {
		/* Enable Timer 6 for DSP2 */
		timer_reg = CM_IPU_TIMER6_CLKCTRL;
		prm_base = DSP2_PRM_BASE;
		dsp_clkstctrl = CM_DSP2_CLKSTCTRL;
		mmu_config = DSP2_SYS_MMU_CONFIG;
	}

	/* Using TIMER_SYS_CLK as the clock source */
	reg = __raw_readl(timer_reg);
	__raw_writel((reg & ~0x0F000003) | 0x00000002, timer_reg);
	debug("Enabled SysBIOS Tick Timer\n");

	/* Enable the DSP Clock domain in SW Wkup */
	__raw_writel(0x2, dsp_clkstctrl);

	/* Enable DSP and check that the clock is gated in the clock domain
	   register */
	__raw_writel(0x1, dsp_clkstctrl + 0x20);
	while ((__raw_readl(dsp_clkstctrl) & 0x100) != 0x100);
	debug("DSP Clock enabled and gated in domain controller\n");

	/*
	 * Enable RESET for the DSP MMU, cache and slave interface and
	 * DSP local reset. This may not be necessary since the reset value
	 * is the same.*/
	__raw_writel(0x3, prm_base + 0x10);

	/* Bring the MMU, cache and reset interface out of reset */
	__raw_writel(0x1, prm_base + 0x10);

	/*
	 * Check that the reset state reflects correctly in the status
	 * register.
	 */
	while ((__raw_readl(prm_base + 0x14) & 0x2) != 0x2);
	debug("DSP MMU out of reset\n");

	/* Enable the DSP1 SDMA and MDMA accesses to pass through the MMU */
	__raw_writel(0x11, mmu_config);

	/* At this point, the DSP MMU can be configured. */

	debug("DSP ready for MMU configuration and code loading\n");

	return 0;
}

u32 dsp_start_core(u32 core_id, struct rproc *cfg)
{
	u32 prm_base = 0;
	u32 boot_addr = 0;
	u32 retVal = 1;

	if (core_id == DSP1) {
		prm_base = DSP1_PRM_BASE;
		boot_addr = DSP1_BOOTADDR;
		retVal = 0;
	} else if (core_id == DSP2) {
		prm_base = DSP2_PRM_BASE;
		boot_addr = DSP2_BOOTADDR;
		retVal = 0;
	}

	if (retVal == 0) {

		u32 boot_reg = 0;

		/* Configure the DSP entry point */
		/* DSP boots from CTRL_CORE_CONTROL_DSP1_RST_VECTOR */
		/* Boot address is shifted by 10 bits before begin written */

		boot_reg = __raw_readl(boot_addr);
		boot_reg = (boot_reg & (~DRA7XX_CTRL_CORE_DSP_RST_VECT_MASK));
		boot_reg =
		    (boot_reg |
		     ((cfg->
		       entry_point >> 10) &
		      DRA7XX_CTRL_CORE_DSP_RST_VECT_MASK));

		__raw_writel(boot_reg, boot_addr);

		/* bring the DSP out of reset */
		__raw_writel(0x0, prm_base + 0x10);

		/* check module is functional or not */
		while (((__raw_readl(prm_base + 0x14) & 0x3) != 0x3));

		retVal = 0;
	}

	return retVal;

}

/*
 * If the remotecore binary expects any peripherals to be setup before it has
 * booted, configure them here.
 *
 * These functions are left empty by default as their operation is usecase
 * specific.
 */

u32 ipu1_config_peripherals(u32 core_id, struct rproc *cfg)
{
	return 0;
}

u32 ipu2_config_peripherals(u32 core_id, struct rproc *cfg)
{
	return 0;
}

u32 dsp1_config_peripherals(u32 core_id, struct rproc *cfg)
{
	return 0;
}

u32 dsp2_config_peripherals(u32 core_id, struct rproc *cfg)
{
	return 0;
}

struct rproc ipu1_config = {
	.num_iommus = 1,
	.cma_base = DRA7_RPROC_CMA_BASE_IPU1,
	.cma_size = DRA7_RPROC_CMA_SIZE_IPU1,
	.page_table_addr = 0,
	.mmu_base_addr = {0x58882000, 0},
	.load_addr = IPU_LOAD_ADDR,
	.core_name = "IPU1",
	.firmware_name = "dra7-ipu1-fw.xem4",
#ifdef CONFIG_MMC_IPU1_PART_NAME
	.ptn = CONFIG_MMC_IPU1_PART_NAME,
#else
	.ptn = NULL,
#endif
	.start_clocks = ipu_start_clocks,
	.config_mmu = ipu_config_mmu,
	.config_peripherals = ipu1_config_peripherals,
	.start_core = ipu_start_core
};

struct rproc ipu2_config = {
	.num_iommus = 1,
	.cma_base = DRA7_RPROC_CMA_BASE_IPU2,
	.cma_size = DRA7_RPROC_CMA_SIZE_IPU2,
	.page_table_addr = 0,
	.mmu_base_addr = {0x55082000, 0},
	.load_addr = IPU_LOAD_ADDR,
	.core_name = "IPU2",
	.firmware_name = "dra7-ipu2-fw.xem4",
#ifdef CONFIG_MMC_IPU2_PART_NAME
	.ptn = CONFIG_MMC_IPU2_PART_NAME,
#else
	.ptn = NULL,
#endif
	.start_clocks = ipu_start_clocks,
	.config_mmu = ipu_config_mmu,
	.config_peripherals = ipu2_config_peripherals,
	.start_core = ipu_start_core
};

struct rproc dsp1_config = {
	.num_iommus = 2,
	.cma_base = DRA7_RPROC_CMA_BASE_DSP1,
	.cma_size = DRA7_RPROC_CMA_SIZE_DSP1,
	.page_table_addr = 0,
	.mmu_base_addr = {0x40D01000, 0x40D02000},
	.load_addr = DSP_LOAD_ADDR,
	.core_name = "DSP1",
	.firmware_name = "dra7-dsp1-fw.xe66",
#ifdef CONFIG_MMC_DSP1_PART_NAME
	.ptn = CONFIG_MMC_DSP1_PART_NAME,
#else
	.ptn = NULL,
#endif
	.start_clocks = dsp_start_clocks,
	.config_mmu = ipu_config_mmu,
	.config_peripherals = dsp1_config_peripherals,
	.start_core = dsp_start_core
};

struct rproc dsp2_config = {
	.num_iommus = 2,
	.cma_base = DRA7_RPROC_CMA_BASE_DSP2,
	.cma_size = DRA7_RPROC_CMA_SIZE_DSP2,
	.page_table_addr = 0,
	.mmu_base_addr = {0x41501000, 0x41502000},
	.load_addr = DSP_LOAD_ADDR,
	.core_name = "DSP2",
	.firmware_name = "dra7-dsp2-fw.xe66",
#ifdef CONFIG_MMC_DSP2_PART_NAME
	.ptn = CONFIG_MMC_DSP2_PART_NAME,
#else
	.ptn = NULL,
#endif
	.start_clocks = dsp_start_clocks,
	.config_mmu = ipu_config_mmu,
	.config_peripherals = dsp2_config_peripherals,
	.start_core = dsp_start_core
};

struct rproc *rproc_cfg_arr[RPROC_END_ENUMS] = {
	[IPU2] = &ipu2_config,
	[IPU1] = &ipu1_config,
	[DSP2] = &dsp2_config,
	[DSP1] = &dsp1_config
};

extern int valid_elf_image(unsigned long addr);
extern unsigned long load_elf_image_phdr_rproc(unsigned long addr,
					       unsigned long *entry_point);

u32 spl_boot_core(u32 core_id)
{
	struct rproc *cfg = NULL;
	unsigned long load_elf_status = 0;

	if ((core_id == 0) || (core_id >= RPROC_END_ENUMS)) {
		debug("Invalid core id speicified: %d\n", core_id);
		return 1;
	}

	cfg = rproc_cfg_arr[core_id];

	/* Check for valid elf image */
	if (!valid_elf_image(cfg->load_addr))
		return 1;
	else
		debug("Core %d ELF Image is valid\n", core_id);

	/* Clock the remote core */
	if (cfg->start_clocks)
		cfg->start_clocks(core_id, cfg);

	/* Calculate the page table address */
	cfg->page_table_addr =
	    cfg->cma_base + cfg->cma_size - (PAGE_TABLE_SIZE);

	debug("Configuring IOMMU\n");

	/* Configure the MMU */
	if (cfg->config_mmu)
		cfg->config_mmu(core_id, cfg);

	debug("Configured the IOMMU\n");
	/* Load the remote core.
	 *
	 * Fill the page table of the first(possibly only) IOMMU during ELF
	 * loading.  Copy the page table to the second IOMMU before running the
	 * remote core.
	 */

	page_table_l1 = (unsigned int *)cfg->page_table_addr;
	page_table_l2 =
	    (unsigned int *)(cfg->page_table_addr + PAGE_TABLE_SIZE_L1);
	mem_base = cfg->cma_base;
	mem_size = cfg->cma_size;
	memset(mem_bitmap, 0x00, sizeof(mem_bitmap));
	mem_count = (cfg->cma_size >> PAGE_SHIFT);

	/* Clear variables used for level 2 page table allocation */
	memset(pgtable_l2_map, 0x00, sizeof(pgtable_l2_map));
	pgtable_l2_cnt = 0;

	debug("Loading ELF Image\n");
	load_elf_status =
	    load_elf_image_phdr_rproc(cfg->load_addr, &cfg->entry_point);
	if (load_elf_status == 0) {
		printf("load_elf_image_phdr returned error for core %s\n",
		       cfg->core_name);
		return 1;
	} else {
		debug("Core entry point is 0x%08x\n",
		      (unsigned int)cfg->entry_point);
	}

	if (cfg->config_peripherals)
		cfg->config_peripherals(core_id, cfg);

	/* Start running the remote core */
	debug("Starting the remote core\n");
	if (cfg->start_core)
		cfg->start_core(core_id, cfg);

	return 0;
}

#endif

/**
 * @brief board_init
 *
 * @return 0
 */
int board_init(void)
{
#if defined(CONFIG_SPL_ENV_SUPPORT) && defined(CONFIG_SPL_SPI_PROD_OS_BOOT)
	char serialno[72];
	uint32_t serialno_lo, serialno_hi;

#ifdef CONFIG_ENV_IS_IN_MMC
	struct mmc *mmc;
	spl_mmc_init(&mmc);
#endif

	env_init();
	env_relocate_spec();

	if (!getenv("serial#")) {
		printf("serial# not set, setting...\n");
		serialno_lo = readl((*ctrl)->control_std_fuse_die_id_3);
		serialno_hi = readl((*ctrl)->control_std_fuse_prod_id_0);
		sprintf(serialno, "%08x%08x", serialno_hi, serialno_lo);
		setenv("serial#", serialno);
	}
#endif

	gpmc_init();
	gd->bd->bi_boot_params = (0x80000000 + 0x100); /* boot param addr */

	return 0;
}

#ifdef CONFIG_CMD_FASTBOOT
extern int load_ptbl(void);
#endif

int board_late_init(void)
{
#ifdef CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG
	char serialno[72];
	uint32_t serialno_lo, serialno_hi;

	if (omap_revision() == DRA722_ES1_0)
		setenv("board_name", "dra72x");
	else
		setenv("board_name", "dra7xx");

	if (!getenv("serial#")) {
		printf("serial# not set, setting...\n");
		serialno_lo = readl((*ctrl)->control_std_fuse_die_id_3);
		serialno_hi = readl((*ctrl)->control_std_fuse_prod_id_0);
		sprintf(serialno, "%08x%08x", serialno_hi, serialno_lo);
		setenv("serial#", serialno);
	}
#endif
	init_sata(0);
#ifdef CONFIG_CMD_FASTBOOT
	load_ptbl();
#endif
	return 0;
}

void set_muxconf_regs_essential(void)
{
	do_set_mux32((*ctrl)->control_padconf_core_base,
		     early_padconf, ARRAY_SIZE(early_padconf));
}

#ifdef CONFIG_IODELAY_RECALIBRATION
void recalibrate_iodelay(void)
{
	struct pad_conf_entry const *pads;
	struct iodelay_cfg_entry const *iodelay;
	int npads, niodelays;

	switch (omap_revision()) {
	case DRA722_ES1_0:
		pads = core_padconf_array_essential;
		npads = ARRAY_SIZE(core_padconf_array_essential);
		iodelay = iodelay_cfg_array;
		niodelays = ARRAY_SIZE(iodelay_cfg_array);
		break;
	case DRA752_ES1_0:
	case DRA752_ES1_1:
		pads = dra74x_core_padconf_array;
		npads = ARRAY_SIZE(dra74x_core_padconf_array);
		iodelay = dra742_es1_1_iodelay_cfg_array;
		niodelays = ARRAY_SIZE(dra742_es1_1_iodelay_cfg_array);
		break;
	default:
	case DRA752_ES2_0:
		pads = dra74x_core_padconf_array;
		npads = ARRAY_SIZE(dra74x_core_padconf_array);
		iodelay = dra742_es2_0_iodelay_cfg_array;
		niodelays = ARRAY_SIZE(dra742_es2_0_iodelay_cfg_array);
		/* Setup port1 and port2 for rgmii with 'no-id' mode */
		clrset_spare_register(1, 0, RGMII2_ID_MODE_N_MASK |
				      RGMII1_ID_MODE_N_MASK);
		break;
	}
	__recalibrate_iodelay(pads, npads, iodelay, niodelays);
}
#endif

#if !defined(CONFIG_SPL_BUILD) && defined(CONFIG_GENERIC_MMC)
int board_mmc_init(bd_t *bis)
{
	omap_mmc_init(0, 0, 0, -1, -1);
	omap_mmc_init(1, 0, 0, -1, -1);
	return 0;
}
#endif

#ifdef CONFIG_USB_DWC3
static struct dwc3_device usb_otg_ss1 = {
	.maximum_speed = USB_SPEED_SUPER,
	.base = DRA7_USB_OTG_SS1_BASE,
	.needs_fifo_resize = false,
	.index = 0,
};

static struct dwc3_omap_device usb_otg_ss1_glue = {
	.base = (void *)DRA7_USB_OTG_SS1_GLUE_BASE,
	.utmi_mode = DWC3_OMAP_UTMI_MODE_SW,
	.index = 0,
};

static struct ti_usb_phy_device usb_phy1_device = {
	.pll_ctrl_base = (void *)DRA7_USB3_PHY1_PLL_CTRL,
	.usb2_phy_power = (void *)DRA7_USB2_PHY1_POWER,
	.usb3_phy_power = (void *)DRA7_USB3_PHY1_POWER,
	.index = 0,
};

static struct dwc3_device usb_otg_ss2 = {
	.maximum_speed = USB_SPEED_SUPER,
	.base = DRA7_USB_OTG_SS2_BASE,
	.needs_fifo_resize = false,
	.index = 1,
};

static struct dwc3_omap_device usb_otg_ss2_glue = {
	.base = (void *)DRA7_USB_OTG_SS2_GLUE_BASE,
	.utmi_mode = DWC3_OMAP_UTMI_MODE_SW,
	.index = 1,
};

static struct ti_usb_phy_device usb_phy2_device = {
	.usb2_phy_power = (void *)DRA7_USB2_PHY2_POWER,
	.index = 1,
};

int board_usb_init(int index, enum usb_init_type init)
{
	enable_usb_clocks(index);
	switch (index) {
	case 0:
		if (init == USB_INIT_DEVICE) {
			usb_otg_ss1.dr_mode = USB_DR_MODE_PERIPHERAL;
			usb_otg_ss1_glue.vbus_id_status = OMAP_DWC3_VBUS_VALID;
		} else {
			usb_otg_ss1.dr_mode = USB_DR_MODE_HOST;
			usb_otg_ss1_glue.vbus_id_status = OMAP_DWC3_ID_GROUND;
		}

		ti_usb_phy_uboot_init(&usb_phy1_device);
		dwc3_omap_uboot_init(&usb_otg_ss1_glue);
		dwc3_uboot_init(&usb_otg_ss1);
		break;
	case 1:
		if (init == USB_INIT_DEVICE) {
			usb_otg_ss2.dr_mode = USB_DR_MODE_PERIPHERAL;
			usb_otg_ss2_glue.vbus_id_status = OMAP_DWC3_VBUS_VALID;
		} else {
			usb_otg_ss2.dr_mode = USB_DR_MODE_HOST;
			usb_otg_ss2_glue.vbus_id_status = OMAP_DWC3_ID_GROUND;
		}

		ti_usb_phy_uboot_init(&usb_phy2_device);
		dwc3_omap_uboot_init(&usb_otg_ss2_glue);
		dwc3_uboot_init(&usb_otg_ss2);
		break;
	default:
		printf("Invalid Controller Index\n");
	}

	return 0;
}

int board_usb_cleanup(int index, enum usb_init_type init)
{
	switch (index) {
	case 0:
	case 1:
		ti_usb_phy_uboot_exit(index);
		dwc3_uboot_exit(index);
		dwc3_omap_uboot_exit(index);
		break;
	default:
		printf("Invalid Controller Index\n");
	}
	disable_usb_clocks(index);
	return 0;
}

int usb_gadget_handle_interrupts(int index)
{
	u32 status;

	status = dwc3_omap_uboot_interrupt_status(index);
	if (status)
		dwc3_uboot_handle_interrupt(index);

	return 0;
}
#endif

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_OS_BOOT)
int spl_start_uboot(void)
{
	/* break into full u-boot on 'c' */
	if (serial_tstc() && serial_getc() == 'c')
		return 1;

#ifdef CONFIG_SPL_SPI_PROD_OS_BOOT
	/* boot the os if boot mode is qspi prod */
	if (spl_boot_mode() == SPI_MODE_PROD)
		return 0;
#else
	if ((get_sysboot_value() & SYSBOOT_TYPE_MASK) == SYSBOOT_TYPE_PROD)
		return 0;
#endif

#ifdef CONFIG_SPL_ENV_SUPPORT
#ifdef CONFIG_ENV_IS_IN_MMC
	struct mmc *mmc;
	spl_mmc_init(&mmc);
#endif

	env_init();
	env_relocate_spec();

	/*
	 * Function call returns 1 only if the environment variable is
	 * set to 1,y,Y,t or T. It returns -1 or 0 otherwise.
	 */
	if (getenv_yesno("boot_os") == 1)
		return 0;
#endif

	return 1;
}
#endif

#ifdef CONFIG_DRIVER_TI_CPSW

/* Delay value to add to calibrated value */
#define RGMII0_TXCTL_DLY_VAL		((0x3 << 5) + 0x8)
#define RGMII0_TXD0_DLY_VAL		((0x3 << 5) + 0x8)
#define RGMII0_TXD1_DLY_VAL		((0x3 << 5) + 0x2)
#define RGMII0_TXD2_DLY_VAL		((0x4 << 5) + 0x0)
#define RGMII0_TXD3_DLY_VAL		((0x4 << 5) + 0x0)
#define VIN2A_D13_DLY_VAL		((0x3 << 5) + 0x8)
#define VIN2A_D17_DLY_VAL		((0x3 << 5) + 0x8)
#define VIN2A_D16_DLY_VAL		((0x3 << 5) + 0x2)
#define VIN2A_D15_DLY_VAL		((0x4 << 5) + 0x0)
#define VIN2A_D14_DLY_VAL		((0x4 << 5) + 0x0)

extern u32 *const omap_si_rev;

static void cpsw_control(int enabled)
{
	/* VTP can be added here */

	return;
}

static struct cpsw_slave_data cpsw_slaves[] = {
	{
		.slave_reg_ofs	= 0x208,
		.sliver_reg_ofs	= 0xd80,
		.phy_addr	= 2,
	},
	{
		.slave_reg_ofs	= 0x308,
		.sliver_reg_ofs	= 0xdc0,
		.phy_addr	= 3,
	},
};

static struct cpsw_platform_data cpsw_data = {
	.mdio_base		= CPSW_MDIO_BASE,
	.cpsw_base		= CPSW_BASE,
	.mdio_div		= 0xff,
	.channels		= 8,
	.cpdma_reg_ofs		= 0x800,
	.slaves			= 2,
	.slave_data		= cpsw_slaves,
	.ale_reg_ofs		= 0xd00,
	.ale_entries		= 1024,
	.host_port_reg_ofs	= 0x108,
	.hw_stats_reg_ofs	= 0x900,
	.bd_ram_ofs		= 0x2000,
	.mac_control		= (1 << 5),
	.control		= cpsw_control,
	.host_port_num		= 0,
	.version		= CPSW_CTRL_VERSION_2,
};

int board_eth_init(bd_t *bis)
{
	int ret;
	uint8_t mac_addr[6];
	uint32_t mac_hi, mac_lo;
	uint32_t ctrl_val;

	/* try reading mac address from efuse */
	mac_lo = readl((*ctrl)->control_core_mac_id_0_lo);
	mac_hi = readl((*ctrl)->control_core_mac_id_0_hi);
	mac_addr[0] = (mac_hi & 0xFF0000) >> 16;
	mac_addr[1] = (mac_hi & 0xFF00) >> 8;
	mac_addr[2] = mac_hi & 0xFF;
	mac_addr[3] = (mac_lo & 0xFF0000) >> 16;
	mac_addr[4] = (mac_lo & 0xFF00) >> 8;
	mac_addr[5] = mac_lo & 0xFF;

	if (!getenv("ethaddr")) {
		printf("<ethaddr> not set. Validating first E-fuse MAC\n");

		if (is_valid_ether_addr(mac_addr))
			eth_setenv_enetaddr("ethaddr", mac_addr);
	}

	mac_lo = readl((*ctrl)->control_core_mac_id_1_lo);
	mac_hi = readl((*ctrl)->control_core_mac_id_1_hi);
	mac_addr[0] = (mac_hi & 0xFF0000) >> 16;
	mac_addr[1] = (mac_hi & 0xFF00) >> 8;
	mac_addr[2] = mac_hi & 0xFF;
	mac_addr[3] = (mac_lo & 0xFF0000) >> 16;
	mac_addr[4] = (mac_lo & 0xFF00) >> 8;
	mac_addr[5] = mac_lo & 0xFF;

	if (!getenv("eth1addr")) {
		if (is_valid_ether_addr(mac_addr))
			eth_setenv_enetaddr("eth1addr", mac_addr);
	}

	ctrl_val = readl((*ctrl)->control_core_control_io1) & (~0x33);
	ctrl_val |= 0x22;
	writel(ctrl_val, (*ctrl)->control_core_control_io1);

	if (*omap_si_rev == DRA722_ES1_0) {
		cpsw_data.active_slave = 0;
		cpsw_data.slave_data[0].phy_addr = 3;
		pcf8575_output(PCF_ENET_MUX_ADDR, PCF_SEL_ENET_MUX_S0,
			       PCF8575_OUT_LOW);
	}

	ret = cpsw_register(&cpsw_data);
	if (ret < 0)
		printf("Error %d registering CPSW switch\n", ret);

	return ret;
}
#endif

#ifdef CONFIG_BOARD_EARLY_INIT_F
/* VTT regulator enable */
static inline void vtt_regulator_enable(void)
{
	if (omap_hw_init_context() == OMAP_INIT_CONTEXT_UBOOT_AFTER_SPL)
		return;

	/* Do not enable VTT for DRA722 */
	if (omap_revision() == DRA722_ES1_0)
		return;

	/*
	 * EVM Rev G and later use gpio7_11 for DDR3 termination.
	 * This is safe enough to do on older revs.
	 */
	gpio_request(GPIO_DDR_VTT_EN, "ddr_vtt_en");
	gpio_direction_output(GPIO_DDR_VTT_EN, 1);
}

int board_early_init_f(void)
{
	vtt_regulator_enable();
	return 0;
}
#endif
