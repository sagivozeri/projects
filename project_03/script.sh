#!/bin/bash

sc=summary_current.csv
art=aggreport_today.csv
arl=aggreport_last.csv

if [ ! -z "$art" ]; then
	rm -f $art
fi

function get_field () {
	echo "$1" | cut -d "," -f$2
}


cat $arl | while read line;
do
	test_name=`get_field $line 1`
	curr_res=`get_field $line 2`
	prev_res=`get_field $line 3`
	days=`get_field $line 4`
	rest=`get_field $line 6-`
	new_res=`get_field $( grep $test_name $sc ) 2`
	days_new=""
	rest_new=""

	if [ "$curr_res" == "$new_res" ]; then
		days_new=$((days+1))
		rest_new=$rest
	else
		days_new=1

		if [ "$new_res" == "PASSED" ]; then
			rest_new="F${days},$rest"
		else
			rest_new="P${days},$rest"
		fi
	fi

	echo "$test_name,$new_res,$curr_res,$days_new,,$rest_new" >> $art
done
