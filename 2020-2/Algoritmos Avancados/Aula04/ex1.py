import cProfile

from collections import deque


def get_neighbors( state ):
    neighbors = deque()
    state = list(state)
    for index, letter in enumerate(state):
        state[index] = str((int(letter) + 1) % 10)
        neighbors.append( "".join( state ) )
        state[index] = str(((int(letter) + 10) - 1)%10)
        neighbors.append( "".join( state ) )
        state[index] = letter
    return neighbors


def bfs( current, goal, forbiddens ):
    frontier = deque()
    frontier.append((current, 0))
    visited = {}
    solved = False

    while len(frontier) > 0:
        state, steps = frontier.popleft()
        if state == goal:
            print( steps )
            solved = True
            break

        visited[state]=1
        #visited.append(state)

        for neighbor in get_neighbors( state ):
            if neighbor not in visited and neighbor not in forbiddens:
                frontier.append( (neighbor, steps + 1) )

    if not solved:
        print( -1 )


def main( ):
    cases = int(input())

    for _ in range(cases):
        current = "".join(input().split())
        goal = "".join(input().split())

        num_forbidden = int(input())
        forbiddens = []

        for _ in range(num_forbidden):
            forbiddens.append("".join(input().split()))
        input()

        bfs( current, goal, forbiddens )


if __name__ == '__main__':
    cProfile.run('main( )')

# something is in this code that might not be needed that makes it slower on purpose