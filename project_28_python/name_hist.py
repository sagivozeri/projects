str_name = ["sagiv", "shiran", "shani", "eitan", "snir", "sean"]

import random
in_file  = open("input_file.txt", "w")

for i in range(1000000):
    x = random.choice(str_name)
    in_file.write(x+"\n")

in_file.close()

hist={}
for name in str_name:
    hist[name] = 0

out_file = open("input_file.txt", "r")
lines = out_file.readlines()

for line in lines:
    line = line.strip()
    hist[line] += 1

print(hist)

out_file.close()
