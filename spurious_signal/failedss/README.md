# Spurious Signal

This project contains three programs used to identify the systematic uncertainty of signal otherwise known as spurious signal. 

## Getting Started!

Now I am updating this tutorial to compile the machine learning and normalizing flow study.

## Step 0: Setting up the ROOT environment

source /global/project/projectdirs/atlas/scripts/setupATLAS.sh

setupATLAS -c centos7+batch

## Step 1: Clone The Spurious-Signal Repository In Your Terminal
### Click the clone button and selecton "clone with SSH". Copy this then do this command:

git clone (**repo link**)

## Step 2: Setting up build

cd spurious-signal/cmake_example

mkdir build run

cd build

asetup AnalysisBase,21.2.165

cmake ../source

make

## Step 3: Running the code
cd ../source/Spurious_Signal/scripts/

source run_ML.sh

source run_MC.sh

source run_truth.sh

### it will take some time to run so sit tight. Every two mintes type "ls" into your terminal to see if everything has finsished running. There are 21 things being processed in total.
### once this is done, produce the plots
### We will no longer be using plotMax.C because I have moved all plotting needing in plotAll.C.

rm log* err* 

root -l plotAll.C
