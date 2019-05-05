#!/bin/sh
#Functions needed by 'UNUSED HEADERS CHECK'
commentHeader() {
    file=$1
    comm=\#include\ $2
	sed -i '' "s|$comm|\/\/$comm|" $file
	# echo commenting $header
}
uncommentHeader() {
    file=$1
	sed -i '' "/#include/s|\/\/||g" $file
	# echo commenting out $header
}

echo "\033[1;31m        :::   :::      :::    :::       ::::::::       :::    :::       :::::::::       ::::::::       ::::::::         :::   :::
     :+:+: :+:+:     :+:    :+:      :+:    :+:      :+:    :+:       :+:    :+:     :+:    :+:     :+:    :+:       :+:+: :+:+:
   +:+ +:+:+ +:+    +:+    +:+      +:+             +:+    +:+       +:+    +:+     +:+    +:+     +:+    +:+      +:+ +:+:+ +:+
  +#+  +:+  +#+    +#+    +:+      +#++:++#++      +#++:++#++       +#++:++#:      +#+    +:+     +#+    +:+      +#+  +:+  +#+
 +#+       +#+    +#+    +#+             +#+      +#+    +#+       +#+    +#+     +#+    +#+     +#+    +#+      +#+       +#+
#+#       #+#    #+#    #+#      #+#    #+#      #+#    #+#       #+#    #+#     #+#    #+#     #+#    #+#      #+#       #+#
###       ###     ########        ########       ###    ###       ###    ###      ########       ########       ###       ###     \033[0m"

echo "          \|||/      " "          \|||/      " "          \|||/      " "          \|||/      "
echo "          (o o)      " "          (o o)      " "          (o o)      " "          (o o)      "
echo "    .~ooO~~(_)~~~~~~." "    .~ooO~~(_)~~~~~~." "    .~ooO~~(_)~~~~~~." "    .~ooO~~(_)~~~~~~."
echo "    |     \033[1;34mLIBFT\033[0m     |" "    |     \033[1;34mFILLIT\033[0m    |" "    |     \033[1;34mFT_LS\033[0m     |" "    |   \033[1;34mMINISHELL\033[0m   |"
echo "    | \033[1;31mCRASHES:    1\033[0m |" "    | \033[1;31mCRASHES:    3\033[0m |" "    | \033[1;31mCRASHES:    1\033[0m |" "    | \033[1;31mCRASHES:    2\033[0m |"
echo "    | \033[1;32mOK:         0\033[0m |" "    | \033[1;32mOK:         0\033[0m |" "    | \033[1;32mOK:         0\033[0m |" "    | \033[1;32mOK:         0\033[0m |"
echo "    '~~~~~~~~~~~ooO~'" "    '~~~~~~~~~~~ooO~'" "    '~~~~~~~~~~~ooO~'" "    '~~~~~~~~~~~ooO~'"
echo "        |___|___|    " "        |___|___|    " "        |___|___|    " "        |___|___|    "
echo "         ||   ||     " "         ||   ||     " "         ||   ||     " "         ||   ||     "
echo "        ooO   Ooo    " "        ooO   Ooo    " "        ooO   Ooo    " "        ooO   Ooo    "

echo -n "\033[0m"

rm -rf checker checker-279

read $arg

if test -e auteur; then echo -n "\033[1;32mAUTHOR FILE: " && cat auteur && echo -n "\n\033[0m"; else echo "\033[1;31m		===> FATAL! AUTHOR FILE NOT FOUND! <===\n \033[0m"; fi;

echo -n "\033[1;32m"
echo "*********************************************************************"
echo "*                            NORM CHECK                             *"
echo "*********************************************************************\033[0m"

echo -n "\033[1;35mNORMINETTE PROCESSING...					"
norminette **/**.[ch] | grep -C 1 "\(Warning\)\|\(Error\)" > NORM_log
if [ -s NORM_log ]
then
	echo "\033[1;31m[FAIL]" && cat NORM_log
else
	echo "\033[1;32m[OK]\033[0m"
fi
echo "\033[1;32m===> DONE <===\033[0m"


read $arg


echo -n "\033[1;32m"
echo "*********************************************************************"
echo "*                        EXTENDED NORM CHECK                        *"
echo "*********************************************************************"
echo -n "\033[0m"

echo -n "\033[1;32m===>	CHECKING VARIABLE-LENGTH ARRAYS...\033[0m			"
grep -Hn "\(signed \|unsigned \|short \|long \)*\(int\|char\|float\|double\|size_t\)\(.\?\)*\\[\(.\?\)*[a-z]\(.\?\)*\\];" **/**.c > VLA_log
if [ -s VLA_log ]
then
	echo "\033[1;31m[FAIL]" && cat VLA_log
