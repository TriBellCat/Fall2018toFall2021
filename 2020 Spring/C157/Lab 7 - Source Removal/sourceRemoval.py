from collections import defaultdict

class Chart:
    #Gets the dictionary that contains the adjacency list and number of vertices
    def __init__(self, vertices):
        self.chart = defaultdict(list)
        self.V = vertices

    #Adds edge to the adjacency chart
    def addEdge(self, row, col):
        self.chart[row].append(col)
        print("Graph has a cycle!") #Message if if graph has edges then it has a cycle

    #Recursive function for sorting the order of a directed graph or chart (topological)
    def VertSortUtil(self, ver, visited, stack):
        visited[ver] = True
        for i in self.chart[ver]:
            if visited[i] == False:
                self.VertSortUtil(i, visited, stack)
        stack.insert(0, ver)

    #Function for sorting the order of a directed graph or chart (topological)
    def VertSort(self):
        visited = [False] * self.V
        stack = []
        for i in range(self.V):
            if visited[i] == False:
                self.VertSortUtil(i, visited, stack)
        print(stack)

def read_graph(filename):
    file = open(filename, "r")
    matrix = file.readlines()  # read in whole file as 1D list of strings
    for row in range(len(matrix)):
        # strip off trailing newline and break each row into a list, creating a 2D list
        matrix[row] = list(matrix[row].strip())
        for col in range(len(matrix[row])):
            # convert each '0' into 0 and '1' into 1 so have numerical matrix instead of character one
            matrix[row][col] = int(matrix[row][col])
    g = Chart(row)
    for i in range(row):
        for j in range(col):
            if row == col and row == 0:
                g.addEdge(row, col)
            if matrix[row][col] == "1":
                g.addEdge(row, col)
    g.VertSort()

def main():
    #Note: The instructions didn't specify in what order the sorted list should be or what exactly the list should look like in the end
    print("graph 1:")
    read_graph("graph1.txt")
    print("graph 2:")
    read_graph("graph2.txt")
    print("graph 3:")
    read_graph("graph3.txt")

if __name__ == "__main__":
    main()