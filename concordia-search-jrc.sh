#!/bin/sh

echo "CONCORDIA SEARCHER: searching for pattern: \"Parlamentu Europejskiego\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Parlamentu Europejskiego" -n
echo "CONCORDIA SEARCHER: searching for pattern: \"Dostęp do zatrudnienia\""
./build/concordia-console/concordia-console -c prod/resources/concordia-config/concordia.cfg -s "Dostęp do zatrudnienia" -n

