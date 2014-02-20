#!/bin/sh

echo "CONCORDIA RUNNER: Decompressing test file"

bunzip2 --keep prod/resources/text-files/jrc.txt.bz2

echo "CONCORDIA RUNNER: Running Concordia"

rm prod/resources/temp/*

echo "CONCORDIA RUNNER: reading from file"
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -r prod/resources/text-files/jrc.txt
echo "CONCORDIA RUNNER: searching for pattern: \"Parlamentu Europejskiego\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Parlamentu Europejskiego" -n
echo "CONCORDIA RUNNER: searching for pattern: \"Dostęp do zatrudnienia\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Dostęp do zatrudnienia" -n

rm prod/resources/text-files/jrc.txt
