#!/bin/sh

echo "CONCORDIA RUNNER: Decompressing test file"

bunzip2 --keep prod/resources/text-files/large.txt.bz2

echo "CONCORDIA RUNNER: Running Concordia"

rm prod/resources/temp/*

echo "CONCORDIA RUNNER: reading from file"
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -r prod/resources/text-files/large.txt
echo "CONCORDIA RUNNER: searching for pattern: \"drawn from his own\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "drawn from his own" -n
echo "CONCORDIA RUNNER: searching for pattern: \"it is\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "it is" -n

rm prod/resources/text-files/large.txt
