import os
import sys
import time

if len(sys.argv) != 5:
    print 'Usage python {} <java program> <input files dir> <output files dir> <time limit>'
    sys.exit(1)

java_program = sys.argv[1]
input_dir = sys.argv[2]
output_dir = sys.argv[3]
time_limit = float(sys.argv[4])

input_files = os.listdir(input_dir)
output_files = os.listdir(output_dir)
input_files.sort()
output_files.sort()

if len(input_files) != len(output_files):
    print 'input files do not match output files'

for i, o in zip(input_files, output_files):
    print 'Comparing output java {} < {} with {}'.format(java_program, i, o)
    t0 = time.time() 
    os.system('java {} < {} > out.txt'.format(java_program, input_dir + '/' + i))
    t1 = time.time()

    if t1 - t0 > time_limit:
        print 'TIME LIMIT EXCEEDED'
        sys.exit(1)

    if os.system('diff {} {}'.format('out.txt', output_dir + '/' + o)):
        print 'WRONG ANSWER'
        sys.exit(1)

print 'CORRECT ANSWER'

