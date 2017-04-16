import os
from subprocess import Popen, PIPE

p = Popen('C:/Users/David/Documents/Club/Reference/a.out', stdin=PIPE) #NOTE: no shell=True here
p.communicate(os.linesep.join(["abab", "abab"]))