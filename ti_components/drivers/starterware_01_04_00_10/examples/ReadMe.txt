
SBL multicore mailbox app:

It is multicore sample application, uses mailbox ip for interprocessor communiction. It is to validate the multi-core boot-up use case. MPU application send  wake-up message to all the slave cores & wait for ack message for all the slave cores in a infinite loop.
Each slave core wait for wake-up message from the master core & respond back with ack message


Memory layout structure
-------------------------------------

MEMORY
{
	/*CODE SECTION - 20MB*/
	/*DATA SECTION - 10MB*/
	/*STACK - 5MB*/
	/*HEAP - 5MB*/	
	DDR3_MPU_CPU0_CODE : org = 0x90000000,len = 0x01400000
	DDR3_MPU_CPU0_DATA :  org = 0x91400000, len = 0x00A00000
	DDR3_MPU_CPU0_STACK : org = 0x91E00000, len = 0x00500000
	DDR3_MPU_CPU0_HEAP :  org = 0x92300000, len = 0x00500000
	
	DDR3_IPU1_CPU0_CODE : org = 0x93200000,len = 0x01400000
	DDR3_IPU1_CPU0_DATA :  org = 0x94600000, len = 0x00A00000
	DDR3_IPU1_CPU0_STACK : org = 0x95000000, len = 0x00500000
	DDR3_IPU1_CPU0_HEAP :  org = 0x95500000, len = 0x00500000
	
	DDR3_IPU1_CPU1_CODE : org = 0x96400000,len = 0x01400000
	DDR3_IPU1_CPU1_DATA :  org = 0x97800000,len = 0x00A00000
	DDR3_IPU1_CPU1_STACK : org = 0x98200000,len = 0x00500000
	DDR3_IPU1_CPU1_HEAP :  org = 0x98700000,len = 0x00500000
	
	DDR3_IPU2_CPU0_CODE : org = 0x99600000,len = 0x01400000
	DDR3_IPU2_CPU0_DATA :  org = 0x9AA00000,len = 0x00A00000
	DDR3_IPU2_CPU0_STACK : org = 0x9B400000,len = 0x00500000
	DDR3_IPU2_CPU0_HEAP :  org = 0x9B900000,len = 0x00500000
	
	DDR3_IPU2_CPU1_CODE : org = 0x9C800000,len = 0x01400000
	DDR3_IPU2_CPU1_DATA :  org = 0x9DC00000,len = 0x00A00000
	DDR3_IPU2_CPU1_STACK : org = 0x9E600000,len = 0x00500000
	DDR3_IPU2_CPU1_HEAP :  org = 0x9EB00000,len = 0x00500000
	
	DDR3_DSP1_CODE : org = 0x83200000,len = 0x01400000
	DDR3_DSP1_DATA : org = 0x84600000, len = 0x00A00000
	DDR3_DSP1_STACK :org = 0x85000000, len = 0x00500000
	DDR3_DSP1_HEAP : org = 0x85500000, len = 0x00500000
	
	DDR3_DSP2_CODE : org = 0x86400000,len = 0x01400000
	DDR3_DSP2_DATA :  org = 0x87800000,len = 0x00A00000
	DDR3_DSP2_STACK : org = 0x88200000,len = 0x00500000
	DDR3_DSP2_HEAP :  org = 0x88700000,len = 0x00500000
	
	DDR3_EVE1_CODE : org = 0x89600000,len = 0x01400000
	DDR3_EVE1_DATA :  org = 0x8AA00000,len = 0x00A00000
	DDR3_EVE1_STACK : org = 0x8B400000,len = 0x00500000
	DDR3_EVE1_HEAP :  org = 0x8B900000,len = 0x00500000
	
	DDR3_EVE2_CODE : org = 0x8C800000,len = 0x01400000
	DDR3_EVE2_DATA :  org = 0x8DC00000,len = 0x00A00000
	DDR3_EVE2_STACK : org = 0x8E600000,len = 0x00500000
	DDR3_EVE2_HEAP :  org = 0x8EB00000,len = 0x00500000
}

====================================================
Application names to build the apps for all the cores

sbl_multicore_app: sbl_multicore_mbx  sbl_multicore_mbx_1  sbl_multicore_mbx_2  sbl_multicore_mbx_3

sbl_multicore_mbx
MPU_CPU0
DSP1
IPU1_CPU0

sbl_multicore_mbx_1
DSP2
IPU1_CPU1

sbl_multicore_mbx_2
IPU2_CPU0

sbl_multicore_mbx_3
IPU2_CPU2


Generating the multicore app image file - AppImage file
-------------------------------------------------------------------------------------

Run the MulticoreImageGen.bat file
