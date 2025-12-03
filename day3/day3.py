def part1():
    with open('input.txt','r') as file:
        total = 0
        for line in file:
            line = line.rstrip()
            leftHighestPos = 0
            leftHighestVal = 0
            rightHighestVal = 0
            for i in range(0,len(line)-1):
                if(int(line[i]) > leftHighestVal):
                    leftHighestPos = i
                    leftHighestVal = int(line[i])
            for i in range(leftHighestPos+
                           1,len(line)):
                if(int(line[i]) > rightHighestVal):
                    rightHighestVal = int(line[i])
            total= total + 10*leftHighestVal+rightHighestVal   

 
    print("Total joltage is " + str(total))
 
def part2():
    with open('input.txt','r') as file:
        total = 0
        for line in file:
            line = line.rstrip()
            startingPos = 0
            lastPos = len(line)
            bestPos = 0
            num = ""
            for i in range(12,0,-1):
                lastPos = len(line) - i
                highestNum = 0
                for j in range(startingPos+bestPos,lastPos+1):
                    if int(line[j]) > highestNum:
                        bestPos = j+1
                        highestNum = int(line[j])
                num+= str(highestNum)
            total +=int(num)
            num = ""

 
    print("Total joltage is " + str(total))
 

if __name__ == "__main__":
    part1()
    part2()
