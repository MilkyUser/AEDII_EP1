# Algoritmo de Kosaraju

Olá, este repositório é dedicado ao EP 1 (exercício de programação) da disciplina 
**ACH2024 - Algoritmos e Estruturas de Dados II** do curso de Sistemas de Informação da EACH - USP.

O programa <i>Kosaraju</i> é resultado da compilação do código-fonte contido neste repositório.
O programa <i>Kosaraju</i> recebe um grafo orientado pela entrada principal e imprime em tela o
grafo das componentes fortemente conectadas correspondentes.

Este repositório contém:

* Kosaraju: programa que encontra as componentes fortemente conectadas ou imprime grafos aleatórios em tela.
* generator.py: script Python que gera grafos a partir de nomes em português ou algarismos alfa númericos seguindo
uma distribuição normal. 

## Dependências

* **GCC**: <i>GNU Compiler Collection</i> - compilador para a linguagem com suporte para a versão C99;
* **Makefile**;
* **Sistema Unix-like**;
* **Git**;
* **Repositório**: https://github.com/rxi/map (instalado automaticamente com uso de git e makefile);
* **Hardware de 64bits** (o funcionamento em outras arquiteturas não é garantido);
* Python 3.8 (opcional)

## Instalação

Para instalar programa execute em <i>shell</i> o comando ``make`` na pasta raiz do repositório (EP1).
O script makefile se encarrega de clonar os repositórios com as dependências e de criar um ambiente
virtual para a execução do gerador Python.

Caso deseje instalar o programa sem o gerador de grafos em Python, substitua o conteudo do arquivo ``EP1/makefile`` por:

```
all:
	+$(MAKE) -C src
```

## Gerador em Python

A execução do script ``generator.py`` é realizada em <i>shell</i> da seguinte forma:

```
python3 generator.py <v> <e> <a>
```

Onde:

* v é a quantidade de vértices do grafo.
* e é a quantidade de arestas do grafo.
* a é uma entrada opcional que representa o alfabeto a ser usado para a geração do grafo, são valores aceitos:
    * ``nomes``: para uso do dicionário de nomes em https://github.com/mauricioomateus/Wordlists-PT-BR
    * ``abc``: para uso de dígitos de a-z, A-Z, 0-9 (nesta ordem. Esta opção é escolhida por padrão caso a opção ``<a>``
    seja omitida.

## Executável Kosaraju

A execução do executável Kosaraju é realizada em <i>shell</i> da seguinte forma:

#### Modo Gerador de Grafos:

```
./kosaraju <v> <a>
```

Onde:

* v é a quantidade de vértices do grafo.
* e é a quantidade de arestas do grafo.

O programa em seguida imprime em tela um grafo com a quantidade (aproximada) de vértices e arestas informados.

#### Modo Processador de Grafos:

```
./kosaraju <sep>
```
Onde:

* sep é uma cadeia de caracteres arbitrária que será concatenada na representação dos vértices do grafo das componentes
fortemente conectadas entre cada vértice original (funcionando como um separador). Se omitida o programa não incluirá
nenhum separador na representação das vértices do grafo de componentes fortemente conectadas.

Após a execução do comando acima o o programa espera uma entrada seguindo o padrão definido pela especificação do EP.

A saída é dada da seguinte forma:

```
<scc>
<no_sccs>
<sccs_graph>
```

Onde:

* scc é a cadeia "Sim" se o grafo for fortemente conectado ou "Não" se o grafo não for fortemente conectado.
* no_sccs é a quantidade de componentes fortemente conectadas
* sccs_graph é o grafo das componentes fortemente conectadas seguindo o padrão definido na especificação do EP, incluindo
também o separadores defindos na chamada do executável.

