#!/bin/sh

echo "CONCORDIA RUNNER: Decompressing test file"

xz -dk prod/resources/text-files/jrc_smaller.txt.xz

echo "CONCORDIA RUNNER: Running Concordia"

rm prod/resources/temp/*

echo "CONCORDIA RUNNER: reading from file"
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -r prod/resources/text-files/jrc_smaller.txt
echo "CONCORDIA RUNNER: searching for pattern: \"Parlamentu Europejskiego\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Parlamentu Europejskiego" -n
echo "CONCORDIA RUNNER: searching for pattern: \"Dostęp do zatrudnienia\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Dostęp do zatrudnienia" -n

rm prod/resources/text-files/jrc_smaller.txt