#!/bin/sh

echo "CONCORDIA RUNNER: Decompressing test file"

xz -dk prod/resources/text-files/jrc_smaller.txt.xz

echo "CONCORDIA RUNNER: Running Concordia"

rm prod/resources/temp/*

echo "CONCORDIA RUNNER: reading from file"
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -r prod/resources/text-files/jrc_smaller.txt


echo "CONCORDIA RUNNER: concordia searching for pattern: \"Współpraca Państw Członkowskich i Komisji Europejskiej\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -x "Współpraca Państw Członkowskich i Komisji Europejskiej"
echo "CONCORDIA RUNNER: concordia searching for pattern: \"8. W odniesieniu do artykułu 45 ustęp 12\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -x "8. W odniesieniu do artykułu 45 ustęp 12"

echo "CONCORDIA RUNNER: searching for pattern: \"Parlamentu Europejskiego\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Parlamentu Europejskiego" -n
echo "CONCORDIA RUNNER: searching for pattern: \"Dostęp do zatrudnienia\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Dostęp do zatrudnienia" -n
echo "CONCORDIA RUNNER: searching for pattern: \"Ma on w szczególności prawo do podjęcia zatrudnienia dostępnego na terytorium innego Państwa Członkowskiego z takim samym pierwszeństwem\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Ma on w szczególności prawo do podjęcia zatrudnienia dostępnego na terytorium innego Państwa Członkowskiego z takim samym pierwszeństwem" -n

#rm prod/resources/text-files/jrc_smaller.txt
