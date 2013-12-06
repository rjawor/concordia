#!/bin/sh

echo "Running Concordia"

rm prod/resources/temp/*
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -r prod/resources/text-files/medium.txt
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -g
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -l
#./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Ala ma chyba kota"

