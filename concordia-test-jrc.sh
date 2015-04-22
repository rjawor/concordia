#!/bin/sh

echo "CONCORDIA RUNNER: Decompressing test file"

xz -dk prod/resources/text-files/jrc_smaller.txt.xz

echo "CONCORDIA RUNNER: Running Concordia"

rm prod/resources/temp/*

echo "CONCORDIA RUNNER: testing"
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -t prod/resources/text-files/jrc_smaller.txt

#rm prod/resources/text-files/jrc_smaller.txt
