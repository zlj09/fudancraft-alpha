#! /bin/bash

src_list=`ls *.cpp *.h PathFinder/*.cpp PathFinder/*.h`
line_sum=0
for file in $src_list
do
	line_num=`awk '
		BEGIN { num = 0;}
		{num = num + 1}
		END {print num}' $file`
	printf "%s\t\t\t%s\n" $file $line_num
	line_sum=`echo "$line_sum + $line_num" | bc`
done
echo $line_sum
