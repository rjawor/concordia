#!/bin/sh

echo "CONCORDIA RUNNER: Running Concordia"

rm prod/resources/temp/*
echo "CONCORDIA RUNNER: reading from file"
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -r prod/resources/text-files/medium.txt
echo "CONCORDIA RUNNER: searching for pattern: \"drawn from his own\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "drawn from his own"
echo "CONCORDIA RUNNER: searching for pattern: \"it is\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "it is" -n
