def part1():
    result = 0
    current_position = 50
    with open('input.txt','r') as file:
        for line in file:
            direction = line[0]
            number = int(line[1:])
            if direction == 'L':
                provisional = -number+current_position
            else:
                provisional = number+current_position
            provisional = provisional %100
            current_position = provisional
            if current_position == 0:
                result += 1
 
    print("Total times the dial points to 0 is " + str(result))
 
def part2():
    result = 0
    current_position = 50
    with open('input.txt','r') as file:
        for line in file:
            direction = line[0]
            number = int(line[1:])
            
            if direction == 'L':
                result += (current_position - 1) // 100 - (current_position - number - 1) // 100
                provisional = -number + current_position
            else:
                result += (current_position + number) // 100 - current_position // 100
                provisional = number + current_position
            provisional = provisional % 100
            current_position = provisional
    
    print("Total times the dial traverses 0 is " + str(result))

if __name__ == "__main__":
    part1()
    part2()
