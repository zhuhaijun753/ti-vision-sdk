#!/bin/sh

if [ $# -ne 2 ]; then
   echo "Invalid arguments"
   echo "Please pass the name of the log file and the application to be launched"
   echo "
           Example: start_tracing.sh logfilename application"
   exit
fi

echo "Enabling system wide tracing..."
echo "tracefile is $1"
echo "application is $2"

mkdir pvrtrace
cd pvrtrace

PVRHUB_DIR=/opt/img-powervr-sdk/PVRHub

#Set the trace envrionment
export LD_LIBRARY_PATH=$PVRHUB_DIR/PVRTrace/Recorder/:$LD_LIBRARY_PATH

ln -s libEGL.so $PVRHUB_DIR/PVRTrace/Recorder/libEGL.so.1
ln -s libGLESv2.so $PVRHUB_DIR/PVRTrace/Recorder/libGLESv2.so.2

cp $PVRHUB_DIR/PVRTrace/Recorder/*.json pvrtraceconfig.json

sed -i "s/test\.pvrt/$1\.pvrt/g" pvrtraceconfig.json
echo "
    NOTE: pvrtraceconfig.json can be edited with any text editor."

cat pvrtraceconfig.json
echo "Launching the application $2, press Ctrl-C when you want to stop tracing.."
sleep 2
$2
cd ..
echo "Trace output is stored is under pvrtrace/$1.pvrt"
ls -al pvrtrace/*.pvrt
