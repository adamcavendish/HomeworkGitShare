fd = open('data241.mat')
for line in fd:
    line = line.rstrip('\n')
    dat = line.split(',')
    print dat
