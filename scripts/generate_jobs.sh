#/usr/bin/env bash

# generate the job for latedays
depth=$1
workers=$2

if [ ${#} -ne 2 ]; then
  echo "Usage: $0 <depth> <cilk workers>"
else
  curdir=`pwd`
  curdir=${curdir%/templates}
  sed "s:PROGDIR:${curdir}:g" ../scripts/example.job.template > tmp1.job
  sed "s:DEPTH:${depth}:g" tmp1.job > tmp2.job
  sed "s:WORKERS:${workers}:g" tmp2.job > ${USER}_${depth}_${workers}.job
  rm -f tmp1.job tmp2.job
fi
