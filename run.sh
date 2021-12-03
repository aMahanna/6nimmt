#!/usr/bin/env bash
echo "${PWD}" > temp

# [[ -z "$1" ]] && adb_path="${PWD}" || adb_path=$(echo "$1" | sed 's:/*$::') # Default path to arangodb as pwd
# [[ -z "$2" ]] && ent_dir="enterprise" || ent_dir=$(echo "$2" | sed 's:/*$::') # Default enterprise dir to enterprise

# echo "ArangoDB directory: $adb_path"
# echo "Enterprise directory: $adb_path/$ent_dir"

# cd "$adb_path"
# echo "$adb_path" > temp