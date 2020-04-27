#person1mt = [['09:30','10:30'],['11:00','12:30'],['14:30','15:00'],['15:00','16:30']]
#this is the times person 1 has meetings. It's a list of lists of person's meeting begin time and end time
#syntax [[meeting 1 begin time,meeting 1 end time],[meeting 2 begin time,meeting 2 end time],[meeting 3 begin time,meeting 3 end time],.....]
#person1do = ['08:00','18:00'] this means this person don't get meetings befor 08:00 and after 18:00
#person2 variables are the same as person1's
#meetingd is the meeting duration


def convertTimeStringListToIntegers(mtlist):
    nlist = []
    for a in mtlist:
        mlist = []
        for b in a:
            c = b.split(':')
            mlist.append(int(c[0]) * 60 + int(c[1]))
        nlist.append(mlist)
    return nlist
    
def convertTimeStringToIntegers(alist):
    nlist = []
    for a in alist:
        b = a.split(':')
        nlist.append(int(b[0]) * 60 + int(b[1]))
    return nlist

def convertStringToInt(sttring):
    a = sttring.split(':')
    return int(a[0]) * 60 + int(a[1])

def findFreeTime(pmt,pdo):
    mt = pmt
    mt.insert(0,[0,pdo[0]])
    mt.append([pdo[1],0])

    nlist = []

    for i in range(len(mt) - 1):
        if mt[i+1][0] > mt[i][1]:
            nlist.append([mt[i][1],mt[i+1][0]])

    return nlist

def decodeIntTime(alist):
    nlist = []

    for a in alist:
        mlist = []
        for b in a:
            c = str(b//60)
            d = str(b%60)

            if len(c)==1:
                c = '0' + c
            if len(d) == 1:
                d = '0' +d
                
            e = c + ":" + d
            
            mlist.append(e)
        nlist.append(mlist)

    return nlist

def findBothFreeTime(person1mt,person1do,person2mt,person2do,meetingd):
    p1mt = convertTimeStringListToIntegers(person1mt)
    print(p1mt)
    p1do = convertTimeStringToIntegers(person1do)
    print(p1do)
    p2mt = convertTimeStringListToIntegers(person2mt)
    print(p2mt)
    p2do = convertTimeStringToIntegers(person2do)
    print(p2do)
    md = convertStringToInt(meetingd)
    print(md)

    p1ft = findFreeTime(p1mt,p1do)
    print(p1ft)
    p2ft = findFreeTime(p2mt,p2do)
    print(p2ft)

    freeTime = []
    
    for a in p1ft:
        for b in p2ft:
            greaterStartTime = max(a[0],b[0])
            lowerEndTime = min(a[1],b[1])

            if greaterStartTime + md <= lowerEndTime:
                freeTime.append([greaterStartTime,lowerEndTime])

    freeTime = decodeIntTime(freeTime)
    print(freeTime)        
    return freeTime
