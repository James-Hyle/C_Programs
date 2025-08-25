#!/bin/bash

EXE=endian
TESTDIR=testdata

TESTDATA=$TESTDIR/test.in
EXPECTED=$TESTDIR/test.out

RESULT=myresults.out
DIFFRESULT=myresults.diff

# Clear out any results from last run
cat /dev/null > $RESULT

echo "Executing test using input file $TESTDATA."
echo

# Read each line of the test data and execute program
while IFS=' ' read -r field1 field2
do
    ./$EXE "$field1" >> $RESULT
done < $TESTDATA;

# Compare the results
diff -w $EXPECTED $RESULT > $DIFFRESULT
if [ $? -ne 0 ]; then
   echo "Test failed. Check $DIFFRESULT for differences."
   echo
else
   echo "All tests passed!"
   echo
   rm $DIFFRESULT
fi
