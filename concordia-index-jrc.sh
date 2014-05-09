#!/bin/sh

echo "CONCORDIA INDEXER: Decompressing test file"

xz -dk prod/resources/text-files/jrc_smaller.txt.xz

echo "CONCORDIA INDEXER: Running Concordia"

rm prod/resources/temp/*

echo "CONCORDIA INDEXER: reading from file"
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -r prod/resources/text-files/jrc_smaller.txt


