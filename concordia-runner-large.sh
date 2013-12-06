#!/bin/sh

echo "Decompressing test file"

bunzip2 --keep prod/resources/text-files/large.txt.bz2

echo "Running Concordia"

rm prod/resources/temp/*
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -r prod/resources/text-files/large.txt
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -g
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "drawn from his own" -n
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "it is" -n

rm prod/resources/text-files/large.txt