else
	echo "\033[1;32m[OK]\033[0m"
fi

echo -n "\033[1;32m===>	CHECKING END-OF-LINE OPERATORS...\033[0m			"
grep -Hn "[^\*/][+%\-\*\?=:&|/]$" **/**.c > OP_log
if [ -s OP_log ]
then
	echo "\033[1;31m[FAIL]" && cat OP_log
else
	echo "\033[1;32m[OK]\033[0m"
fi

echo -n "\033[1;32m===>	CHECKING CODE-OBFUSCATING DEFINES...\033[0m			"
grep -Hn "define\s\+[A-Z0-9_]\+\((\(.\?\)*)\)\?\s\+\(.\?\)*\(\\[\|(\)\(.\?\)*\(\\]\|)\)" **/**.h > DEFINE_log
if [ -s DEFINE_log ]
then
	echo "\033[1;31m[FAIL]" && cat DEFINE_log
else
	echo "\033[1;32m[OK]\033[0m"
fi

echo "\033[1;32m===>	CHECKING MAKEFILE RULES...							"
echo -n "\033[1;35m> RULE 'NAME'...						"
grep "^\$(NAME):" Makefile > RULE_NAME_log
if [ ! -s RULE_NAME_log ]
then
	echo "\033[1;31m[FAIL]\033[0m"
else
	echo "\033[1;32m[OK]\033[0m"
fi
echo -n "\033[1;35m> RULE 'CLEAN'...						"
grep "^clean:" Makefile > RULE_CLEAN_log
if [ ! -s RULE_CLEAN_log ]
then
	echo "\033[1;31m[FAIL]\033[0m"
else
	echo "\033[1;32m[OK]\033[0m"
fi
echo -n "\033[1;35m> RULE 'FCLEAN'...						"
grep "^fclean:" Makefile > RULE_FCLEAN_log
if [ ! -s RULE_FCLEAN_log ]
then
	echo "\033[1;31m[FAIL]\033[0m"
else
	echo "\033[1;32m[OK]\033[0m"
fi
echo -n "\033[1;35m> RULE 'RE'...							"
grep "^re:" Makefile > RULE_RE_log
if [ ! -s RULE_RE_log ]
then
	echo "\033[1;31m[FAIL]\033[0m"
else
	echo "\033[1;32m[OK]\033[0m"
fi

echo -n "\033[1;32m===>	CHECKING WILDCARD IN MAKEFILE...\033[0m			"
tail -n +12 Makefile | grep "\(\*\|wildcard\)" > WILDCARD_log
if [ -s WILDCARD_log ]
then
	echo "\033[1;31m[FAIL]" && cat WILDCARD_log
else
	echo "\033[1;32m[OK]\033[0m"
fi

echo "\033[1;32m===> DONE <===\033[0m"

read $arg

echo -n "\033[1;32m"
echo "*********************************************************************"
echo "*                     CHECKING FOR UNUSED HEADER                    *"
echo "*********************************************************************"
echo -n "\033[0m"

for file in `ls **/**.c`
do
	echo "\033[1;34m===>	SCANNING FILE:	$file\033[0m"
	for header in `grep "^[ \t]*#include" $file | awk '{print $2;}'`
	do
		#echo Matched header $header
		touch $file # update file's modification date to trigger MAKEFILE'S RECOMPILATION
		commentHeader $file $header
		make 1>/dev/null 2> MAKE_log
		if [ -s MAKE_log ]
		then
			echo "\033[1;32m> Header needed: $header\033[0m"
		else
			echo "\033[1;31m> ERROR! UNUSED HEADER: $header\033[0m"
		fi
		uncommentHeader $file $header
	done
done

read $arg

echo -n "\033[1;32m"
echo "*********************************************************************"
echo "*                DOWNLOADING CLANG STATIC ANALYZER                  *"
echo "*********************************************************************"
echo "\033[0m"

curl -o checker https://clang-analyzer.llvm.org/downloads/checker-279.tar.bz2

echo -n "\033[1;32m"
echo "*********************************************************************"
echo "*                EXCTRACTING CLANG STATIC ANALYZER                  *"
echo "*********************************************************************"
echo "\033[0m"

tar -xf checker

echo -n "\033[1;32m"
echo "*********************************************************************"
echo "*                       SCANNING SOURCE CODE                        *"
echo "*********************************************************************"
echo "\033[0m"

./checker-279/bin/scan-build make re

echo "==========>		CLEANING		<=========="
rm -f NORM_log
rm -f OP_log
rm -f DEFINE_log
rm -f RULE_NAME_log
rm -f RULE_CLEAN_log
rm -f RULE_FCLEAN_log
rm -f RULE_RE_log
rm -f WILDCARD_log
rm -f HEADERS_log
rm -f checker
