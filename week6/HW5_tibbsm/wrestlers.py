# Author: Marc Tibbs (tibbsm@oregonstate.edu)
# Date: Feb. 18, 2018
# Description: This program takes a text file name from the command line and reads wrestler names and
#  rivalries and outputs if a matchup is possible and then the wrestler types to the console. If not 
#  possible it outputs that the matchup is not possible to the console.
import sys

class Wrestler:
	"""A class to create and manage wrestlers."""

	def __init__(self, name):
		"""Create a wrestler object with passed in name."""
		self.name = name
		self.type = None
		self.rivals = list() 
		self.d = sys.maxsize
		self.color = 'WHITE'

	def addRival(self, rival):
		"""Adds a rival to Wrestler"""
		if rival not in self.rivals:
			self.rivals.append(rival)

class Graph:
	"""A class to keep track of all the wrestlers."""
	wrestlers = {}
	flag = True

	def addV(self, vertex):
		"""Adds a vertex(wrestler) to the Graph."""
		if vertex.name not in self.wrestlers:
			self.wrestlers[vertex.name] = vertex

	def addE(self, v1, v2):
		"""Adds an edge(rivalry) between verices on Graph."""
		for key, value in self.wrestlers.items():
			if key == v1:
				value.addRival(v2)
			if key == v2:
				value.addRival(v1)

	def BFS(self, wrestler):
		"""Performs BFS of Graph from passed in vertex."""
		Q = list()
		wrestler.d = 0

		for i in wrestler.rivals:
			self.wrestlers[i].d = wrestler.d + 1
			self.wrestlers[i].type = 'Heel'
			Q.append(i)

		while Q:
			u = self.wrestlers[Q.pop(0)]
			for v in u.rivals:
				if self.wrestlers[v].color == 'WHITE':
					if self.wrestlers[v].d > u.d + 1:
						self.wrestlers[v].d = u.d + 1
					if (self.wrestlers[v].d & 1) == 0:
						self.wrestlers[v].type = 'Babyface'
					else:
						self.wrestlers[v].type = 'Heel'
					if self.wrestlers[v].type == u.type:
						self.flag = False
			u.color = 'BLACK'

# inFile = open("wrestler.txt")
inFile = open(sys.argv[1])
data = inFile.read().splitlines()

names = int(data[0])
rivals = int(data[names+1])

matchUp = Graph()

# Add wrestlers/vertices
for i in range(1, names+1):
	wrestler = Wrestler(data[i])
	matchUp.addV(wrestler)

# Add rivals/edges
for i in range(names+2, names+rivals+2):
	rival = data[i]
	matchUp.addE(rival.split()[0],rival.split()[1])

for value in matchUp.wrestlers:
	if matchUp.wrestlers[value].color == 'WHITE':
		matchUp.BFS(matchUp.wrestlers[value])

if matchUp.flag:
	babies = "Babyfaces: "
	heels = "Heels: "
	for i in matchUp.wrestlers:
		if matchUp.wrestlers[i].type == "Babyface":
			babies = babies + matchUp.wrestlers[i].name + ' '
		else:
			heels = heels + matchUp.wrestlers[i].name + ' '
	print("Yes")
	print(babies)
	print(heels)
else:
	print("No. Impossible.")

inFile.close()