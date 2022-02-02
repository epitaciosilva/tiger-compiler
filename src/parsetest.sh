for file in ../testcases/*.tig
do
    echo "$file: "
    ./parse $file 2>&1
done
