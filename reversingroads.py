'''
Problem: https://open.kattis.com/problems/reversingroads
Runtime: 0.15s
'''
from fileinput import input
from copy import deepcopy

def strongly_connected_components(graph):
    """
    Tarjan's Algorithm (named for its discoverer, Robert Tarjan) is a graph theory algorithm
    for finding the strongly connected components of a graph.

    Based on: http://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
    """

    index_counter = [0]
    stack = []
    lowlinks = {}
    index = {}
    result = []

    def strongconnect(node):
        # set the depth index for this node to the smallest unused index
        index[node] = index_counter[0]
        lowlinks[node] = index_counter[0]
        index_counter[0] += 1
        stack.append(node)

        # Consider successors of `node`
        try:
            successors = graph[node]
        except:
            successors = []
        for successor in successors:
            if successor not in lowlinks:
                # Successor has not yet been visited; recurse on it
                strongconnect(successor)
                lowlinks[node] = min(lowlinks[node],lowlinks[successor])
            elif successor in stack:
                # the successor is in the stack and hence in the current strongly connected component (SCC)
                lowlinks[node] = min(lowlinks[node],index[successor])

        # If `node` is a root node, pop the stack and generate an SCC
        if lowlinks[node] == index[node]:
            connected_component = []

            while True:
                successor = stack.pop()
                connected_component.append(successor)
                if successor == node: break
            component = tuple(connected_component)
            # storing the result
            result.append(component)

    for node in graph:
        if node not in lowlinks:
            strongconnect(node)

    return result


def solution(edges, m):
    S = strongly_connected_components(graph)

    if (len(S) == 1):
        return 'valid'
    else:
        return 'crap'


def convertGraph(edges, m):
    graph = {}

    for j in range(m):
        graph[j] = []

    for edge in edges:
        v1, v2 = edge.split()
        v1 = int(v1)
        v2 = int(v2)

        graph[v1].append(v2)

    return graph

lines = [line for line in input()]

i = 0
case_count = 1
while i < len(lines):
    m, n = lines[i].split()
    m = int(m)
    n = int(n)

    E = lines[i + 1: i + n + 1]
    G = convertGraph(E, m)

    if len(strongly_connected_components(G)) == 1:
        print 'Case {}: {}'.format(case_count, 'valid')
    else:
        broke = False
        for k, e in enumerate(E):
            E1 = deepcopy(E)
            v1, v2 = e.split()

            E1[k] = '{} {}'.format(v2, v1)

            G = convertGraph(E1, m)
            if len(strongly_connected_components(G)) == 1:
                print 'Case {}: {}'.format(case_count, '{} {}'.format(v1, v2))
                broke = True
                break

        if not broke:
            print 'Case {}: {}'.format(case_count, 'invalid')


    case_count += 1
    i += n + 1
