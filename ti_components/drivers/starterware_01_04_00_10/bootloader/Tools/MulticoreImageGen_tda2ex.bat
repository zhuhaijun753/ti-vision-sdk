REM @echo off
REM Define Device Id J6 ECO - 66 - choosen random value will be updated
REM Device ID & CPU ID should be in sync with SBL. Refer SBL user guide for values
set Dev_ID=66
set MPU_CPU0_ID=0
set IPU1_CPU0_ID=2
set IPU1_CPU1_ID=3
set IPU1_CPU_SMP_ID=4
set DSP1_ID=8

REM Define Output file path
set Out_Path=C:\ti\starterware\binary\sbl_multicore_app\

IF NOT EXIST %Out_Path%\ mkdir %Out_Path%

REM Define Input file paths; To skip the core leave it blank
set App_MPU_CPU0=C:\ti\starterware\binary\sbl_multicore_mbx\bin\tda2ex\sbl_multicore_mbx_a15host_release.xa15fg
set App_IPU1_CPU0=C:\ti\starterware\binary\sbl_multicore_mbx\bin\tda2ex\sbl_multicore_mbx_m4_release.xem4
set App_IPU1_CPU1=C:\ti\starterware\binary\sbl_multicore_mbx_1\bin\tda2ex\sbl_multicore_mbx_1_m4_release.xem4
REM App_IPU1_CPU_SMP is to define the IPU SMP application
set App_IPU1_CPU_SMP=
set App_DSP1=C:\ti\starterware\binary\sbl_multicore_mbx\bin\tda2ex\sbl_multicore_mbx_c66x_release.xe66

if defined App_MPU_CPU0 (
set MPU_CPU0=%MPU_CPU0_ID%
set image_gen=1
set App_MPU_CPU0_RPRC=%App_MPU_CPU0%.rprc )
if defined App_MPU_CPU0 (
"out2rprc\out2rprc.exe" %App_MPU_CPU0% %App_MPU_CPU0_RPRC% )

if defined App_IPU1_CPU0 (
set IPU1_CPU0=%IPU1_CPU0_ID%
set image_gen=1
set App_IPU1_CPU0_RPRC=%App_IPU1_CPU0%.rprc )
if defined App_IPU1_CPU0 (
"out2rprc\out2rprc.exe" %App_IPU1_CPU0% %App_IPU1_CPU0_RPRC% )

if defined App_IPU1_CPU1 (
set IPU1_CPU1=%IPU1_CPU1_ID%
set image_gen=1
set App_IPU1_CPU1_RPRC=%App_IPU1_CPU1%.rprc )
if defined App_IPU1_CPU1 (
"out2rprc\out2rprc.exe" %App_IPU1_CPU1% %App_IPU1_CPU1_RPRC% )

if defined App_IPU1_CPU_SMP (
set IPU1_CPU_SMP=%IPU1_CPU_SMP_ID%
set image_gen=1
set App_IPU1_CPU_SMP_RPRC=%App_IPU1_CPU_SMP%.rprc )
if defined App_IPU1_CPU_SMP (
"out2rprc\out2rprc.exe" %App_IPU1_CPU_SMP% %App_IPU1_CPU_SMP_RPRC% )

if defined App_DSP1 (
set DSP1_CPU=%DSP1_ID%
set image_gen=1
set App_DSP1_RPRC=%App_DSP1%.rprc )
if defined App_DSP1 (
"out2rprc\out2rprc.exe" %App_DSP1% %App_DSP1_RPRC% )

REM ImageGen
if defined image_gen (

REM Gerating MulticoreImage Gen
"multicore_image_generator\MulticoreImageGen.exe" LE %Dev_ID% %Out_Path%\AppImage_LE %MPU_CPU0% %App_MPU_CPU0_RPRC% %IPU1_CPU0% %App_IPU1_CPU0_RPRC% %IPU1_CPU1% %App_IPU1_CPU1_RPRC% %IPU1_CPU_SMP% %IPU1_CPU_SMP_RPRC% %DSP1_CPU% %App_DSP1_RPRC%

"multicore_image_generator\MulticoreImageGen.exe" BE %Dev_ID% %Out_Path%\AppImage_BE %MPU_CPU0% %App_MPU_CPU0_RPRC% %IPU1_CPU0% %App_IPU1_CPU0_RPRC% %IPU1_CPU1% %App_IPU1_CPU1_RPRC% %IPU1_CPU_SMP% %IPU1_CPU_SMP_RPRC% %DSP1_CPU% %App_DSP1_RPRC%
)
pause