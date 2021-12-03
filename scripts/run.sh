#!/usr/bin/env bash
[[ -z "$1" ]] && adb_path="${PWD}" || adb_path=$(echo "$1" | sed 's:/*$::') # Default path to arangodb as pwd
[[ -z "$2" ]] && ent_dir="enterprise" || ent_dir=$(echo "$2" | sed 's:/*$::') # Default enterprise dir to enterprise

echo "ArangoDB directory: $adb_path"
echo "Enterprise directory: $adb_path/$ent_dir"

# cd "$adb_path"
community_diff=$(git diff --cached --diff-filter=ACMR --name-only -- '*.cpp' '*.hpp' '*.cc' '*.c' '*.h')

if [ -d "$adb_path/$ent_dir" ] # assume enterprise directory is within arangodb directory
then
   cd "$adb_path/$ent_dir"
   enterprise_diff=$(git diff --cached --diff-filter=ACMR --name-only -- '*.cpp' '*.hpp' '*.cc' '*.c' '*.h' | sed "s,^,$ent_dir/,")
fi

echo $community_diff
echo $enterprise_diff

diff="$community_diff $enterprise_diff"
echo $diff
if [[ -z "${diff// }" ]]; then
    echo "nothing to format"
else
    echo "docker run -it --rm -v "$adb_path":/usr/src/arangodb clang-format:latest $diff"
    docker run -it --rm -v "$adb_path":/usr/src/arangodb clang-format:latest "$diff"
fi