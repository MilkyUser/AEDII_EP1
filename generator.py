from linecache import getline
from numpy.random import dirichlet, normal
from sys import argv
import random


def generate_graph(v: int, a: int)->dict: # returns a dict with the structure <<str>: [<str>, ...], ...>
	graph = dict()
	
	with open('./Wordlists-PT-BR/nomes.txt', 'r') as names_file:
		no_lines = sum(1 for line in names_file)		
		for _ in range(v):
			graph[getline(names_file.name, random.randrange(no_lines)).replace('\n', '')] = []
	
	dist = lambda size, count: [(elem*size)//1 for elem in dirichlet(
		[elem if elem > 0 else 0.01 for elem in normal(size=count, loc=1, scale=1/3)]
	)]
	dist_a = dist(a, v)
	while sum(dist_a) < a:
		if (a - sum(dist_a)) < v:
			remainder_sample = random.sample(range(v), k=int(a-sum(dist_a)))
			for i in remainder_sample:
				dist_a[i]+=1		
		else:
			remainder = dist(a - sum(dist_a), v)
			dist_a = [dist_a[i] + remainder[i] for i in range(v)]	
	
	for key in graph.keys():
		graph[key] = random.sample(graph.keys(), int(dist_a.pop()))
	
	return graph


if __name__ == '__main__':
	graph = generate_graph(int(argv[1]), int(argv[2]))
	print(len(graph))
	for key, value in graph.items():
		print(key + ": " + "; ".join(value), end='')
		if len(value) == 0:
			print()
		else:
			print(';')

