import sys
import random

filename = ''
defualt_count = 1000
count = defualt_count

if len(sys.argv) > 1:
    filename = sys.argv[1] + '.txt'
    if len(sys.argv) == 3:
        try:
            count = int(sys.argv[2])
        except:
            sys.stderr.write("Invalid Parameter!\n")
else:
    sys.stderr.write("File Name Required!\n")
    exit()

f = open(filename,"w+")

def findSign(num):
    if num >= 0:
        return '+'
    else:
        return '-'

def magnitude(num):
    if num >= 0:
        if num == 1:
            return ''
        else:
            return str(num)
    else:
        r_num = num * -1
        if r_num == 1:
            return ''
        else:
            return str(r_num)

for c in range(count):

    x = random.randint(1,random.randint(1,100))
    y = random.randint(1,random.randint(1,100))

    cx1 = random.randint(1,random.randint(1,50))
    cy1 = random.randint(random.randint(-25,-1),random.randint(1,25))
    if cy1 == 0:
        cy1 += random.randint(1,random.randint(1,50))

    ans1 = cx1 * x + cy1 * y

    cx2 = random.randint(1,random.randint(1,50))
    cy2 = random.randint(random.randint(-25,-1),random.randint(1,25))
    if cy2 == 0:
        cy2 += random.randint(1,random.randint(1,50))

    ans2 = cx2 * x + cy2 * y

    first_eq = magnitude(cx1) + 'x' + ' ' + findSign(cy1) + ' ' +  magnitude(cy1) + 'y' + ' = ' + str(ans1) + '\n'
    second_eq = magnitude(cx2) + 'x' + ' ' + findSign(cy2) + ' ' +  magnitude(cy2) + 'y' + ' = ' + str(ans2) + '\n'
    f.write('('+str(c + 1) + ').\n' + first_eq + second_eq + '\n')

f.close()
