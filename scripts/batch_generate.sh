#/usr/bin/env bash
# generate jobs in batch

depths=(5) # The name of the input files
workers=(16)
rm -f *.job


for depth in ${depths[@]}
do
    for work in ${workers[@]}
    do
        ../scripts/generate_jobs.sh $depth $work
    done
done
