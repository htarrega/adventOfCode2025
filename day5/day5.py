def binary_search_range(ranges, num):
    left, right = 0, len(ranges) - 1
    result = -1
    
    while left <= right:
        mid = (left + right) // 2
        if ranges[mid][0] <= num:
            result = mid
            left = mid + 1
        else:
            right = mid - 1
    
    if result != -1:
        for i in range(result, -1, -1):
            if num >= ranges[i][0] and num <= ranges[i][1]:
                return True
    
    return False

def part1():
    with open('input.txt', 'r') as file:
        fresh = 0
        gettingRanges = True
        ranges = []
        numbers = []
        
        for line in file:
            line = line.rstrip()
            if len(line) == 0:
                gettingRanges = False
                continue
            if gettingRanges:
                divided = line.split("-")
                init = int(divided[0])
                end = int(divided[1])
                ranges.append([init, end])
            else:
                numbers.append(int(line))
        
        ranges.sort(key=lambda x: x[0])
        
        for num in numbers:
            if binary_search_range(ranges, num):
                fresh += 1
        
        print("Part1->Total fresh aliments are " + str(fresh))

def merge_ranges(ranges):
    if not ranges:
        return []
    sorted_ranges = sorted(ranges, key=lambda x: x[0])
    merged = [sorted_ranges[0]]
    for current in sorted_ranges[1:]:
        last = merged[-1]
        if current[0] <= last[1] + 1:
            merged[-1] = [last[0], max(last[1], current[1])]
        else:
            merged.append(current)
    return merged

def count_numbers_in_ranges(ranges):
    merged = merge_ranges(ranges)
    total = sum(end - start + 1 for start, end in merged)
    return total

def part2():
    ranges = []
    with open('input.txt', 'r') as file:
        for line in file:
            line = line.rstrip()
            if len(line) == 0:
                break
            if "-" in line:
                divided = line.split("-")
                if len(divided) == 2:
                    init = int(divided[0])
                    end = int(divided[1])
                    ranges.append([init, end])
    total = count_numbers_in_ranges(ranges)
    print(f"Part2 -> Total fresh aliments are {total}")
    return total

if __name__ == "__main__":
    part1()
    part2()