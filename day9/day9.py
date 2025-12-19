def part1():
    points = []
    with open('input.txt', 'r') as file:
        for line in file:
            line = line.rstrip()
            x, y = line.split(",")
            points.append([int(x), int(y)])
    
    points.sort()
    
    # Using Andrew's monotone chain convex hull algo
    def cross(o, a, b):
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])
    
    lower_hull = []
    for p in points:
        while len(lower_hull) >= 2 and cross(lower_hull[-2], lower_hull[-1], p) <= 0:
            lower_hull.pop()
        lower_hull.append(p)
    
    upper_hull = []
    for p in reversed(points):
        while len(upper_hull) >= 2 and cross(upper_hull[-2], upper_hull[-1], p) <= 0:
            upper_hull.pop()
        upper_hull.append(p)
    
    points = lower_hull[:-1] + upper_hull[:-1]
    print(points)
    
    largest_area = 0
    for p1 in points:
        for p2 in points:
            area = (abs(p2[0]-p1[0]) + 1) * (abs(p2[1] -p1[1]) + 1)
            if area > largest_area:
                largest_area = area
    
    return largest_area

def part2():
    points = []
    with open('input.txt', 'r') as file:
        for line in file:
            line = line.rstrip()
            x, y = line.split(",")
            points.append((int(x), int(y)))
    
    red_tiles = set(points)
    
    v_segs = []
    h_segs = []
    for i in range(len(points)):
        p1 = points[i]
        p2 = points[(i + 1) % len(points)]
        if p1[0] == p2[0]:
            v_segs.append((p1[0], min(p1[1], p2[1]), max(p1[1], p2[1])))
        else:
            h_segs.append((p1[1], min(p1[0], p2[0]), max(p1[0], p2[0])))
    
    def on_boundary(px, py):
        for (x, y1, y2) in v_segs:
            if px == x and y1 <= py <= y2:
                return True
        for (y, x1, x2) in h_segs:
            if py == y and x1 <= px <= x2:
                return True
        return False
    
    def is_valid(px, py):
        if on_boundary(px, py):
            return True
        crossings = 0
        for (x, y1, y2) in v_segs:
            if x > px and y1 <= py < y2:
                crossings += 1
        return crossings % 2 == 1
    
    all_x = sorted(set(p[0] for p in points))
    all_y = sorted(set(p[1] for p in points))
    
    x_to_idx = {x: i for i, x in enumerate(all_x)}
    y_to_idx = {y: i for i, y in enumerate(all_y)}
    n, m = len(all_x), len(all_y)
    
    valid = [[is_valid(all_x[i], all_y[j]) for j in range(m)] for i in range(n)]
    
    prefix = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            inv = 0 if valid[i-1][j-1] else 1
            prefix[i][j] = inv + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
    
    def count_invalid(i1, j1, i2, j2):
        return prefix[i2+1][j2+1] - prefix[i1][j2+1] - prefix[i2+1][j1] + prefix[i1][j1]
    
    largest_area = 0
    points_list = list(red_tiles)
    
    for i, p1 in enumerate(points_list):
        for p2 in points_list[i+1:]:
            x1, x2 = min(p1[0], p2[0]), max(p1[0], p2[0])
            y1, y2 = min(p1[1], p2[1]), max(p1[1], p2[1])
            
            i1, i2 = x_to_idx[x1], x_to_idx[x2]
            j1, j2 = y_to_idx[y1], y_to_idx[y2]
            
            if count_invalid(i1, j1, i2, j2) == 0:
                area = (x2 - x1 + 1) * (y2 - y1 + 1)
                if area > largest_area:
                    largest_area = area
    
    return largest_area

if __name__ == "__main__":
    print("Largest area in part 1 -> " + str(part1()))
    print("Largest area in part 2 -> " + str(part2()))