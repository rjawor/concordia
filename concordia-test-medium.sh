#!/bin/sh

echo "CONCORDIA RUNNER: Running Concordia"

rm prod/resources/temp/*

echo "CONCORDIA RUNNER: testing"
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -t prod/resources/text-files/medium.txt

