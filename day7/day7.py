from collections import deque

def part1():
    with open('input.txt', 'r') as file:
        beams = set()
        splits = 0 
        firstLine = True
        
        for line in file:
            line = line.rstrip()
            if firstLine:
                for i in range(0,len(line)):
                    if line[i] == "S":
                        beams.add(i)
                firstLine = False
            else:
                for i in range(0,len(line)):
                    if line[i] == "^" and i in beams:
                        beams.remove(i)
                        beams.add(i+1)
                        beams.add(i-1)
                        splits +=1

    return splits

def part2():
    with open('input.txt', 'r') as file:
        beams = set()
        currentLine = 0
        startingPos = 0
        lastLine = 0
        for line in file:
            line = line.rstrip()
            for i in range(0,len(line)):
                if line[i] == "S":
                    startingPos = i
                if line[i] == "^":
                    beams.add((currentLine,i))
            currentLine+= 1
        lastLine = currentLine-1
        
        particles = {(0, startingPos): 1}
        timeline_count = 0
        
        while particles:
            new_particles = {}
            for (x, y), count in particles.items():
                x += 1
                if x > lastLine:
                    timeline_count += count
                elif (x, y) in beams:
                    new_particles[(x, y-1)] = new_particles.get((x, y-1), 0) + count
                    new_particles[(x, y+1)] = new_particles.get((x, y+1), 0) + count
                else:
                    new_particles[(x, y)] = new_particles.get((x, y), 0) + count
            particles = new_particles
        
        return timeline_count

if __name__ == "__main__":
    print("Total splitted beams in part 1 -> "+str(part1()))
    print("Total quantum beams in part 2 -> "+str(part2()))