from linecache import getline
from numpy.random import dirichlet, normal
from sys import argv
import random


def generate_graph(v: int, a: int, alphabet: str = 'abc')->dict: # returns a dict with the structure <<str>: [<str>, ...], ...>
	
	graph = dict()
	
	if v < 1:
		raise ValueError(f'número mínimo de vértices \'v\' = 1')
	
	if alphabet.upper() == 'NOMES':
		with open('./Wordlists-PT-BR/nomes.txt', 'r') as names_file:
			no_lines = sum(1 for line in names_file)		
			for _ in range(v):
				graph[getline(names_file.name, random.randrange(no_lines)).replace('\n', '')] = []
	
	if alphabet.upper() == 'AIRLINES':
		with open('./airlines-dict.txt', 'r') as IATA_file:
			no_lines = sum(1 for line in IATA_file)		
			for _ in range(v):
				graph[getline(IATA_file.name, random.randrange(no_lines)).replace('\n', '')] = []

	elif alphabet.upper() == 'ABC':
		if v > 26*2:
			raise ValueError(f'número máximo de vértices para modo "abc" = {26*2}')
		if v > 26:
			char_range = list(range(97, 123)) + list(range(65, 65+v-26))
		if v <= 26:
			char_range = list(range(97, 97+v))
		for val in char_range:
				graph[chr(val)] = []
	
	dist = lambda size, count: [(elem*size)//1 for elem in dirichlet(
		[elem if elem > 0 else 0.01 for elem in normal(size=count, loc=1, scale=25/count)]
	)]
	
	dist_a = [v-1 if elem >= v else elem for elem in dist(a, v)]

	if (a - sum(dist_a)) < v:
		remainder_sample = random.sample(list(filter(lambda elem: dist_a[elem] <= v, range(v))), k=int(a-sum(dist_a)))
		for i in remainder_sample:
			dist_a[i]+=1			
	
	for key in graph.keys():
		graph[key] = random.sample(graph.keys(), int(dist_a.pop()))
		
	if alphabet.upper() == 'AIRLINES':
		print(graph)
		graph = {key: ([random.choice(list(graph.keys()))] if len(value) == 0 else value) for key, value in graph.items()}
		print(graph)
		
	return graph


if __name__ == '__main__':
	if len(argv) >= 4:
		alphabet = argv[3]
	else:
		alphabet = 'abc' 
	graph = generate_graph(int(argv[1]), int(argv[2]), alphabet)
	print(len(graph))
	for key, value in graph.items():
		print(key + ": " + "; ".join(value), end='')
		if len(value) == 0:
			print()
		else:
			print(';')


