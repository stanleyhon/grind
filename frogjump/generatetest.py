import random

random.seed()

increment = 1
value = 1

count = 0

print 0
print 1

while count < 1000:
    step = random.randrange(-1,2)
    
    tStep = step + increment
    if tStep < 1:
        tStep = 1;
    
    print value + tStep
    value = value + tStep;
    increment = tStep; 

    count = count + 1
    

