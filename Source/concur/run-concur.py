#!/usr/bin/python
import os
import sys
from optparse import OptionParser


parser = OptionParser("\n%prog [options] -R -t -r")
parser.add_option("-R", "--runs", dest = "num_test_runs", type = "int", help = "number of test runs")
parser.add_option("-t", "--threads", dest = "num_threads", type = "int", help = "number of threads")
parser.add_option("-r", "--rounds", dest = "num_rounds", type = "int", help = "number of rounds")

(opts, args) = parser.parse_args()

# Set local variables
numRuns = opts.num_test_runs
if (numRuns < 1) :
        parser.error("Number of test runs must be greater than 0.  Found:  " + str(numRuns))

numThreads = str(opts.num_threads)
if (opts.num_threads < 1) :
	parser.error("Number of threads must be greater than 0.  Found:  " + numThreads)

numRounds = str(opts.num_rounds)
if (opts.num_rounds < 1) :
        parser.error("Number of rounds must be greater than 0.  Found:  " + numRounds)

#print "numTestRuns=" + str(numRuns) + ", numThreads=" + numThreads + ", numRounds=" + numRounds


# Build command line
cmdLine = "./concur.synch.exe " + numThreads + " " + numRounds + " RANDOM OFF"
print cmdLine

# Run tests for numRounds iterations
for i in xrange(1, numRuns+1) :
	print "Run " + str(i) + ":" 
	if os.system(cmdLine):
		print "----Test FAILED at round " + str(i) + ".\n"
		sys.exit(-1)
else :
	print "----All tests PASSED\n"


# Successful exit
sys.exit(0)

